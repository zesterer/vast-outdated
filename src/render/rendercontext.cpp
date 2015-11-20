//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "rendercontext.h"
#include "common/io.h"
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		RenderContext::RenderContext()
		{
            IO::output("Creating render context");
		}
		
		RenderContext::~RenderContext()
		{
			//Destructor
		}

		void RenderContext::initiate()
		{
			this->renderer.initiate(*this);
			this->renderer.setCamera(this->camera);

			///Testing
			this->camera.getState().orientation = quat(v3(0.0, 3.141592 / 2.0 - 0.4, 3.141592 / 2.0));
			this->camera.getState().position = v3(0.0, 0.0, 5.0);
			
			Resources::Texture& tex = this->resource_manager.newTextureFromFile("../../starclock/mickey.bmp");
			//Resources::Texture& normal_map = this->resource_manager.newTextureFromFile("../normal.png");
			Resources::Mesh& mesh = this->resource_manager.newMeshFromFile("../../starclock/mickey.obj");

			Figures::Part& part = this->figure_manager.newFigure().newPart();
			part.setMesh(&mesh);
			part.setTexture(&tex);
			//part.setNormalMap(&normal_map);
			part.bufferAll();
			
			this->figure_manager.getFigure(0).getState().position = v3(12.0, 0.0, -5.0);
			this->figure_manager.getFigure(0).getState().orientation = quat(v3(3.14159 / 2, 0.0, 0.0));
			this->figure_manager.getFigure(0).getState().spin = quat(v3(0.0, 0.0, 0.01));
			this->figure_manager.getFigure(0).getState().scale = v3(1.0, 1.0, 1.0);
			this->figure_manager.getFigure(0).getState().update();
			
			Resources::Texture& tex1 = this->resource_manager.newTextureFromFile("../texture.jpg");
			Resources::Texture& normal_map1 = this->resource_manager.newTextureFromFile("../normal.jpg");
			normal_map1.buffer();
			Resources::Mesh& mesh1 = this->resource_manager.newMeshFromFile("../floor.obj");
			
			Figures::Part& part1 = this->figure_manager.newFigure().newPart();
			part1.setMesh(&mesh1);
			part1.setTexture(&tex1);
			//part1.setNormalMap(&normal_map1);
			part1.bufferAll();
			
			this->figure_manager.getFigure(1).getState().position = v3(12.0, 0.0, -5.0);
			this->figure_manager.getFigure(1).getState().scale = v3(12.0, 12.0, 12.0);
			this->figure_manager.getFigure(1).getState().spin = quat(v3(0.0, 0.0, 0.01));
			this->figure_manager.getFigure(1).getState().orientation = quat(v3(3.14159 / 2, 0.0, 0.0));
			this->figure_manager.getFigure(1).getState().update();
			///Testing
		}

		bool RenderContext::render(double fps, uint32 width, uint32 height)
		{
			if (this->time % 480 == 240)
				this->figure_manager.getFigure(1).getPart(0).setNormalMap(&this->resource_manager.getTexture(2));
			if (this->time % 480 == 0)
				this->figure_manager.getFigure(1).getPart(0).setNormalMap(nullptr);
			
			///Testing
			this->figure_manager.getFigure(0).getState().update();
			this->figure_manager.getFigure(0).getState().tick();
			this->figure_manager.getFigure(1).getState().update();
			this->figure_manager.getFigure(1).getState().tick();
			///Testing
			
			if (this->time % 60 == 0)
				IO::output("Rendering context, time = " + std::to_string(this->time) + ".");
			bool closed = false;

			//Update things
			this->camera.update((float)width / (float)height);
			this->renderer.update(width, height);

			//Rendering goes here
			this->renderer.preRender(Renderer::RenderMethod::Standard);
			this->renderer.renderFigures(this->figure_manager, this->time);
			
			this->renderer.preRender(Renderer::RenderMethod::PostProcess);
			this->renderer.renderPostProcess(this->time);

			//Increment time
			this->time ++;

			return closed;
		}

		void RenderContext::close()
		{
			IO::output("Closing render context");

			this->resource_manager.close();
		}

		Resources::ResourceManager& RenderContext::getResourceManager()
		{
			return this->resource_manager;
		}

		Figures::FigureManager& RenderContext::getFigureManager()
		{
			return this->figure_manager;
		}
	}
}
