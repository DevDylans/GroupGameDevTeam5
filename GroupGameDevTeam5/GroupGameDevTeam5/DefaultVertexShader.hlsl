cbuffer ConstantBuffer : register (b0)
{
	float4x4 wvpMatrix;
	//matrix view;
	//matrix projection;
}
struct VSInput
{
	float3 pos : POSITION;
	float2 tex : TEXCOORD;
};
struct VSOutput
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

VSOutput main(VSInput input)
{
	VSOutput output;
	output.pos = mul(input.pos, wvpMatrix);
	output.tex = input.tex;
	return output;
}