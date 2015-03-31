//=============================================================================
//                          SkeletonClass.cpp
//
// Adopted from CubeDemo.cpp by Frank Luna (C) 2005 All Rights Reserved.
//
// Edited and changed by Adi Bar-Lev, 2013
// EGP-300-101 - Computer Graphics II, Spring 2013.
//
// This project creates a skeleton workspace and base classes for the student to be 
// able to start working with sample classes and develop evolve it according to the 
// given exercises
//
// Controls: Use mouse to orbit and zoom; use the 'W' and 'S' keys to 
//           alter the height of the camera.
//=============================================================================
#include "DirectInput.h"
#include <crtdbg.h>
#include "GfxStats.h"
#include <list>

#include "SkeletonClass.h"
#include "3DClasses\BaseObject3D.h"
#include "3DClasses\Vertex.h"
#include "Cone.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Teapot.h"
#include "Torus.h"
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	SkeletonClass app(hInstance, "Exercise Skeleton Project", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	gd3dApp = &app;

	DirectInput di(DISCL_NONEXCLUSIVE|DISCL_FOREGROUND, DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
	gDInput = &di;

	return gd3dApp->run();
}

SkeletonClass::SkeletonClass(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP)
: D3DApp(hInstance, winCaption, devType, requestedVP)
{
	if(!checkDeviceCaps())
	{
		MessageBox(0, "checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}

	InitAllVertexDeclarations();
	//	Load Texture

	HR(D3DXCreateTextureFromFile(gd3dDevice, "texture.jpg", &mp_texture));

	//	Initialize camera
	mCameraRadius    = 10.0f;
	mCameraRotationY = 0;//1.2 * D3DX_PI;
	mCameraRotationX = 0;// 1.2 * D3DX_PI;
	mCameraHeight    = 5.0f;

	m_Light_vector_W = D3DXVECTOR3(1.0, 1.0f, 1.0f);
		//	Red
	m_Light_diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_Light_Diffuse_A);
	m_Light_ambient = RED * 0.4f;
		//	White
	m_Light_specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Light_Specular_A);

	//	set original Specular & Diffuse
	m_Light_OriginalSpec = m_Light_specular;
	m_Light_OriginalDiff = m_Light_diffuse;

	m_spot_power = 16.0f;

	buildSpotFX();
	buildPhongFX();

	mConeMaterial = new BaseMaterial();

	mConeMaterial->ConnectToEffect(m_spot_FX);
	mConeMaterial->AddTexture(mp_texture);
	mConeMaterial->setMat(WHITE, WHITE, WHITE, 8.0f);

    // repleace or add to the following object creation
    //m_Objects.push_back( new BaseObject3D );
	BaseObject3D* temp;

	temp = new Cylinder();
	temp->Create(gd3dDevice);
	temp->setMaterial(mConeMaterial);
	m_Objects.push_back(temp);

	temp = new Sphere();
	temp->Create(gd3dDevice);
	temp->setMaterial(mConeMaterial);
	m_Objects.push_back(temp);

	temp = new Cone();
	temp->Create(gd3dDevice);
	temp->setMaterial(mConeMaterial);
	m_Objects.push_back(temp);

	temp = new Torus();
	temp->Create(gd3dDevice);
	temp->setMaterial(mConeMaterial);
	m_Objects.push_back(temp);

	temp = new Teapot();
	temp->Create(gd3dDevice);
	temp->setMaterial(mConeMaterial);
	m_Objects.push_back(temp);


	//	Initialize the World Matrix (centered in origin, ie identity matrix)
	D3DXMatrixIdentity(&mWorld);


	//	initialize object index & key down
	m_currentobject_index = 0;
	m_key_O_down = false;
	m_key_W_down = false;
	m_key_T_down = false;
	m_key_R_down = false;
	m_key_N_down = false;
	m_key_min_down = false;
	m_key_pls_down = false;
	m_key_A_down = false;
	m_key_S_down = false;
	m_key_1_down = false;
	m_key_2_down = false;
	m_key_3_down = false;
	m_key_4_down = false;
	m_key_5_down = false;
	m_key_6_down = false;
	m_key_7_down = false;
	m_current_effect = nullptr;


	onResetDevice();

}

SkeletonClass::~SkeletonClass()
{
	delete mConeMaterial;
    GfxStats::DeleteInstance();

	//	Delete objects
    for ( unsigned int obj=0 ; obj<m_Objects.size() ; obj++ )
        delete m_Objects[obj];
    m_Objects.clear();

	//	Destroy effects
	ReleaseCOM(m_phong_FX);
	ReleaseCOM(m_spot_FX);
	ReleaseCOM(mp_texture);

	DestroyAllVertexDeclarations();
}

bool SkeletonClass::checkDeviceCaps()
{
	//return true;

	//	**Referenced from AmbientDiffuseSpecularDemo**
	D3DCAPS9 caps;
	HR(gd3dDevice->GetDeviceCaps(&caps));

	// Check for vertex shader version 2.0 support.
	if (caps.VertexShaderVersion < D3DVS_VERSION(2, 0))
		return false;

	// Check for pixel shader version 2.0 support.
	if (caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
		return false;

	return true;
}

void SkeletonClass::onLostDevice()
{
	GfxStats::GetInstance()->onLostDevice();
	
	//	Effects
	HR(m_phong_FX->OnLostDevice());
	HR(m_spot_FX->OnLostDevice());
}

void SkeletonClass::onResetDevice()
{
	GfxStats::GetInstance()->onResetDevice();

	//	Effects
	HR(m_phong_FX->OnResetDevice());
	HR(m_spot_FX->OnResetDevice());

	// The aspect ratio depends on the backbuffer dimensions, which can 
	// possibly change after a reset.  So rebuild the projection matrix.
	buildProjMtx();
}

void SkeletonClass::updateScene(float dt)
{
	// Reset the statistics for the scene - each object will add to it.
	GfxStats::GetInstance()->setVertexCount(0);
	GfxStats::GetInstance()->setTriCount(0);
	GfxStats::GetInstance()->update(dt);

	// Get snapshot of input devices.
	gDInput->poll();

	// Check input.
	if (gDInput->keyDown(DIK_W) && !m_key_W_down)
	{
		i_Solid_frame = !i_Solid_frame;
		m_key_W_down = true;
	}
	else if (!gDInput->keyDown(DIK_W))
		m_key_W_down = false;

	if (gDInput->keyDown(DIK_T) && !m_key_T_down)
	{
		i_texture_on = !i_texture_on;
		m_key_T_down = true;
	}
	else if (!gDInput->keyDown(DIK_T))
		m_key_T_down = false;

	//	Check for "O" input for changing currentobject_index
	if (gDInput->keyDown(DIK_O) && !m_key_O_down)
		ChangeObject();
	else if (!gDInput->keyDown(DIK_O))
		m_key_O_down = false;


	if (gDInput->keyDown(DIK_R) && !m_key_R_down)
	{
		i_evir_reflect_on = !i_evir_reflect_on;
		m_key_R_down = true;
	}
	else if (!gDInput->keyDown(DIK_R))
		m_key_R_down = false;

	if (gDInput->keyDown(DIK_N) && !m_key_N_down)
	{
		i_norm_mapping_on = !i_norm_mapping_on;
		m_key_N_down = true;
	}
	else if (!gDInput->keyDown(DIK_N))
		m_key_N_down = false;

	if (gDInput->keyDown(DIK_NUMPADPLUS) && !m_key_pls_down)
	{
		i_blend += 0.1f;
		if (i_blend > 1)
		{
			i_blend = 1;
		}
		m_key_pls_down = true;
	}
	else if (!gDInput->keyDown(DIK_NUMPADPLUS))
		m_key_pls_down = false;
	if (gDInput->keyDown(DIK_NUMPADMINUS) && !m_key_min_down)
	{
		i_blend -= 0.1f;
		if (i_blend < 0)
		{
			i_blend = 0;
		}
		m_key_min_down = true;
	}
	else if (!gDInput->keyDown(DIK_NUMPADMINUS))
		m_key_min_down = false;

	if (gDInput->keyDown(DIK_A) && !m_key_A_down)
	{
		i_norm_strength += 0.1f;
		if (i_norm_strength > 1)
		{
			i_norm_strength = 1;
		}
		m_key_A_down = true;
	}
	else if (!gDInput->keyDown(DIK_A))
		m_key_A_down = false;
	if (gDInput->keyDown(DIK_S) && !m_key_S_down)
	{
		i_norm_strength -= 0.1f;
		if (i_norm_strength < 0)
		{
			i_norm_strength = 0;
		}
		m_key_S_down = true;
	}
	else if (!gDInput->keyDown(DIK_S))
		m_key_S_down = false;

	if (gDInput->keyDown(DIK_1) && !m_key_1_down)
	{
		i_spec_coefficient = 2;
		m_key_1_down = true;
	}
	else if (!gDInput->keyDown(DIK_1))
		m_key_1_down = false;
	if (gDInput->keyDown(DIK_2) && !m_key_2_down)
	{
		i_spec_coefficient = 4;
			m_key_2_down = true;
	}
	else if (!gDInput->keyDown(DIK_2))
		m_key_1_down = false;
	if (gDInput->keyDown(DIK_3) && !m_key_3_down)
	{
		i_spec_coefficient = 8;
			m_key_1_down = true;
	}
	else if (!gDInput->keyDown(DIK_3))
		m_key_3_down = false;
	if (gDInput->keyDown(DIK_4) && !m_key_4_down)
	{
		i_spec_coefficient = 16;
			m_key_4_down = true;
	}
	else if (!gDInput->keyDown(DIK_4))
		m_key_4_down = false;
	if (gDInput->keyDown(DIK_5) && !m_key_5_down)
	{
		i_spec_coefficient = 32;
		m_key_5_down = true;
	}
	else if (!gDInput->keyDown(DIK_5))
		m_key_5_down = false;
	if (gDInput->keyDown(DIK_6) && !m_key_6_down)
	{
		i_spec_coefficient = 64;
		m_key_6_down = true;
	}
	else if (!gDInput->keyDown(DIK_6))
		m_key_6_down = false;
	if (gDInput->keyDown(DIK_7) && !m_key_7_down)
	{
		i_spec_coefficient = 16;
		m_key_7_down = true;
	}
	else if (!gDInput->keyDown(DIK_7))
		m_key_7_down = false;


	// Divide by 50 to make mouse less sensitive. 
	mCameraRotationY += gDInput->mouseDY() / 100.0f;
	mCameraRotationX += gDInput->mouseDX() / 100.0f;
	mCameraRadius += gDInput->mouseDZ() / 100.0f;

	// If we rotate over 360 degrees, just roll back to 0
	if( fabsf(mCameraRotationY) >= 2.0f * D3DX_PI ) 
		mCameraRotationY = 0.0f;

	// Don't let radius get too small.
	if (fabsf(mCameraRotationX) >= 2.0f * D3DX_PI)
		mCameraRotationX = 0.0f;

	if (fabsf(mCameraRotationX) < 0.0f)
		mCameraRotationX = 2.0f * D3DX_PI;





	// The camera position/orientation relative to world space can 
	// change every frame based on input, so we need to rebuild the
	// view matrix every frame with the latest changes.
	buildViewMtx();
}


void SkeletonClass::drawScene()
{
	// Clear the backbuffer and depth buffer.
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));

	HR(gd3dDevice->BeginScene());

    // Set render statws for the entire scene here:

	//	Check if we're SOLID or WIRE frame
	if (i_Solid_frame)
	{
		HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	}
	else
	{
		HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	}

	ID3DXEffect* current;
	//	Setup the rendering EFFECT
		//	iterate between various shaders
	m_Objects[m_currentobject_index]->setEffect(m_current_effect);
	if (m_current_effect != nullptr)
	{
		HR(m_current_effect->SetBool(mh_textureOn, i_texture_on));
		//	set technique
		HR(m_current_effect->SetTechnique(mh_Technique));
		//	set world view proj matrix
		HR(m_current_effect->SetMatrix(mh_WVP, &(mWorld*mView*mProj)));

		//	Set world inverse transpose matrix
		D3DXMATRIX worldInverseTranspose;
		D3DXMatrixInverse(&worldInverseTranspose, 0, &mWorld);
		D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);
		HR(m_current_effect->SetMatrix(mh_WorldInverseTranspose, &worldInverseTranspose));

		//	Set values of World Light
		HR(m_current_effect->SetValue(mh_ambientLight, &m_Light_ambient, sizeof(D3DXCOLOR)));
		HR(m_current_effect->SetValue(mh_diffuseLight, &m_Light_diffuse, sizeof(D3DXCOLOR)));
		HR(m_current_effect->SetValue(mh_specularLight, &m_Light_specular, sizeof(D3DXCOLOR)));
		HR(m_current_effect->SetFloat(mh_spotPower, m_spot_power));


		UINT numPasses = 0;
		HR(m_current_effect->Begin(&numPasses, 0));
		for (UINT i = 0; i < numPasses; ++i)
		{
			HR(m_current_effect->BeginPass(i));
			m_Objects[m_currentobject_index]->Render(gd3dDevice, mView, mProj);

			HR(m_current_effect->EndPass());
		}
		HR(m_current_effect->End());
		//	Set values of OBJECT MATERIAL
		/* current object variable */
		//HR(m_current_effect->SetValue(object_handler_diffuse, actual_value, sizeof(D3DXCOLOR)));
		//HR(m_current_effect->SetValue(object_handler_ambient, actual_value, sizeof(D3DXCOLOR)));
		//HR(m_current_effect->SetValue(object_handler_specular, actual_value, sizeof(D3DXCOLOR)));
		//HR(m_current_effect->SetValue(object_handler_spec_power, actual_value, sizeof(D3DXCOLOR)));


		//	Set world Matrix
	}
	else
	{
		m_Objects[m_currentobject_index]->Render(gd3dDevice, mView, mProj);
	}



	/*
    //// Render all the objects
    //for ( unsigned int obj=0 ; obj<m_Objects.size() ; obj++ )
    //{
    //    m_Objects[obj]->Render( gd3dDevice, mView, mProj );
    //}

	//	Render the currentobject_index
	m_Objects[m_currentobject_index]->Render(gd3dDevice, mView, mProj);
	*/

    // display the render statistics
    GfxStats::GetInstance()->display();

	HR(gd3dDevice->EndScene());

	// Present the backbuffer.
	HR(gd3dDevice->Present(0, 0, 0, 0));
}

