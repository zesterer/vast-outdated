#include "vast/sys/app/app.h"
#include "vast/com/io/output.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			id app_id_count = 0;

			i32 App::build()
			{
				if (this->_is_built)
				{
					Com::IO::output("App[" + std::to_string(this->_id) + "] is already built. Skipping rebuild", Com::IO::OUTMODE_ERROR);
					return 1;
				}

				this->_id = app_gen_id();
				this->_main_window.build();

				this->_is_built = true; // We're done building

				// Debug
				Com::IO::output("Built new App instance");

				return 0; // No error
			}

			i32 App::run()
			{
				// Debug info
				Com::IO::output("Running app");

				if (!this->_main_window.is_open())
					this->_main_window.activate();

				while (this->_main_window.is_open())
				{
					this->_main_window.tick();
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
