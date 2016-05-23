#ifndef VAST_APP_WINDOW
#define VAST_APP_WINDOW

#include "vast/com/atomic/type.h"

#include "SFML/Window.hpp"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			struct Window
			{
				sf::ContextSettings _intern_settings;
				sf::Window _intern_window;

				std::string _title = "";
				i32 _framelimit = 60;
				bool _vsync = true;

				bool is_open();
			};

			i32 window_build(Window& window);
			i32 window_activate(Window& window, bool activate = true);
			i32 window_handle_events(Window& window);
			i32 window_tick(Window& window);
		}
	}
}

#endif
