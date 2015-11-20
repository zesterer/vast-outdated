//----LOCAL----
#include "lightmanager.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Lights
		{
			LightManager::LightManager()
			{
				IO::output("Created light manager");
			}
			
			Light& LightManager::newLight()
			{
				this->lights.push_back(new Light());
				return *this->lights.back();
			}
			
			Light& LightManager::getLight(uint32 id)
			{
				return *this->lights[id];
			}
			
			std::vector<Light*>& LightManager::getLights()
			{
				return this->lights;
			}
			
			uint32 LightManager::getNumber()
			{
				return this->lights.size();
			}
			
			Sun& LightManager::getSun()
			{
				return this->sun;
			}
			
			void LightManager::updatePriorityArrays()
			{
				for (uint32 light = 0; light < MAX_LIGHT_NUMBER; light ++)
				{
					if (light < this->getNumber())
					{
						this->position_array[light] = this->getLight(light).position;
						this->colour_array[light] = this->getLight(light).colour;
						this->direction_array[light] = this->getLight(light).direction;
						
						this->type_array[light] = this->getLight(light).type;
						this->spot_angle_array[light] = this->getLight(light).spot_angle;
						this->ambiance_array[light] = this->getLight(light).ambiance;
					}
					else
					{
						this->position_array[light] = glm::vec3(0.0, 0.0, 0.0);
						this->colour_array[light] = glm::vec3(0.0, 0.0, 0.0);
						this->direction_array[light] = glm::vec3(0.0, 0.0, 0.0);
						
						this->type_array[light] = 0;
						this->spot_angle_array[light] = 0.0f;
						this->ambiance_array[light] = 0.0f;
					}
				}
			}
			
			glm::vec3* LightManager::getPriorityArrayPosition()
			{
				return &this->position_array[0];
			}
			
			glm::vec3* LightManager::getPriorityArrayColour()
			{
				return &this->colour_array[0];
			}
			
			glm::vec3* LightManager::getPriorityArrayDirection()
			{
				return &this->direction_array[0];
			}
			
			int* LightManager::getPriorityArrayType()
			{
				return &this->type_array[0];
			}
			
			float* LightManager::getPriorityArraySpotAngle()
			{
				return &this->spot_angle_array[0];
			}
			
			float* LightManager::getPriorityArrayAmbiance()
			{
				return &this->ambiance_array[0];
			}
		}
	}
}
