#version 120

//----UNIFORMS----
uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;
uniform mat4 CAMERA_INVERSE_MATRIX;
uniform mat4 MODEL_MATRIX;

uniform int TIME;

//----INPUTS----
attribute vec3 VERTEX_POS;
attribute vec3 VERTEX_COL;
attribute vec3 VERTEX_NORM;
attribute vec2 VERTEX_UV;
attribute vec3 VERTEX_TANGENT;
attribute vec3 VERTEX_BITANGENT;

//----OUTPUTS----
varying vec4 F_W_POSITION;
varying vec3 F_W_COLOUR;
varying vec2 F_W_UV;
varying vec4 F_W_NORMAL;
varying vec4 F_M_POSITION;
varying vec4 F_M_NORMAL;
invariant varying vec3 F_W_TANGENT;
invariant varying vec3 F_W_BITANGENT;

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
	
	F_W_TANGENT = normalize(MODEL_MATRIX * vec4(normalize(VERTEX_TANGENT), 0.0)).xyz;
	F_W_BITANGENT = normalize(MODEL_MATRIX * vec4(normalize(VERTEX_BITANGENT), 0.0)).xyz;
}
