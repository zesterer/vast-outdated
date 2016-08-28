#ifndef VAST_COM_IO_OUTPUT
#define VAST_COM_IO_OUTPUT

#include "vast/com/atomic/type.h"

namespace Vast
{
	namespace Com
	{
		namespace IO
		{
			enum class OutMode
			{
				DEBUG,
				INFO,
				WARNING,
				ERROR,
				FATAL,
			};

			void output(const char* msg,	enum OutMode mode = OutMode::DEBUG);
			void output(std::string msg,	enum OutMode mode = OutMode::DEBUG);

			void error(const char* msg, i32 line = -1);
			void error(std::string msg, i32 line = -1);
		}
	}
}

#endif
