//struct GS_OUTPUT
//{
//	float4 pos : SV_POSITION;
//    float3 color : COLOR;
//    uint viewportIndex : SV_ViewportArrayIndex;
//};

////[maxvertexcount(3)]
////void gsmain(
////	triangle float4 input[3] : SV_POSITION, 
////	inout TriangleStream<GS_OUTPUT> output
////)
////{
////	for (uint i = 0; i < 3; i++)
////	{
////		GSOutput element;
////		element.pos = input[i];
////		output.Append(element);
////	}
////}

//[instance(2)]
//[maxvertexcount(3)]
//void gsmain(triangle VS_OUTPUT input[3], inout TriangleStream<GS_OUTPUT> triStream, uint instanceID : SV_GSInstanceID)
//{
//    GS_OUTPUT output;
    
//    for (int i = 0; i < 3; ++i)
//    {
//        output.pos = input[i].pos;
//        output.color = input[i].color;
//        output.viewportIndex = instanceID; // or hardcoded 0, 1, etc.
//        triStream.Append(output);
//    }
//}

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




      //  output.vpIndex = 1;
        
     //  output.pos = mul(input[i].pos, viewProj[input[i].instanceID]);
      //  output.pos = float4(input[i].pos.xyz, 1.0f); // No transform
            
        
      //  uint id = min(input[i].instanceID, 1); // assuming 2 viewports
       // output.pos = mul(input[i].pos, viewProj[id]);