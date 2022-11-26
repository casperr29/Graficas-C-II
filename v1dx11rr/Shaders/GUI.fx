Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer constantBuffer : register(b0)
{
    matrix worldMatrix;
}

struct VS_Input
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input psOut;
    
    psOut.pos = mul(vertex.pos, worldMatrix);
    psOut.normal = mul(vertex.normal, worldMatrix);
    psOut.uv = vertex.uv;
    
    return psOut;
}

float4 PS_Main(PS_Input vertex) : SV_TARGET
{
    float4 textura = colorMap.Sample(colorSampler, vertex.uv);
    clip(textura.a - 0.9f);
    return textura;
}