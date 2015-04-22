

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;
uniform extern float3   gEyePosW;

struct ProtoOutputVS
{
	float4 posH		: POSITION0;
};

//	Compute data about/from the vertex
//	Returns vertex structurep containing data on vertex we modified
ProtoOutputVS ProtoVS(float3 posL : POSITION0, float3 normalL : NORMAL0)
{
	//	Transform to homogenous clip space
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	//	return the output & continue into PS
	return outVS;

}


//	Returns a float4 that is the COLOR.
float4 PhongPS(float3 normalW : TEXCOORD0, float posW : TEXCOORD1) : COLOR
{
	return float4(1, 1, 1, 1);
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