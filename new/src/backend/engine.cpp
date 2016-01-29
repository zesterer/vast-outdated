//local
#include "engine.h"
#include "../common/io.h"

namespace Vast
{
	namespace Backend
	{
		Engine::Engine()
		{
			//Constructor
		}
		
		void Engine::init()
		{
			Common::output("Initiated engine");
		}
		
		void Engine::tick()
		{
			Common::output("Ticked engine");
		}
	}
}