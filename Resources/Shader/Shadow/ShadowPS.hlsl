#include "Shawow.hlsli"


//		シャドウマップテクスチャ
Texture2D ShadowMapTexture : register(t1);

//		シャドウマップ用テクスチャサンプラー
SamplerComparisonState ShadowMapSampler : register(s1);

struct Input
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
};

// マッハバンド対策
#define SHADOW_EPSILON 0.0005f

float4 main(Input pin) : SV_TARGET0
{
    // ライトの向きを求める
    float3 lightDir = normalize(pin.PositionWS.xyz - LightPos.xyz);

    // 正規化デバイス座標にする
    pin.LightPosPS.xyz /= pin.LightPosPS.w;

    // 参照するシャドウマップのUV値を求める
    float2 uv = pin.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

    // シャドウマップの深度値とライト空間のピクセルのZ値を比較して影になるか調べる
    float percentLit = ShadowMapTexture.SampleCmpLevelZero(ShadowMapSampler, uv, pin.LightPosPS.z - SHADOW_EPSILON).x;
        
    //-------------
    //      ディヒューズ色
    //-------------
    
    //      法線とライトの向きの内積を求める
    float direction = dot(pin.NormalWS, LightDir);

    direction *= -1;

    //      ０以下の値を０にする
    direction *= floor(direction + 1.0f);

    //      ライトの明るさを求める
    float3 diffuseLig = percentLit * (LightAmbient * direction);

    //      環境光の強さ
    float lightAmbient = 0.3f;

    //      環境光を足す
    diffuseLig.x += lightAmbient;
    diffuseLig.y += lightAmbient;
    diffuseLig.z += lightAmbient;

    // テクスチャ色とディフューズ色を掛ける 
    float4 color = Texture.Sample(Sampler, pin.TexCoord);

    //      ディヒューズ色を掛ける
    color.rgb *= diffuseLig;

    return color;

}




