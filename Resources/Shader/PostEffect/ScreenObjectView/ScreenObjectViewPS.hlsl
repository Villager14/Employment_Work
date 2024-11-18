#include "ScreenObjectView.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);


	return lerp(tex2.Sample(samLinear, input.tex), output, (floor(clamp(output.r + output.g + output.b - 3.0f, -0.1f, 0.0f)) * -1.0f));

	//if (output.r + output.g + output.b >= 3.0f)
	//{
	//	return tex2.Sample(samLinear, input.tex);
	//}


	//return output;
}