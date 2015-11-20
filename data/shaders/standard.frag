#version 330

//----UNIFORMS----
uniform uint TIME;

uniform int RESOURCE_INFO;

//Sun information
uniform vec3 SUN_DIRECTION;
uniform vec3 SUN_COLOUR;
uniform float SUN_AMBIANCE;

//Matricies
uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;
uniform mat4 CAMERA_INVERSE_MATRIX;
uniform mat4 MODEL_MATRIX;

uniform vec3 LIGHT_POSITION[16];
uniform vec3 LIGHT_COLOUR[16];
uniform vec3 LIGHT_DIRECTION[16];

uniform int LIGHT_TYPE[16];
uniform float LIGHT_SPOT_ANGLE[16];
uniform float LIGHT_AMBIENCE[16];

//uniform vec4 MATERIAL_DATA;
//uniform int MATERIAL_EFFECTS;

//Textures

uniform sampler2D TEXTURE_TEXTURE;
uniform sampler2D NORMAL_TEXTURE;

//----INPUTS----
smooth in vec4 F_W_POSITION;
smooth in vec3 F_W_COLOUR;
smooth in vec2 F_W_UV;
smooth in vec4 F_W_NORMAL;
smooth in vec4 F_M_POSITION;
smooth in vec4 F_M_NORMAL;
flat in vec3 F_W_TANGENT;
flat in vec3 F_W_BITANGENT;

//----OUTPUTS----
layout (location = 0) out vec4 COLOUR_BUFFER;
//layout (location = 1) out float DEPTH_BUFFER;

//----GLOBALS----
vec3 COLOUR = vec3(1.0, 1.0, 1.0);

vec3 W_NEW_POSITION;
vec3 W_NEW_NORMAL;

//Find out which resources are loaded
bool getResourceInfo(int id)
{
	if (int(RESOURCE_INFO / pow(2, id)) % 2 == 1)
		return true;
	return false;
}

//Find the type of the light
int getLightType(int light)
{
	if (light == -1)
		return 0;
	
	return LIGHT_TYPE[light];
}

//Find the vector of the light
vec3 getLightVector(int light)
{
	if (light == -1)
		return SUN_DIRECTION;
	
	if (getLightType(light) == 1) //It's a point light
		return normalize(W_NEW_POSITION - LIGHT_POSITION[light]);
	else //It's a directional light
		return normalize(LIGHT_DIRECTION[light]);
}

//Find the distance to the light
float getLightDistance(int light)
{
	return distance(W_NEW_POSITION, LIGHT_POSITION[light]);
}

//Find the colour of the light
vec3 getLightColour(int light)
{
	if (light == -1)
		return SUN_COLOUR;
	
	return LIGHT_COLOUR[light];
}

//Find the ambiance factor of the light
vec3 getLightAmbiance(int light)
{
	if (light == -1)
		return SUN_COLOUR * SUN_AMBIANCE;
	
	return getLightColour(light) * LIGHT_COLOUR[light];
}

//Find the diffuse factor of the light
vec3 getLightDiffuse(int light)
{
	return getLightColour(light) * max(0.0, dot(-W_NEW_NORMAL, getLightVector(light)));
}

vec3 getLightSpecular(int light)
{
	float smoothness = 2.0;//MATERIAL_DATA[0];
	float shininess = 0.5;//MATERIAL_DATA[1];
	
	vec3 E = normalize((CAMERA_INVERSE_MATRIX * vec4(0.0, 0.0, 1.0, 0.0)).xyz);
	
	vec3 R = reflect(getLightVector(light), W_NEW_NORMAL);
	
	float specular = max(0.0, dot(E, R));
	
	specular = pow(specular, smoothness);
	
	return getLightColour(light) * specular * shininess;
}

vec4 getTextureValue()
{
	if (!getResourceInfo(1))
		return vec4(1.0, 1.0, 1.0, 1.0);
		
	//No proper texture has been loaded in, so revert to colours
	if (textureSize(TEXTURE_TEXTURE, 0) == ivec2(1, 1))
		return vec4(1.0, 1.0, 1.0, 1.0);

	if (F_W_UV == vec2(-1.0, -1.0)) //If there's no texture
		return vec4(1.0, 1.0, 1.0, 1.0);
	else //It's got a texture!
		return vec4(F_W_COLOUR, 1.0) * texture2D(TEXTURE_TEXTURE, F_W_UV).rgba;
}

vec3 getTextureColour()
{
	return F_W_COLOUR * getTextureValue().rgb;
}

vec3 getNormalMapVector()
{
	//No normal map texture has been loaded in, so revert to default
	if (textureSize(NORMAL_TEXTURE, 0) == ivec2(1, 1))
		return vec3(0.0, 0.0, 0.0);

	if (F_W_UV == vec2(-1.0, -1.0)) //If there's no texture
		return vec3(0.0, 0.0, 0.0);
	else //It's got a texture!
		return normalize(texture2D(NORMAL_TEXTURE, F_W_UV).rgb - 0.5);
}

vec3 applyNormalMapping(vec3 normal)
{
	if (!getResourceInfo(3))
		return normal;
	
	vec3 map_vector = getNormalMapVector();
	
	if (map_vector != vec3(0.0, 0.0, 0.0));
	{
		normal = normalize(-F_W_TANGENT * map_vector.x - F_W_BITANGENT * map_vector.y + normal * map_vector.z);
	}
	
	return normal;
}

void main()
{
	//Initialise the specular and diffuse
	vec3 ambiance = vec3(0.0);
	vec3 diffuse  = vec3(0.0);
	vec3 specular = vec3(0.0);
	
	//LIGHT_VECTOR[0] = vec4(12.0, 6.0, -8.5, 1.0);
	//LIGHT_COLOUR[0] = vec4(1.3, 1.2, 1.0, 0.3);

	//Set up the modified values
	W_NEW_POSITION = F_W_POSITION.xyz;
	W_NEW_NORMAL = normalize(F_W_NORMAL.xyz);
	
	//Apply normal mapping
	W_NEW_NORMAL = applyNormalMapping(W_NEW_NORMAL);

	//Loop through all the lights
	for (int light = -1; light < 16; light ++)
	{
		//Find the direction and colour of each light
		vec3 vector = getLightVector(light);

		if (getLightColour(light) != vec3(0.0, 0.0, 0.0)) //If the light is actually a light
		{
			float multiplier = 1.0;

			if (getLightType(light) == 1) //Decrease brightness with distance
			{
				multiplier = min(1.0, 10.0 / pow(getLightDistance(light), 2.0));
			}

			specular += getLightSpecular(light) * multiplier;
			ambiance += getLightAmbiance(light) * multiplier;
			diffuse += getLightDiffuse(light) * multiplier;
		}
	}

	//Combine colours with light
	COLOUR = getTextureColour() * (ambiance + diffuse + specular);
	
	//Apply transparency (if there is any)
	COLOUR_BUFFER = vec4(COLOUR, getTextureValue().a);
}
