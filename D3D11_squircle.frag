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
/*
void frag_main()
{
    float i = 1.0f - (pow(abs(coords.x), 4.0f) + pow(abs(coords.y), 4.0f));
    i = smoothstep(ubuf_t - 0.800000011920928955078125f, ubuf_t + 0.800000011920928955078125f, i);
    i = floor(i * 20.0f) / 20.0f;
    fragColor = float4((coords * 0.5f) + 0.5f.xx, i, i);
}*/

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{/*
    coords = stage_input.coords;
    //frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output.fragColor = fragColor;
    return stage_output;
    */
    float4 textureColor;


    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, stage_input.tex);
    SPIRV_Cross_Output stage_output;
    stage_output.fragColor = textureColor;
    return stage_output;
}
