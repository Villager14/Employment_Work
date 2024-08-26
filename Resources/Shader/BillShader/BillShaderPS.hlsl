cbuffer ConstBuffer : register(b0)
{
    float4 fogColor;        //      フォグの色
    float4 fogLength;       //      フォグの変化距離
    float4 cameraPosition;  //      カメラの座標
};

Texture2D<float4> tex : register(t0);
sampler Sampler : register(s0);

struct PS_INPUT
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 Diffuse    : COLOR0;
};

float4 fog(float4 color, float3 position)
{
    float dis = distance(cameraPosition.xyz, position);

    float length = (fogLength.y - dis) / (fogLength.y - fogLength.x);

    float val = clamp(length, 0.0f, 1.0f);

    color.rgb = lerp(fogColor.xyz, color.rgb, val);

    return color;
}

float4 main(PS_INPUT pin) : SV_Target0
{
    float4 color = tex.Sample(Sampler, pin.TexCoord);

    color = fog(color, pin.PositionWS.xyz);

    return color;
}