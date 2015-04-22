#include "MainSystem.h"
#include "DirectInput.h"
#include <crtdbg.h>
#include "GfxStats.h"
#include <list>
#include "Vertex.h"

//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MainSystem app(hInstance, "Exercise Skeleton Project", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	gd3dApp = &app;

	DirectInput di(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDInput = &di;

	return gd3dApp->run();
}

MainSystem::MainSystem(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP)
: D3DApp(hInstance, winCaption, devType, requestedVP)
{

	if (!checkDeviceCaps())
	{
		MessageBox(0, "checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}

	InitAllVertexDeclarations();

	//	Initialize camera
	mCameraRadius = 10.0f;
	mCameraRotationY = 0;//1.2 * D3DX_PI;
	mCameraRotationX = 0;// 1.2 * D3DX_PI;
	i_Solid_frame = false;

	mpSolarSystem = new SolarSystem();
	mpSolarSystem->create();
	//	Initialize the World Matrix (centered in origin, ie identity matrix)
	D3DXMatrixIdentity(&mWorld);

	onResetDevice();
}
MainSystem::~MainSystem()
{
	GfxStats::DeleteInstance();
	DestroyAllVertexDeclarations();
}

bool MainSystem::checkDeviceCaps()
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
void MainSystem::onLostDevice()
{
	GfxStats::GetInstance()->onLostDevice();

	//	Effects
}
void MainSystem::onResetDevice()
{
	GfxStats::GetInstance()->onResetDevice();
	buildProjMtx();

	// Effects
}
void MainSystem::updateScene(float dt)
{
	GfxStats::GetInstance()->setVertexCount(0);
	GfxStats::GetInstance()->setTriCount(0);
	GfxStats::GetInstance()->update(dt);

	// Get snapshot of input devices.
	gDInput->poll();

	// Divide by 50 to make mouse less sensitive. 
	mCameraRotationY += gDInput->mouseDY() / 100.0f;
	mCameraRotationX += gDInput->mouseDX() / 100.0f;
	mCameraRadius -= gDInput->mouseDZ() / 100.0f;

	// If we rotate over 360 degrees, just roll back to 0
	if (mCameraRotationY > 2.0f * D3DX_PI)
		mCameraRotationY = gDInput->mouseDY() / 100.0f;

	if (mCameraRotationY < 0.0f)
		mCameraRotationY = 2.0f * D3DX_PI;

	// Don't let radius get too small.
	if (mCameraRotationX > 2.0f * D3DX_PI)
		mCameraRotationX = 0.0f;

	if (mCameraRotationX < 0.0f)
		mCameraRotationX = 2.0f * D3DX_PI;

	mpSolarSystem->update(dt);
	buildViewMtx();
}
void MainSystem::drawScene()
{
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));
	HR(gd3dDevice->BeginScene());
	if (i_Solid_frame)
	{
		HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	}
	else
	{
		HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	}
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &mWorld));
	HR(gd3dDevice->SetTransform(D3DTS_VIEW, &mView));
	HR(gd3dDevice->SetTransform(D3DTS_PROJECTION, &mProj));
	mpSolarSystem->render();


	// display the render statistics
	GfxStats::GetInstance()->display();

	//	display UI help
	//GfxStats::GetInstance()->displayAssignment4(i_blend, i_norm_strength, i_spec_coefficient, i_texture_on, i_Solid_frame, i_evir_reflect_on, i_norm_mapping_on, i_reflect_diffuse_on);

	HR(gd3dDevice->EndScene());

	// Present the backbuffer.
	HR(gd3dDevice->Present(0, 0, 0, 0));
}


void MainSystem::buildViewMtx()
{
	float y = mCameraRadius *cosf(mCameraRotationY);
	float x = mCameraRadius *sinf(mCameraRotationY)*sinf(mCameraRotationX);
	float z = mCameraRadius *sinf(mCameraRotationY)*cosf(mCameraRotationX);

	float upVec = 1.0f;
	float rightVec = 0.0f;
	if (mCameraRotationY > D3DX_PI && mCameraRotationY < 2.0f * D3DX_PI/* && mCameraRotationX < 3 * D3DX_PI/4*/)
	{
		upVec = -upVec;
		//y = -y;
		//xyRadius = -xyRadius;
		//mCameraRotationX = 2;
	}
	else if (mCameraRotationY == 0)
	{
		upVec = 0;
		rightVec = -1.0f;
	}

	D3DXVECTOR3 pos(x, y, z);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, upVec, rightVec);
	D3DXMatrixLookAtLH(&mView, &pos, &target, &up);
}
void MainSystem::buildProjMtx()
{
	float w = (float)md3dPP.BackBufferWidth;
	float h = (float)md3dPP.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, w / h, 1.0f, 5000.0f);
}