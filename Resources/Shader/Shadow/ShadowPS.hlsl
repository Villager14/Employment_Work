#include "Shawow.hlsli"


//		�V���h�E�}�b�v�e�N�X�`��
Texture2D ShadowMapTexture : register(t1);

//		�V���h�E�}�b�v�p�e�N�X�`���T���v���[
SamplerComparisonState ShadowMapSampler : register(s1);

struct Input
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
};

// �}�b�n�o���h�΍�
#define SHADOW_EPSILON 0.0005f

float4 main(Input pin) : SV_TARGET0
{
    // ���C�g�̌��������߂�
    float3 lightDir = normalize(pin.PositionWS.xyz - LightPos.xyz);

    // ���K���f�o�C�X���W�ɂ���
    pin.LightPosPS.xyz /= pin.LightPosPS.w;

    // �Q�Ƃ���V���h�E�}�b�v��UV�l�����߂�
    float2 uv = pin.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

    // �V���h�E�}�b�v�̐[�x�l�ƃ��C�g��Ԃ̃s�N�Z����Z�l���r���ĉe�ɂȂ邩���ׂ�
    float percentLit = ShadowMapTexture.SampleCmpLevelZero(ShadowMapSampler, uv, pin.LightPosPS.z - SHADOW_EPSILON).x;
        
    //-------------
    //      �f�B�q���[�Y�F
    //-------------
    
    //      �@���ƃ��C�g�̌����̓��ς����߂�
    float direction = dot(pin.NormalWS, LightDir);

    direction *= -1;

    //      �O�ȉ��̒l���O�ɂ���
    direction *= floor(direction + 1.0f);

    //      ���C�g�̖��邳�����߂�
    float3 diffuseLig = percentLit * (LightAmbient * direction);

    //      �����̋���
    float lightAmbient = 0.3f;

    //      �����𑫂�
    diffuseLig.x += lightAmbient;
    diffuseLig.y += lightAmbient;
    diffuseLig.z += lightAmbient;

    // �e�N�X�`���F�ƃf�B�t���[�Y�F���|���� 
    float4 color = Texture.Sample(Sampler, pin.TexCoord);

    //      �f�B�q���[�Y�F���|����
    color.rgb *= diffuseLig;

    return color;

}



