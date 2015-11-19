#version 330

smooth in vec2 UV;

out vec4 COLOUR_BUFFER;

uniform sampler2D COLOUR_TEXTURE;
uniform sampler2D DEPTH_TEXTURE;

uniform uint TIME;

//----GLOBALS----
vec3 COLOUR;

float getRandom(vec4 pos)
{
	float val = fract(sin(37.17 * dot(mod(pos * 3733.7, 177.31), vec4(3.1415, 2.9898, 8.233, 5.327))));
	return val;
}

float getNoise(vec4 pos, float octave)
{
	pos *= pow(2.0, octave);
	vec3 mpos = mod(pos.xyz, 1.0);
	pos = floor(pos);

	float c000 = getRandom(pos + vec4(0.0, 0.0, 0.0, 0.0));
	float c100 = getRandom(pos + vec4(1.0, 0.0, 0.0, 0.0));
	float c010 = getRandom(pos + vec4(0.0, 1.0, 0.0, 0.0));
	float c110 = getRandom(pos + vec4(1.0, 1.0, 0.0, 0.0));

	float c001 = getRandom(pos + vec4(0.0, 0.0, 1.0, 0.0));
	float c101 = getRandom(pos + vec4(1.0, 0.0, 1.0, 0.0));
	float c011 = getRandom(pos + vec4(0.0, 1.0, 1.0, 0.0));
	float c111 = getRandom(pos + vec4(1.0, 1.0, 1.0, 0.0));

	float eX00 = mix(c000, c100, mpos.x);
	float eX10 = mix(c010, c110, mpos.x);
	float eX01 = mix(c001, c101, mpos.x);
	float eX11 = mix(c011, c111, mpos.x);

	float fXX0 = mix(eX00, eX10, mpos.y);
	float fXX1 = mix(eX01, eX11, mpos.y);

	float value = mix(fXX0, fXX1, mpos.z);

	return 2.0 * (value - 0.5);
}

float getPerlin(vec4 pos, float initial, float octaves, float skip)
{
	float val = 0.0;

	for (float x = initial; x < initial + octaves; x += skip)
		val += getNoise(pos, x + 2.0) / pow(2.0, x - initial);

	return val;
}

float getDepthAt(vec2 UV)
{
	return texture2D(DEPTH_TEXTURE, clamp(1.0 + UV, 0.0, 2.0) / 2.0).r;
}

vec3 getTextureAt(vec2 UV)
{
	return texture2D(COLOUR_TEXTURE, clamp(1.0 + UV, 0.0, 2.0) / 2.0).rgb;
}

void main()
{
	vec2 pos = clamp(vec2(1.0, 1.0) + UV, 0.0, 2.0) / 2.0;

	COLOUR = getTextureAt(UV);
	
	//Toon Shading
	//COLOUR = floor(COLOUR * 6.0) / 6.0;

	COLOUR = mix(vec3(0.0, 0.0, 0.0), COLOUR, min(1, 1.8 - length(UV)));
	//Faded corners

	COLOUR_BUFFER = vec4(COLOUR, 1.0);
}
