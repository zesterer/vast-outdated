#ifndef VAST_RENDER_RENDERCONTEXT_H
#define VAST_RENDER_RENDERCONTEXT_H

//----LOCAL----
#include "resources/resourcemanager.h"
#include "figures/figuremanager.h"
#include "common/basictypes.h"
#include "camera.h"
#include "renderer/renderer.h"
#include "lights/lightmanager.h"

namespace Vast
{
	namespace Render
	{
		class RenderContext
		{
			private:
				int32 time = 0;

				Camera camera;

				Renderer::Renderer renderer;
				Resources::ResourceManager resource_manager;
				Figures::FigureManager figure_manager;
				Lights::LightManager light_manager;
				
				Resources::Texture* null_texture = nullptr;
				
				void renderFigures();
			public:
				RenderContext();
				virtual ~RenderContext();
				void initiate();
				bool render(double fps, uint32 width, uint32 height);
				void close();
				
				int32 getTime();
				Resources::Texture& getNullTexture();

				Resources::ResourceManager& getResourceManager();
				Figures::FigureManager& getFigureManager();
				Lights::LightManager& getLightManager();
				Camera& getCamera();
				Renderer::Renderer& getRenderer();
		};
	}
}

#endif
