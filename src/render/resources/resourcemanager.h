#ifndef VAST_RENDER_RESOURCES_RESOURCEMANAGER_H
#define VAST_RENDER_RESOURCES_RESOURCEMANAGER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "texture.h"
#include "mesh.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class ResourceManager
			{
				private:
					std::vector<Mesh> meshes;
					std::vector<Texture> textures;
				public:
					ResourceManager();
					void close();

					Mesh& newMesh();
					Mesh& newMeshFromFile(std::string filename);

					Texture& newTexture();
					Texture& newTextureFromBlank(uint16 width, uint16 height, const uint8* pixels = nullptr);
					Texture& newTextureFromFile(std::string filename);
			};
		}
	}
}

#endif
