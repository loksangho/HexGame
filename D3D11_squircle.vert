cbuffer MatrixBuffer
{
    matrix camMatrix;
    matrix translation;
    matrix rotation;
    matrix scale;
    matrix model;
};



struct SPIRV_Cross_Input
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 color : COLOR;
    float2 tex : TEXCOORD0;


};

struct SPIRV_Cross_Output
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
    float3 color: COLOR;
    float2 tex : TEXCOORD0;
};

//void vert_main()
//{
//    position = vertices;
//    coords = vertices.xy;
//}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    float4 crntPos = mul(model*translation*rotation*scale,float4(stage_input.position.x, stage_input.position.y, stage_input.position.z, 1.0f));
    crntPos.w = 1;
    //vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.position = mul(camMatrix, crntPos);
    stage_output.tex = stage_input.tex;
    stage_output.color = stage_input.color;
    stage_output.normal = stage_input.normal;
    return stage_output;
}
