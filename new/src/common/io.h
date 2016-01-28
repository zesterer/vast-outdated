#ifndef VAST_COMMON_IO_H
#define VAST_COMMON_IO_H

//standard
#include "string"

namespace Vast
{
	namespace Common
	{
		enum OutputType
		{
			DEBUG,
			ERROR,
			INFO,
		};
		
		void output(std::string message, OutputType type = OutputType::DEBUG);
	}
}

#endif