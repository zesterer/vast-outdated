//----LOCAL----
#include "mesh.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			void Mesh::addPolygon(Structures::Polygon polygon)
			{
				this->polygons.push_back(polygon);
			}
		}
	}
}
