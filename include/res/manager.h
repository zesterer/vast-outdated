#ifndef VAST_RES_MANAGER
#define VAST_RES_MANAGER

#include "res/box.h"
#include "util/result.h"

#include "list"
#include "string"
#include "typeinfo"

namespace Vast
{
	namespace Res
	{
		struct Manager
		{
			std::list<Box<void>> _list;
			id _id_count = 0;

			template<typename T>
			Util::Result<Box<T>*> get(id res_id, bool test_type = true)
			{
				for (auto iter = this->_list.begin(); iter != this->_list.end(); iter ++)
				{
					if ((*iter).get_id() == res_id)
					{
						if (!test_type || typeid(T).hash_code() == (*iter)._type_hash)
							return  Util::Result<Box<T>*>((Box<T>*)(&*iter), true);
						else
						{
							Util::output("Failed to cast resource with id '" +
								std::to_string((*iter).get_id()) + "' because a type mismatch occured",
								Util::OUTMODE_ERROR);

							return Util::Result<Box<T>*>(nullptr, false);
						}
					}
				}

				return Util::Result<Box<T>*>(nullptr, false);
			}

			i32 dealloc(id res_id)
			{
				Box<void>* res_box = this->get<void>(res_id, false).val();
				res_box->dealloc();
				this->_list.remove(*res_box);
				return 0;
			}

			template<typename T>
			Util::Result<Box<T>*> alloc(bool construct = true)
			{
				T* item_ptr;

				try
				{
					if (construct)
						item_ptr = new T();
					else
						item_ptr = (T*)malloc(sizeof(T));
				}
				catch (...)
				{
					Util::output("Failed to allocate space for '" +
						std::string(typeid(T).name()) + "' in resource manager");

					return Util::Result<Box<T>*>(nullptr, false);
				}

				Box<T> res_box;
				res_box._ptr = item_ptr;
				res_box._id = this->gen_id();
				res_box._type_hash = typeid(T).hash_code();

				this->_list.push_back(*(Box<void>*)(&res_box));

				return Util::Result<Box<T>*>((Box<T>*)&this->_list.back(), true);
			}

			template<typename T>
			Util::Result<Box<T>*> add(T item)
			{
				Util::Result<Box<T>*> box = this->alloc<T>();

				if (box.is_valid())
					*box.val()->get_ptr() = item;
				else
					Util::output("Invalid resource manager box could not be assigned value", Util::OUTMODE_ERROR);

				return box;
			}

			imem get_count() { return this->_list.size(); }

			id gen_id();
		};
	}
}

#endif
