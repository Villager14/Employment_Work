#include "TEST.hlsli"

struct VSInput
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD0;
	float4x4 modelMatrix : INSTANCE_MODEL_MATRIX;

};

//struct InstanceInput
//{
//	float4x4 modelMatrix : INSTANCE_MODEL_MATRIX;
//};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

PSInput main(VSInput input)
{
	PSInput output;
	output.position = mul(input.position, input.modelMatrix);
	output.texCoord = input.texCoord;
	return output;
}