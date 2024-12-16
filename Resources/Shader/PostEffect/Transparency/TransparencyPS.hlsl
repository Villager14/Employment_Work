#include "Transparency.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);

SamplerState samLinear : register(s0);

float4 viewColor()
{
	float r = 43.0f;
	float g = 156.0f;
	float b = 8.0f;

	return float4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output3 = tex3.Sample(samLinear, input.tex);

	return lerp(tex2.Sample(samLinear, input.tex),
		        tex.Sample(samLinear, input.tex),
					floor(clamp(output3.r + output3.g + output3.b - 3.0f, -0.1f, 0.0f)) * -1.0f);
}