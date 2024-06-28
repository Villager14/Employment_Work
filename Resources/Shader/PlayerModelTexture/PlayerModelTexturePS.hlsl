#include "PlayerModelTexture.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//		Fî•ñ‚ğó‚¯æ‚é
	float4 output = tex.Sample(samLinear, input.tex);

	output.a *= ceil(input.tex.x - 0.4f);
	output.a *= floor(input.tex.x - 0.6f) * -1.0f;

	output.a *= ceil(input.tex.y - 0.22f);
	output.a *= floor(input.tex.y - 0.75f) * -1.0f;



	return output;
}