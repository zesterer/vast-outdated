#version 130

//----INPUTS----
in highp vec3 VERTEX_POS;

//----OUTPUTS----
smooth out highp vec2 UV;

void main()
{
	gl_Position = vec4(VERTEX_POS, 1.0);
	UV = VERTEX_POS.xy;
}
