#ifndef PARASOL_RESOURCE_H
#define PARASOL_RESOURCE_H

//local
#include "common.h"

namespace Parasol
{
	class Resource
	{
		private:
			ResourceID resource_id;
		
		public:
			std::string getResourceID() { return this->resource_id; }
			void setResourceID(std::string resource_id) { this->resource_id = resource_id; }
	};
}

#endif
