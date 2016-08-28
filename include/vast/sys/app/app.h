#ifndef VAST_SYS_APP_APP
#define VAST_SYS_APP_APP

#include "vast/com/atomic/type.h"
#include "vast/com/util/buildable.h"

#include "vast/sys/app/window.h"
#include "vast/sys/app/timer.h"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			id glob_gen_app_id();

			struct App : Com::Util::Buildable
			{
				id _id;

				Window _main_window;
				Timer _fps_timer;

				i32 build();
				i32 run();
				i32 close();
			};
		}
	}
}

#endif
