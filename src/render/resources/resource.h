#ifndef VAST_RENDER_RESOURCES_RESOURCE_H
#define VAST_RENDER_RESOURCES_RESOURCE_H

//----STANDARD----
#include "string"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Resource
			{
				private:
					std::string id_string;
				protected:
					void setIDString(std::string id_string) { this->id_string = id_string; }
				public:
					std::string getIDString() { return this->id_string; }
			};
		}
	}
}

#endif
