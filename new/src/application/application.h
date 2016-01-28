#ifndef VAST_APPLICATION_APPLICATION_H
#define VAST_APPLICATION_APPLICATION_H

namespace Vast
{
	namespace Application
	{
		class Application
		{
		private:
			int argc;
			char** argv;
		public:
			Application(int argc, char* argv[]);
			
			int run();
		};
	}
}

#endif