void SkeletonClass::buildViewMtx()
{
	float z = mCameraRadius *sinf(mCameraRotationX);
	float xyRadius = mCameraRadius* cosf(mCameraRotationX);
	float x = xyRadius *cosf(mCameraRotationY);
	float y = xyRadius *sinf(mCameraRotationY);

	if (mCameraRotationX >= D3DX_PI/* && mCameraRotationX < 3 * D3DX_PI/4*/)
	{
		y = -y;
		//xyRadius = -xyRadius;
		//mCameraRotationX = 2;
	}
	D3DXVECTOR3 pos(x, y, z);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &pos, &target, &up);

	if (m_current_effect != nullptr)
	{
		HR(m_current_effect->SetValue(mh_eyePos, &pos, sizeof(D3DXVECTOR3)));

		// Spotlight position is the same as the camera position.
		HR(m_current_effect->SetValue(mh_LightPosW, &pos, sizeof(D3DXVECTOR3)));
		D3DXVECTOR3 lightDir = target - pos;
		D3DXVec3Normalize(&lightDir, &lightDir);
		HR(m_current_effect->SetValue(mh_LightDirectW, &lightDir, sizeof(D3DXVECTOR3)));
	}
}

void SkeletonClass::buildProjMtx()
{
	float w = (float)md3dPP.BackBufferWidth;
	float h = (float)md3dPP.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);
}



