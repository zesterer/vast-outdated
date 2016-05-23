#ifndef VAST_COM_GENERIC_RESULT
#define VAST_COM_GENERIC_RESULT

namespace Vast
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

		T val() { return this->_item; }
		bool is_valid() { return this->_valid; }
	};
}

#endif
