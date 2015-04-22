#include "WaterMaterial.h"

void WaterMaterial::ConnectToEffect(ID3DXEffect* effect)
{
	EnhancedMaterial::ConnectToEffect(effect);
	m_gNormalMap2 = m_Effect->GetParameterByName(0, "gNormalMap2");
	m_gXDisplacement = m_Effect->GetParameterByName(0, "gXDisplacement");
	m_gYDisplacement = m_Effect->GetParameterByName(0, "gYDisplacement");
};

void WaterMaterial::AddSecondNormalMap(IDirect3DTexture9* normal2){};

void WaterMaterial::Update(float dt){};