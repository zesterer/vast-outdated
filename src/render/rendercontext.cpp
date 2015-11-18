//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "rendercontext.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		RenderContext::RenderContext()
		{
            IO::output("Creating render context");
		}

		void RenderContext::initiate()
		{
			this->renderer.initiate(*this);
			this->renderer.setCamera(this->camera);

			///Testing
			Resources::Texture& tex = this->resource_manager.newTextureFromFile("/home/barry/Documents/Projects/starclock/mickey.bmp");
			Resources::Mesh& mesh = this->resource_manager.newMeshFromFile("../spaceship1.obj");

			Figures::Part& part = this->figure_manager.newFigure().newPart();
			part.setMesh(&mesh);
			part.setTexture(&tex);
			part.getMesh().buffer();
			part.getTexture().buffer();
			
			IO::output("ID:" + std::to_string(tex.getGLID()));
			
			this->figure_manager.getFigure(0).getState().position = v3(10.0, 0.0, 0.0);
			this->figure_manager.getFigure(0).getState().orientation = quat(v3(0.0, -3.14159 / 2, 0.0));
			this->figure_manager.getFigure(0).getState().spin = quat(v3(0.02, 0.02, 0.02));
			this->figure_manager.getFigure(0).getState().scale = v3(1.0, 1.0, 1.0);
			this->figure_manager.getFigure(0).getState().update();
			///Testing
		}

		bool RenderContext::render(double fps, uint32 width, uint32 height)
		{
			this->figure_manager.getFigure(0).getState().update();
			this->figure_manager.getFigure(0).getState().tick();
			
			if (this->time % 60 == 0)
				IO::output("Rendering context | time = " + std::to_string(this->time) + ".");
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
