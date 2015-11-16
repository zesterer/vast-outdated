//----STANDARD----
#include "stdio.h"
#include "cstring"
#include "chrono"

//----LOCAL----
#include "application.h"
#include "common/io.h"
#include "timer.h"

namespace Vast
{
	namespace Application
	{
		Application::Application(int32 argc, char* argv[])
		{
			IO::output("Created application");

			this->parseArguments(argc, argv);

			if (this->config.print_args)
			{
				IO::output("Application arguments:");

				for (int16 c = 1; c < argc; c ++)
					printf("> %s\n", argv[c]);

				if (argc <= 1)
					printf("None\n");
			}

			this->config.print();
		}

		int Application::run()
		{
			IO::output("Running application");

			//Set up the main window
			this->main_window.initiate();
			this->render_context.initiate();
			
			//Create the FPS timer
			Timer fps_timer;

			bool closed = false;
			while (!closed)
			{
				closed |= this->render_context.render(fps);
				closed |= this->main_window.tick(fps);
				
				//Calculate FPS
				double new_fps = 1.0 / fps_timer.getLap();
				if (abs(this->fps - new_fps) > new_fps / 10.0)
					this->fps = new_fps;
				else //Use a smoothing system to make sure the FPS doesn't flicker about like crazy
					this->fps = this->fps * (1.0 - 1.0 / this->fps) + (1.0 / this->fps) * new_fps;
			}

			//Close everything down
			this->render_context.close();
			this->main_window.close();

			IO::output("Stopped running application");

			return 0;
		}

		void Application::parseArguments(int32 argc, char* argv[])
		{
            ApplicationConfig appcfg;

            for (int16 c = 1; c < argc; c ++)
			{
				if (strcmp(argv[c], "--server") == 0)
					appcfg.server_mode = true;
				if (strcmp(argv[c], "--printargs") == 0)
					appcfg.print_args = true;
			}

			this->config = appcfg;
		}

		void ApplicationConfig::print()
		{
			if (this->server_mode)
				IO::output("SERVER_MODE = TRUE");
			else
				IO::output("SERVER_MODE = FALSE");
		}
	}
}
