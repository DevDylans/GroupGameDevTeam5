//#pragma pack_matrix( row_major )
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
	//output.pos = mul(input.pos, wvpMatrix);
	//output.pos.x = input.pos.x;
	//output.pos.y = input.pos.y;
	//output.pos.z = input.pos.z;
	//output.pos.w = 1;
	output.tex = input.tex;
	return output;
}