varying vec3 varVert;

void main(void)
{
	gl_Position = ftransform();

	varVert = gl_Position.xyz;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;	
}
