#include "vast/com/util/buildable.h"

namespace Vast
{
	namespace Com
	{
		namespace Util
		{
			i32 Buildable::finish_build()
			{
				this->_is_built = true;
				return 0;
			}

			bool Buildable::is_built()
			{
				return this->_is_built;
			}
		}
	}
}
