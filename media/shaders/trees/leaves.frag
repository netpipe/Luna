uniform sampler2D Texture;

varying vec4 Color;

void main()
{
	gl_FragColor = texture2D( Texture, gl_TexCoord[0].xy ) * Color;
}