Texture2D colorMap : register(t0);
Texture2D colorMapN : register(t1);
Texture2D colorMapS : register(t2);
Texture2D colorMapA : register(t3);
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
	float3 cameraPos;
};

cbuffer cbChangerEveryFrame : register(b4)
{
	float wave;
};

cbuffer cbChangesOccasionally : register(b5)
{
	float3 lightDirF;
};

cbuffer cbChangesOccasionally : register(b6)
{
	float4 lightColorF;
};

float3 NormalSampleToWorldSpace(float3 normalMapSample,
	float3 unitNormalW,
	float3 tangentW)
{
	// Uncompress each component from [0,1] to [-1,1].
	float3 normalT = 2.0f * normalMapSample - 1.0f;
	// Build orthonormal basis.
	float3 N = unitNormalW;
	float3 T = normalize(tangentW - dot(tangentW, N) * N);
	float3 B = cross(N, T);
	float3x3 TBN = float3x3(T, B, N);
	// Transform from tangent space to world space.
	float3 bumpedNormalW = mul(normalT, TBN);
	return bumpedNormalW;
}

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
	float3 normal : NORMAL0;
	float3 tangente : NORMAL1;
	float3 binormal : NORMAL2;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
	float3 normal : NORMAL0;
	float3 tangent : NORMAL1;
	float3 binorm : NORMAL2;
	float3 viewDirection : TEXCOORD1;
	float3 lightDirF : TEXCOORD2;
	float4 lightColorF : TEXCOORD3;
};

PS_Input VS_Main(VS_Input vertex)
{
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, worldMatrix);
	vsOut.pos = mul(vsOut.pos, viewMatrix);
	vsOut.pos = mul(vsOut.pos, projMatrix);

	vsOut.tex0 = vertex.tex0 + wave;
	vsOut.normal = normalize(mul(vertex.normal, worldMatrix));
	vsOut.tangent = normalize(mul(vertex.tangente, worldMatrix));
	vsOut.binorm = normalize(mul(vertex.binormal, worldMatrix));

	// Calculate the position of the vertex in the world.
	float4 worldPosition = mul(vertex.pos, worldMatrix);

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	vsOut.viewDirection = cameraPos.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	vsOut.viewDirection = normalize(vsOut.viewDirection);

	vsOut.lightDirF = normalize(lightDirF);
	vsOut.lightDirF = -lightDirF;

	vsOut.lightColorF = lightColorF;

	return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
	float3 reflection;
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 fColor = float4(1,0,0,1);
	float3 ambient = float3(0.3f, 0.3f, 0.3f);

	//Ambiental
	float4 textf = colorMap.Sample(colorSampler, pix.tex0/4);

	//Difusa

	float4 normalMapSample = colorMapN.Sample(colorSampler, pix.tex0 / 4);
	float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, pix.normal, pix.tangent);
	float diff = clamp(dot(lightDirF, bumpedNormalW), 0.0f, 1.0f);
	diff = saturate(diff * lightColorF * 0.8);



	//Especular
	float4 specmap = colorMapS.Sample(colorSampler, pix.tex0 / 4);
	reflection = normalize(2 * bumpedNormalW + lightDirF);
	specular = pow(saturate(dot(reflection, pix.viewDirection)), 32);
	specular = specular * specmap * 2;


	fColor = float4(textf.rgb * (ambient + diff + specular), 0.7f);
	fColor = fColor;
	return fColor;
}
