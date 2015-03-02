//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//                             Torus
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// inherites from BaseObject3D class
//=============================================================================
#ifndef _TORUS_OBJECT_3D_H
#define _TORUS_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "3DClasses\BaseObject3D.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class Torus : public BaseObject3D
{
private:
	float mInnerRadius;
	float mOuterRadius;
	int mSideFacetsNum;

protected:
	// Replace the code in the following methods
	void LoadObject(IDirect3DDevice9* gd3dDevice);

public:
	Torus(float iRadius = 2, float oRadius = 4, int sideFacetsNum = 10);
	~Torus(void);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H