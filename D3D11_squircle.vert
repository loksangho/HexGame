cbuffer MatrixBuffer : register(cb0)
{
    float4x4 mvpMatrix;
};

/*
cbuffer TranslationBuffer : register(cb1)
{
    matrix translation;
};

cbuffer RotationBuffer : register(cb2)
{
    matrix rotation;
};

cbuffer ScaleBuffer : register(cb3)
{
    matrix scale;

};

cbuffer ModelBuffer : register(cb1)
{
    matrix model;
};
*/

struct SPIRV_Cross_Input
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 color : COLOR;
    float2 tex : TEXCOORD0;
};

struct SPIRV_Cross_Output
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 color: COLOR;
    float2 tex : TEXCOORD0;
};


SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    float4 crntPos = mul(float4(stage_input.position, 1.0f), mvpMatrix);
    SPIRV_Cross_Output stage_output;
    stage_output.position = crntPos;
    stage_output.tex = stage_input.tex;
    stage_output.color = stage_input.color;
    stage_output.normal = stage_input.normal;
    return stage_output;
}
