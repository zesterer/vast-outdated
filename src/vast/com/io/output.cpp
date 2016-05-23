#include "vast/com/io/output.h"

#include "vast/config.h"

namespace Vast
{
	namespace Com
	{
		namespace IO
		{
			void output(const char* msg, enum OutMode mode)
			{
				if (mode == OUTMODE_DEBUG && !VAST_DEBUG_ENABLED)
					return;

				switch(mode)
				{
					case OUTMODE_DEBUG:
						printf("[ DEBUG ]  ");
						break;

					case OUTMODE_INFO:
						printf("[ INFO  ]  ");
						break;

					case OUTMODE_WARNING:
						printf("[WARNING]  ");
						break;

					case OUTMODE_ERROR:
						printf("[ ERROR ]  ");
						break;

					case OUTMODE_FATAL:
						printf("[ FATAL ]  ");
						break;

					default:
						break;
				}

				printf("%s\n", msg);
			}

			void output(std::string msg, enum OutMode mode)
			{
				output(msg.c_str(), mode);
			}
		}
	}
}
