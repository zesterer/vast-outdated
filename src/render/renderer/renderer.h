#ifndef VAST_RENDER_RENDERER_RENDERER_H
#define VAST_RENDER_RENDERER_RENDERER_H

//----LOCAL----
#include "common/basictypes.h"
#include "figure/figure.h"
#include "figure/part.h"

namespace Vast
{
	namespace Render
	{
		namespace Renderer
		{
			class Renderer
			{
				private:
					glid gl_screen_quad_id;
				public:
					Renderer();
					void initiate();
					void bufferScreenQuad();

					void renderFigure(Figures::Figure& figure);
					void renderPart(Figures::Part& part);
					void renderFigureMultiple(std::vector<Figures::Figure>& figures);
			};
		}
	}
}

#endif
