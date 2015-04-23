//=============================================================================
//                              BaseObject3D
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Cylinder class to generate a 3d cylinder object.
//=============================================================================
#define _USE_MATH_DEFINES
#include "Cylinder.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Cylinder::Cylinder(int height, float radius, int sideFacetsNum) : BaseObject3D()
{
	mHeight = height;
	mRadius = radius;
	mSideFacetsNum = sideFacetsNum;
	m_Sphere = false;
}

//-----------------------------------------------------------------------------
Cylinder::~Cylinder(void)
{
}

//-----------------------------------------------------------------------------
void Cylinder::LoadObject(IDirect3DDevice9* gd3dDevice)
{
	D3DXCreateCylinder(gd3dDevice,mRadius,mRadius,mHeight,mSideFacetsNum,5,&m_MeshObject,0);
}