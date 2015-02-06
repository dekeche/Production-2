//=============================================================================
//                             Cone
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// inherites from BaseObject3D class
//=============================================================================
#ifndef _CYLINDER_OBJECT_3D_H
#define _CYLINDER_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "3DClasses\BaseObject3D.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class Cylinder : public BaseObject3D
{
private:
	float mHeight;
	float mRadius;
	int mSideFacetsNum;

protected:
	// Replace the code in the following methods
	virtual void buildDemoCubeVertexBuffer(IDirect3DDevice9* gd3dDevice);
	virtual void buildDemoCubeIndexBuffer(IDirect3DDevice9* gd3dDevice);

public:
	Cylinder(int height = 6, float radius = 1, int sideFacetsNum = 12);
	~Cylinder(void);

	// Replace or add to the following code as you progress with the material
	virtual void Create(IDirect3DDevice9* gd3dDevice);
	virtual void Render(IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H