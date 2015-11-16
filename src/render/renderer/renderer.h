#ifndef VAST_RENDER_RENDERER_RENDERER_H
#define VAST_RENDER_RENDERER_RENDERER_H

//----LOCAL----
#include "common/basictypes.h"
#include "figures/figure.h"
#include "figures/part.h"
#include "resources/shader.h"
#include "figures/figuremanager.h"

namespace Vast
{
	namespace Render
	{
		class RenderContext;

		namespace Renderer
		{
			class Renderer
			{
				private:
					glid gl_screen_quad_id;

					Resources::Shader* standard_shader;
					Resources::Shader* postprocess_shader;
				public:
					Renderer();
					void initiate(RenderContext& context);
					void bufferScreenQuad();

					void renderPart(Figures::Part& part);
					void renderFigures(Figures::FigureManager& figure_manager);
					void renderPostProcess(uint32 time);
			};
		}
	}
}

#endif
