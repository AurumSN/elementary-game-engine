struct VS_INPUT 
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VS_OUTPUT 
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 direction_to_camera : TEXCOORD2;
};

cbuffer constant : register(b0) 
{
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 proj;
    float4 light_direction;
    float4 camera_position;
    float time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.position = mul(input.position, world);
    output.direction_to_camera = normalize(output.position.xyz - camera_position.xyz);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    output.texcoord = input.texcoord;
    output.normal = input.normal;


    return output;
}