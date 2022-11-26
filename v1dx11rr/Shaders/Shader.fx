Texture2D colorMap : register(t0);
Texture2D colorMap2 : register(t1);
Texture2D colorMap3 : register(t2);
Texture2D colorMapN : register(t3);
Texture2D colorMapN2 : register(t4);
Texture2D colorMapN3 : register(t5);
Texture2D colorMapS : register(t6);
Texture2D colorMapS2 : register(t7);
Texture2D colorMapS3 : register(t8);
Texture2D blendMap : register(t9);
Texture2D blendMap2 : register(t10);

SamplerState colorSampler : register(s0);

cbuffer cbChangerEveryFrame : register(b0)
{
	matrix worldMatrix;
};

cbuffer cbNeverChanges : register(b1)
{
	matrix viewMatrix;
};

cbuffer cbChangeOnResize : register(b2)
{
	matrix projMatrix;
};

cbuffer cbChangesOccasionally : register(b3)
{
	float3 lightDirF;
};

cbuffer cbChangesOccasionally : register(b4)
{
	float4 lightColorF;
};

cbuffer cbChangesOccasionally : register(b5) 
{
	float4 cameraPos;
};

float3 NormalSampleToWorldSpace(float3 normalMapSample, float3 unitNormalW, float3 tangentW)
{
	float3 normalT = 2.0f * normalMapSample - 1.0f;
	float3 N = unitNormalW;
	float3 T = normalize(tangentW - dot(tangentW, N) * N);
	float3 B = cross(N, T);
	float3x3 TBN = float3x3(T, B, N);
	float3 bumpedNormalW = mul(normalT, TBN);
	return bumpedNormalW;
}

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
	float2 blendTex : TEXCOORD1;
	float3 normal : NORMAL0;
	float3 tangente : NORMAL1;
	float3 binormal : NORMAL2;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
	float2 blendTex : TEXCOORD1;
	float3 lightDirF : TEXCOORD2;
	float4 lightColorF : TEXCOORD3;
	float3 viewDirection : TEXCOORD4;
	float3 normal : NORMAL0;
	float3 tangent : NORMAL1;
	float3 binorm : NORMAL2;
};

PS_Input VS_Main(VS_Input vertex)
{
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, worldMatrix);
	vsOut.pos = mul(vsOut.pos, viewMatrix);
	vsOut.pos = mul(vsOut.pos, projMatrix);

	vsOut.tex0 = vertex.tex0;
	vsOut.blendTex = vertex.blendTex;
	vsOut.normal = normalize(mul(vertex.normal, worldMatrix));
	vsOut.tangent = normalize(mul(vertex.tangente, worldMatrix));
	vsOut.binorm = normalize(mul(vertex.binormal, worldMatrix));

	vsOut.lightDirF = lightDirF;
	vsOut.lightColorF = lightColorF;

	float4 worldPosition = mul(vertex.pos, worldMatrix);
	vsOut.viewDirection = cameraPos.xyz - worldPosition.xyz;
	vsOut.viewDirection = normalize(vsOut.viewDirection);

	return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
	float4 fColor = float4(1,0,0,1);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 text = colorMap.Sample(colorSampler, pix.tex0 / 2);
	float4 text2 = colorMap2.Sample(colorSampler, pix.tex0 / 2);
	float4 text3 = colorMap3.Sample(colorSampler, pix.tex0 / 2);
	float4 alphaBlend = blendMap.Sample(colorSampler, pix.blendTex);
	float4 alphaBlend2 = blendMap2.Sample(colorSampler, pix.blendTex);
	float4 textf = (text * alphaBlend) + ((1.0 - alphaBlend) * text2);
	textf = (textf * alphaBlend2) + ((1.0 - alphaBlend2) * text3);

	float4 normalMapSample = colorMapN.Sample(colorSampler, pix.tex0 / 2);
	float4 normalMapSample2 = colorMapN2.Sample(colorSampler, pix.tex0 / 2);
	float4 normalMapSample3 = colorMapN3.Sample(colorSampler, pix.tex0 / 2);
	float4 textf2 = (normalMapSample * alphaBlend) + ((1.0 - alphaBlend) * normalMapSample2);
	textf2 = (textf2 * alphaBlend2) + ((1.0 - alphaBlend2) * normalMapSample3);
	float3 bumpedNormalW = NormalSampleToWorldSpace(textf2, pix.normal, pix.tangent);
	float diff = clamp(dot(-pix.lightDirF, bumpedNormalW), 0.0, 1.0f);
	diff = saturate(diff * pix.lightColorF.rgb * 0.5);

	float4 specmap = colorMapS.Sample(colorSampler, pix.tex0 / 2);
	float4 specmap2 = colorMapS2.Sample(colorSampler, pix.tex0 / 2);
	float4 specmap3 = colorMapS3.Sample(colorSampler, pix.tex0 / 2);
	float4 textf3 = (specmap * alphaBlend) + ((1.0 - alphaBlend) * specmap2);
	textf3 = (textf3 * alphaBlend2) + ((1.0 - alphaBlend2) * specmap3);
	float3 reflection = normalize(2 * bumpedNormalW + pix.lightDirF);
	specular = pow(saturate(dot(reflection, pix.viewDirection)), 16);
	specular = specular * specmap * 0.6;

	fColor = float4(textf.rgb * ( diff + specular), 1.0f);

	return fColor;
}