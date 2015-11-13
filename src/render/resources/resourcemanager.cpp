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

			Texture& ResourceManager::newTexture()
			{
				this->textures.emplace_back();
				return this->textures.back();
			}

			Texture& ResourceManager::newTextureFromFile(std::string filename)
			{
				this->textures.emplace_back(filename);
				return this->textures.back();
			}
		}
	}
}
