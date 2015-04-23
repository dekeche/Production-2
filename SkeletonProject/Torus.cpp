//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#define _USE_MATH_DEFINES
#include "Torus.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Torus::Torus(float iRadius, float oRadius, int sideFacetsNum) : BaseObject3D()
{
	mInnerRadius = iRadius;
	mOuterRadius = oRadius;
	mSideFacetsNum = sideFacetsNum;

	m_Sphere = true;
}

//-----------------------------------------------------------------------------
Torus::~Torus(void)
{
}

//-----------------------------------------------------------------------------
void Torus::LoadObject(IDirect3DDevice9* gd3dDevice)
{
	D3DXCreateTorus(gd3dDevice, mInnerRadius, mOuterRadius, mSideFacetsNum, 7, &m_MeshObject, 0);
}