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

				this->textures.clear();
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
		}
	}
}
