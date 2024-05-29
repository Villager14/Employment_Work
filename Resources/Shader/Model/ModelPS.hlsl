Texture2D tex : register(t0);

struct PSInputNoFog
{
	float4 Diffuse : COLOR0;
};

// Pixel shader: no fog.
float4 main(PSInputNoFog pin) : SV_Target0
{
	return pin.Diffuse;
}

