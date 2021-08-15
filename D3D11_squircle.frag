Texture2D shaderTexture;
SamplerState SampleType;

struct SPIRV_Cross_Input
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 color: COLOR;
    float2 tex : TEXCOORD0;

};

struct SPIRV_Cross_Output
{
    float4 fragColor : SV_Target0;
};

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    float4 textureColor;
    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, stage_input.tex);
    SPIRV_Cross_Output stage_output;
    stage_output.fragColor = textureColor;
    return stage_output;
}
