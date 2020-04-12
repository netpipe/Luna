//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 mWorldViewProj;  // World * View * Projection transformation
//float4x4 mInvWorld;       // Inverted world matrix
//float4x4 mTransWorld;     // Transposed world matrix
//float3 mLightPos;         // Light position
//float4 mLightColor;       // Light color

texture texture0;
sampler2D tex0 = sampler_state
{
	texture			= <texture0>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 		= 1;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};

texture texture1;
sampler2D tex1 = sampler_state
{
	texture			= <texture1>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 		= 8;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};

texture texture2;
sampler2D tex2 = sampler_state
{
	texture			= <texture2>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 		= 8;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};

texture texture3;
sampler2D tex3 = sampler_state
{
	texture			= <texture3>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 		= 8;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};
texture texture4;
sampler2D tex4 = sampler_state
{
	texture			= <texture4>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 		= 8;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};

// Vertex shader output structure
struct VS_OUTPUT
{
	float4 Position   : POSITION;   // vertex position 
	float4 Diffuse    : COLOR0;     // vertex diffuse color
	float4 TexCoord1  : TEXCOORD0;  // tex coords
};

VS_OUTPUT vertexMain(	float4 vPosition	: POSITION,
						float4 Color		: COLOR0,
						float2 texCoord     : TEXCOORD0 )
{
	VS_OUTPUT Output;

	Output.Position = mul(vPosition, mWorldViewProj);

	Output.Diffuse = Color;

	Output.TexCoord1.xy = texCoord * 32;
	Output.TexCoord1.zw = texCoord;

	float4 splat = tex2D(tex0, texCoord); // splat map

	return Output;
}

float4 pixelMain(float4 TexCoord : TEXCOORD0, float4 Diffuse : COLOR0) : COLOR0
{ 	
	float3 outColor = tex2D(tex1, TexCoord.xy).rgb;
	float4 splat = tex2D(tex0, TexCoord.zw); // splat map

	outColor = (outColor*(1-splat.r)) + tex2D(tex2, TexCoord.xy).rgb * splat.r;
	outColor = (outColor*(1-splat.g)) + tex2D(tex3, TexCoord.xy).rgb * splat.g;
	outColor = (outColor*(1-splat.b)) + tex2D(tex4, TexCoord.xy).rgb * splat.b;

	return float4((outColor * clamp(1 - (splat.a * 0.255), 0, 1) * (Diffuse * 0.71)) * 1.0, 1);
}

