//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#include "BaseObject3D.h"
#include "Vertex.h"
#include "../GfxStats.h"
//=============================================================================
BaseObject3D::BaseObject3D(void)
{
    D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
BaseObject3D::~BaseObject3D(void)
{
	ReleaseCOM(m_MeshObject);


	//	destroy pointer to BaseMaterial
	delete m_ObjectMaterial;
}

//-----------------------------------------------------------------------------
void BaseObject3D::Create(IDirect3DDevice9* gd3dDevice)
{
	LoadObject(gd3dDevice);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Render( IDirect3DDevice9* gd3dDevice,
    D3DXMATRIX& view, D3DXMATRIX& projection )
{
	// Set matrices and model relevant render date
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &m_World));
	HR(gd3dDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gd3dDevice->SetTransform(D3DTS_PROJECTION, &projection));


	HR(m_MeshObject->DrawSubset(0));
}
