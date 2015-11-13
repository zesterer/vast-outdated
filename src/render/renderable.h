#ifndef VAST_RENDER_RENDERABLE_H
#define VAST_RENDER_RENDERABLE_H

namespace Vast
{
	namespace Render
	{
		class Renderable
		{
			private:
				bool visible = true;
			public:
				Renderable();

				void setVisible(bool visible = true);
				bool getVisible();
		};
	}
}

#endif
