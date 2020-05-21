struct VSOutput
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};
Texture2D texDiffuse : register(t0);
SamplerState samLinear : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
	float4 colour = texDiffuse.Sample(samLinear, input.tex);
	return colour;
}