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
				double fps = 60.0;
				bool show_fps = true;
				bool vsync = true;
				
				std::string title = "Window";

				sf::ContextSettings settings;
				sf::Window internal_window;
				
				void updateTitle();
			public:
				Window();
				void initiate();
				bool activate(bool active = true);
				bool tick(double fps);
				void close();

				void setTitle(std::string title);
				void setFPS(uint16 fps);
				void setSize(uint16 width, uint16 height);
				void setShowFPS(bool show_fps);
				void setVSync(bool vsync);

				std::string getTitle();
				glm::ivec2 getSize();
				bool getShowFPS();
				bool getVSync();
		};
	}
}

#endif
