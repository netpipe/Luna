float4x4 mWorldViewProj;  	// World * View * Projection transformation
float4x4 mInvWorld;       	// Inverted world matrix
float4x4 mTransWorld;     	// Transposed world matrix
float3 mSunPos;         	// Sun light position
float3 mAmbientData;

struct VS_OUTPUT
{
	float4 Position   : POSITION;   // vertex position 
	float4 Diffuse    : COLOR0;     // vertex diffuse color
	float2 TexCoord1  : TEXCOORD0;  // tex coords
};

VS_OUTPUT vertexMain(	float4 vPosition	: POSITION,
						float3 vNormal   	: NORMAL,
						float4 Color		: COLOR0,
						float2 texCoord     : TEXCOORD0 )
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

	Output.Diffuse = lerp(mAmbientData.y + (tmp.y*mAmbientData.y), (mAmbientData.y + mAmbientData.x) / 2, mAmbientData.z);

	Output.Diffuse.a = 1;
	
	Output.TexCoord1 = texCoord;
	
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

float4 pixelMain(float2 TexCoord : TEXCOORD0, float4 Diffuse : COLOR0) : COLOR0
{ 	
	float4 outColor = tex2D(tex0, TexCoord.xy) * Diffuse;

	return outColor;
}

