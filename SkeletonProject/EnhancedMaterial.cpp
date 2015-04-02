#include "EnhancedMaterial.h"


void EnhancedMaterial::ConnectToEffect(ID3DXEffect* effect)
{

	m_Effect = effect;

	if (m_Effect != nullptr)
	{
		m_WorldMatHandle = m_Effect->GetParameterByName(0, "gWorld");
		m_gWorldInverseTranspose = m_Effect->GetParameterByName(0, "gWorldInverseTranspose");
		m_ViewProjectionMatHandel = m_Effect->GetParameterByName(0, "gWVP");
		m_gEyePosW = m_Effect->GetParameterByName(0, "gEyePosW");

		m_texture = m_Effect->GetParameterByName(0, "gTex");
		m_gEnvironment = m_Effect->GetParameterByName(0, "gEnvironment");
		m_gNormalMap = m_Effect->GetParameterByName(0, "gNormalMap");

		m_AmbientHandel = m_Effect->GetParameterByName(0, "gAmbientMtrl");
		m_DiffuseHandel = m_Effect->GetParameterByName(0, "gDiffuseMtrl");
		m_SpecHandel = m_Effect->GetParameterByName(0, "gSpecMtrl");
		m_SpecPowerHandel = m_Effect->GetParameterByName(0, "gSpecPower");
		m_gSpotPower = m_Effect->GetParameterByName(0, "gSpotPower");

		m_gLightVecW = m_Effect->GetParameterByName(0, "gLightVecW");
		m_gLightPosW = m_Effect->GetParameterByName(0, "gLightPosW");
		m_gLightDirW = m_Effect->GetParameterByName(0, "gLightDirW");

		m_gAmbientLight = m_Effect->GetParameterByName(0, "gAmbientLight");
		m_gDiffuseLight = m_Effect->GetParameterByName(0, "gDiffuseLight");
		m_gSpecLight = m_Effect->GetParameterByName(0, "gSpecLight");

		m_gSpecReflectBlend = m_Effect->GetParameterByName(0, "gSpecReflectBlend");
		m_gNormalBlend = m_Effect->GetParameterByName(0, "gNormalBlend");

		m_gTextureOn = m_Effect->GetParameterByName(0, "gTextureOn");
		m_gNormalMappingOn = m_Effect->GetParameterByName(0, "gNormalMappingOn");
		m_gEnvirnReflectionOn = m_Effect->GetParameterByName(0, "gEnvirnReflectionOn");
	}
};
void EnhancedMaterial::setViewMtx(D3DXVECTOR3 pos, D3DXVECTOR3 target, D3DXVECTOR3 up)
{
	D3DXVECTOR3 lightDir = target - pos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	HR(m_Effect->SetValue(m_gEyePosW, &pos, sizeof(D3DXVECTOR3)));
	HR(m_Effect->SetValue(m_gLightPosW, &pos, sizeof(D3DXVECTOR3)));
	HR(m_Effect->SetValue(m_gLightDirW, &lightDir, sizeof(D3DXVECTOR3)));
};
void EnhancedMaterial::setLight(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR spec, D3DXVECTOR3 vect)
{
	HR(m_Effect->SetValue(m_gAmbientLight, &ambient, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetValue(m_gDiffuseLight, &diffuse, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetValue(m_gSpecLight, &spec, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetValue(m_gLightVecW, &vect, sizeof(D3DXVECTOR3)));
};
void EnhancedMaterial::setTextures(IDirect3DTexture9* texture, IDirect3DTexture9* normal, IDirect3DCubeTexture9* reflection)
{
	HR(m_Effect->SetTexture(m_texture, texture));
	HR(m_Effect->SetTexture(m_gNormalMap, normal));
	HR(m_Effect->SetTexture(m_gEnvironment, reflection));
};
void EnhancedMaterial::setValues(bool textureOn, bool normalOn, bool envReflecOn, float blendNormal, float reflectBlend, float specCo)
{
	HR(m_Effect->SetBool(m_gTextureOn, textureOn));
	HR(m_Effect->SetBool(m_gNormalMappingOn, normalOn));
	HR(m_Effect->SetBool(m_gEnvirnReflectionOn, envReflecOn));

	HR(m_Effect->SetFloat(m_gNormalBlend, blendNormal));
	HR(m_Effect->SetFloat(m_gSpecReflectBlend, reflectBlend));
};