void SkeletonClass::ChangeObject(void)
{
	//	increment the m_currentobject_index
	m_currentobject_index++;

	//	Check if index is over current amount (3)
	if (m_currentobject_index >= 5)
		m_currentobject_index = 0;

	//	Set m_mousedown to true so that we only iterate once per mouse click
	m_key_O_down = true;
}


void SkeletonClass::buildPhongFX()
{
	//	Buffer for any errors
	ID3DXBuffer* errors = 0;

	//	Create FX from .fx file
	HR(D3DXCreateEffectFromFile(gd3dDevice, "phong.fx", 0, 0, D3DXSHADER_DEBUG, 0, &m_phong_FX, &errors));

	//	Check for & display any errors
	if (errors)
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);



	//	Obtain the handles
	obtainPhongHandles();

	HR(m_phong_FX->SetValue(mh_ambientLight, &m_Light_ambient, sizeof(D3DXCOLOR)));
	HR(m_phong_FX->SetValue(mh_diffuseLight, &m_Light_diffuse, sizeof(D3DXCOLOR)));
	HR(m_phong_FX->SetValue(mh_specularLight, &m_Light_specular, sizeof(D3DXCOLOR)));
	HR(m_phong_FX->SetValue(mh_LightVecW, &m_Light_vector_W, sizeof(D3DXVECTOR3)));

}

