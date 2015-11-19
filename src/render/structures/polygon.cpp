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
			
			void Polygon::calculateTangents()
			{
				//Position delta
				glm::vec3 delta_pos_1 = this->b.pos - this->a.pos;
				glm::vec3 delta_pos_2 = this->c.pos - this->a.pos;
				
				//Tex delta
				glm::vec2 delta_uv_1 = this->b.tex - this->a.tex;
				glm::vec2 delta_uv_2 = this->c.tex - this->a.tex;
				
				float r = 1.0f / (delta_uv_1.x * delta_uv_2.y - delta_uv_1.y * delta_uv_2.x);
				
				glm::vec3 tangent = (delta_pos_1 * delta_uv_2.y - delta_pos_2 * delta_uv_1.y) * r;
				glm::vec3 bitangent = (delta_pos_2 * delta_uv_1.x - delta_pos_1 * delta_uv_2.x) * r;
				
				this->a.tangent = tangent;
				this->b.tangent = tangent;
				this->c.tangent = tangent;
				
				this->a.bitangent = bitangent;
				this->b.bitangent = bitangent;
				this->c.bitangent = bitangent;
			}
		}
	}
}
