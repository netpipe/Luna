float4x4 mWorldViewProj;  	// World * View * Projection transformation
float4x4 mInvWorld;       	// Inverted world matrix
float4x4 mTransWorld;     	// Transposed world matrix
float3 mSunPos;         	// Sun light position
float3 mAmbientData;		// Sun light parameters

struct VS_OUTPUT
{
	float4 Position   : POSITION;   // vertex position 
	float4 Diffuse    : COLOR0;     // vertex diffuse color
	float4 TexCoord1  : TEXCOORD0;  // tex coords
};

VS_OUTPUT vertexMain(	in float4 vPosition	: POSITION,
						in float3 vNormal   : NORMAL,
						in float4 Color		: COLOR0,
						in float2 texCoord     : TEXCOORD0 )
{
	VS_OUTPUT Output;

	Output.Position = mul(vPosition, mWorldViewProj);

	// transform normal 
	float3 normal = mul(vNormal, mInvWorld);
	
	// renormalize normal 
	normal = normalize(normal);
	
	// position in world coodinates
	float3 worldpos = mul(mTransWorld, vPosition);
	
	// calculate light vector, vtxpos - lightpos
	float3 lightVector = worldpos - mSunPos;
	
	// normalize light vector 
	lightVector = normalize(lightVector);
	
	// calculate light color 
	float3 tmp = dot(-lightVector, normal);
	tmp = lit(tmp.x, tmp.y, 1);

	Output.Diffuse.rgb = Color.rgb * (mAmbientData.y + (tmp.y*mAmbientData.y));
	Output.Diffuse.a = mAmbientData.x * 1.3f;
	
	Output.TexCoord1.xy = texCoord * 32;
	Output.TexCoord1.zw = texCoord;

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

texture texture1;
sampler2D tex1 = sampler_state
{
	texture			= <texture1>;
	MinFilter		= Anisotropic;
	MagFilter		= Linear;
	MipFilter		= Linear;
	MaxAnisotropy 	= 4;  
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
	MaxAnisotropy 	= 4;  
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
	MaxAnisotropy 	= 4;  
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
	MaxAnisotropy 	= 4;  
	AddressU		= WRAP;
	AddressV		= WRAP;
};

float4 pixelMain(in float4 TexCoord : TEXCOORD0, in float4 Diffuse : COLOR0) : COLOR0
{ 	
	float3 outColor = tex2D(tex1, TexCoord.xy).rgb;
	float4 splat = tex2D(tex0, TexCoord.zw); // splat map

	outColor = 
		((((((outColor*(1-splat.r)) + tex2D(tex2, TexCoord.xy).rgb * splat.r)
		* (1-splat.g)) + tex2D(tex3, TexCoord.xy).rgb * splat.g)
		* (1-splat.b)) + tex2D(tex4, TexCoord.xy).rgb * splat.b);	
	return float4(outColor * (1 - (splat.a * Diffuse.a)) * Diffuse.rgb, 1);
}

