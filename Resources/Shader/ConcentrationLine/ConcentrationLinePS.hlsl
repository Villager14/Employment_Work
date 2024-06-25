#include "ConcentrationLine.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

//		サイトのシェーダーを参考(https://scrapbox.io/sayachang/%E3%81%8B%E3%82%93%E3%81%9F%E3%82%93%E3%82%A8%E3%83%95%E3%82%A7%E3%82%AF%E3%83%88%E5%8A%A0%E5%B7%A5%E3%82%B7%E3%82%A7%E3%83%BC%E3%83%80%E3%83%BC)
float4 ConcentrationLine(float2 tex)
{
	float2 uv = 2 * tex - 1;

	float r = length(uv);
	r = 0.7 * r - 0.7;

	float a = atan2(uv.y, uv.x);
	a = abs(cos(40 * a + concentrationLineTime.x) + sin(20 * a + concentrationLineTime.x));

	float d = a - r;

	float n = smoothstep(0.4, 0.1f, saturate(d));

	n = 1.0f;

	float alpha = 0.0f;

	alpha = smoothstep(0.15, 0.1f, saturate(d));

	//alpha = ceil(alpha) * lerp(0.0f, 1.0f, (distance(tex, float2(0.5f, 0.5f)) / 0.5f));
	
	if (ceil(alpha) >= 1.0f)
	{
		alpha = 0.5f;
	}

	return float4(n, n, n, alpha);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float4 sen = ConcentrationLine(input.tex);

	output.rgb *= sen.xyz;

	output.a = sen.w;

	output.a = 0.0f;

	return output;
}