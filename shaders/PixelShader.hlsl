struct PS_INPUT 
{
    float4 position : SV_POSITION;
    float4 position1 : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0) 
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_Target
{
    return float4(lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f), 1.0f);
    // float2 uv = input.color;
    // int n = 10;

    // float c = min((float)floor(uv.x * n) / (n - 1), 1.0f);

    // return float4(c, c, c, 1.0f);
}