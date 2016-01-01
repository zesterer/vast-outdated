#ifndef VAST_RENDER_RESOURCES_RESOURCEMANAGER_H
#define VAST_RENDER_RESOURCES_RESOURCEMANAGER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "texture.h"
#include "mesh.h"
#include "material.h"
#include "shader.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class ResourceManager
			{
				private:
					std::vector<Mesh*> meshes;
					std::vector<Texture*> textures;
					std::vector<Material*> materials;
					std::vector<Shader*> shaders;
					
					Mesh* default_mesh = nullptr;
					Texture* default_texture = nullptr;
					Material* default_material = nullptr;
					Shader* default_shader = nullptr;
				public:
					ResourceManager();
					virtual ~ResourceManager();
					void initiate();
					void close();

					Mesh& newMesh();
					Mesh& newMeshFromFile(std::string filename);
					
					Mesh& getMesh(int32 id);

					Texture& newTexture();
					Texture& newTextureFromBlank(uint16 width, uint16 height, const uint8* pixels = nullptr);
					Texture& newTextureFromFile(std::string filename, unsigned char flip_flags = 0b00000010);
					
					Texture& getTexture(int32 id);

					Material& newMaterial();
					
					Material& getMaterial(int32 id);

					Shader& newShader();
					Shader& newShaderFromStrings(std::string vertex_shader_code, std::string fragment_shader_code);
					Shader& newShaderFromFiles(std::string vertex_shader_filename, std::string fragment_shader_filename);
					
					Shader& getShader(int32 id);
			};
		}
	}
}

#endif
