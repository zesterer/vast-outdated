//local
#include "application.h"
#include "../common/io.h"

namespace Vast
{
	namespace Application
	{
		Application::Application(int argc, char* argv[])
		{
			this->argc = argc;
			this->argv = argv;
		}
		
		void Application::init()
		{
			Common::output("Initiating application");
			
			this->main_game.init();
		}
		
		int Application::run()
		{
			Common::output("Running application");
			
			return 0;
		}
	}
}