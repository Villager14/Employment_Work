#include "GenerationWorld.hlsli"

struct Input
{
    float4 Position     : SV_Position;
    float3 Normal       : NORMAL;
    float2 TexCoord     : TEXCOORD0;
};

struct Output
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
    float4 PositionPS   : SV_Position;
};

Output main(Input vin)
{
    Output output;
    
    // ���_�̈ʒu�𓊉e��Ԃ�
    output.PositionPS = mul(vin.Position, WorldViewProj);
    // ���_�̈ʒu�����[���h��Ԃ�
    output.PositionWS = mul(vin.Position, World);
    // �@���x�N�g�������[���h��Ԃցi�g��k���̉e����ł��������ߋt�]�u�s���������j
    output.NormalWS = mul(vin.Normal, WorldInverseTranspose);
    // �e�N�X�`����UV���W
    output.TexCoord = vin.TexCoord;
    // ���_�̈ʒu�����C�g�̓��e��Ԃ�
    output.LightPosPS = mul(vin.Position, World);


    return output;
}