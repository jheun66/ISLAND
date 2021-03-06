cbuffer W : register(b0)
{
    matrix world;
}

cbuffer V : register(b1)
{
    matrix view;
}
cbuffer P : register(b2)
{
    matrix projection;
}

struct VertexInput
{
	//          �ø�ƽ ����
    float4 pos : Position;
    float4 color : Color;
};

struct PixelInput
{
    float4 pos : SV_Position;
    float4 color : Color;
};


PixelInput main(VertexInput input)
{
    PixelInput output;
	
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
	
    output.color = input.color;
	
    return output;
}