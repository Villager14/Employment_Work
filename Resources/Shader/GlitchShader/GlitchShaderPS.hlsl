#include "GlitchShader.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 Noise(float2 noiseTex, float power, float2 inputTex)
{
	float2 noise = noiseTex;

	noise = (noise - 0.5f) * power;

	return tex.Sample(samLinear, inputTex + float2(noise.x, 0.0f));
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 scaledTex = input.tex * noiseScale;

	float2 noise = tex2.Sample(samLinear, scaledTex + time.x).rg;

	float4 output = tex.Sample(samLinear, input.tex);

	float4 outputNoise = tex.Sample(samLinear, input.tex + float2(noise.x, 0.0f));

	float4 finalColor;

	finalColor.r = Noise(noise, 0.03f, input.tex).r;
	finalColor.g = output.g;
	finalColor.b = output.b;
	finalColor.a = output.a;

	return finalColor;
}