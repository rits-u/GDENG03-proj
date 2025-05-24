struct VS_INPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};


VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.pos = input.pos;
    output.color = input.color;
    
    //if (pos.y > 0 && pos.y < 1)
    //{
    //    pos.x += 0.25f;
    //}
    
    //if (pos.y > -1 && pos.y < 0 && pos.x > 0 && pos.x < 1)
    //{
    //    pos.y += 0.25f;
    //}
    
    //if (pos.y > 0 && pos.y < 1 && pos.x > -1 && pos.x < 0)
    //{
    //    pos.y -= 0.25f;
    //}
	
	return output;
}