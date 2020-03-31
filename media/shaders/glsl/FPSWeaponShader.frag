uniform sampler2D tex0;
uniform sampler2D tex1;
varying vec3 normal;
uniform vec3 mSunPos;         // Sun light position
varying vec3 vertex;
uniform float shadow;

float specMap(vec3 tmp) {
	return pow(length(tmp),2.5);
}

void main(void)
{
	vec3 msun = normalize(mSunPos);
	vec3 nmal = normalize(normal);
	float tmp2 = max(0.0,dot(msun, nmal));
	vec3 R = reflect(normalize(vertex),nmal);
	
	float mix_val = gl_LightModel.ambient*gl_FrontMaterial.ambient + tmp2*shadow*gl_FrontMaterial.diffuse;
	vec4 color = texture2D(tex0, gl_TexCoord[0]);
	gl_FragColor = color*mix_val+pow(max(dot(R,msun),0.0),gl_FrontMaterial.shininess)*shadow*gl_FrontMaterial.specular*specMap(color.xyz);
}
