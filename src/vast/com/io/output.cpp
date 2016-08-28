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

			void error(const char* msg, const char* file, i32 line, const char* func)
			{
				if (file != nullptr)
				{
					if (line != -1)
					{
						if (func != nullptr)
							output("File " + std::string(file) + ", line " + std::to_string(line) + " in function " + std::string(func) + " : " + msg, OutMode::ERROR);
						else
							output("File " + std::string(file) + ", line " + std::to_string(line) + " : " + msg, OutMode::ERROR);
					}
					else
						output("File " + std::string(file) + " : " + msg, OutMode::ERROR);
				}
				else
					output(msg, OutMode::ERROR);
			}

			void error(std::string msg, const char* file, i32 line, const char* func)
			{
				error(msg.c_str(), file, line, func);
			}
		}
	}
}