void SkeletonClass::obtainPhongHandles()
{
	//	set technique
	mh_Technique = m_phong_FX->GetTechniqueByName("PhongTech");

		//	set world view proj matrix
	mh_WVP						= m_phong_FX->GetParameterByName(0, "gWVP");
		//	set world inverse transpose
	mh_WorldInverseTranspose	= m_phong_FX->GetParameterByName(0, "gWorldInverseTranspose");
		//	eye/camera position
	mh_eyePos					= m_phong_FX->GetParameterByName(0, "gEyePosW");
		//	world matrix
	mh_World					= m_phong_FX->GetParameterByName(0, "gWorld");
		//	Light components
	mh_ambientLight				= m_phong_FX->GetParameterByName(0, "gAmbientLight");
	mh_diffuseLight				= m_phong_FX->GetParameterByName(0, "gDiffuseLight");
	mh_specularLight			= m_phong_FX->GetParameterByName(0, "gSpecLight");

	mh_spotPower				= m_phong_FX->GetParameterByName(0, "gSpotPower");

		//	Light as a Vector
	mh_LightVecW				= m_phong_FX->GetParameterByName(0, "gLightVecW");

		//	Light as a position & direction
	mh_LightPosW				= m_phong_FX->GetParameterByName(0, "gLightPosW");
	mh_LightDirectW				= m_phong_FX->GetParameterByName(0, "gLightDirW");

		//	attuenuation of light
	mh_attenuation				= m_phong_FX->GetParameterByName(0, "gAttenuation012");

	mh_textureOn = m_phong_FX->GetParameterByName(0, "gTextureOn");

}



