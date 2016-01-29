#ifndef VAST_BACKEND_ENGINE_H
#define VAST_BACKEND_ENGINE_H

namespace Vast
{
	namespace Backend
	{
		class Engine
		{
		private:
		public:
			Engine();
			void init();
			void tick();
		};
	}
}

#endif