#ifndef VAST_COMMON_GENERICS_H
#define VAST_COMMON_GENERICS_H

//----LIBRARY----
#include "SFML/Graphics.hpp"

//----LOCAL----
#include "basictypes.h"

namespace Vast
{
	struct Pixel
	{
		uint8 r, g, b, a;

		Pixel(sf::Color colour)
		{
			this->r = colour.r;
			this->g = colour.g;
			this->b = colour.b;
			this->a = colour.a;
		}
	};
}

#endif
