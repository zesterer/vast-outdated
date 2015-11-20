#ifndef VAST_RENDER_LIGHTS_LIGHTMANAGER_H
#define VAST_RENDER_LIGHTS_LIGHTMANAGER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "light.h"
#include "sun.h"

#define MAX_LIGHT_NUMBER 16

namespace Vast
{
	namespace Render
	{
		namespace Lights
		{
			class LightManager
			{
				private:
					Sun sun;
					
					glm::vec3 position_array[MAX_LIGHT_NUMBER];
					glm::vec3 colour_array[MAX_LIGHT_NUMBER];
					glm::vec3 direction_array[MAX_LIGHT_NUMBER];
					int type_array[MAX_LIGHT_NUMBER];
					float spot_angle_array[MAX_LIGHT_NUMBER];
					float ambiance_array[MAX_LIGHT_NUMBER];
					
					std::vector<Light*> lights;
				public:
					LightManager();

					Light& newLight();
					
					Light& getLight(uint32 id);
					std::vector<Light*>& getLights();
					uint32 getNumber();
					
					void updatePriorityArrays();
					
					glm::vec3* getPriorityArrayPosition();
					glm::vec3* getPriorityArrayColour();
					glm::vec3* getPriorityArrayDirection();
					
					int* getPriorityArrayType();
					float* getPriorityArraySpotAngle();
					float* getPriorityArrayAmbiance();
					
					Sun& getSun();
			};
		}
	}
}

#endif
