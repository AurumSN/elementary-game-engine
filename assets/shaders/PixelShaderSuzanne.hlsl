struct PS_INPUT 
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

float4 psmain(PS_INPUT input) : SV_Target
{
    float ka = 0.3f;
    float3 ia = float3(1.0f, 1.0f, 1.0f);

    float3 ambient_light = ka * ia;



    float kd = 0.7f;
    float3 id = float3(1.0f, 1.0f, 1.0f);

    float amount_diffuse_light = dot(light_direction.xyz, input.normal);

    float3 diffuse_light = kd * amount_diffuse_light * id;



    float ks = 1.0f;
    float3 is = float3(1.0f, 1.0f, 1.0f);
    float3 reflected_light = reflect(light_direction.xyz, input.normal);
    float shininess = 30.0f;

    float amount_specular_light = pow(max(0.0f, dot(reflected_light, input.direction_to_camera)), shininess);

    float3 specular_light = ks * amount_specular_light * is;

    float3 final_light = ambient_light + diffuse_light + specular_light;

    // return Texture.Sample(TextureSampler, input.texcoord * 0.5f);
    return float4(final_light, 1.0f);
}