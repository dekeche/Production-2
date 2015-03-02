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



	//	Initialize camera
	mCameraRadius    = 10.0f;
	mCameraRotationY = 0;//1.2 * D3DX_PI;
	mCameraRotationX = 0;// 1.2 * D3DX_PI;
	mCameraHeight    = 5.0f;


	buildPhongFX();
	buildSpotFX();

	BaseMaterial basic;

	basic.ConnectToEffect(m_spot_FX);
	basic.setMat(RED, RED, WHITE, 8.0f);

    // repleace or add to the following object creation
    //m_Objects.push_back( new BaseObject3D );
	BaseObject3D* temp;

	temp = new Cylinder();
	temp->setMaterial(&basic);
	m_Objects.push_back(temp);

	temp = new Sphere();
	temp->setMaterial(&basic);
	m_Objects.push_back(temp);

	temp = new Cone();
	temp->setMaterial(&basic);
	m_Objects.push_back(temp);

	//	Initialize World components
		//	Light
	m_Light_vector_W = D3DXVECTOR3(0.0, 0.0f, -1.0f);	//	shine towards negative Z direction
	m_Light_diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light_ambient = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	m_Light_specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//	Initialize the World Matrix (centered in origin, ie identity matrix)
	D3DXMatrixIdentity(&mWorld);


	//	initialize object index & key down
	m_currentobject_index = 0;
	m_key_O_down = false;


	onResetDevice();

	InitAllVertexDeclarations();
}

SkeletonClass::~SkeletonClass()
{
    GfxStats::DeleteInstance();

	//	Delete objects
    for ( unsigned int obj=0 ; obj<m_Objects.size() ; obj++ )
        delete m_Objects[obj];
    m_Objects.clear();

	//	Destroy effects
	ReleaseCOM(m_phong_FX);
	ReleaseCOM(m_spot_FX);

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
	if( gDInput->keyDown(DIK_W) )	 
		mCameraHeight   += 25.0f * dt;
	if( gDInput->keyDown(DIK_S) )	 
		mCameraHeight   -= 25.0f * dt;

	//	Check for "O" input for changing currentobject_index
	if (gDInput->keyDown(DIK_O) && !m_key_O_down)
		ChangeObject();
	else if (!gDInput->keyDown(DIK_O))
		m_key_O_down = false;


	// Divide by 50 to make mouse less sensitive. 
	mCameraRotationY += gDInput->mouseDY() / 100.0f;
	mCameraRotationX += gDInput->mouseDX() / 100.0f;

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
//	HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));

	ID3DXEffect* current;
	//	Setup the rendering EFFECT
	switch (m_current_shader_index)
	{
		case 0:	//	NONE
			break;
		case 1:	//	PHONG
			current = m_phong_FX;
			break;
		case 2: // Gouraud
			current = m_spot_FX;
			break;
	}
	m_Objects[m_currentobject_index]->setEffect(current);
	UINT numPasses = 0;
	HR(current->Begin(&numPasses, 0));
	for (UINT i = 0; i < numPasses; ++i)
	{
		HR(current->BeginPass(i));
		m_Objects[m_currentobject_index]->Render(gd3dDevice, mView, mProj);

		HR(current->EndPass());
	}
	HR(current->End());


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
	if (m_currentobject_index >= 3)
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

}