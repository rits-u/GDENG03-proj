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
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
	//return float4(0.0f, 0.0f, 1.0f, 1.0f);
    //return float4(input.color, 1.0f);
    
    return float4(lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f), 1.0f);

    //float t = (sin(m_time / 3000.0f) + 1.0f) * 0.5f;
    //return float4(lerp(input.color, input.color1, t), 1.0f);
   
}