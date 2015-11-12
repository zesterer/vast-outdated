//----STANDARD----
#include "iostream"

//----LOCAL----
#include "io.h"
#include "settings.h"

namespace Vast
{
	namespace IO
	{
		void output(std::string message, OutputType type)
		{
			std::string output_strings[] = {"OUTPUT", "DEBUG", "ERROR"};

			if ((VAST_DEBUG_ENABLED && type == OutputType::Debug) || type != OutputType::Debug)
			{
				std::string output_tag = output_strings[type];

				std::cout << "[" << output_tag << "]: " << message << std::endl;
			}
		}

		bool test(bool test, std::string label, bool critical, bool silent)
		{
			if (test)
			{
				if (!silent)
					output(label + ": success", OutputType::Debug);
			}
			else
			{
				output(label + ": failure", OutputType::Error);

				if (critical)
				{
					output("Critical error, program closing.", OutputType::Error);
					exit(EXIT_FAILURE);
				}
			}

			return test;
		}
	}
}
