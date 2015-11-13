#ifndef VAST_RENDER_RENDERCONTEXT_H
#define VAST_RENDER_RENDERCONTEXT_H

//----LOCAL----
#include "resources/resourcemanager.h"
#include "figures/figuremanager.h"
#include "common/basictypes.h"
#include "camera.h"

namespace Vast
{
	namespace Render
	{
		class RenderContext
		{
			private:
				uint32 time = 0;

				Camera camera;
				Resources::ResourceManager resource_manager;
				Figures::FigureManager figure_manager;
			public:
				RenderContext();
				void initiate();
				bool render();
				void close();
		};
	}
}

#endif
