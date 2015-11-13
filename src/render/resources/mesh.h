#ifndef VAST_RENDER_RESOURCES_MESH_H
#define VAST_RENDER_RESOURCES_MESH_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "structures/polygon.h"
#include "render/bufferable.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Mesh : public Bufferable
			{
				private:
					std::vector<Structures::Polygon> polygons;
				public:
					void addPolygon(Structures::Polygon polygon);
			};
		}
	}
}

#endif
