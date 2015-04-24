/*
Referenced from Introduction To 3D Programming, ch. 10
*/

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;
uniform extern float3 gEyePosW;
uniform extern texture gTex;
uniform extern texture gEnvironment;
uniform extern texture gNormalMap;
uniform extern texture gNormalMap2;
//	Components of the Vertex(object) color
uniform extern float4 gAmbientMtrl;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gSpecMtrl;
uniform extern float  gSpecPower;
uniform extern float  gSpotPower;

//	Components of the Light color
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecLight;
//	General Vector of the Light in the World
uniform extern float3 gLightVecW;


// *********** For Point/Spot Lighting

//	Position of the Light in the World
uniform extern float3 gLightPosW;
//	Direction of the Light in the World
uniform extern float3 gLightDirW;

uniform extern float3 gAttenuation012;

uniform extern float gSpecReflectBlend;


uniform extern float gNormalBlend;

uniform extern bool gTextureOn;
uniform extern bool gNormalMappingOn;
uniform extern bool gEnvirnReflectionOn;
uniform extern bool gRecflectDiffuseOn;

uniform extern float gXDisplacement;
uniform extern float gYDisplacement;

struct OutputVS
{
	float4 posH		: POSITION0;
	float2 tex0 : TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float3 position : TEXCOORD3;
};

sampler EnvMapS = sampler_state
{
	Texture = <gEnvironment>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

sampler NormalMapS = sampler_state
{
	Texture = <gNormalMap>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
sampler NormalMapS2 = sampler_state
{
	Texture = <gNormalMap2>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

//	Compute data about/from the vertex
//	Returns vertex structurep containing data on vertex we modified
OutputVS NormalMapVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float3 tangentL : TANGENT0, float3 binormalL : BINORMAL0, float2 tex0 : TEXCOORD0)
{
	//	Initialize our return value
	OutputVS outVS = (OutputVS)0;
	//	Transform the normal to be in world space
	outVS.normal = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	//	NORMALIZE IT
	outVS.normal = normalize(outVS.normal);

	//	Transform vertex position to world space
	outVS.position = mul(float4(posL, 1.0f), gWorld).xyz;

	// not used in shader, but breaks if absent.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	//transfer texture coordinate
	outVS.tex0 = tex0;

	float2 tex1 = float2(tex0.x + gXDisplacement, tex0.y + gYDisplacement);

	outVS.tex1 = tex1;


	//	return the output & continue into PS
	return outVS;


}
//	Returns a float4 that is the COLOR.
float4 NormalMapPS(float2 tex0 : TEXCOORD0,
	float2 tex1 : TEXCOORD1,
	float3 normal : TEXCOORD2,
	float3 position : TEXCOORD3) : COLOR
{
	//create local values for Mtrl.
	float4 specMtrl = gSpecMtrl;
	float4 diffMtrl = gDiffuseMtrl;
	float4 ambiMtrl = gAmbientMtrl;

	//if texture is on, reset local Mtrl values to texture values.
	if (gTextureOn)
	{
		//get texture color.
		float4 texColor = tex2D(TexS, tex0);
			specMtrl = texColor;
		diffMtrl = texColor;
		ambiMtrl = texColor;
	}

	//if normal mapping is on, reset normal to normal map
	if (gNormalMappingOn)
	{
		//get normal at position.
		float3 normalT0 = tex2D(NormalMapS, tex0);
		float3 normalT1 = tex2D(NormalMapS2, tex1);
		//change to [-1,1] range
		normalT0 = 2.0f*normalT0 - 1.0f;
		normalT1 = 2.0f*normalT1 - 1.0f;
		//normalize
		normal = normalize(0.5f*(normalT0+normalT1));
		//calculate blend between original normal and this, Strength of the normal
		normal = normal * gNormalBlend;
	}

	//calculate vector to eye from position.
	float3 toEye = normalize(gEyePosW - position);
		//calculate the light vector.
		float3 lightVecW = normalize(gLightPosW - position);

		//	Compute reflection vector
		//float3 r = reflect(-gLightVecW, normalW);
		float3 r = reflect(-gLightDirW, normal);

		//	Determine how much specular light makes it's way into the eye(camera)
		float t = pow(max(dot(r, toEye), 0.0f), gSpecPower);

	////	Determine diffuse light intensity that strikes the vertex
	//float s = max(dot(gLightDirW, normalW), 0.0f);
	//	Spotlight factor
	// 0.5f is spot power.
	float spot = pow(max(dot(-lightVecW, gLightDirW), 0.0f), 0.5f);

	//	Compute the ambient, diffuse, and specular terms respecitively.
	float3 spec = t*(specMtrl*gSpecLight).rgb;
		float3 diffuse = spot*(diffMtrl*gDiffuseLight).rgb;
		float3 ambient = ambiMtrl*gAmbientLight;

		//if environment reflection, calculate recflection
	if (gEnvirnReflectionOn)
	{
		//get reflect direction.
		float3 envMapTex = reflect(-toEye, normal);
			//get reflect color.
			float3 reflectColor = texCUBE(EnvMapS, envMapTex);
			//calculate reflect blend with specular
			spec = spec*(gSpecReflectBlend)+reflectColor*(1 - gSpecReflectBlend);

		//if also blending diffuse, blend diffuse.
		if (gRecflectDiffuseOn)
		{
			diffuse = diffuse*(gSpecReflectBlend)+reflectColor*(1 - gSpecReflectBlend);
		}
	}
	//calculate final color.
	float4 all_together = float4(((ambient*0.2f + spec* 0.15f + diffuse * 0.65f)), gDiffuseMtrl.a);

		//return color.
		return all_together;
}

technique Assignment4Tech
{
	pass P0
	{
		//	Specify vertex & pixel shader associated w/ this pass
		vertexShader = compile vs_2_0 NormalMapVS();
		pixelShader = compile ps_2_0 NormalMapPS();
	}
}