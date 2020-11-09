#include "PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 worldPos : POSITION0;
    float3 camPos : POSITION1;
};

float4 main(PixelInput input) : SV_Target
{
    float4 albedo = input.color;
    float4 result = CalcAmbient(input.normal, albedo);

    for (uint i = 0; i < lightCount; i++)
    {
        if (!lights[i].active)
            continue;
        
        [flatten]
        if (lights[i].type == 0)
        {
            float3 toLight = -normalize(lights[i].direction);
            float3 light = normalize(toLight);
            input.normal = normalize(input.normal);
            float diffuseIntensity = saturate(dot(input.normal, light));
            
            albedo *= lights[i].color * saturate(diffuseIntensity) * mDiffuse;
    
            result += float4(albedo.rgb, 1.0f);
        }
        else if (lights[i].type == 1)
        {
            float3 toLight = lights[i].position - input.worldPos;
            float3 distanceToLight = length(toLight);
            toLight /= distanceToLight;
            float3 light = normalize(toLight);
            input.normal = normalize(input.normal);
            float diffuseIntensity = saturate(dot(input.normal, light));
            
            float3 toEye = normalize(input.camPos - input.worldPos);
            float3 halfWay = normalize(toEye + toLight);
            float specularIntensity = saturate(dot(halfWay, input.normal));
    
            specularIntensity = pow(specularIntensity, mSpecular.w);
    
            albedo += lights[i].color * float4(specularIntensity.xxx, 1.0f) * mSpecular;
    
            float distanceToLightNormal = 1.0f - saturate(distanceToLight / lights[i].range);
            float attention = distanceToLightNormal * distanceToLightNormal;
 
            result += float4(albedo.rgb * attention, 1.0f);
        }
    }
    
    return result;
}