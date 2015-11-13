//----LOCAL----
#include "figuremanager.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			FigureManager::FigureManager()
			{
				IO::output("Created figure manager");
			}

			Figure& FigureManager::newFigure()
			{
				this->figures.emplace_back();
				return this->figures.back();
			}
		}
	}
}
