#ifndef VAST_APPLICATION_APPLICATION_H
#define VAST_APPLICATION_APPLICATION_H

//local
#include "../master/game.h"

namespace Vast
{
	namespace Application
	{
		class Application
		{
		private:
			int argc;
			char** argv;
			
			Master::Game main_game;
		public:
			Application(int argc, char* argv[]);
			void init();
			
			int run();
		};
	}
}

#endif