#include "DegitalRain.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

int mod(int a, int b)
{
	return a - (b * (a / b));
}

float Raund(float val)
{
	return floor(val);
}

inline float4 SelectTexture(float2 uv, float val)
{
	return lerp(tex2.Sample(samLinear, uv), tex.Sample(samLinear, uv), Raund(val));
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.Tex;

	//トムの画像表示
	float4 output = float4(1.0f, 0.0f, 0.0f, 1.0f);

	//		万の位
	output = lerp(SelectTexture(uv, (number / 10000) % 10), output, clamp(ceil(uv.y - 3.0f), 0.0f, 1.0f));

	//		千の位
	output = lerp(SelectTexture(uv, ((number / 1000) % 10)),	output, clamp(ceil(uv.y - 2.0f), 0.0f, 1.0f));

	//		百の位
	output = lerp(SelectTexture(uv, ((number / 100) % 10)),		output, clamp(ceil(uv.y - 1.0f), 0.0f, 1.0f));

	//		十の位
	output = lerp(SelectTexture(uv, ((number / 10) % 10)),		output, clamp(ceil(uv.y), 0.0f, 1.0f));

	//		壱の位
	output = lerp(SelectTexture(uv, (number % 10)), output, clamp(ceil(uv.y + 1.0f), 0.0f, 1.0f));

	output.a = lerp(0.0f, 1.0f, clamp((length - 10.0f) / 30.0f, 0.0f, 1.0f));

	return output;
}