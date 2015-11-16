//----LOCAL----
#include "figure.h"
#include "figuremanager.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			Figure::Figure(FigureManager* manager)
			{
				this->manager = manager;
			}

			Part& Figure::newPart()
			{
				this->parts.emplace_back(this);
				return this->parts.back();
			}
			
			std::vector<Part>& Figure::getParts()
			{
				return this->parts;
			}
		}
	}
}
