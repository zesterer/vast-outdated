#ifndef VAST_RENDER_RESOURCES_MATERIAL_H
#define VAST_RENDER_RESOURCES_MATERIAL_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

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

			class Material
			{
				private:
					glm::vec3 ambient_colour = glm::vec3(1.0f, 1.0f, 1.0f);
					glm::vec3 diffuse_colour = glm::vec3(1.0f, 1.0f, 1.0f);
					glm::vec3 specular_colour = glm::vec3(1.0f, 1.0f, 1.0f);
					float smoothness = 1.0f;
					float transparency = 0.0f;
					IlluminationModel illumination_model = IlluminationModel::Phong;
				public:
					Material();
			};
		}
	}
}

#endif
