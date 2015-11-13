#ifndef VAST_RENDER_ENTITIES_ENTITYMANAGER_H
#define VAST_RENDER_ENTITIES_ENTITYMANAGER_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "figure.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			class FigureManager
			{
				private:
					std::vector<Figure> figures;
				public:
					FigureManager();
			};
		}
	}
}

#endif
