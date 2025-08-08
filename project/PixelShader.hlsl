Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 texCoord : TEXCOORD0;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float useWireColor;
    float useTexture;
    float2 padding;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float4 defaultColor = float4(0.8, 0.8, 0.8, 1);
    
    if (useWireColor > 0.5)
    {
        return defaultColor;
    }
    else
    {
        if (useTexture > 0.5)
        {
            return Texture.Sample(TextureSampler, input.texCoord * 0.5);
        }
        else
        {
            return defaultColor;
        }
    }
        
  
}