#ifndef VAST_RENDER_RENDERCONTEXT_H
#define VAST_RENDER_RENDERCONTEXT_H

namespace Vast
{
	namespace Render
	{
		class RenderContext
		{
			private:
			public:
				RenderContext();
				bool render();
				void close();
		};
	}
}

#endif
