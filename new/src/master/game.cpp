//local
#include "game.h"
#include "../common/io.h"

namespace Vast
{
	namespace Master
	{
		Game::Game()
		{
			//Constructor
		}
		
		void Game::init()
		{
			Common::output("Initiating game");
			
			this->backend_engine.init();
			this->frontend_context.init();
		}
	}
}