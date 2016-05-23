#ifndef VAST_COM_IO_OUTPUT
#define VAST_COM_IO_OUTPUT

#include "string"

namespace Vast
{
	namespace Com
	{
		namespace IO
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
}

#endif
