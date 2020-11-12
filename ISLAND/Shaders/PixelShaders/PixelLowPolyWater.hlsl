#include "PixelHeader.hlsli"

Texture2D reflectionMap : register(t10);
Texture2D refractionMap : register(t11);
Texture2D depthMap : register(t12);

const static float3 waterColor = float3(0.604f, 0.867f, 0.851f);
const static float fresnelReflective = 0.5f;
const static float edgeSoftness = 1.0f;
const static float minBlueness = 0.4f;
const static float maxBlueness = 0.8f;
const static float murkyDepth = 14.0f;

const static float specularReflectivity = 0.4f;
const static float shineDamper = 20.0f;

cbuffer Planes : register(b10)
{
    float2 nearFarPlanes;
}

struct PixelInput
{
    float4 clipSpaceReal : SV_Position;
    float4 wClipSpaceReal : Position0;
    float4 wClipSpaceGrid : Position1;
    float3 normal : Normal;
    float3 toCamera : ToCamera;
};

float3 ApplyMurkiness(float3 refractColor, float waterDepth)
{
    float murkyFactor = clamp(waterDepth / murkyDepth, 0.0, 1.0);
    float murkiness = minBlueness + murkyFactor * (maxBlueness - minBlueness);
    return lerp(refractColor, waterColor, murkiness);
}

float ToLinearDepth(float zDepth)
{
    float near = nearFarPlanes.x;
    float far = nearFarPlanes.y;
    return 2.0 * near * far / (far + near - (2.0 * zDepth - 1.0) * (far - near));
}

float CalculateWaterDepth(float2 texCoords, float4 clipSapceReal)
{
    float depth = depthMap.Sample(samp, texCoords).r;
    float floorDistance = ToLinearDepth(depth);
    depth = clipSapceReal.z;
    float waterDistance = ToLinearDepth(depth);
    return floorDistance - waterDistance;
}

float2 ClipSpaceToTexCoords(float4 clipSpace)
{
    float2 ndc = (clipSpace.xy / clipSpace.w);
    float2 texCoords = ndc / 2.0 + 0.5;
    return clamp(texCoords, 0.002, 0.998);
}

float CalculateFresnel(float3 toCamera, float3 noraml)
{
    float3 viewVector = normalize(toCamera);
    float3 normal = normalize(noraml);
    float refractiveFactor = dot(viewVector, normal);
    refractiveFactor = pow(refractiveFactor, fresnelReflective);
    return clamp(refractiveFactor, 0.0, 1.0);
}

float3 CalcSpecularLighting(float3 toCamVector, float3 toLightVector, float3 normal, float3 lightColor)
{
    float3 reflectedLightDirection = reflect(-toLightVector, normal);
    float specularFactor = dot(reflectedLightDirection, toCamVector);
    specularFactor = max(specularFactor, 0.0);
    specularFactor = pow(specularFactor, shineDamper);
    return specularFactor * specularReflectivity * lightColor;
}

float3 CalculateDiffuseLighting(float3 toLightVector, float3 normal, float3 lightColor, float2 lightBias)
{
    float brightness = max(dot(toLightVector, normal), 0.0);
    return (lightColor * lightBias.x) + (brightness * lightColor * lightBias.y);
}

float4 main(PixelInput input) : SV_Target
{
    float4 result = 0;
    
    float2 texCoordsReal = ClipSpaceToTexCoords(input.wClipSpaceReal);
    float2 texCoordsGrid = ClipSpaceToTexCoords(input.wClipSpaceGrid);
	
    float2 reflectionTexCoords = texCoordsGrid;
    float2 refractionTexCoords = float2(texCoordsGrid.x, 1.0f - texCoordsGrid.y);
    float waterDepth = CalculateWaterDepth(texCoordsReal, input.clipSpaceReal);
	
    float3 refractColor = refractionMap.Sample(samp, refractionTexCoords).rgb;
    float3 reflectColor = reflectionMap.Sample(samp, reflectionTexCoords).rgb;
	
	//apply some blueness
    refractColor = ApplyMurkiness(refractColor, waterDepth);
    reflectColor = lerp(reflectColor, waterColor, minBlueness);
	
    float3 finalColor = lerp(reflectColor, refractColor, CalculateFresnel(input.toCamera, input.normal));
    
    // 일단 직사광으로
    float3 toLight = -normalize(lights[0].direction);
    float3 specular = CalcSpecularLighting(input.toCamera, toLight, input.normal, lights[0].color.xyz);
    float3 diffuse = CalculateDiffuseLighting(toLight, input.normal, lights[0].color.xyz, float2(0.3f, 0.8f));
    
    finalColor = finalColor * diffuse + specular;
	
    result = float4(finalColor, 1.0);
	
	//apply soft edges
    result.a = clamp(waterDepth / edgeSoftness, 0.0f, 1.0f);
    
    return result;
}