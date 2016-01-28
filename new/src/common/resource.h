#ifndef VAST_COMMON_RESOURCE_H
#define VAST_COMMON_RESOURCE_H

//local
#include "resourceid.h"

namespace Vast
{
	namespace Common
	{
		class Resource
		{
		private:
			ResourceID resource_id;
		public:
			void setResourceID(ResourceID resource_id) { this->resource_id = resource_id; }
			ResourceID getResourceID() { return this->resource_id; }
		};
	}
}

#endif