#ifndef VAST_SYS_APP_APP
#define VAST_SYS_APP_APP

#include "vast/com/atomic/type.h"
#include "vast/sys/app/window.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			struct App
			{
				id _id;
				bool _is_built = false;

				Window _main_window;

				i32 build();
				i32 run();
			};

			id app_gen_id();
		}
	}
}

#endif
