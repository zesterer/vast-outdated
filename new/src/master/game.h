#ifndef VAST_MASTER_GAME_H
#define VAST_MASTER_GAME_H

//local
#include "../backend/engine.h"

namespace Vast
{
	namespace Master
	{
		class Game
		{
		private:
			Backend::Engine main_engine;
		public:
			Game();
			void init();
		};
	}
}

#endif