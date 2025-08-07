//struct PS_INPUT
//{
//    float4 pos : SV_POSITION;
//    float3 color : COLOR;
//    float3 color1 : COLOR1;
//};

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
    //float3 baseColor = lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    //return float4(lerp(baseColor, wireColor.rgb, useWireColor), 1.0f);
    
    //if (useTexture = 1.0)
    //{
    //    return Texture.Sample(TextureSampler, input.texCoord * 0.5);
    //}
    //else
    //{
    //    float3 baseColor = (1.0, 1.0, 1.0);
    //    float3 wireColor = (1.0, 1.0, 1.0);
    //    return float4(lerp(baseColor.rgb, wireColor.rgb, 1), 1.0f);
    //}
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