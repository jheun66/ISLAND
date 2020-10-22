// 거의 모든데 쓰는 것들 모아놓음
Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samp : register(s0);

// 빛 추가하기

cbuffer Material : register(b1)
{
    float4 mDiffuse;
    float4 mSpecular;
    float4 mAmbient;
    
    int4 hasMap;
}