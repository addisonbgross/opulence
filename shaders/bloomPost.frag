#version 130

uniform sampler2D frameTexture;

void main (void)
{
	gl_FragColor = texture2D(frameTexture, gl_TexCoord[0].st);
}