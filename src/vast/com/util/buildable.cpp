#include "vast/com/util/buildable.h"
#include "vast/com/io/output.h"

#include "typeinfo"

namespace Vast
{
	namespace Com
	{
		namespace Util
		{
			i32 Buildable::finish_build(std::string name)
			{
				this->_is_built = true;
				Com::IO::output("Finished building object of type " + name);
				return 0;
			}

			bool Buildable::is_built()
			{
				return this->_is_built;
			}

			i32 Buildable::unbuild()
			{
				this->_is_built = false;
				return 0;
			}
		}
	}
}
