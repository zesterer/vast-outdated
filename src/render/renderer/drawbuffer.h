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
					glid gl_id;
					
					glid gl_texture_id;
					glid gl_depth_id;
					
					uint32 width = 1;
					uint32 height = 1;
				public:
					DrawBuffer();
					void initialise();
					
					void setSize(uint32 width, uint32 height);
					
					glid getGLID();
					glid getTextureGLID();
					glid getDepthGLID();
			};
		}
	}
}

#endif
