#include "res/manager.h"

namespace Vast
{
	namespace Res
	{
		id ResManager::gen_id()
		{
			this->id_count ++;
			return this->id_count - 1;
		}
	}
}
