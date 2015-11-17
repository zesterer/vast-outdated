#ifndef VAST_RENDER_RENDERER_RENDERER_H
#define VAST_RENDER_RENDERER_RENDERER_H

//----LOCAL----
#include "common/basictypes.h"
#include "figures/figure.h"
#include "figures/part.h"
#include "resources/shader.h"
#include "figures/figuremanager.h"
#include "drawbuffer.h"
#include "camera.h"

namespace Vast
{
	namespace Render
	{
		class RenderContext;

		namespace Renderer
		{
			enum RenderMethod
			{
				Standard,
				PostProcess
			};
			
			class Renderer
			{
				private:
					glid gl_screen_quad_id;
					
					Camera* camera = nullptr;

					Resources::Shader* standard_shader;
					Resources::Shader* postprocess_shader;
					
					uint32 width = 1;
					uint32 height = 1;
					
					DrawBuffer draw_buffer;
				public:
					Renderer();
					void initiate(RenderContext& context);
					void bufferScreenQuad();
					
					void update(uint32 width, uint32 height);

					void preRender(RenderMethod method);

					void renderPart(Figures::Part& part, uint32 time);
					void renderFigures(Figures::FigureManager& figure_manager, uint32 time);
					void renderPostProcess(uint32 time);
					
					void setCamera(Camera& camera);
			};
		}
	}
}

#endif
