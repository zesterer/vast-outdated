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
			T* _ptr = nullptr;
			id _id;
			imem _refs = 0;
			imem _type_hash;

			T* ptr() { return static_cast<T*>(this->_ptr); }

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
					Util::output("Cannot deallocate resource at location '" +
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
			id _id_count = 0;

			template<typename T>
			Util::Result<ResBox<T>> get(id res_id, bool test_type = true)
			{
				for (auto iter = this->_list.begin(); iter != this->_list.end(); iter ++)
				{
					if ((*iter)._id == res_id)
					{
						if (!test_type || typeid(T).hash_code() == (*iter)._type_hash)
							return  Util::Result<ResBox<T>>(*(ResBox<T>*)(&*iter), true);
						else
						{
							Util::output("Failed to cast resource with id '" +
								std::to_string((*iter)._id) + "' because a type mismatch occured",
								Util::OUTMODE_ERROR);

							return Util::Result<ResBox<T>>(ResBox<T>(), false);
						}
					}
				}

				return Util::Result<ResBox<T>>(ResBox<T>(), false);
			}

			i32 dealloc(id res_id)
			{
				ResBox<void> res_box = this->get<void>(res_id, false).value();
				res_box.dealloc();
				this->_list.remove(res_box);
				return 0;
			}

			template<typename T>
			Util::Result<ResBox<T>> alloc()
			{
				T* item_ptr;

				try
				{
					item_ptr = new T();
				}
				catch (...)
				{
					Util::output("Failed to allocate space for '" +
						std::string(typeid(T).name()) + "' in resource manager");

					return Util::Result<ResBox<T>>(ResBox<T>(), false);
				}

				ResBox<T> res_box;
				res_box._ptr = item_ptr;
				res_box._id = this->gen_id();
				res_box._type_hash = typeid(T).hash_code();

				this->_list.push_back(*(ResBox<void>*)(&res_box));

				return Util::Result<ResBox<T>>(res_box, true);
			}

			template<typename T>
			Util::Result<ResBox<T>> add(T item)
			{
				Util::Result<ResBox<T>> box = this->alloc<T>();

				if (box.is_valid())
					*box.value().ptr() = item;
				else
					Util::output("Invalid resource manager box could not be assigned value", Util::OUTMODE_ERROR);

				return box;
			}

			id gen_id();
		};
	}
}

#endif
