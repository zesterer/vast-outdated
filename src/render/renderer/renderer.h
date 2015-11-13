#ifndef VAST_RENDER_RENDERER_RENDERER_H
#define VAST_RENDER_RENDERER_RENDERER_H

//----LOCAL----
#include "common/basictypes.h"

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
			};
		}
	}
}

#endif
