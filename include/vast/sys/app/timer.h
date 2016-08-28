#ifndef VAST_SYS_APP_TIMER
#define VAST_SYS_APP_TIMER

#include "vast/com/atomic/type.h"

#include "chrono"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			struct Timer
			{
				double _target_fps = 60.0;
				long _ticker = 0;

				std::chrono::milliseconds _tick_delta;
				std::chrono::milliseconds _time;

				i32 build();
				i32 reset();
				i32 tick();
				i32 wait();
				i32 set_target_fps(double fps);

				i32 get_load();
				i32 get_fps();
				i32 get_target_fps();
			};
		}
	}
}

#endif
