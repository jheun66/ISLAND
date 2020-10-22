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


////////////////////////////
// VertexTypeµé 
////////////////////////////

struct VertexUV
{
    float4 pos : Position;
    float2 uv : UV;
};