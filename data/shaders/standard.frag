#version 120

//----UNIFORMS----
uniform int TIME;

//Sun information
uniform vec3 SUN_DIRECTION;
uniform vec3 SUN_COLOUR;
uniform float SUN_AMBIANCE;

//Lights
uniform int LIGHT_NUMBER;

uniform vec3 LIGHT_POSITION[16];
uniform vec3 LIGHT_COLOUR[16];
uniform vec3 LIGHT_DIRECTION[16];

uniform int LIGHT_TYPE[16];
uniform float LIGHT_SPOT_ANGLE[16];
uniform float LIGHT_AMBIENCE[16];

//Matricies
uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;
uniform mat4 CAMERA_INVERSE_MATRIX;
uniform mat4 MODEL_MATRIX;

uniform vec3 MATERIAL_AMBIENT_COLOUR;
uniform vec3 MATERIAL_DIFFUSE_COLOUR;
uniform vec3 MATERIAL_SPECULAR_COLOUR;

uniform float MATERIAL_SMOOTHNESS;
uniform float MATERIAL_SHININESS;

uniform float MATERIAL_TRANSPARENCY;

//Textures
uniform sampler2D TEXTURE_TEXTURE;
uniform sampler2D NORMAL_TEXTURE;

//----INPUTS----
centroid varying vec4 F_W_POSITION;
centroid varying vec3 F_W_COLOUR;
centroid varying vec2 F_W_UV;
centroid varying vec4 F_W_NORMAL;
centroid varying vec4 F_M_POSITION;
centroid varying vec4 F_M_NORMAL;
invariant varying vec3 F_W_TANGENT;
invariant varying vec3 F_W_BITANGENT;

//----OUTPUTS----
//out vec4 COLOUR_BUFFER;
//layout (location = 1) out float DEPTH_BUFFER;

//----GLOBALS----
vec3 COLOUR = vec3(1.0, 1.0, 1.0);

vec3 W_NEW_POSITION;
vec3 W_NEW_NORMAL;

//Find the type of the light (0 = directional, 1 = point, 2 = spot)
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
	
	return getLightColour(light) * LIGHT_COLOUR[light] * MATERIAL_AMBIENT_COLOUR;
}

//Find the diffuse factor of the light
vec3 getLightDiffuse(int light)
{
	return getLightColour(light) * max(0.0, dot(-W_NEW_NORMAL, getLightVector(light))) * MATERIAL_DIFFUSE_COLOUR;
}

vec3 getLightSpecular(int light)
{
	float smoothness = MATERIAL_SMOOTHNESS;//MATERIAL_DATA[0];
	float shininess = MATERIAL_SHININESS;//MATERIAL_DATA[1];
	
	vec3 E = normalize((CAMERA_INVERSE_MATRIX * vec4(0.0, 0.0, 1.0, 0.0)).xyz);
	
	vec3 R = reflect(getLightVector(light), W_NEW_NORMAL);
	
	float specular = max(0.0, dot(E, R));
	
	specular = pow(specular, smoothness);
	
	return getLightColour(light) * specular * shininess * MATERIAL_SPECULAR_COLOUR;
}

vec4 getTextureValue()
{
	//No proper texture has been loaded in, so revert to colours
	//if (textureSize(TEXTURE_TEXTURE, 0) == ivec2(1, 1))
		//return vec4(1.0, 1.0, 1.0, 1.0);

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
	//if (textureSize(NORMAL_TEXTURE, 0) == ivec2(1, 1))
		//return vec3(0.0, 0.0, 1.0);

	if (F_W_UV == vec2(-1.0, -1.0)) //If there's no texture
		return vec3(0.0, 0.0, 1.0);
	else //It's got a texture!
		return normalize(texture2D(NORMAL_TEXTURE, clamp(F_W_UV, 0.0, 1.0)).rgb - 0.5);
}

vec3 applyNormalMapping(vec3 normal)
{
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

	//Set up the modified values
	W_NEW_POSITION = F_W_POSITION.xyz;
	
	if (gl_FrontFacing)
		W_NEW_NORMAL = normalize(F_W_NORMAL.xyz);
	else
		W_NEW_NORMAL = normalize(-F_W_NORMAL.xyz);
	
	//Apply normal mapping
	W_NEW_NORMAL = applyNormalMapping(W_NEW_NORMAL);

	//Loop through all the lights
	for (int light = -1; light < LIGHT_NUMBER; light ++)
	{
		if (getLightType(light) != -1) //Make sure that the light is in use
		{
			//Find the direction and colour of each light
			vec3 vector = getLightVector(light);

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
	gl_FragColor = vec4(COLOUR, getTextureValue().a * MATERIAL_TRANSPARENCY);
}
