#ifndef VAST_RENDER_RESOURCES_FIGURE_H
#define VAST_RENDER_RESOURCES_FIGURE_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "common/state.h"
#include "part.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			class Figure
			{
				private:
					State state;

					std::vector<Part> parts;
				public:
					Figure();

					Part& newPart();
			};
		}
	}
}

#endif
