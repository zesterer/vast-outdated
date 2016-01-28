//standard
#include "stdio.h"

//local
#include "io.h"

namespace Vast
{
	namespace Common
	{
		void output(std::string message, OutputType type)
		{
			std::string prefix;
			
			switch (type)
			{
				case OutputType::DEBUG:
					prefix = "DEBUG";
				case OutputType::ERROR:
					prefix = "ERROR";
				case OutputType::INFO:
					prefix = "INFOS";
			}
			
			printf(("[" + prefix + "] " + message + "\n").c_str());
		}
	}
}