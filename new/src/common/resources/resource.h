#ifndef VAST_COMMON_RESOURCE_H
#define VAST_COMMON_RESOURCE_H

//local
#include "resourceid.h"

namespace Vast
{
	namespace Common
	{
		namespace Resources
		{
			//The type of resource. To be extended by later module additions.
			enum ResourceType
			{
				NONE,
			};
			
			//An abstract class representing a Resource
			class Resource
			{
			private:
				//Set some defaults should major screw-ups occur
				ResourceID resource_id = "NONE";
				ResourceType resource_type = ResourceType::NONE;
			public:
				//Get | set resource ID
				void setResourceID(ResourceID resource_id) { this->resource_id = resource_id; }
				ResourceID getResourceID() { return this->resource_id; }
				
				//Get | set resource type
				void setResourceType(ResourceType resource_type) { this->resource_type = resource_type; }
				ResourceType getResourceType() { return this->resource_type; }
			};
		}
	}
}

#endif