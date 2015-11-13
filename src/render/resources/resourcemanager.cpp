//----LOCAL----
#include "resourcemanager.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			ResourceManager::ResourceManager()
			{
				IO::output("Created resource manager");
			}

			void ResourceManager::close()
			{
				IO::output("Closing resource manager");

				this->meshes.clear();
				this->textures.clear();
				this->materials.clear();
			}

			//Create a new mesh and load it into the resource manager
			Mesh& ResourceManager::newMesh()
			{
				this->meshes.emplace_back();
				return this->meshes.back();
			}

			//Create a new mesh from a given file and load it into the resource manager
			Mesh& ResourceManager::newMeshFromFile(std::string filename)
			{
				this->meshes.emplace_back(filename);
				return this->meshes.back();
			}

			//Create a new texture and load it into the resource manager
			Texture& ResourceManager::newTexture()
			{
				this->textures.emplace_back();
				return this->textures.back();
			}

			//Create a new texture with the given parameters and load it into the resource manager
			Texture& ResourceManager::newTextureFromBlank(uint16 width, uint16 height, const uint8* pixels)
			{
				this->textures.emplace_back(width, height, pixels);
				return this->textures.back();
			}

			//Create a new texture from a given file and load it into the resource manager
			Texture& ResourceManager::newTextureFromFile(std::string filename)
			{
				this->textures.emplace_back(filename);
				return this->textures.back();
			}

			//Create a new material and load it into the resource manager
			Material& ResourceManager::newMaterial()
			{
				this->materials.emplace_back();
				return this->materials.back();
			}

			Shader& ResourceManager::newShader()
			{
				this->shaders.emplace_back();
				return this->shaders.back();
			}

			Shader& ResourceManager::newShaderFromStrings(std::string vertex_shader_string, std::string fragment_shader_string)
			{
				this->shaders.emplace_back();
				this->shaders.back().loadFromStrings(vertex_shader_string, fragment_shader_string);
				return this->shaders.back();
			}

			Shader& ResourceManager::newShaderFromFiles(std::string vertex_shader_filename, std::string fragment_shader_filename)
			{
				this->shaders.emplace_back();
				this->shaders.back().loadFromFiles(vertex_shader_filename, fragment_shader_filename);
				return this->shaders.back();
			}
		}
	}
}
