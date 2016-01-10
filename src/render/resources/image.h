#ifndef VAST_RENDER_RESOURCES_IMAGE_H
#define VAST_RENDER_RESOURCES_IMAGE_H

//----LIBRARY----
#include "SFML/Graphics.hpp"

//----LOCAL----
#include "common/basictypes.h"
#include "common/generics.h"
#include "resource.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Image : public Resource
			{
				private:
					sf::Image internal_image;
				public:
					Image();
					virtual ~Image();

					Image(uint16 width, uint16 height, const uint8* pixels = nullptr);
					void create(uint16 width, uint16 height, const uint8* pixels = nullptr);

					//We use flip-flags because some textures (such as normal maps) expect to
					//be flipped in various non-standard ways (don't ask me why).
					Image(std::string filename, unsigned char flip_flags = 0b00000010);
					
					bool loadFromFile(std::string filename, unsigned char flip_flags = 0b00000010);

					v2 getSize();
					void setSize(v2 size);
					
					const uint8* getPixelData();
					Pixel getPixel(uint16 x, uint16 y);
					void setPixel(uint16 x, uint16 y, Pixel pixel);
			};
		}
	}
}

#endif
