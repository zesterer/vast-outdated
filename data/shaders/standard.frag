#version 330

//----UNIFORMS----
uniform highp uint TIME;

uniform lowp mat4 PERSPECTIVE_MATRIX;
uniform lowp mat4 CAMERA_MATRIX;
uniform lowp mat4 MODEL_MATRIX;

uniform lowp vec4 LIGHT_VECTOR[16];
uniform lowp vec4 LIGHT_COLOUR[16];

uniform lowp vec4 MATERIAL_DATA;
uniform int MATERIAL_EFFECTS;

uniform sampler2D TEXTURE_SAMPLER;

//----INPUTS----
smooth in highp vec4 FRAG_M_POS;
smooth in highp vec4 FRAG_POS;
smooth in lowp vec3 FRAG_COL;
smooth in mediump vec2 FRAG_UV;
smooth in lowp vec4 FRAG_NORM;

//----OUTPUTS----
out lowp vec3 COLOUR;
//out       lowp    vec3      FRAMEBUFFER_COLOR;

//----GLOBALS----
          lowp    vec4      MOD_NORM;

float getSpecular(vec4 vector)
{
	lowp float specular_shininess = MATERIAL_DATA[0];
	lowp float specular_amount = MATERIAL_DATA[1];
	lowp float specular_cap = MATERIAL_DATA[2];

	vec4 cam_normal = CAMERA_MATRIX * MODEL_MATRIX * MOD_NORM;

	lowp vec3 N = normalize((cam_normal).xyz);
	lowp vec3 L = normalize((CAMERA_MATRIX * vector).xyz);
	lowp vec3 R = normalize(2.0 * N * dot(N, L) - L);
	lowp vec3 V = normalize(FRAG_POS.xyz / 2.0);

	lowp float specular = (dot(R, V) - (1.0 - specular_amount)) * 1.0 / specular_amount;
	specular = min(specular_cap, pow(max(0.0, specular), max(0.00001, specular_shininess)) * specular_shininess * 0.2);
	return specular;
}

float getDiffuse(vec4 vector, float ambiance)
{
	return min(1.0, max(ambiance, dot(normalize(MODEL_MATRIX * MOD_NORM).xyz, -normalize(vector.xyz))));
}

vec3 getTexture()
{
	return mix(vec3(0.7, 0.35, 0.05), vec3(0.0, 1.0, 0.0), dot((normalize(MODEL_MATRIX * MOD_NORM)).xyz, vec3(0.0, 0.0, 1.0)));

	/*//No proper texture has been loaded in, so revert to colours
	if (textureSize(TEXTURE_SAMPLER, 0) == ivec2(1, 1))
		return FRAG_COL;

	if (FRAG_UV == vec2(-1.0, -1.0)) //If there's no texture
		return FRAG_COL;
	else //It's got a texture!
		return FRAG_COL * texture2DProjLod(TEXTURE_SAMPLER, vec3(FRAG_UV, 1.0), 0.0).rgb;*/
}

vec4 getVector(vec4 vector)
{
	if (vector.w == 1.0) //It's a point light
		return normalize(vec4((MODEL_MATRIX * FRAG_M_POS).xyz - vector.xyz, 0.0));
	else //It's a directional light
		return normalize(vector);
}

bool getEffect(int x)
{
	return true;
	if (int(MATERIAL_EFFECTS / pow(2, x)) % 2 == 1)
		return true;
	return false;
}

void main()
{
	//Initialise the specular and diffuse
	lowp vec3 specular = vec3(0.0, 0.0, 0.0);
	lowp vec3 diffuse  = vec3(0.0, 0.0, 0.0);

	//Initialise the normal
	MOD_NORM = normalize(FRAG_NORM);

	//Loop through all the lights
	/*for (int count = 0; count < 16; count ++)
	{
		//Find the direction and colour of each light
		vec4 vector = getVector(LIGHT_VECTOR[count]);
		vec4 colour = LIGHT_COLOUR[count];

		if (colour.xyz != vec3(0.0, 0.0, 0.0)) //If the light is actually a light
		{
			float multiplier = 1.0;

			if (vector.w == 1.0) //Decrease brightness with distance
			{
				multiplier = min(1.0, 5.0 / pow(distance((MODEL_MATRIX * FRAG_M_POS).xyz, LIGHT_VECTOR[count].xyz), 1.5));

				//Spotlight - WIP
				//multiplier *= pow(1.05 * dot(normalize(vec3(1.0, 0.9, -2.5)), vector.xyz), 5.0);
			}

			//Add the light to the existing lighting conditions
			specular += colour.xyz * getSpecular(vector) * multiplier; //Find the specular component
			diffuse  += colour.xyz * getDiffuse(vector, colour.w) * multiplier; //Find the diffuse component
		}
	}*/

	//Cel-shading
	/*if (getEffect(0))
	{
		diffuse  = floor(diffuse * 4.0) / 4.0;
		specular = floor(specular * 2.0) / 2.0;
	}*/

	COLOUR = getTexture() * diffuse + specular;
	COLOUR = vec3(1.0, 0.0, 0.0);
}
