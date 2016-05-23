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

				i32 build();
				i32 activate(bool activate = true);
				i32 handle_events();
				i32 tick();

				bool is_open();
			};
		}
	}
}

#endif
