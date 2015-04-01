/*
Referenced from Introduction To 3D Programming, ch. 10
*/

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;
uniform extern float3 gEyePosW;
uniform extern texture gTex;
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

uniform extern bool gTextureOn;
uniform extern bool gNormalMappingOn;
uniform extern bool gEnvirnReflectionOn;


struct OutputVS
{
	float4 posH		: POSITION0;
	float3 toEyeT	: TEXCOORD0;
	float3 LightDirT : TEXCOORD1;
	float2 tex0 : TEXCOORD2;
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
OutputVS NormalMapVS(float3 posL : POSITION0, float3 tangentL : TANGENT0, float3 binormalL : BINORMAL0, float3 normalL : NORMAL0, float2 tex0 : TEXCOORD0)
{
	//	Initialize our return value
	OutputVS outVS = (OutputVS)0;


	float3x3 TBN;
	TBN[0] = tangentL;
	TBN[1] = binormalL;
	TBN[2] = normalL;

	//Matrix transforms from object space to tangent space
	float3x3 toTangentSpace = transpose(TBN);

	//	Transform eye position to local space
	float3 eyePosL = mul(float4(gEyePosW, 1.0f), gwWorldInv);

	// Transform light direction to tangent space.
	float3 lightDirL = mul(float4(gLightVecW, 0.0f), gWorldInv);
	outVS.LightDirT = mul(lightDirL, toTangentSpace);

	//Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	// Pass on texture coordinates to be interpolated
	// in rasterization.
	outVS.tex0 = tex0;

	//	return the output & continue into PS
	return outVS;


}


//	Returns a float4 that is the COLOR.
float4 NormalMapPS(float3 toEyeT : TEXCOORD0, float3 lightDirT : TEXCOORD1, float2 tex0 : TEXCOORD2) : COLOR
{

	//	Interpolated normals can become unnormal--so normalize
	toEyeT = normalize(toEyeT);
	lightDirT = normalize(lightDirT);

	// Light vector is opposite the direction of the light.
	float3 lightVecT = -lightDirT;

	// Expand from [0,1] compressed interval to
	//true[-1,1] interval (Equation 21.1).
	normalT = 2.0f*normalT - 1.0f;

	// Make it a unit vector
	normalT = normalize(normalT);

	//lighting calculations
	float3 r = reflect(lightDirT, normalT);
	float3 t = pow(max(dot(r,toEyeT))
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