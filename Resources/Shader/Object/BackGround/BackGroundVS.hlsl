#include "BackGround.hlsli"

struct Input
{
    float3 Position     : POSITION;
    float3 Normal       : NORMAL;
    float2 TexCoord     : TEXCOORD;
    column_major float4x4 mat : MATRIX;
};

struct Output
{
    float4 Position : SV_POSITION;
    float3 NormalWS : NORMAL;
    float2 TexCoord : TEXCOORD0;
};

Output main(Input vin)
{
    Output output;

    output.Position = mul(float4(vin.Position, 1.0f), vin.mat);

    output.NormalWS = vin.Normal;

    output.TexCoord = vin.TexCoord;

    return output;
}