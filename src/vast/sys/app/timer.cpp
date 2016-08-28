#include "vast/sys/app/timer.h"
#include "vast/com/io/output.h"

#include "thread"

namespace Vast
{
	namespace Sys
	{
		namespace App
		{
			i32 Timer::build()
			{
				return 0;
			}

			i32 Timer::reset()
			{
				// Reset the clock timer
				this->_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				return 0;
			}

			i32 Timer::tick()
			{
				std::chrono::milliseconds current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

				// Find the difference between the current time and the last reset
				this->_tick_delta = current_time - this->_time;

				// Update the tick counter and display an update
				if ((this->_ticker % (i32)this->_target_fps) == 0)
					Com::IO::output("Ticked timer with FPS " + std::to_string(1000.0 / this->_tick_delta.count()));
				this->_ticker ++;

				return 0;
			}

			i32 Timer::wait()
			{
				// Find the milliseconds-per-frame target
				std::chrono::milliseconds interval((i32)(1000.0 / this->_target_fps));

				if (this->_tick_delta.count() > interval.count())
				{
					// FPS is below target, there's nothing we can do
					return 1;
				}
				else
				{
					// We have some time to wait for the next frame
					std::this_thread::sleep_for(interval - this->_tick_delta);
					return 0;
				}
			}
		}
	}
}
