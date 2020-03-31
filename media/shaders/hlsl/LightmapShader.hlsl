float4x4 mWorldViewProj;  	// World * View * Projection transformation
float3 mAmbientData;

struct VS_OUTPUT
{
	float4 Position   	: POSITION;   // vertex position 
	float4 Diffuse    	: COLOR0;     // vertex diffuse color
	float4 TexCoord1	: TEXCOORD0;
	float2 TexCoord2	: TEXCOORD1;
};

VS_OUTPUT vertexMain(	in float4 vPosition		: POSITION,
						in float3 vNormal   	: NORMAL,
						in float4 Color			: COLOR0,
						in float2 texCoord1     : TEXCOORD0,
						in float2 texCoord2     : TEXCOORD1)
{
	VS_OUTPUT Output;

	Output.Position = mul(vPosition, mWorldViewProj);

	// transform normal 
	//float3 normal = normalize(mul(vNormal, mInvWorld));
	
	// calculate light color 
	//float3 tmp = dot(-normalize(mul(mTransWorld, vPosition) - mLightPos), normal);
	//tmp = lit(tmp.x, tmp.y, 1);

	Output.Diffuse = Color * (mAmbientData.y*2.5); //(mAmbientData.y*1.75 + (0.50*tmp.y*mAmbientData.y));
	
	Output.TexCoord1 = texCoord1;
	Output.TexCoord2 = texCoord2;
	
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

float4 pixelMain(in float2 TexCoord1 : TEXCOORD0, in float2 TexCoord2 : TEXCOORD1, in float4 Diffuse : COLOR0) : COLOR0
{ 	
	float3 outColor = tex2D(tex0, TexCoord1).rgb;
	float3 lightmapColor = tex2D(tex1, TexCoord2).rgb;
	
	return float4(outColor * lightmapColor * Diffuse.rgb, 1);
}

