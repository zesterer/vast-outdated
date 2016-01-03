#ifndef VAST_RENDER_LIGHTS_SUN_H
#define VAST_RENDER_LIGHTS_SUN_H

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		namespace Lights
		{
			struct Sun
			{
				private:
				public:
					glm::vec3 direction = glm::vec3(1.0, 1.0, -1.0);
					glm::vec3 colour = glm::vec3(0.5, 0.5, 0.5) * 0.0f;
					float ambiance = 0.2;
					
					Sun();
			};
		}
	}
}

#endif
