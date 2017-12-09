float4x4 mWorldViewProj;  // World * View * Projection transformation

// Vertex shader output structure
struct VS_OUTPUT
{
	float4 Position   : POSITION;   // vertex position 
	float4 Diffuse    : COLOR0;     // vertex diffuse color
	float2 TexCoord1  : TEXCOORD0;  // tex coords
	float2 TexCoord2  : TEXCOORD1;  // tex coords
};

VS_OUTPUT vertexMain(	float4 vPosition	: POSITION,
						float4 Color		: COLOR0,
						float2 texCoord     : TEXCOORD0 )
{
	VS_OUTPUT Output;

	Output.Position = mul(vPosition, mWorldViewProj);

	Output.Diffuse = Color * 1.12;

	Output.TexCoord1 = texCoord * 32;
	Output.TexCoord2 = texCoord;
	
	return Output;
}

sampler2D tex0 : register(s0);
sampler2D tex1 : register(s1);
sampler2D tex2 : register(s2);
sampler2D tex3 : register(s3);
sampler2D tex4 : register(s4);

float4 pixelMain(float2 TexCoord1 : TEXCOORD0, float2 TexCoord2 : TEXCOORD1, float4 Diffuse : COLOR0) : COLOR0
{ 	
	float3 outColor = tex2D(tex1, TexCoord1).rgb;
	float4 splat = tex2D(tex0, TexCoord2); // splat map

	outColor = (outColor*(1-splat.r)) + tex2D(tex2, TexCoord1).rgb * splat.r;
	outColor = (outColor*(1-splat.g)) + tex2D(tex3, TexCoord1).rgb * splat.g;
	outColor = (outColor*(1-splat.b)) + tex2D(tex4, TexCoord1).rgb * splat.b;

	return float4((outColor * clamp(1 - (splat.a * 0.255), 0, 1) * Diffuse), 1);
}

