#include "vast/sys/app/app.h"
#include "vast/com/io/output.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			id app_id_count = 0;

			i32 app_build(App& app)
			{
				if (app._is_built)
				{
					Com::IO::output("App[" + std::to_string(app._id) + "] is already built. Skipping rebuild", Com::IO::OUTMODE_ERROR);
					return 1;
				}

				app._id = app_gen_id();
				window_build(app._main_window);

				app._is_built = true; // We're done building

				// Debug
				Com::IO::output("Built new App instance");

				return 0; // No error
			}

			i32 app_run(App& app)
			{
				// Debug info
				Com::IO::output("Running app");

				if (!app._main_window.is_open())
					window_activate(app._main_window);

				while (app._main_window.is_open())
				{
					window_tick(app._main_window);
				}

				return 0; // No error
			}

			id app_gen_id()
			{
				app_id_count ++;
				return app_id_count - 1;
			}
		}
	}
}
