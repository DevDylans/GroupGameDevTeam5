
cbuffer ConstantBuffer : register (b0)
{
	matrix world;
	matrix view;
	matrix proj;
}
struct VSInput
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};
struct VSOutput
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

VSOutput main(VSInput input)
{
	VSOutput output =(VSOutput)0;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, proj);
	output.tex = input.tex;
	return output;
}