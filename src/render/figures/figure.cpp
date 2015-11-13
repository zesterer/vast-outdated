//----LOCAL----
#include "figure.h"

namespace Vast
{
	namespace Render
	{
		namespace Figures
		{
			Figure::Figure()
			{
				//Constructor
			}

			Part& Figure::newPart()
			{
				this->parts.emplace_back();
				return this->parts.back();
			}
		}
	}
}
