#include "app/app.h"

#include "util/io.h"

namespace Vast
{
	namespace App
	{
		id app_id_count = 0;

		i32 app_build(App& app)
		{
			if (app._is_built)
			{
				Util::output("App[" + std::to_string(app._id) + "] is already built. Skipping rebuild", Util::OUTMODE_ERROR);
				return 1;
			}

			app._id = app_gen_id();
			window_build(app._main_window);

			app._is_built = true; // We're done building

			// Debug
			Util::output("Built new App instance");

			return 0; // No error
		}

		i32 app_run(App& app)
		{
			// Debug info
			Util::output("Running app");

			if (!app._main_window.is_open())
				window_activate(app._main_window);

			while (app._main_window.is_open())
			{
				window_handle_events(app._main_window);
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
