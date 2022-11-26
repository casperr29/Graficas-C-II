Texture2D texDay : register(t0);
Texture2D texAfter : register(t1);
Texture2D texNight : register(t2);

SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projMatrix;
	float4 valores;
};

cbuffer cbChangesOccasionally : register(b1)
{
	float horaTLim;
};

cbuffer cbChangesOccasionally : register(b2)
{
	float horaNLim;
};

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
	float horaTLim : TEXCOORD1;
	float horaNLim : TEXCOORD2;
};

PS_Input VS_Main(VS_Input vertex)
{
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, worldMatrix);
	vsOut.pos = mul(vsOut.pos, viewMatrix);
	vsOut.pos = mul(vsOut.pos, projMatrix);

	vsOut.tex0 = vertex.tex0;

	vsOut.horaTLim = horaTLim;

	vsOut.horaNLim = horaNLim;

	return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
	float4 day = texDay.Sample(colorSampler, pix.tex0);
	float4 afternoon = texAfter.Sample(colorSampler, pix.tex0);
	float4 night = texNight.Sample(colorSampler, pix.tex0);

	float4 finalColor = lerp(day, afternoon, pix.horaTLim);
	finalColor = lerp(finalColor, night, pix.horaNLim);

	//float4 finalColor = texDay.Sample(colorSampler, pix.tex0);

	return finalColor;
}