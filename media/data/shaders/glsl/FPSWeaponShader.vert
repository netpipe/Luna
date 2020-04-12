varying vec3 normal;
varying vec3 vertex;

void main(void)
{
	gl_Position = ftransform();

	vertex = gl_ModelViewMatrix*gl_Vertex;
	
	normal = gl_NormalMatrix*gl_Normal;

	gl_TexCoord[0] = gl_MultiTexCoord0;
}
