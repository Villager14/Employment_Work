#include "SmokeEffect.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.Tex);

	output.a = 0.1f;
	
	output.a *= ceil(tex.Sample(samLinear, input.Tex).a);

	return output;
}