#include "GenerationWorld.hlsli"

struct PS_INPUT
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
    float4 PositionPS   : SV_Position;
};

float4 main(PS_INPUT input) : SV_Target0
{
    //      テクスチャの情報
    float4 color = tex.Sample(samLinear, float2(input.TexCoord.x, input.TexCoord.y + time));

    float le = distance(input.PositionWS.xyz, EyePosition);

    float num = max(ceil(clamp(length - le, 0.0f, 1.0f)), stop);

    return lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), color, num);
}