#ifndef VAST_RENDER_RESOURCES_RESOURCE_H
#define VAST_RENDER_RESOURCES_RESOURCE_H

//----STANDARD----
#include "string"

//----LOCAL----
#include "resourceid.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			//Forward declaration
			class ResourceManager;
			
			enum ResourceType
			{
				NONE = 0,
				MESH = 1,
				TEXTURE = 2,
				SURFACE = 2, //Ambiguous (soon to replace Texture)	
				IMAGE = 3,
				MATERIAL = 4,
				SHADER = 5,
				SHADER_HOOK = 6,
			};
			
			class Resource
			{
				friend class ResourceManager;
				private:
					ResourceType resource_type = ResourceType::NONE;
					ResourceID resource_id;
					ResourceManager* manager = nullptr;
				protected:
					void setResourceID(ResourceID resource_id) { this->resource_id = resource_id; }
					void setResourceType(ResourceType resource_type) { this->resource_type = resource_type; }
					void setManager(ResourceManager* manager) { this->manager = manager; }
					
					//THIS METHOD MUST BE EXECUTED BY A ResourceManager OBJECT!
					void attach(ResourceManager* manager) { this->manager = manager; }
					//THIS METHOD MUST BE EXECUTED BY A ResourceManager OBJECT!
					void detach() { this->manager = nullptr; }
				public:
					ResourceID getResourceID() { return this->resource_id; }
					ResourceType getResourceType() { return this->resource_type; }
					bool isManaged() { return this->manager != nullptr; }
					ResourceManager* getManager() { return this->manager; }
			};
		}
	}
}

#endif
