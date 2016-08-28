#ifndef VAST_RES_BOX
#define VAST_RES_BOX

#include "vast/com/atomic/type.h"
#include "vast/com/io/output.h"

namespace Vast
{
	namespace Com
	{
		namespace Resource
		{
			template<typename T>
			struct Box
			{
				T* _ptr = nullptr;
				id _id;
				imem _refs = 0;
				imem _type_hash;

				id get_id() { return this->_id; }
				imem get_refs() { return this->_refs; }
				T* ptr() { return static_cast<T*>(this->_ptr); }

				Box<T>* hold() { this->_refs ++; return this; }
				Box<T>* drop() { this->_refs --; return this; }

				i32 dealloc()
				{
					if (this->_refs <= 0)
					{
						free(this->_ptr);
						return 0;
					}
					else
					{
						IO::output("Cannot deallocate resource with id '" +
							std::to_string(this->get_id()) +
							"' because it still has references",
							IO::OutMode::ERROR);

						return 1; // Error
					}
				}

				bool operator==(const Box<T>& other)
				{
					return (this->get_id() == other._id);
				}
			};
		}
	}
}

#endif
