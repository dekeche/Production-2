#include "WaterMaterial.h"

WaterMaterial::WaterMaterial() : EnhancedMaterial()
{ 
	xRate = .1f;
	yRate = .05f;  
	yDispl = 0;
	xDispl = 0;
};
void WaterMaterial::ConnectToEffect(ID3DXEffect* effect)
{
	EnhancedMaterial::ConnectToEffect(effect);
	m_gNormalMap2 = m_Effect->GetParameterByName(0, "gNormalMap2");
	m_gXDisplacement = m_Effect->GetParameterByName(0, "gXDisplacement");
	m_gYDisplacement = m_Effect->GetParameterByName(0, "gYDisplacement");
};

void WaterMaterial::AddSecondNormalMap(IDirect3DTexture9* normal2)
{
	HR(m_Effect->SetTexture(m_gNormalMap2, normal2));
};

void WaterMaterial::Update(float dt)
{
	yDispl += yRate*dt;
	xDispl += xRate*dt;

	if (yDispl > 1.0f)
		yDispl -= 1.0f;

	if (xDispl > 1.0f)
		xDispl -= 1.0f;

	HR(m_Effect->SetFloat(m_gXDisplacement, yDispl));
	HR(m_Effect->SetFloat(m_gYDisplacement, xDispl));
};