//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#define _USE_MATH_DEFINES
#include "Sphere.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Sphere::Sphere(float radius, int sideFacetsNum) : BaseObject3D()
{
	mRadius = radius;
	mSideFacetsNum = sideFacetsNum;
	m_Sphere = true;
}

//-----------------------------------------------------------------------------
Sphere::~Sphere(void)
{
}

//-----------------------------------------------------------------------------
void Sphere::LoadObject(IDirect3DDevice9* gd3dDevice)
{
	D3DXCreateSphere(gd3dDevice, mRadius, mSideFacetsNum, mSideFacetsNum, &m_MeshObject, 0);
}