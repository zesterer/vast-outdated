#ifndef PARASOL_HOOK_H
#define PARASOL_HOOK_H

//standard
#include "string"

namespace Parasol
{
	struct Hook
	{
		private:
			std::string uniform_name;
		
		public:
			std::string getUniformName() { return this->uniform_name; }
			void setUniformName(std::string uniform_name) { this->uniform_name = uniform_name; }
	};
}

#endif
