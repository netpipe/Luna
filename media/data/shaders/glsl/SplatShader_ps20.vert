varying vec3 varVert;
varying vec3 normal;

void main(void)
{
	gl_Position = ftransform();
	varVert = gl_Position.xyz;
	normal = gl_NormalMatrix*normalize(gl_Normal);
	
	gl_TexCoord[0] = gl_MultiTexCoord0 * 32.0;
	gl_TexCoord[1] = gl_MultiTexCoord0;	
}
