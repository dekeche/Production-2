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
#include "BaseMaterial.h"
//=============================================================================
class EnhancedMaterial : public BaseMaterial
{
protected:

	D3DXHANDLE          m_gWorldInverseTranspose;
	D3DXHANDLE          m_gEyePosW;

	D3DXHANDLE          m_gEnvironment;
	D3DXHANDLE          m_gNormalMap;

	D3DXHANDLE          m_gSpotPower;

	D3DXHANDLE          m_gLightVecW;
	D3DXHANDLE          m_gLightPosW;
	D3DXHANDLE          m_gLightDirW;

	D3DXHANDLE          m_gAmbientLight;
	D3DXHANDLE          m_gDiffuseLight;
	D3DXHANDLE          m_gSpecLight;

	D3DXHANDLE          m_gSpecReflectBlend;
	D3DXHANDLE          m_gNormalBlend;

	D3DXHANDLE          m_gTextureOn;
	D3DXHANDLE          m_gNormalMappingOn;
	D3DXHANDLE          m_gEnvirnReflectionOn;

public:
	EnhancedMaterial(void) :BaseMaterial(){};
	virtual ~EnhancedMaterial(void){};

	virtual void ConnectToEffect(ID3DXEffect* effect);
	void setLight(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR spec, D3DXVECTOR3 vect);
	void setViewMtx(D3DXVECTOR3 pos, D3DXVECTOR3 target, D3DXVECTOR3 up);
	void setTextures(IDirect3DTexture9* texture, IDirect3DTexture9* normal,IDirect3DCubeTexture9* reflection);
	void setValues(bool textureOn, bool normalOn, bool envReflecOn, float blendNormal, float reflectBlend, float specCo);
};
//=============================================================================

