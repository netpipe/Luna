float4x4 mWorldViewProj;  	// World * View * Projection transformation
float alphaValue;

struct VS_OUTPUT
{
	float4 Position   	: POSITION;   // vertex position 
	float4 Diffuse    	: COLOR0;     // vertex diffuse color
	float2 TexCoord1	: TEXCOORD0;
};

VS_OUTPUT vertexMain(	in float4 vPosition		: POSITION,
						in float3 vNormal   	: NORMAL,
						in float4 Color			: COLOR0,
						in float2 texCoord1     : TEXCOORD0)
{
	VS_OUTPUT Output;

	Output.Position = mul(vPosition, mWorldViewProj);

	Output.Diffuse = Color;
	Output.Diffuse.a = alphaValue;
	
	Output.TexCoord1 = texCoord1;

	return Output;
}

texture texture0;
sampler2D tex0 = sampler_state
{
	texture			= <texture0>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 	= 1;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};

float4 pixelMain(in float2 TexCoord1 : TEXCOORD0, in float4 Diffuse : COLOR0) : COLOR0
{ 	
	float4 outColor = tex2D(tex0, TexCoord1);
	outColor.a *= Diffuse.a;
	
	return outColor;
}

