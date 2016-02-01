#version 120

smooth in vec2 UV;

out vec4 COLOUR_BUFFER;

uniform sampler2D COLOUR_TEXTURE;
//uniform sampler2D DEPTH_TEXTURE;

//----GLOBALS----
vec3 COLOUR;

vec3 getTextureAt(vec2 UV)
{
	return texture2D(COLOUR_TEXTURE, clamp(1.0 + UV, 0.0, 2.0) / 2.0).rgb;
}

void main()
{
	//vec2 pos = clamp(vec2(1.0, 1.0) + UV, 0.0, 2.0) / 2.0;

	//COLOUR = getTextureAt(UV);
	
	//Faded corners
	//COLOUR = mix(vec3(0.0, 0.0, 0.0), COLOUR, min(1, 1.8 - length(UV)));

	//COLOUR_BUFFER = vec4(COLOUR, 1.0);
	COLOUR_BUFFER = vec4(vec3(0.0, 0.0, 0.0), 1.0);
}
