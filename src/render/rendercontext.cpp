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
			
			//Create null texture
			this->null_texture = &this->resource_manager.newTextureFromBlank(1, 1, nullptr);

			///Testing
			this->camera.getState().orientation = quat(v3(0.0, 3.141592 / 2.0 - 0.4, 3.141592 / 2.0));
			this->camera.getState().position = v3(0.0, 0.0, 5.0);
			
			Resources::Texture& tex = this->resource_manager.newTextureFromFile("../data/test/texture.jpg");
			Resources::Mesh& mesh = this->resource_manager.newMeshFromFile("../data/test/spaceship1.obj");

			Figures::Part& part = this->figure_manager.newFigure().newPart();
			part.setMesh(&mesh);
			part.setTexture(&tex);
			part.bufferAll();
			IO::output(std::to_string(part.getInfoInt()));
			
			this->figure_manager.getFigure(0).getState().position = v3(12.0, 0.0, -2.0);
			this->figure_manager.getFigure(0).getState().orientation = quat(v3(0.0, -3.14159 / 2, 0.0));
			this->figure_manager.getFigure(0).getState().spin = quat(v3(0.0, 0.0, 0.01));
			this->figure_manager.getFigure(0).getState().scale = v3(1.0, 1.0, 1.0);
			this->figure_manager.getFigure(0).getState().update();
			
			Resources::Texture& tex1 = this->resource_manager.newTextureFromFile("../data/test/texture.jpg");
			Resources::Texture& normal_map1 = this->resource_manager.newTextureFromFile("../data/test/normal.jpg");
			normal_map1.buffer();
			Resources::Mesh& mesh1 = this->resource_manager.newMeshFromFile("../data/test/floor.obj");
			
			Figures::Part& part1 = this->figure_manager.newFigure().newPart();
			part1.setMesh(&mesh1);
			part1.setTexture(&tex1);
			part1.setNormalMap(&normal_map1);
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
			this->renderFigures();
			
			this->renderer.preRender(Renderer::RenderMethod::PostProcess);
			this->renderer.renderPostProcess(this->time);

			//Increment time
			this->time ++;

			return closed;
		}
		
		void RenderContext::renderFigures()
		{
			for (uint32 figure_count = 0; figure_count < this->figure_manager.getNumber(); figure_count ++)
			{
				Figures::Figure& current_figure = this->figure_manager.getFigure(figure_count);
				
				for (uint32 part_count = 0; part_count < current_figure.getPartNumber(); part_count ++)
				{
					Figures::Part& part = current_figure.getPart(part_count);
					
					if (part.getVisible())
						this->renderer.renderPart(part, *this);
				}
			}
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
		
		int32 RenderContext::getTime()
		{
			return this->time;
		}
		
		Resources::Texture& RenderContext::getNullTexture()
		{
			return *this->null_texture;
		}
	}
}
