//local
#include "context.h"
#include "../common/io.h"

namespace Vast
{
	namespace Frontend
	{
		Context::Context()
		{
			//Constructor
		}
		
		void Context::init()
		{
			Common::output("Initiated context");
		}
	}
}