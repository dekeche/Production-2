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


struct OutputVS
{
	float4 posH		: POSITION0;
	float3 normal : TEXCOORD0;
	float3 tangent : TEXCOORD1;
	float3 binormal : TEXCOORD2;
	float3 position : TEXCOORD3;
	float3 lightDir : TEXCOORD4;
	float3 viewDir : TEXCOORD5;
	float2 tex0 : TEXCOORD6;
};

sampler EnvMapS = sampler_state
{
	Texture = <gEnvironment>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressV = WRAP;
	AddressV = WRAP;
};

sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressV = WRAP;
	AddressV = WRAP;
};

sampler NormalMapS = sampler_state
{
	Texture = <gNormalMap>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressV = WRAP;
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

#if gNormalMappingOn

	float3x3 TBN;
	TBN[0] = tangentL;
	TBN[1] = binormalL;
	TBN[2] = normalL;

	//Matrix transforms from object space to tangent space
	float3x3 toTangentSpace = transpose(TBN);

	//	Transform eye position to local space
	float3 eyePosL = mul(float4(gEyePosW, 1.0f), gwWorldInv);

	outVS.toEyeT = mul(toEyeL, toTangentSpace);

	// Transform light direction to tangent space.
	outVS.normal = normalL;
	outVS.tangent = tangentL;
	outVS.binormal = binormalL;

#endif
	// Pass on texture coordinates to be interpolated
	// in rasterization.
	outVS.tex0 = tex0;
	//	return the output & continue into PS
	return outVS;


}


//	Returns a float4 that is the COLOR.
float4 NormalMapPS(float3 normal : TEXCOORD0,
float3 tangent : TEXCOORD1,
float3 binormal : TEXCOORD2,
float3 position : TEXCOORD3,
float2 tex0 : TEXCOORD6) : COLOR
{

#if gNormalMappingOn
	float3x3 TBN;
	TBN[0] = tangent;
	TBN[1] = binormal;
	TBN[2] = normal;
	TBN = transpose(TBN);
	normal = tex2D(NormalMapS, tex0);
	normal = mul(TBN, normal);
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
#endif

	float3 toEye = normalize(gEyePosW - position);
	float3 lightVecW = normalize(gLightPosW - position);
	
	//	Compute reflection vector
    //float3 r = reflect(-gLightVecW, normalW);
	float3 r = reflect(gLightDirW, normal);

	//	Determine how much specular light makes it's way into the eye(camera)
	float t = pow(max(dot(r, toEye), 0.0f), gSpecPower);

	////	Determine diffuse light intensity that strikes the vertex
	//float s = max(dot(gLightDirW, normalW), 0.0f);
	//	Spotlight factor
	float spot = pow(max(dot(-lightVecW, gLightDirW), 0.0f), gSpotPower);

	//	Compute the ambient, diffuse, and specular terms respecitively.
	float3 spec = t*(gSpecMtrl*gSpecLight).rgb;
		float3 diffuse = spot*(gDiffuseMtrl*gDiffuseLight).rgb;
		float3 ambient = gAmbientMtrl*gAmbientLight;

#if gEnvirnReflectionOn
		float3 envMapTex = reflect(-toEyeW, normal);
#endif
		float4 all_together = float4(((ambient*0.2f + spec* 0.15f + diffuse * 0.65f)), gDiffuseMtrl.a);

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