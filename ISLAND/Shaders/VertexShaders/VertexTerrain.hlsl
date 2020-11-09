#include "VertexHeader.hlsli"

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
    float4 color : COLOR;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 worldPos : POSITION0;
    float3 camPos : POSITION1;
};


PixelInput main(VertexInput input)
{
    PixelInput output;
    
    output.pos = mul(input.pos, world);
    
    output.worldPos = output.pos.xyz;
    output.camPos = invView._41_42_43;
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.color = input.color;
    output.uv = input.uv;

    output.normal = mul(input.normal, (float3x3) world);
    
    return output;
}