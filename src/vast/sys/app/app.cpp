#include "vast/sys/app/app.h"
#include "vast/com/io/output.h"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			id app_id_count = 0;

			id glob_gen_app_id()
			{
				app_id_count ++;
				return app_id_count - 1;
			}

			i32 App::build()
			{
				if (this->_is_built)
				{
					Com::IO::error("App[" + std::to_string(this->_id) + "] is already built. Skipping rebuild");
					return 1;
				}

				// Assign a valid ID to the app
				this->_id = glob_gen_app_id();

				// Build the FPS timer
				this->_fps_timer.build();

				// Build the main window
				this->_main_window.build();

				// Initiate glbinding
				glbinding::Binding::initialize();

				this->finish_build("App");

				return 0; // No error
			}

			i32 App::run()
			{
				// Debug info
				Com::IO::output("Running app");

				while (this->_main_window.is_active() && this->_fps_timer._ticker < 200)
				{
					// Reset FPS timer ready for the frame
					this->_fps_timer.reset();

					gl::glClearColor(0.0, 1.0, 0.0, 1.0);

					this->_main_window.tick();

					// Tick the FPS timer after this frame's execution
					this->_fps_timer.tick();

					// Wait for the syncronisation refresh
					this->_fps_timer.wait();
				}

				return 0; // No error
			}

			i32 App::close()
			{
				this->_main_window.close();

				return 0;
			}
		}
	}
}
