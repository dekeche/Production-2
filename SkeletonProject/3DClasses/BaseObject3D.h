//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#ifndef _BASE_OBJECT_3D_H
#define _BASE_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include <d3dx9.h>

#include "../d3dUtil.h"

#include "../BaseMaterial.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class BaseObject3D
{
protected:	
    D3DXMATRIX                  m_World;

	ID3DXMesh* m_MeshObject;


	//	The material object that defines this mesh's color & material
	BaseMaterial* m_ObjectMaterial;

protected:
	virtual void LoadObject(IDirect3DDevice9* gd3dDevice) = 0;

public:
    BaseObject3D(void);
    ~BaseObject3D(void);

    // Replace or add to the following code as you progress with the material
	void Create( IDirect3DDevice9* gd3dDevice );
    void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection );
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

