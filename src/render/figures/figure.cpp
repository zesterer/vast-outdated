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
			
			State& Figure::getState()
			{
				return this->state;
			}
			
			std::vector<Part>& Figure::getParts()
			{
				return this->parts;
			}
			
			Part& Figure::getPart(uint32 id)
			{
				return this->parts[id];
			}
			
			uint32 Figure::getPartNumber()
			{
				return this->parts.size();
			}
		}
	}
}
