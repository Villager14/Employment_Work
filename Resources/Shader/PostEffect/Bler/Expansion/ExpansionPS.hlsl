#include "Expansion.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.tex;

	float4 color = tex.Sample(samLinear, uv);

	return color;
}