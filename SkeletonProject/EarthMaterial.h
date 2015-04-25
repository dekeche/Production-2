//=============================================================================
//                              EarthMaterial
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Enhanced class of BaseMaterial, used for Assignment 4
// Planed to implement earth-like world, did not succed.
//=============================================================================
#pragma once
#include "d3dApp.h"
#include "EnhancedMaterial.h"
//=============================================================================
class EarthMaterial : public EnhancedMaterial
{
protected:

	D3DXHANDLE          m_gNightTerrain;

	D3DXHANDLE          m_gNightDayTime;

	float mDayNightRate;
	float mDayNightLine;

public:
	EarthMaterial(void) :EnhancedMaterial(){ mDayNightRate = .1f; mDayNightLine = 0; };
	virtual ~EarthMaterial(void){};

	virtual void ConnectToEffect(ID3DXEffect* effect);

	virtual void AddNightTexture(IDirect3DTexture9* night);

	virtual void Update(float dt);
};
//=============================================================================

