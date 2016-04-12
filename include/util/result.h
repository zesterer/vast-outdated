#ifndef VAST_UTIL_RESULT
#define VAST_UTIL_RESULT

namespace Vast
{
	namespace Util
	{
		template<typename T>
		struct Result
		{
			T _item;
			bool _valid;
			
			Result(T item, bool valid)
			{
				this->_item = item;
				this->_valid = valid;
			}
			
			T value() { return this->_item; }
			bool is_valid() { return this->_valid; }
		};
	}
}

#endif
