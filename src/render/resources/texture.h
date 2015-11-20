#ifndef VAST_RENDER_RESOURCES_TEXTURE_H
#define VAST_RENDER_RESOURCES_TEXTURE_H

//----LIBRARY----
#include "SFML/Graphics.hpp"

//----LOCAL----
#include "render/bufferable.h"
#include "common/generics.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Shader;
			
			class Texture : public Bufferable
			{
				private:
					sf::Image internal_image;
				public:
					Texture();
					virtual ~Texture();

					Texture(uint16 width, uint16 height, const uint8* pixels = nullptr);
					void create(uint16 width, uint16 height, const uint8* pixels = nullptr);

					Texture(std::string filename);
					bool loadFromFile(std::string filename);

					sf::Vector2u getSize();
					const uint8* getPixelData();
					Pixel getPixel(uint16 x, uint16 y);
					void setPixel(uint16 x, uint16 y, Pixel pixel);
					
					void bindTo(uint16 texture_slot);
					void bindToWithUniform(uint16 texture_slot, std::string uniform_name, Shader& shader);

					void buffer(bool force = false) override;
			};
		}
	}
}

#endif
