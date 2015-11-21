#ifndef VAST_RENDER_RENDERER_DRAWBUFFER_H
#define VAST_RENDER_RENDERER_DRAWBUFFER_H

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		namespace Renderer
		{
			class DrawBuffer
			{
				private:
					glid gl_id = -1;
					
					glid gl_depthbuffer_id = -1;
					glid gl_texture_id = -1;
					
					glm::ivec2 dimensions = glm::ivec2(1, 1);
				public:
					DrawBuffer();
					void initialise();
					
					void setSize(glm::ivec2 dimensions);
					
					glid getGLID();
					glid getTextureGLID();
					glid getDepthBufferGLID();
			};
		}
	}
}

#endif
