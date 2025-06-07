struct GS_INPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
    uint instanceID : SV_InstanceID;
};

struct GS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
    uint vpIndex : SV_ViewportArrayIndex;
};

cbuffer constant : register(b0)
{
    uint time;
    float4x4 viewProj[4];
};


[maxvertexcount(3)]
void gsmain(triangle GS_INPUT input[3], inout TriangleStream<GS_OUTPUT> stream)
{
    [unroll]
    for (int i = 0; i < 3; ++i)
    {
        GS_OUTPUT output;
        output.pos = input[i].pos;
        output.color = input[i].color;
        output.color1 = input[i].color1;
        output.vpIndex = input[i].instanceID; 
        stream.Append(output);
    }
}