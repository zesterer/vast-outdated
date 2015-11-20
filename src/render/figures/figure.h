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
			class FigureManager;
			
			class Figure
			{
				private:
					State state;
					
					FigureManager* manager;

					std::vector<Part*> parts;
				public:
					Figure(FigureManager* manager);

					Part& newPart();
					
					State& getState();
					
					std::vector<Part*>& getParts();
					Part& getPart(uint32 id);
					uint32 getPartNumber();
			};
		}
	}
}

#endif
