#include "vast/com/resource/manager.h"

namespace Vast
{
	namespace Com
	{
		namespace Resource
		{
			id Manager::gen_id()
			{
				this->_id_count ++;
				return this->_id_count - 1;
			}
		}
	}
}
