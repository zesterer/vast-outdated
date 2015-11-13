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
		}
	}
}
