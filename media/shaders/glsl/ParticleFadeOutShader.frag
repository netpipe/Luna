uniform sampler2D tex0;
uniform float alphaValue;
varying vec3 varVert;

void main(void)
{
	float fogFactor = clamp(exp2( -gl_Fog.density*length(varVert.xyz)*1.442695 ), 0.0, 1.0);

	vec4 color = texture2D(tex0, gl_TexCoord[0]);

	gl_FragColor.rgb = mix(gl_Fog.color.rgb,color.rgb,fogFactor);
	gl_FragColor.a = color.a*alphaValue;
}
