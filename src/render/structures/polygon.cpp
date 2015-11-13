//----LOCAL----
#include "polygon.h"

namespace Vast
{
	namespace Render
	{
		namespace Structures
		{
			void Polygon::invert()
			{
				//Swap the vertices
				Vertex temp = this->a;
				this->a = this->c;
				this->c = temp;

				this->a.norm = -this->a.norm;
				this->b.norm = -this->b.norm;
				this->c.norm = -this->c.norm;
			}

			void Polygon::calculateFlatNormals(float curvature_bias)
			{
				//Find the normal to the surface
				glm::vec3 n0 = glm::cross(this->b.pos - this->a.pos, this->c.pos - this->a.pos);
				n0 /= glm::length(n0);

				glm::vec3 average = (this->a.pos + this->b.pos + this->c.pos) / glm::vec3(3.0, 3.0, 3.0);

				//Curvature bias is used only to make things look a little 3D...
				this->a.norm = n0 + (a.norm - average) * curvature_bias;
				this->b.norm = n0 + (b.norm - average) * curvature_bias;
				this->c.norm = n0 + (c.norm - average) * curvature_bias;
			}
		}
	}
}
