#ifndef VAST_RENDER_RESOURCES_PART_H
#define VAST_RENDER_RESOURCES_PART_H

//----LOCAL----
#include "common/state.h"
#include "resources/mesh.h"
#include "resources/texture.h"
#include "resources/material.h"
#include "resources/shader.h"
#include "renderable.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			class Part : public Renderable
			{
				private:
					State state;

					Resources::Mesh* mesh = nullptr;
					Resources::Texture* texture = nullptr;
					Resources::Texture* bump_map = nullptr;
					Resources::Texture* normal_map = nullptr;
					Resources::Material* material = nullptr;
					Resources::Shader* shader = nullptr;
				public:
					Part();

					void setMesh(Resources::Mesh* mesh);
					void setTexture(Resources::Texture* texture);
					void setBumpMap(Resources::Texture* bump_map);
					void setNormalMap(Resources::Texture* normal_map);
					void setMaterial(Resources::Material* material);
					void setShader(Resources::Shader* shader);

					Resources::Mesh& getMesh();
					Resources::Texture& getTexture();
					Resources::Texture& getBumpMap();
					Resources::Texture& getNormalMap();
					Resources::Material& getMaterial();
					Resources::Shader& getShader();

					void bufferAll();
			};
		}
	}
}

#endif
