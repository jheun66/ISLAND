#include "VertexHeader.hlsli"

cbuffer Reflection : register(b10)
{
    matrix reflection;
}

struct PixelInput
{
    float4 pos : SV_Position;
    
    float4 wvpPositionSub : POSITION;
};


PixelInput main(VertexInstance input)
{
    PixelInput output;
    
    matrix transform = 0;
    
    [flatten]
    if (modelType)
    {
        transform = SkinWorld(input.instanceID, input.indices, input.weights);
        transform = mul(transform, input.transform);
    }
    else
        transform = input.transform;
	
    output.pos = mul(input.pos, transform);
    
    output.wvpPositionSub = mul(output.pos, reflection);
    output.wvpPositionSub = mul(output.wvpPositionSub, projection);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    return output;
}