#include "BackGround.hlsli"

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float3 NormalWS : NORMAL;
    float2 TexCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_Target0
{
    //      �e�N�X�`���̏��
    float4 color = tex.Sample(samLinear, input.TexCoord);
    
    return color;
}