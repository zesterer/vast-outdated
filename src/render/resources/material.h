#ifndef VAST_RENDER_RESOURCES_MATERIAL_H
#define VAST_RENDER_RESOURCES_MATERIAL_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

//----LOCAL----
#include "resource.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			enum IlluminationModel
			{
				Phong,
				GGX
			};

			class Material : public Resource
			{
				private:
					glm::vec3 ambient_colour = glm::vec3(1.0f, 1.0f, 1.0f);
					glm::vec3 diffuse_colour = glm::vec3(1.0f, 1.0f, 1.0f);
					glm::vec3 specular_colour = glm::vec3(1.0f, 1.0f, 1.0f);
					float smoothness = 2.0f;
					float shininess = 0.25;
					float transparency = 1.0f;
					IlluminationModel illumination_model = IlluminationModel::Phong;
				public:
					Material();
					glm::vec3 getAmbientColour() { return this->ambient_colour; }
					glm::vec3 getDiffuseColour() { return this->diffuse_colour; }
					glm::vec3 getSpecularColour() { return this->specular_colour; }
					float getSmoothness() { return this->smoothness; }
					float getShininess() { return this->shininess; }
					float getTransparency() { return this->transparency; }
					
					void setAmbientColour(glm::vec3 ambient_colour) { this->ambient_colour = ambient_colour; }
					void setDiffuseColour(glm::vec3 diffuse_colour) { this->diffuse_colour = diffuse_colour; }
					void setSpecularColour(glm::vec3 specular_colour) { this->specular_colour = specular_colour; }
					
					void setSmoothness(float smoothness) { this->smoothness = smoothness; }
					void setShininess(float shininess) { this->shininess = shininess; }
					void setTransparency(float transparency) { this->transparency = transparency; }
			};
		}
	}
}

#endif
