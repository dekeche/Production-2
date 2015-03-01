//=============================================================================
//                              BaseObject3D
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Cone class to generate a 3d cone object.
//=============================================================================
#define _USE_MATH_DEFINES
#include "Cone.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Cone::Cone(int height, float radius, int sideFacetsNum) : BaseObject3D()
{
	mHeight = height;
	mRadius = radius;
	mSideFacetsNum = sideFacetsNum;
}

//-----------------------------------------------------------------------------
Cone::~Cone(void)
{
}

//-----------------------------------------------------------------------------
void Cone::LoadObject(IDirect3DDevice9* gd3dDevice)
{
	D3DXCreateCylinder(gd3dDevice, mRadius, 0, mHeight, mSideFacetsNum, 5, &m_MeshObject, 0);
}
