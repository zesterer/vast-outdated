#ifndef VAST_RENDER_RESOURCES_RESOURCEID_H
#define VAST_RENDER_RESOURCES_RESOURCEID_H

//----STANDARD----
#include "string"

#define RESOURCE_ID_MAX_SIZE 32

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			struct ResourceID
			{
				char id[RESOURCE_ID_MAX_SIZE];
				
				void set(const char* str)
				{
					bool found_end = false;
					for (int i = 0; i < RESOURCE_ID_MAX_SIZE; i ++)
					{
						if (found_end)
							this->id[i] = ' ';
						else
						{
							if (str[i] == '\0')
							{
								found_end = true;
								this->id[i] = ' ';
							}
							else
								this->id[i] = str[i];
						}
					}
				}
				
				ResourceID()
				{
					for (int i = 0; i < RESOURCE_ID_MAX_SIZE; i ++)
						this->id[i] = ' ';
				}
				
				ResourceID(const char* str)
				{
					this->set(str);
				}
				
				ResourceID(std::string str)
				{
					this->set(str.c_str());
				}
				
				std::string toString()
				{
					return std::string(this->id);
				}
				
				bool operator==(const ResourceID& other)
				{
					for (int i = 0; i < RESOURCE_ID_MAX_SIZE; i ++)
					{
						if (this->id[i] != other.id[i])
							return false;
					}
					
					return true;
				}
			};
		}
	}
}

#endif
