#ifndef VAST_APP_WINDOW
#define VAST_APP_WINDOW

#include "vast/com/atomic/type.h"
#include "vast/com/util/buildable.h"

#include "SDL2/SDL.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			i32 glob_init_window();

			struct Window : Com::Util::Buildable
			{
				SDL_Window* _intern_window;
				SDL_GLContext _intern_context;

				i32 _width = 640;
				i32 _height = 480;
				std::string _title = "";
				bool _vsync = true;

				i32 build(i32 width = 640, i32 height = 480);
				i32 activate(bool activate = true);
				i32 handle_events();
				i32 tick();
				i32 close();

				bool is_active();
			};
		}
	}
}

#endif
