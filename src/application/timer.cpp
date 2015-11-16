//----LOCAL----
#include "timer.h"

namespace Vast
{
	namespace Application
	{
		Timer::Timer()
		{
			this->reset();
		}
		
		void Timer::reset()
		{
			this->timestamp = std::chrono::high_resolution_clock::now();
		}
		
		double Timer::getLap()
		{
			std::chrono::duration<float> temp = std::chrono::high_resolution_clock::now() - this->timestamp;
			this->reset();
			
			return temp.count();
		}
		
		double Timer::getTime()
		{
			std::chrono::duration<float> temp = std::chrono::high_resolution_clock::now() - this->timestamp;
			
			return temp.count();
		}
	}
}
