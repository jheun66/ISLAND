#include "VertexHeader.hlsli"

const static float PI = 3.1415926535897932384626433832795;

cbuffer WaterOptionBuffer : register(b11)
{
    float waterHeight;
    float waveLength;
    float waveAmplitude;
}

//const static float waveLength = 4.0;
//const static float waveAmplitude = 0.2;

struct VertexInput
{
    float4 pos : Position;
    float4 indicator : Indicator;
};

struct PixelInput
{
    float4 clipSpaceReal : SV_Position;
    float4 wClipSpaceReal : Position0;
    float4 wClipSpaceGrid : Position1;
    float3 normal : Normal;
    float3 toCamera : ToCamera;
};

float3 CalcNormal(float3 vertex0, float3 vertex1, float3 vertex2)
{
    float3 tangent = vertex1 - vertex0;
    float3 bitangent = vertex2 - vertex0;
    return normalize(cross(bitangent, tangent));
}

float Mod(float x, float y)
{
    return x - y * floor(x / y);
}

float generateOffset(float x, float z, float val1, float val2)
{
    float radiansX = ((Mod(x + z * x * val1, waveLength) / waveLength) + time * Mod(x * 0.8 + z, 1.5)) * 2.0 * PI;
    float radiansZ = ((Mod(val2 * (z * x + x * z), waveLength) / waveLength) + time * 2.0 * Mod(x, 2.0)) * 2.0 * PI;
    return waveAmplitude * 0.5 * (sin(radiansZ) + cos(radiansX));
}

float3 ApplyDistortion(float3 vertex)
{
    float xDistortion = generateOffset(vertex.x, vertex.z, 0.2, 0.1);
    float yDistortion = generateOffset(vertex.x, vertex.z, 0.1, 0.3);
    float zDistortion = generateOffset(vertex.x, vertex.z, 0.15, 0.2);
    return vertex + float3(xDistortion, yDistortion, zDistortion);
}

PixelInput main(VertexInput input)
{
    PixelInput output;
    
    float3 currentVertex = float3(input.pos.x, waterHeight, input.pos.z);
    float3 vertex1 = currentVertex + float3(input.indicator.y, 0.0f, input.indicator.x);
    float3 vertex2 = currentVertex + float3(input.indicator.w, 0.0f, input.indicator.z);
    
    output.wClipSpaceGrid = mul(float4(currentVertex, 1.0f), view);
    output.wClipSpaceGrid = mul(output.wClipSpaceGrid, projection);
    
    currentVertex = ApplyDistortion(currentVertex);
    vertex1 = ApplyDistortion(vertex1);
    vertex2 = ApplyDistortion(vertex2);
    
    output.normal = CalcNormal(currentVertex, vertex1, vertex2);
    
    output.wClipSpaceReal = mul(float4(currentVertex, 1.0f), view);
    output.wClipSpaceReal = mul(output.wClipSpaceReal, projection);
    
    output.clipSpaceReal = output.wClipSpaceReal;
    
    output.toCamera = normalize(invView._41_42_43 - currentVertex);
    
    return output;
}