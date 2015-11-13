//----LOCAL----
#include "renderable.h"

namespace Vast
{
	namespace Render
	{
		Renderable::Renderable()
		{
			//Constructor
		}

		void Renderable::setVisible(bool visible)
		{
			this->visible = visible;
		}

		bool Renderable::getVisible()
		{
			return this->visible;
		}
	}
}
