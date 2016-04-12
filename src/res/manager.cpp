#include "res/manager.h"

namespace Vast
{
	namespace Res
	{
		id Manager::gen_id()
		{
			this->_id_count ++;
			return this->_id_count - 1;
		}
	}
}
