cbuffer W : register(b0)
{
    matrix world;
}

cbuffer V : register(b1)
{
    matrix view;
    matrix invView;
}
cbuffer P : register(b2)
{
    matrix projection;
}

cbuffer Type : register(b5)
{
    int modelType;
}


////////////////////////////
// VertexTypeµé 
////////////////////////////

struct VertexUV
{
    float4 pos : Position;
    float2 uv : UV;
};

struct VertexInstance
{
    float4 pos : Position;
    float2 uv : UV;
    float3 normal : Normal;
    float3 tangent : Tangent;
    float4 indices : BlendIndices;
    float4 weights : BlendWeights;
    
    matrix transform : Instance;
    uint instanceID : SV_InstanceID;
};