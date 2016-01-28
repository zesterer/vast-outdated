#ifndef PARASOL_IMAGE_H
#define PARASOL_IMAGE_H

//standard
#include "string.h"

//library
#include "SFML/Graphics.hpp"

//local
#include "resource.h"
#include "common.h"

namespace Parasol
{
	class Image : public Resource
	{
		private:
			sf::Image internal;
		public:
			int loadFrom(std::string filename);
			int loadFrom(const void* data, std::size_t length);
			
			v2 getSize() { return iv2(this->internal.getSize().x, this->internal.getSize().y); }
	};
}

#endif
