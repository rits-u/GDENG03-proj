struct VS_INPUT
{
    float4 pos : POSITION0;
    float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
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


VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    //output.pos = mul(input.pos, m_world);
    
    ////VIEW SPACE
    //output.pos = mul(output.pos, m_view);
    
    ////PROJECTION SPACE
    //output.pos = mul(output.pos, m_proj);
    
    
    //float4 pos4 = float4(input.pos, 1.0f); // convert float3 to float4

    //output.pos = mul(input.pos, m_world);
    //output.pos = mul(output.pos, m_view);
    //output.pos = mul(output.pos, m_proj);
    //output.texCoord = input.texCoord;
    
    return output;
}