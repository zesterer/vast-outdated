#ifndef VAST_RES_MANAGER
#define VAST_RES_MANAGER

#include "util/type.h"
#include "util/result.h"
#include "util/io.h"

#include "list"
#include "string"
#include "typeinfo"

namespace Vast
{
	namespace Res
	{
		template<typename T>
		struct ResBox
		{
			T* _ptr;
			id _id;
			imem _refs = 0;

			T* value() { return static_cast<T*>(this->_ptr); }

			ResBox<T> hold() { this->_refs ++; }
			ResBox<T> drop() { this->_refs --; }

			i32 dealloc()
			{
				if (this->_refs <= 0)
				{
					free(this->_ptr);
					return 0;
				}
				else
				{
					Util::output("Couldn't free resource at location '" +
						std::to_string((imem)this->_ptr) +
						"' because it still has references",
						Util::OUTMODE_ERROR);

					return 1; // Error
				}
			}

			bool operator==(const ResBox<T>& other)
			{
				return (this->_id == other._id);
			}
		};

		struct ResManager
		{
			std::list<ResBox<void>> _list;
			id id_count;

			template<typename T>
			Util::Result<ResBox<T>> get(id res_id)
			{
				for (auto iter = this->_list.begin(); iter != this->_list.end(); iter ++)
				{
					if ((*iter)._id == res_id)
					{
						return  Util::Result<ResBox<T>>(*(ResBox<T>*)(&*iter), true);
					}
				}

				return Util::Result<ResBox<T>>(ResBox<T>(), false);
			}

			i32 dealloc(id res_id)
			{
				ResBox<void> res_box = this->get<void>(res_id).value();
				res_box.dealloc();
				this->_list.remove(res_box);
				return 0;
			}

			template<typename T>
			Util::Result<ResBox<T>> alloc()
			{
				T* item_ptr = static_cast<T*>(malloc(sizeof(T)));

				ResBox<T> res_box;
				res_box._ptr = item_ptr;
				res_box._id = this->gen_id();

				this->_list.push_back(*(ResBox<void>*)(&res_box));

				return Util::Result<ResBox<T>>(res_box, true);
			}

			id gen_id();
		};
	}
}

#endif
