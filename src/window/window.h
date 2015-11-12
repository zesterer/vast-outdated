#ifndef VAST_WINDOW_WINDOW_H
#define VAST_WINDOW_WINDOW_H

//----LIBRARY----
#include "common/basictypes.h"
#include "SFML/Window.hpp"

namespace Vast
{
	namespace Window
	{
		class Window
		{
			private:
				std::string title;

				sf::ContextSettings settings;
				sf::Window internal_window;
			public:
				Window();
				void initiate();
				bool activate(bool active = true);
				bool tick();
				void close();

				void setTitle(std::string title);
				void setFPS(uint16 fps);
				void setSize(uint16 width, uint16 height);

				std::string getTitle();
				sf::Vector2u getSize();
		};
	}
}

#endif
