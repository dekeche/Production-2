/*
	Referenced from Introduction To 3D Programming, ch. 10
*/


uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;
uniform extern float3   gEyePosW;

//	Components of the Vertex(object) color
uniform extern float4 gAmbientMtrl;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gSpecMtrl;
uniform extern float  gSpecPower;

//	Components of the Light color
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecLight;

// *********** For General Lighting 

//	General Vector of the Light in the World
uniform extern float3 gLightVecW;


// *********** For Point/Spot Lighting

//	Position of the Light in the World
uniform extern float3 gLightPosW;
//	Direction of the Light in the World
uniform extern float3 gLightDirW;

uniform extern float3 gAttenuation012;

uniform extern bool gTextureOn;
uniform extern texture gTex;
uniform extern float  gSpotPower;




struct PhongOutputVS
{
	float4 posH		: POSITION0;
	float3 normalW	: TEXCOORD0;
	float3 posW : TEXCOORD1;
	float2 tex0 : TEXCOORD2;
};

sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

//	Compute data about/from the vertex
//	Returns vertex structurep containing data on vertex we modified
PhongOutputVS PhongVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0 : TEXCOORD2)
{
	//	Initialize our return value
	PhongOutputVS outVS = (PhongOutputVS)0;

	//	Transform the normal to be in world space
	outVS.normalW = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	//	NORMALIZE IT
	outVS.normalW = normalize(outVS.normalW);

	//	Transform vertex position to world space
	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;





	//	Transform to homogenous clip space
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	if (gTextureOn)
		outVS.tex0 = tex0;

	//	return the output & continue into PS
	return outVS;


}


//	Returns a float4 that is the COLOR.
float4 PhongPS(float3 normalW : TEXCOORD0, float posW : TEXCOORD1, float2 tex0 : TEXCOORD2) : COLOR
{
	//	The pixel shader will compute the Specular equation to get the light/color
	//	that will make it's way to the camera eye.


	//	Interpolated normals can become unnormal, so renormalize again just to be sure
	normalW = normalize(normalW);

	//	Compute vector from vertex to eye position
	float3 toEye = normalize(gEyePosW - posW);

	// Unit vector from vertex to light source.
		float3 lightVecW = normalize(gLightPosW - posW);


		//	Compute reflection vector
		//float3 r = reflect(-gLightVecW, normalW);
		float3 r = reflect(gLightDirW, normalW);

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
		float4 all_together;
		//	Sum all the components together and copy over the diffuse alpha

	all_together = float4(  ((ambient + spec + diffuse)), gDiffuseMtrl.a);


		//	return color
		return all_together;
}

technique PhongTech
{
	pass P0
	{
		//	Specify vertex & pixel shader associated w/ this pass
		vertexShader = compile vs_2_0 PhongVS();
		pixelShader = compile ps_2_0 PhongPS();
	}
}