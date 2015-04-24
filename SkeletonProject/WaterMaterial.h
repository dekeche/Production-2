//=============================================================================
//                              BaseMaterial
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Enhanced class of BaseMaterial, used for Assignment 4
//=============================================================================
#pragma once
#include "d3dApp.h"
#include "EnhancedMaterial.h"
//=============================================================================
class WaterMaterial : public EnhancedMaterial
{
protected:

	D3DXHANDLE          m_gNormalMap2;

	D3DXHANDLE          m_gXDisplacement;
	D3DXHANDLE          m_gYDisplacement;

	float xRate;
	float yRate;

	float xDispl;
	float yDispl;
public:
	WaterMaterial(void);
	virtual ~WaterMaterial(void){};

	virtual void ConnectToEffect(ID3DXEffect* effect);

	virtual void AddSecondNormalMap(IDirect3DTexture9* normal2);

	virtual void Update(float dt);

};
//=============================================================================

