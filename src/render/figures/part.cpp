//----LOCAL----
#include "part.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			Part::Part()
			{
				//Constructor
			}

			void Part::setMesh(Resources::Mesh* mesh)
			{
				this->mesh = mesh;
			}

			void Part::setTexture(Resources::Texture* texture)
			{
				this->texture = texture;
			}

			void Part::setBumpMap(Resources::Texture* bump_map)
			{
				this->bump_map = bump_map;
			}

			void Part::setNormalMap(Resources::Texture* normal_map)
			{
				this->normal_map = normal_map;
			}

			void Part::setMaterial(Resources::Material* material)
			{
				this->material = material;
			}
		}
	}
}
