//=============================================================================
//                              BaseMaterial
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#include "BaseMaterial.h"
//=============================================================================
BaseMaterial::BaseMaterial(void)
{
    m_Effect = NULL;
}

//-----------------------------------------------------------------------------
// Relase shader, blah...
BaseMaterial::~BaseMaterial(void)
{
}

//-----------------------------------------------------------------------------
// Need to add here a code that will associate with your shader parameters and 
// register them.
void BaseMaterial::ConnectToEffect( ID3DXEffect* effect )
{
    m_Effect = effect;

	if (m_Effect != nullptr)
	{
		m_WorldMatHandle = m_Effect->GetParameterByName(0, "gWorld");
		m_ViewProjectionMatHandel = m_Effect->GetParameterByName(0, "gWVP");
		m_AmbientHandel = m_Effect->GetParameterByName(0, "gAmbientMtrl");
		m_DiffuseHandel = m_Effect->GetParameterByName(0, "gDiffuseMtrl");
		m_SpecHandel = m_Effect->GetParameterByName(0, "gSpecMtrl");
		m_SpecPowerHandel = m_Effect->GetParameterByName(0, "gSpecPower");
	}
}
void BaseMaterial::setMat(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR spec, float specPower)
{
	m_Ambient = ambient;
	m_Diffuse = diffuse;
	m_Spec = spec;
	m_SpecPower = specPower;
};

//=============================================================================

void BaseMaterial::Render(D3DXMATRIX& worldMat, D3DXMATRIX& viewProjMat)
{
	if (m_Effect != nullptr)
	{
		HR(m_Effect->SetMatrix(m_WorldMatHandle, &worldMat));
		HR(m_Effect->SetMatrix(m_ViewProjectionMatHandel, &viewProjMat));
		HR(m_Effect->SetValue(m_AmbientHandel, &m_Ambient, sizeof(D3DXCOLOR)));
		HR(m_Effect->SetValue(m_DiffuseHandel, &m_Diffuse, sizeof(D3DXCOLOR)));
		HR(m_Effect->SetValue(m_SpecHandel, &m_Spec, sizeof(D3DXCOLOR)));
		HR(m_Effect->SetValue(m_SpecPowerHandel, &m_SpecPower, sizeof(D3DXCOLOR)));
		HR(m_Effect->CommitChanges());
	}
}