//=============================================================================
//                             Cone
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// inherites from BaseObject3D class
//=============================================================================
#ifndef _CONE_OBJECT_3D_H
#define _CONE_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "3DClasses\BaseObject3D.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class Cone : public BaseObject3D
{
private:
	float mHeight;
	float mRadius;
	int mSideFacetsNum;

protected:

	void LoadObject(IDirect3DDevice9* gd3dDevice);

public:
	Cone(int height = 6, float radius = 2, int sideFacetsNum = 12);
	~Cone(void);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

