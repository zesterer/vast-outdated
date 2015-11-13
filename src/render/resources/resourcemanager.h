#ifndef VAST_RENDER_RESOURCES_RESOURCEMANAGER_H
#define VAST_RENDER_RESOURCES_RESOURCEMANAGER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "texture.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class ResourceManager
			{
				private:
					std::vector<Texture> textures;
				public:
					ResourceManager();
					void close();

					Texture& newTexture();
					Texture& newTextureFromFile(std::string filename);
			};
		}
	}
}

#endif