void SkeletonClass::buildSpotFX()
{
	//	Buffer for any errors
	ID3DXBuffer* errors = 0;

	//	Create FX from .fx file
	HR(D3DXCreateEffectFromFile(gd3dDevice, "spotlight.fx", 0, 0, D3DXSHADER_DEBUG, 0, &m_spot_FX, &errors));

	//	Check for & display any errors
	if (errors)
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	//	Obtain the handles
	obtainSpotHandles();

	D3DXVECTOR3 attenuation012 = D3DXVECTOR3(1.0f,0.0f,0.0f);
	HR(m_spot_FX->SetValue(mh_ambientLight, &m_Light_ambient, sizeof(D3DXCOLOR)));
	HR(m_spot_FX->SetValue(mh_diffuseLight, &m_Light_diffuse, sizeof(D3DXCOLOR)));
	HR(m_spot_FX->SetValue(mh_specularLight, &m_Light_specular, sizeof(D3DXCOLOR)));
	HR(m_spot_FX->SetValue(mh_attenuation, &attenuation012, sizeof(D3DXVECTOR3)));
}
void SkeletonClass::obtainSpotHandles()
{
	//	set technique
	mh_Technique = m_spot_FX->GetTechniqueByName("SpotlightTech");

	//	set world view proj matrix
	mh_WVP = m_spot_FX->GetParameterByName(0, "gWVP");
	//	set world inverse transpose
	mh_WorldInverseTranspose = m_spot_FX->GetParameterByName(0, "gWorldInvTrans");
	//	eye/camera position
	mh_eyePos = m_spot_FX->GetParameterByName(0, "gEyePosW");
	//	world matrix
	mh_World = m_spot_FX->GetParameterByName(0, "gWorld");
	//	Light components
	mh_ambientLight = m_spot_FX->GetParameterByName(0, "gAmbientLight");
	mh_diffuseLight = m_spot_FX->GetParameterByName(0, "gDiffuseLight");
	mh_specularLight = m_spot_FX->GetParameterByName(0, "gSpecLight");

	//	Light as a Vector
	//mh_LightVecW = m_spot_FX->GetParameterByName(0, "gLightVecW");

	//	Light as a position & direction
	mh_LightPosW = m_spot_FX->GetParameterByName(0, "gLightPosW");
	mh_LightDirectW = m_spot_FX->GetParameterByName(0, "gLightDirW");

	//	attuenuation of light
	mh_attenuation = m_spot_FX->GetParameterByName(0, "gAttenuation012");

	//	power of the spotlight
	mh_spotPower = m_spot_FX->GetParameterByName(0, "gSpotPower");

	mh_textureOn = m_spot_FX->GetParameterByName(0, "gTextureOn");
}