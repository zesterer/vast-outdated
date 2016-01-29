#ifndef VAST_MASTER_GAME_H
#define VAST_MASTER_GAME_H

//local
#include "../backend/engine.h"
#include "../frontend/context.h"

namespace Vast
{
	namespace Master
	{
		class Game
		{
		private:
			Backend::Engine backend_engine;
			Frontend::Context frontend_context;
		public:
			Game();
			void init();
		};
	}
}

#endif