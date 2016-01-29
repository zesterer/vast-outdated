#ifndef VAST_COMMON_RESOURCECONTAINER_H
#define VAST_COMMON_RESOURCECONTAINER_H

//local
#include "resource.h"

namespace Vast
{
	namespace Common
	{
		namespace Resources
		{
			//Abstract class representing a resource management system
			class ResourceContainer
			{
			public:
				int attach(Resource* resource);
				Resource* get(ResourceID resource_id);
				bool contains(ResourceID resource_id);
				int detach(ResourceID resource_id);
			};
		}
	}
}

#endif