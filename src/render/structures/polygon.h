#ifndef VAST_RENDER_STRUCTURES_POLYGON_H
#define VAST_RENDER_STRUCTURES_POLYGON_H

//----LOCAL----
#include "vertex.h"

namespace Vast
{
	namespace Render
	{
		namespace Structures
		{
			struct Polygon
			{
				public:
					Vertex a, b, c;

					void invert();
					void calculateFlatNormals(float curvature_bias = 0.0f);
			};
		}
	}
}

#endif
