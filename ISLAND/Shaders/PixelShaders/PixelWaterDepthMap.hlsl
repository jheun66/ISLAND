#include "PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_Position;
        
    float clip : SV_ClipDistance0;
};


float4 main(PixelInput input) : SV_Target
{
    float depth = input.pos.z / input.pos.w;
    
    return float4(depth.xxx, 1);
}