#include "PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 main(PixelInput input) : SV_TARGET
{
    if (hasMap[0])
        return diffuseMap.Sample(samp, input.uv);
    else
        return mDiffuse;
}