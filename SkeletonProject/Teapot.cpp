//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#define _USE_MATH_DEFINES
#include "Teapot.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Teapot::Teapot() : BaseObject3D()
{

}

//-----------------------------------------------------------------------------
Teapot::~Teapot(void)
{
}

//-----------------------------------------------------------------------------
void Teapot::LoadObject(IDirect3DDevice9* gd3dDevice)
{
	D3DXCreateTeapot(gd3dDevice, &m_MeshObject, 0);
}