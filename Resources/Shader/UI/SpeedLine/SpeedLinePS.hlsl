#include "SpeedLine.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float Front(float colorPower)
{
	return ceil(clamp(colorPower - time.y, 0.0f, 1.0f));
}

float Back(float colorPower)
{
	return floor(clamp(colorPower - time.x, -1.0f, 0.0f)) * -1.0f;
}

float HerfFront(float colorPower)
{
	return floor(clamp(colorPower - time.y, -1.0f, 0.0f))
			* -1.0f * ceil(colorPower);
}

float HerfBack(float colorPower)
{
	return ceil(clamp(colorPower - time.x, 0.0f, 1.0f));
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	output = lerp(float4(0.0f, 0.0f, 0.0f,0.0f),
				  float4(1.0f, 1.0f, 1.0f, 0.1f),
	lerp(Front(output.r) * Back(output.r),
		max(HerfFront(output.r), HerfBack(output.r)), time.z));

	return output;
}