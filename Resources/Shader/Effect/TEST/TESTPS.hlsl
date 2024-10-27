Texture2D tex1 : register(t0);
SamplerState samplerState : register(s0);

struct PSInput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
	return tex1.Sample(samplerState, input.texCoord);
}

