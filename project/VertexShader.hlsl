
struct VS_INPUT
{
    float4 pos : POSITION;
    float4 pos1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
    uint instanceID : SV_InstanceID;
};

cbuffer constant : register(b0)
{
    unsigned int m_time;
    matrix viewProj[4];
};


VS_OUTPUT vsmain(VS_INPUT input, uint instanceID : SV_InstanceID)
{
    VS_OUTPUT output;
    float4 worldPos = lerp(input.pos, input.pos1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    //output.pos = mul(worldPos, viewProj[instanceID]);
    output.pos = worldPos;
    
    output.color = input.color;
    output.color1 = input.color1;
    output.instanceID = instanceID;
    
    return output;
}
