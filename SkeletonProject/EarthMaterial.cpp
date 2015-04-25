#include "EarthMaterial.h"

void EarthMaterial::ConnectToEffect(ID3DXEffect* effect)
{
	EnhancedMaterial::ConnectToEffect(effect);
	m_gNightTerrain = m_Effect->GetParameterByName(0, "gNightTerrain");
	m_gNightDayTime = m_Effect->GetParameterByName(0, "gNightDayTime");
};

void EarthMaterial::AddNightTexture(IDirect3DTexture9* night)
{
	HR(m_Effect->SetTexture(m_gNightTerrain, night));
};

void EarthMaterial::Update(float dt)
{
	mDayNightLine += mDayNightRate*dt;
	if (mDayNightLine > 1.0f)
		mDayNightLine -= 1.0f;

	HR(m_Effect->SetFloat(m_gNightDayTime, mDayNightLine));
};