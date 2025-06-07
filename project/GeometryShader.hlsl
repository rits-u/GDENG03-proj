
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
       // output.pos = mul(input[i].pos, viewProj[input[i].instanceID]);
        
        output.color = input[i].color;
        output.color1 = input[i].color1;
        output.vpIndex = input[i].instanceID; 
        stream.Append(output);
    }
}




      //  output.vpIndex = 1;
        
     //  output.pos = mul(input[i].pos, viewProj[input[i].instanceID]);
      //  output.pos = float4(input[i].pos.xyz, 1.0f); // No transform
            
        
      //  uint id = min(input[i].instanceID, 1); // assuming 2 viewports
       // output.pos = mul(input[i].pos, viewProj[id]);