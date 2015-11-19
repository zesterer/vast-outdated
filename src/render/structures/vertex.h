#ifndef VAST_RENDER_STRUCTURES_VERTEX_H
#define VAST_RENDER_STRUCTURES_VERTEX_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

namespace Vast
{
	namespace Render
	{
		namespace Structures
		{
			struct Vertex
			{
				public:
					glm::vec3 pos;
					glm::vec3 col;
					glm::vec3 norm;
					glm::vec2 tex;
					glm::vec3 tangent;
					glm::vec3 bitangent;
			};
		}
	}
}

#endif
