//----LOCAL----
#include "texture.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			Texture::Texture()
			{
				//Constructor
			}

			//Construct a texture with a given width and height, optionally from pixel data.
			Texture::Texture(uint16 width, uint16 height, const uint8* pixels)
			{
				this->create(width, height, pixels);
			}

			//Create a texture with a given width and height, optionally from pixel data.
			void Texture::create(uint16 width, uint16 height, const uint8* pixels)
			{
				this->internal_image.create(width, height, pixels);
			}

			//Construct a texture from the data contained within a given file
			Texture::Texture(std::string filename)
			{
				this->loadFromFile(filename);
			}

			//Create a texture from the data contained within a given file
			bool Texture::loadFromFile(std::string filename)
			{
				return this->internal_image.loadFromFile(filename);
			}

			//Find the size of the texture
			sf::Vector2u Texture::getSize()
			{
				return this->internal_image.getSize();
			}
		}
	}
}
