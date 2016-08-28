#ifndef VAST_COM_UTIL_BUILDABLE
#define VAST_COM_UTIL_BUILDABLE

#include "vast/com/atomic/type.h"

namespace Vast
{
	namespace Com
	{
		namespace Util
		{
			struct Buildable
			{
			protected:
				bool _is_built = false;

				i32 finish_build(std::string name = "<Unknown>");
				i32 unbuild();

			public:
				bool is_built();
			};
		}
	}
}

#endif
