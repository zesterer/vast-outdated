#ifndef VAST_ENGINE_SCENE_H
#define VAST_ENGINE_SCENE_H

//----LOCAL----
#include "render/rendercontext.h"

namespace Vast
{
	namespace Engine
	{
		class Scene
		{
			private:
				Render::RenderContext render_context;
			public:
				Scene();
				void initiate();
				bool tick(double fps, glm::ivec2 dimensions);
				void close();
		};
	}
}

#endif
