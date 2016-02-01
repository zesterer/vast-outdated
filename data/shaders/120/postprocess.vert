#version 120

//----INPUTS----
attribute vec3 VERTEX_POS;

//----OUTPUTS----
varying vec2 UV;

void main()
{
	gl_Position = vec4(VERTEX_POS, 1.0);
	UV = VERTEX_POS.xy;
}
