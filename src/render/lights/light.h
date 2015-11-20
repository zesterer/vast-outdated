#ifndef VAST_RENDER_LIGHTS_LIGHT_H
#define VAST_RENDER_LIGHTS_LIGHT_H

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		namespace Lights
		{
			enum LightType
			{
				Directional,
				Point,
				Spot,
			};
			
			struct Light
			{
				private:
				public:
					LightType type = LightType::Directional;
					
					v3 position = glm::vec3(0.0, 0.0, 0.0);
					glm::vec3 colour = glm::vec3(1.0, 1.0, 1.0);
					glm::vec3 direction = glm::vec3(1.0, 0.0, 0.0);
					
					float spot_angle = 0.0;
					float ambiance = 0.1;
					
					Light();
			};
		}
	}
}

#endif
