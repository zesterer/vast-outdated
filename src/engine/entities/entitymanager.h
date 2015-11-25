#ifndef VAST_ENGINE_ENTITYMANAGER_H
#define VAST_ENGINE_ENTITYMANAGER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "entity.h"

namespace Vast
{
	namespace Engine
	{
		namespace Entities
		{
			class EntityManager
			{
				private:
					std::vector<Entity*> entities;
				public:
					EntityManager();
			};
		}
	}
}

#endif
