//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//                             Torus
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// inherites from BaseObject3D class
//=============================================================================
#ifndef _TEAPOT_OBJECT_3D_H
#define _TEAPOT_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "3DClasses\BaseObject3D.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class Teapot : public BaseObject3D
{
private:

protected:
	// Replace the code in the following methods
	void LoadObject(IDirect3DDevice9* gd3dDevice);

public:
	Teapot();
	~Teapot(void);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H