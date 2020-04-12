//terrain
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform vec3 mSunPos;         	// Sun light position
uniform vec3 mAmbientData;	// Sun light parameters
varying vec3 varVert;
varying vec3 normal;

void main(void)
{
    vec4 splat = texture2D(tex0, vec2(gl_TexCoord[1]));
    vec4 col = texture2D(tex1, vec2(gl_TexCoord[0]));
	
	col = 
		((((((col*(1-splat.r)) + texture2D(tex2, vec2(gl_TexCoord[0])) * splat.r)
		* (1-splat.g)) + texture2D(tex3, vec2(gl_TexCoord[0])) * splat.g)
		* (1-splat.b)) + texture2D(tex4, vec2(gl_TexCoord[0])) * splat.b);		
	
	// More efficient as a one-liner
	float fogFactor = clamp(exp2( -gl_Fog.density*length(varVert.xyz)*1.442695 ), 0.0, 1.0);

    gl_FragColor = vec4(mix(gl_Fog.color.rgb,col.rgb*(mAmbientData.x*0.95+max(dot(normalize(normal),normalize(mSunPos)),0.0)*0.5*(1.0-splat.a)),fogFactor), 1.0);
}
