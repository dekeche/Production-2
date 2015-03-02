//=============================================================================
//                              BaseMaterial
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#pragma once
#include "d3dApp.h"
//=============================================================================
class BaseMaterial
{
protected:
    ID3DXEffect*        m_Effect;               // the shader associate effect file

	D3DXCOLOR m_Ambient;
	D3DXCOLOR m_Diffuse;
	D3DXCOLOR m_Spec;
	float m_SpecPower;           // specualr power


    //---------- Shader Handles ----------
    // Generic shader handles
    D3DXHANDLE          m_WorldMatHandle;    
	D3DXHANDLE          m_ViewProjectionMatHandel;

	D3DXHANDLE          m_AmbientHandel;
	D3DXHANDLE          m_DiffuseHandel;
	D3DXHANDLE          m_SpecHandel;
	D3DXHANDLE          m_SpecPowerHandel;



public:
    BaseMaterial(void);
    virtual ~BaseMaterial(void);

    void ConnectToEffect( ID3DXEffect* effect );
	void setMat(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR spec, float specPower );
    void Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewProjMat ); 
};
//=============================================================================

