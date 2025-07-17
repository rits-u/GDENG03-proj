struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float m_time;
    float useWireColor;
    //float3 padding; // for 16-byte alignment
    float2 padding; // for 8-byte alignment
    float4 wireColor;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float3 baseColor = lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    return float4(lerp(baseColor, wireColor.rgb, useWireColor), 1.0f);
  
}