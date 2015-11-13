#ifndef VAST_RENDER_RENDERCONTEXT_H
#define VAST_RENDER_RENDERCONTEXT_H

//----LOCAL----
#include "resources/resourcemanager.h"
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		class RenderContext
		{
			private:
				uint32 time = 0;

				Resources::ResourceManager resource_manager;
			public:
				RenderContext();
				void initiate();
				bool render();
				void close();
		};
	}
}

#endif
