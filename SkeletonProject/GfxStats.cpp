//=============================================================================
// GfxStats.cpp by Frank Luna (C) 2005 All Rights Reserved.
// Edited by Adi Bar-Lev, 2013
//=============================================================================

#include "d3dUtil.h"
#include "d3dApp.h"
#include "GfxStats.h"
#include <tchar.h>

//=============================================================================
DEFINE_SINGLETON(GfxStats);
//=============================================================================

GfxStats::GfxStats()
: mFont(0), mFPS(0.0f), mMilliSecPerFrame(0.0f), mNumTris(0), mNumVertices(0)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height          = 18;
    fontDesc.Width           = 0;
    fontDesc.Weight          = 0;
    fontDesc.MipLevels       = 1;
    fontDesc.Italic          = false;
    fontDesc.CharSet         = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality         = DEFAULT_QUALITY;
    fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    _tcscpy(fontDesc.FaceName, _T("Times New Roman"));

	HR(D3DXCreateFontIndirect(gd3dDevice, &fontDesc, &mFont));
}

GfxStats::~GfxStats()
{
	ReleaseCOM(mFont);
}

void GfxStats::onLostDevice()
{
	HR(mFont->OnLostDevice());
}

void GfxStats::onResetDevice()
{
	HR(mFont->OnResetDevice());
}

void GfxStats::addVertices(DWORD n)
{
	mNumVertices += n;
}

void GfxStats::subVertices(DWORD n)
{
	mNumVertices -= n;
}

void GfxStats::addTriangles(DWORD n)
{
	mNumTris += n;
}

void GfxStats::subTriangles(DWORD n)
{
	mNumTris -= n;
}

void GfxStats::setTriCount(DWORD n)
{
	mNumTris = n;
}

void GfxStats::setVertexCount(DWORD n)
{
	mNumVertices = n;
}

void GfxStats::update(float dt)
{
	// Make static so that their values persist accross function calls.
	static float numFrames   = 0.0f;
	static float timeElapsed = 0.0f;

	// Increment the frame count.
	numFrames += 1.0f;

	// Accumulate how much time has passed.
	timeElapsed += dt;

	// Has one second passed?--we compute the frame statistics once 
	// per second.  Note that the time between frames can vary so 
	// these stats are averages over a second.
	if( timeElapsed >= 1.0f )
	{
		// Frames Per Second = numFrames / timeElapsed,
		// but timeElapsed approx. equals 1.0, so 
		// frames per second = numFrames.

		mFPS = numFrames;

		// Average time, in miliseconds, it took to render a single frame.
		mMilliSecPerFrame = 1000.0f / mFPS;

		// Reset time counter and frame count to prepare for computing
		// the average stats over the next second.
		timeElapsed = 0.0f;
		numFrames   = 0.0f;
	}
}

void GfxStats::display()
{
	// Make static so memory is not allocated every frame.
	static char buffer[256];

	sprintf_s(buffer, "Frames Per Second = %.2f\n"
		"Milliseconds Per Frame = %.4f\n"
		"Triangle Count = %d\n"
		"Vertex Count = %d\n", mFPS, mMilliSecPerFrame, mNumTris, mNumVertices);

	RECT R = {5, 5, 0, 0};
	HR(mFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(0,0,0)));
}


// Display UI choices/help 
void GfxStats::displayAssignment4(float pRSBlend, float pNormStr, int pSpecCoef, bool pTextureToggle, bool pSolidToggle, bool pEnvReflectToggle, bool pNormalMapToggle, bool pDiffuseReflectToggle)
{
	//	Make static so memory is not allocated every frame
		static char v_buffer[600];

	//	set message
	sprintf_s(v_buffer,
		"Keys:\n"
		"W -- Switch b/t Solid / Wireframe\n%s is active\n"
		"\nT -- Switch texture On / Off\nTexture is %s\n"
		"\nO -- Switch b / t Rendering Objects\n"
		"\nR -- Switch Environment Reflection On / Off\nEnvironment Reflection is %s\n"
		"\nN -- Switch Normal Mapping On/Off\nNormal Mapping is %s\n"
		"\nE -- Switch Diffuse/Reflection blend On/Off\nDiffuse Blend is %s\n"
		"\n+/- -- Increment / Decrement Blend b / t Reflection & Specular\n"
		"Current Blend : %.1f\n"
		"\nA/S -- Increment / Decrement Strength of Normal\n"
		"Current Strength : %.1f\n"
		"\n1..7 -- Set Specular Coefficient\n"
		"Current Coefficient Value: %d\n"
		   , (pSolidToggle ? "Solid frame" :"Wire frame")
		   , (pTextureToggle ? "on" : "off")
		   , (pEnvReflectToggle ? "on" : "off")
		   , (pNormalMapToggle ? "on" : "off")
		   , (pDiffuseReflectToggle ? "on" : "off")
		   , pRSBlend, pNormStr, pSpecCoef);

	RECT v_R = { 5, 80, 0, 0 };
	HR(mFont->DrawText(0, v_buffer, -1, &v_R, DT_NOCLIP, D3DCOLOR_XRGB(200, 0, 0)));

}