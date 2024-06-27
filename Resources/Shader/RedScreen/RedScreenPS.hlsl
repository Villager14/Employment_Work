#include "RedScreen.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float Gray(float4 color)
{
	return color.r * 0.3f + color.g * 0.6f + color.b * 0.1f;
}

float4 Sepia(float4 color)
{
	float r = 255;
	float g = 0;
	float b = 0;


	float all = (r + g + b);

	float gray = Gray(color);

	return float4(gray * (r / all * 3), gray * (g / all * 3), gray * (b / all * 3), color.a);
}

float random(float2 uv)
{
	return frac(sin(dot(uv, float2(12.9898, 78.223))) * 43758.5453f);
}

float4 blur(float2 uv)
{
	float power = 0.1f;
	float center = 1.0f - power * 9.0f;

	float4 output = 0;

	for (int i = 0; i < 9; i++)
	{
		output += tex.Sample(samLinear, uv
			+ float2(((i % 3.0f) - 1.0f) * 0.01f,
			((i / 3.0f) - 1.0f) * 0.01f)) * power;
	}

	output += tex.Sample(samLinear, uv) * center;

	///*		消すとぼかし状態になる
	output = tex.Sample(samLinear, uv);
	//*/

	return output;
}

//		サイトのシェーダーを参考(https://scrapbox.io/sayachang/%E3%81%8B%E3%82%93%E3%81%9F%E3%82%93%E3%82%A8%E3%83%95%E3%82%A7%E3%82%AF%E3%83%88%E5%8A%A0%E5%B7%A5%E3%82%B7%E3%82%A7%E3%83%BC%E3%83%80%E3%83%BC)
float4 ConcentrationLine(float2 tex)
{
	float2 uv = 2 * tex - 1;

	float r = length(uv);
	r = 0.7 * r - 0.7;

	float cosval = lerp(20.0f, 50.0f, (sin(concentrationLineTime.x) + 1.0f) / 2.0f);
	float sinval = lerp(50.0f, 20.0f, (sin(concentrationLineTime.x) + 1.0f) / 2.0f);

	float a = atan2(uv.y, uv.x);
	a = abs(cos(50 * a + concentrationLineTime.x) + sin(20 * a + concentrationLineTime.x));

	float d = a - r;
	//float n = smoothstep(0.1, concentrationLineTime.y, saturate(d));

	float n = smoothstep(0.1, 0.3f, saturate(d));

	float alpha = smoothstep(0.0, 1.0f, saturate(d));

	return float4(n, n, n, alpha);
}

float4 MotionBler(float2 texcoord)
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = -10; i <= 10; ++i) {
		float2 offset = float2(motionVector.x, motionVector.y) * (i / 10.0f) * blurStrength.x;

		color += tex.Sample(samLinear, texcoord + offset);
	}

	color /= 21.0f; // サンプル数で割る

	return color;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	//		色情報を受け取る
	float4 output = tex.Sample(samLinear, input.tex);

	float4 g = Sepia(output);

	float elapsedTime = clamp(time.x, 0.0f, 1.0f);
	
	output = blur(input.tex);

	//		時間経過により色を変える
	output.r = lerp(output.r, g.x, elapsedTime);
	output.g = lerp(output.g, g.y, elapsedTime);
	output.b = lerp(output.b, g.z, elapsedTime);

	//output = MotionBler(input.tex);
	
	float alpha = 1.0f;

	//output *= ConcentrationLine(input.tex);

	return output;
}