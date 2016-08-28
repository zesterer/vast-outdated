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
				if (mode == OutMode::DEBUG && !VAST_DEBUG_ENABLED)
					return;

				switch(mode)
				{
				case OutMode::DEBUG:
						printf("[ DEBUG ]  ");
						break;

					case OutMode::INFO:
						printf("[ INFO  ]  ");
						break;

					case OutMode::WARNING:
						printf("[WARNING]  ");
						break;

					case OutMode::ERROR:
						printf("[ ERROR ]  ");
						break;

					case OutMode::FATAL:
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

			void error(const char* msg, i32 line)
			{
				if (line != -1)
				{
					output("Line " + std::to_string(line) + ": " + msg, OutMode::ERROR);
				}
				else
				{
					output(msg, OutMode::ERROR);
				}
			}

			void error(std::string msg, i32 line)
			{
				error(msg.c_str(), line);
			}
		}
	}
}
