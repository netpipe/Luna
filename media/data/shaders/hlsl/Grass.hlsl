//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 mWorldViewProj;
float4x4 mTransWorld;
float3 mCameraPos;
float3 mGrassWave;

// Vertex shader output structure
struct VS_OUTPUT
{
	float4 Position	: POSITION;   // vertex position 
	float4 Diffuse	: COLOR0;     // vertex diffuse color
	float3 TexCoord	: TEXCOORD0;  // tex coords
};

VS_OUTPUT vertexMain(	float4 vPosition 	: POSITION,
						float3 vNormal   	: NORMAL,
						float4 Color		: COLOR0,
						float2 texCoord  	: TEXCOORD0)
{
	VS_OUTPUT Output;

	float3 worldPos = mul(mTransWorld, vPosition);
	float dist = distance(mCameraPos, worldPos);
	Output.TexCoord.z = dist;

	if(dist <= 200 && texCoord.y <= 0.85) 
	{
		vPosition.x += mGrassWave.x;
		vPosition.z += mGrassWave.y;
		vPosition.y += mGrassWave.x / 5;
	}
	Output.Position = mul(vPosition, mWorldViewProj);

	Output.Diffuse.rgb = Color.rgb;
	Output.Diffuse.a = mGrassWave.z;

	Output.TexCoord.xy = texCoord;
	
	return Output;
}

sampler2D tex0 : register(s0);

struct PSInput
{
	float4 Diffuse : COLOR0;
	float3 TexCoord : TEXCOORD0;
};

float4 pixelMain(in PSInput input) : COLOR0
{ 	
	if(input.TexCoord.z > 200) discard;

	float4 outputColor = tex2D(tex0, input.TexCoord.xy);
	outputColor.rgb *= (float3(1,1,1) - (input.Diffuse.a * float3(0.9, 0.9, 0.9)));

	return outputColor;
}

