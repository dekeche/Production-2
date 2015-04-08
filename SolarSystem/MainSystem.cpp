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

	// Effects
}
void MainSystem::updateScene(float dt)
{
}
void MainSystem::drawScene()
{
}


void MainSystem::buildViewMtx()
{
}
void MainSystem::buildProjMtx()
{
}