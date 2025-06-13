struct VS_INPUT
{
    float4 pos : POSITION;
   // float4 pos1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 worldMatrix;
    row_major float4x4 viewMatrix;
    row_major float4x4 projMatrix;
    unsigned int time;
}


VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
   // output.pos = input.pos
   // output.pos = lerp(input.pos, input.pos1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    
    
    //WORLD SPACE
    output.pos = mul(input.pos, worldMatrix);
    
    //VIEW SPACE
    output.pos = mul(output.pos, viewMatrix);
    
    //PROJECTION SPACE
    output.pos = mul(output.pos, projMatrix);
    
    output.color = input.color;
    output.color1 = input.color1;
   // output.color = lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    
  
	return output;
}