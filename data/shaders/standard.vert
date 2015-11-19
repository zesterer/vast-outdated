#version 330 core

//----UNIFORMS----
uniform mat4  PERSPECTIVE_MATRIX;
uniform mat4  CAMERA_MATRIX;
uniform mat4 CAMERA_INVERSE_MATRIX;
uniform mat4  MODEL_MATRIX;

uniform uint TIME;

//----INPUTS----
in vec3 VERTEX_POS;
in vec3 VERTEX_COL;
in vec3 VERTEX_NORM;
in vec2 VERTEX_UV;

//----OUTPUTS----
smooth out vec4 F_W_POSITION;
smooth out vec3 F_W_COLOUR;
smooth out vec2 F_W_UV;
smooth out vec4 F_W_NORMAL;
smooth out vec4 F_M_POSITION;
smooth out vec4 F_M_NORMAL;

void main()
{
	F_W_POSITION = MODEL_MATRIX * vec4(VERTEX_POS, 1.0);
	F_M_POSITION = vec4(VERTEX_POS, 1.0);

	gl_Position = PERSPECTIVE_MATRIX * CAMERA_MATRIX * F_W_POSITION;
	gl_Position.z *= 1000.0;
	gl_Position.z = (gl_Position.z) / (1.0 - gl_Position.z);

	F_W_NORMAL = normalize(MODEL_MATRIX * vec4(VERTEX_NORM, 0.0));
	F_M_NORMAL = normalize(vec4(VERTEX_NORM, 0.0));

	F_W_COLOUR = VERTEX_COL;
	F_W_UV = VERTEX_UV;
}
