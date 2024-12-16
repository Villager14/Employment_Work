#include "CoolTime.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float3 Velocity(float angle)
{
	float3 velocity = float3(0.0f, 0.0f, 0.0f);

	float move = step(0.0f, angle) * (1.0f - step(90.0f, angle));
	velocity += move * lerp(float3(0.5f, 0.0f, 0.0f), float3(1.0f, 0.5f, 0.0f), angle / 90.0f);

	float move2 = step(90.0f, angle) * (1.0f - step(180.0f, angle));
	velocity += move2 * lerp(float3(1.0f, 0.5f, 0.0f), float3(0.5f, 1.0f, 0.0f), (angle - 90.0f) / 90.0f);

	float move3 = step(180.0f, angle) * (1.0f - step(270.0f, angle));
	velocity += move3 * lerp(float3(0.5f, 1.0f, 0.0f), float3(0.0f, 0.5f, 0.0f), (angle - 180.0f) / 90.0f);

	float move4 = step(270, angle);
	velocity += move4 * lerp(float3(0.0f, 0.5f, 0.0f), float3(0.5f, 0.0f, 0.0f), (angle - 270.0f) / 90.0f);

	return velocity;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float2 uv = input.tex;

	//		��]��
	float angle = rotation.x;

	//		�e�N�X�`���̃A���t�@
	float textureAlpha = output.w;

	//		���S�ɂȂ�悤�ɂ��炷
	float3 vv = cross(Velocity(angle) - float3(0.5f, 0.5f, 0.0f),
				float3(uv.x, uv.y, 0.0f) - float3(0.5f, 0.5f, 0.0f));

	output.w *= step(vv.z, 0.0f);

	//		X������ɂ��ĉE�����g���Ă���ꍇ�͍����������I�������g��Ă���ꍇ�͉E����`�悷��
	output.w = lerp(lerp(0.0f, output.w, step(0.5f, uv.x)),
			   lerp(output.w , textureAlpha, step(0.5f, uv.x)),
			   step(180.0f, angle));

	return output;
}