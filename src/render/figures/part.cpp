//----LOCAL----
#include "part.h"
#include "figure.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			Part::Part(Figure* parent)
			{
				this->parent = parent;
			}
			
			State& Part::getState()
			{
				return this->state;
			}
			
			Figure& Part::getParent()
			{
				return *this->parent;
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

			void Part::setShader(Resources::Shader* shader)
			{
				this->shader = shader;
			}

			Resources::Mesh& Part::getMesh()
			{
				return *this->mesh;
			}

			Resources::Texture& Part::getTexture()
			{
				return *this->texture;
			}

			Resources::Texture& Part::getBumpMap()
			{
				return *this->bump_map;
			}

			Resources::Texture& Part::getNormalMap()
			{
				return *this->normal_map;
			}

			Resources::Material& Part::getMaterial()
			{
				return *this->material;
			}

			Resources::Shader& Part::getShader()
			{
				return *this->shader;
			}

			void Part::bufferAll()
			{
				if (this->mesh != nullptr)
					this->mesh->buffer();

				if (this->texture != nullptr)
					this->texture->buffer();

				if (this->bump_map != nullptr)
					this->bump_map->buffer();

				if (this->normal_map != nullptr)
					this->normal_map->buffer();
			}
		}
	}
}
