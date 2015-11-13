#ifndef VAST_RENDER_RESOURCES_TEXTURE_H
#define VAST_RENDER_RESOURCES_TEXTURE_H

//----LIBRARY----
#include "SFML/Graphics.hpp"

//----LOCAL----
#include "render/bufferable.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Texture : public Bufferable
			{
				private:
					sf::Image internal_image;
				public:
					Texture();

					Texture(uint16 width, uint16 height, const uint8* pixels = nullptr);
					void create(uint16 width, uint16 height, const uint8* pixels = nullptr);

					Texture(std::string filename);
					bool loadFromFile(std::string filename);

					sf::Vector2u getSize();
					const uint8* getPixelData();

					void buffer() override;
			};
		}
	}
}

#endif
