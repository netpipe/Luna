float3 fvLightPosition;
float3 fvEyePosition;

float4x4 matWorld;
float4x4 matWorldViewProjection;
float4x4 matWorldInverse;

struct VS_INPUT
{
   float4 Position  : POSITION;
   float2 Texcoord1 : TEXCOORD0;
   float3 Normal    : NORMAL;
};

struct VS_OUTPUT
{
   float4 Position         :  POSITION;
   float2 Texcoord1        :  TEXCOORD0;
   float3 ViewDirection    :  TEXCOORD1;
   float3 LightDirection   :  TEXCOORD2;
   float  z                :  TEXCOORD3;
};

VS_OUTPUT vertexMain( in VS_INPUT IN )
{
   VS_OUTPUT OUT;
   OUT.Position  = mul( IN.Position , matWorldViewProjection );
   OUT.Texcoord1 = IN.Texcoord1;
   OUT.z = OUT.Position.z;

   float3 RealPos = mul( IN.Position , matWorld);

   float3 viewVec  = fvEyePosition - RealPos;
   float3 lightVec = fvLightPosition - RealPos;

   float3 tViewVec;
   float3 tLightVec;

   float3 ONormal   = mul(matWorldInverse,IN.Normal);
   float3 OTangent  = float3(abs(ONormal.y) + abs(ONormal.z), abs(ONormal.x), 0);
   float3 OBinormal = cross(OTangent,ONormal);

   OTangent = normalize( OTangent);
   ONormal  = normalize( ONormal);
   OTangent = normalize( OTangent );

   float3 RTangent  = mul( matWorldInverse , OTangent );
   float3 RBinormal = mul( matWorldInverse , OBinormal );
   float3 RNormal   = mul( matWorldInverse , ONormal );

   tViewVec.x = dot(viewVec,RTangent);
   tViewVec.y = dot(viewVec,RBinormal);
   tViewVec.z = dot(viewVec,RNormal);

   tLightVec.x = dot(lightVec,RTangent);
   tLightVec.y = dot(lightVec,RBinormal);
   tLightVec.z = dot(lightVec,RNormal);

   OUT.ViewDirection = tViewVec;
   OUT.LightDirection = tLightVec;

   return( OUT ); 
}




float  fSpecularPower;

float4 fvDiffuseColor;
float4 fvSpecularColor;
float4 fvAmbientColor;

sampler2D baseMap;
sampler2D bumpMap;
sampler2D specMap;

struct PS_INPUT
{
   float2 Texcoord1      : TEXCOORD0;
   float3 ViewDirection  : TEXCOORD1;
   float3 LightDirection : TEXCOORD2;
   float  z              : TEXCOORD3;
};

float4 pixelMain( in PS_INPUT IN ) : COLOR0
{

      float4 Color;

      float3 fvLightDirection = normalize( IN.LightDirection );

      // Diffuse

      float4 baseColor    = tex2D(baseMap,IN.Texcoord1);
      float4 diffuseColor = fvDiffuseColor * baseColor;
      float4 ambientColor = fvAmbientColor * baseColor;

      // BumpMap

      float3 fvNormal = normalize( ( tex2D( bumpMap, IN.Texcoord1 ).xyz * 2.0f ) - 1.0f );
      float fBumpMap = dot( fvNormal, fvLightDirection );

      // SpecularMap

      float3 fvReflection     = normalize( ( ( 2.0f * fvNormal ) * ( fBumpMap ) ) - fvLightDirection );
      float3 fvViewDirection  = normalize( IN.ViewDirection );
      float  fRDotV           = max( 0.0f, dot( fvReflection, fvViewDirection ) );
      float4 Specular         = fvSpecularColor * pow( fRDotV, fSpecularPower ) * tex2D( specMap, IN.Texcoord1 );

      // Final color

      Color = ( diffuseColor * fBumpMap ) + ambientColor + Specular;

      return ( Color );
} 