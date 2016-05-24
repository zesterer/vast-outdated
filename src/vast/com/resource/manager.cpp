#include "vast/com/resource/manager.h"

namespace Vast
{
	namespace Com
	{
		namespace Resource
		{
			id Manager::gen_id()
			{
				this->_mutex.lock();

				this->_id_count ++;
				id val = this->_id_count - 1;

				this->_mutex.unlock();

				return val;
			}

			i32 Manager::dealloc(id res_id)
			{
				Box<void>* res_box = this->get_box<void>(res_id, false).val();

				this->_mutex.lock();

				res_box->dealloc();
				this->_list.remove(*res_box);

				this->_mutex.unlock();

				return 0;
			}
		}
	}
}
