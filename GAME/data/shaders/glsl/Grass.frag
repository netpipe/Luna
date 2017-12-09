// s
uniform sampler2D tex0;
uniform vec3 mAmbientData;
uniform sampler2D shadowMap;

void main()
{
	vec4 Color = texture2D(tex0, gl_TexCoord[0].xy);

	if (Color.a<0.35) discard;

	gl_FragColor = vec4(mix(gl_Fog.color.rgb, Color.rgb * (gl_FrontMaterial.ambient*mAmbientData.x+(1.0-texture2D(shadowMap,gl_TexCoord[0].zw).a)*gl_Color.x*gl_FrontMaterial.diffuse), gl_Color.a), 1.0);
}
