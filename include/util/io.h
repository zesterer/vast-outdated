#ifndef VAST_UTIL_IO
#define VAST_UTIL_IO

#include "string"

namespace Vast
{
	namespace Util
	{
		enum OutMode
		{
			OUTMODE_DEBUG,
			OUTMODE_INFO,
			OUTMODE_WARNING,
			OUTMODE_ERROR,
			OUTMODE_FATAL,
		};

		void output(const char* msg,		enum OutMode mode = OUTMODE_DEBUG);
		void output(std::string msg,	enum OutMode mode = OUTMODE_DEBUG);
	}
}

#endif
