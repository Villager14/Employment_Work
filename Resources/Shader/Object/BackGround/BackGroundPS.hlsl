#include "BackGround.hlsli"

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float3 NormalWS : NORMAL;
    float2 TexCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_Target0
{
    //      テクスチャの情報
    float4 color = tex.Sample(samLinear, input.TexCoord);
    
    return color;
}