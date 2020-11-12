#include "VertexHeader.hlsli"

cbuffer ClipPlaneBuffer : register(b10)
{
    float4 clipPlane;
}

struct VertexInput
{
    float4 pos : Position;
    float4 color : COLOR;
    float2 uv : UV;
    float3 normal : NORMAL;
};

struct PixelInput
{
    float4 pos : SV_Position;
    
    float clip : SV_ClipDistance0;
};


PixelInput main(VertexInput input)
{
    PixelInput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.clip = dot(mul(input.pos, world), clipPlane);
    
    return output;
}