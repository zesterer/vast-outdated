#ifndef VAST_APPLICATION_APPLICATION_H
#define VAST_APPLICATION_APPLICATION_H

//----LOCAL----
#include "common/basictypes.h"
#include "window/window.h"
#include "render/rendercontext.h"

namespace Vast
{
	namespace Application
	{
		struct ApplicationConfig
		{
			private:
			public:
				bool server_mode = false;
				bool print_args = false;

				void print();
		};

		class Application
		{
			private:
				ApplicationConfig config;
				
				double fps;

				Window::Window main_window;
				Render::RenderContext render_context;

				void parseArguments(int32 argc, char* argv[]);
			public:
				Application(int32 argc, char* argv[]);
				int run();
		};
	}
}

#endif
