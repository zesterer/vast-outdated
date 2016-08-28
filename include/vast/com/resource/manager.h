#ifndef VAST_COM_RESOURCE_MANAGER
#define VAST_COM_RESOURCE_MANAGER

#include "vast/com/resource/box.h"
#include "vast/com/generic/result.h"

#include "list"
#include "string"
#include "typeinfo"
#include "mutex"

namespace Vast
{
	namespace Com
	{
		namespace Resource
		{
			struct Manager
			{
				std::list<Box<void>> _list;
				id _id_count = 0;
				std::mutex _mutex;

				template<typename T>
				Result<Box<T>*> get_box(id res_id, bool test_type = true)
				{
					this->_mutex.lock();

					for (auto iter = this->_list.begin(); iter != this->_list.end(); iter ++)
					{
						if ((*iter).get_id() == res_id)
						{
							if (!test_type || typeid(T).hash_code() == (*iter)._type_hash)
							{
								this->_mutex.unlock();
								return  Result<Box<T>*>((Box<T>*)(&*iter), true);
							}
							else
							{
								IO::output("Failed to cast resource with id '" +
									std::to_string((*iter).get_id()) + "' because a type mismatch occured",
									IO::OUTMODE_ERROR);

								this->_mutex.unlock();
								return Result<Box<T>*>(nullptr, false);
							}
						}
					}

					this->_mutex.unlock();

					return Result<Box<T>*>(nullptr, false);
				}

				template<typename T>
				Result<T*> get(id res_id, bool test_type = true)
				{
					Result<Box<T>*> res = this->get_box<T>(res_id, test_type);
					return Result<T*>(res.val()->ptr(), res.is_valid());
				}

				i32 dealloc(id res_id);

				template<typename T>
				Result<Box<T>*> alloc(bool construct = true)
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
						IO::output("Failed to allocate space for '" +
							std::string(typeid(T).name()) + "' in resource manager");

						return Result<Box<T>*>(nullptr, false);
					}

					Box<T> res_box;
					res_box._ptr = item_ptr;
					res_box._id = this->gen_id();
					res_box._type_hash = typeid(T).hash_code();

					this->_mutex.lock();

					this->_list.push_back(*(Box<void>*)(&res_box));
					Box<T>* res = (Box<T>*)&this->_list.back();

					this->_mutex.unlock();

					return Result<Box<T>*>(res, true);
				}

				template<typename T>
				Result<Box<T>*> add(T item)
				{
					Result<Box<T>*> box = this->alloc<T>();

					if (box.is_valid())
						*box.val()->ptr() = item;
					else
						IO::output("Invalid resource manager box could not be assigned value", IO::OUTMODE_ERROR);

					return box;
				}

				imem count() { return this->_list.size(); }

				id gen_id();
			};
		}
	}
}

#endif
