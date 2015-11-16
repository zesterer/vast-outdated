#ifndef VAST_APPLICATION_TIMER_H
#define VAST_APPLICATION_TIMER_H

//----STANDARD----
#include "chrono"

namespace Vast
{
	namespace Application
	{
		struct Timer
		{
			private:
				std::chrono::high_resolution_clock::time_point timestamp;
			public:
				Timer();
				void reset();
				double getLap();
				double getTime();
		};
	}
}

#endif
