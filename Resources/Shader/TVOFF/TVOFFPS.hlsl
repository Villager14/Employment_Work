#include "TVOFF.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	//		アスペクト比
	float aspect = windowSize.x / windowSize.y;

	float2 uv = input.tex;

	uv.x *= aspect;

	return output;
}