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
			this->resource_manager.initiate();
			
			//Create null texture
			this->null_texture = &this->resource_manager.newTextureFromBlank(1, 1, nullptr);

			///Testing
			this->camera.getState().orientation = quat(v3(0.0, 3.141592 / 2.0 - 0.4, 3.141592 / 2.0));
			this->camera.getState().position = v3(0.0, 0.0, 5.0);
			
			Resources::Texture& tex = this->resource_manager.newTextureFromFile("../data/proprietary/tie-tex.png");
			Resources::Mesh& mesh = this->resource_manager.newMeshFromFile("../data/proprietary/tie-mesh.obj");
			Resources::Texture& norm = this->resource_manager.newTextureFromFile("../data/proprietary/tie-norm.png");
			Resources::Material& mat = this->resource_manager.newMaterial();
			mat.setShininess(3.0f);
			//mat.setAmbientColour(glm::vec3(1.0, 1.0, 0.3));
			//mat.setDiffuseColour(glm::vec3(1.0, 1.0, 0.3));
			mat.setDiffuseColour(glm::vec3(0.6, 0.6, 1.0));
			mat.setSpecularColour(glm::vec3(0.6, 0.6, 1.0));

			Figures::Part& part = this->figure_manager.newFigure().newPart();
			part.setMesh(&mesh);
			part.setTexture(&tex);
			part.setNormalMap(&norm);
			part.setMaterial(&mat);
			part.bufferAll();
			
			this->figure_manager.getFigure(0).getState().position = v3(12.0, 0.0, 2.0);
			//this->figure_manager.getFigure(0).getState().orientation = quat(v3(0.0, -3.14159 / 2, 0.0));
			this->figure_manager.getFigure(0).getState().orientation = quat(v3(-3.14159 / 2, 0.0, 0.0));
			this->figure_manager.getFigure(0).getState().spin = quat(v3(0.0, 0.0, 0.01));
			this->figure_manager.getFigure(0).getState().scale = v3(1.0, 1.0, 1.0);
			this->figure_manager.getFigure(0).getState().update();
			
			Resources::Texture& tex1 = this->resource_manager.newTextureFromFile("../data/test/texture3.png");
			Resources::Texture& normal_map1 = this->resource_manager.newTextureFromFile("../data/test/normal3.png", 3);
			normal_map1.buffer();
			Resources::Mesh& mesh1 = this->resource_manager.newMeshFromFile("../data/test/floor.obj");
			Resources::Material& mat1 = this->resource_manager.newMaterial();
			mat1.setShininess(3.5f);
			mat1.setDiffuseColour(glm::vec3(1.0, 0.8, 0.3));
			mat1.setSpecularColour(glm::vec3(1.0, 0.8, 0.3));
			
			Figures::Part& part1 = this->figure_manager.newFigure().newPart();
			part1.setMesh(&mesh1);
			part1.setTexture(&tex1);
			part1.setNormalMap(&normal_map1);
			part1.setMaterial(&mat1);
			part1.bufferAll();
			
			this->figure_manager.getFigure(1).getState().position = v3(12.0, 0.0, -5.0);
			this->figure_manager.getFigure(1).getState().scale = v3(12.0, 12.0, 12.0);
			this->figure_manager.getFigure(1).getState().spin = quat(v3(0.0, 0.00, 0.01));
			this->figure_manager.getFigure(1).getState().orientation = quat(v3(3.14159 / 2, 0.0, 0.0));
			this->figure_manager.getFigure(1).getState().update();
			
			/*Lights::Light& point0 = this->getLightManager().newLight();
			point0.position = glm::vec3(12.0, 8.0, -7.0);
			point0.direction = glm::vec3(0.0, 0.0, 1.0);
			point0.colour = glm::vec3(0.0, 1.0, 0.0);
			point0.ambiance = 0.0;
			point0.type = Lights::LightType::Point;
			
			Lights::Light& point1 = this->getLightManager().newLight();
			point1.position = glm::vec3(11.0, -8.0, -5.0);
			point1.direction = glm::vec3(0.0, 0.0, 1.0);
			point1.colour = glm::vec3(1.0, 0.0, 0.0);
			point1.ambiance = 0.0;
			point1.type = Lights::LightType::Point;
			
			Lights::Light& point2 = this->getLightManager().newLight();
			point2.position = glm::vec3(16.0, -5.0, -5.0);
			point2.direction = glm::vec3(0.0, 0.0, 1.0);
			point2.colour = glm::vec3(0.0, 0.0, 1.0);
			point2.ambiance = 0.0;
			point2.type = Lights::LightType::Point;*/
			///Testing
		}

		bool RenderContext::render(double fps, glm::ivec2 dimensions)
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
			this->getCamera().update((float)dimensions.x/ (float)dimensions.y);
			this->getRenderer().update(dimensions);
			this->getLightManager().updatePriorityArrays();

			//Rendering goes here
			this->renderer.preRender(Renderer::RenderMethod::Standard);
			this->renderFigures();
			
			this->renderer.preRender(Renderer::RenderMethod::PostProcess);
			this->renderer.renderPostProcess(*this);

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
		}
		
		Camera& RenderContext::getCamera()
		{
			return this->camera;
		}
		
		Renderer::Renderer& RenderContext::getRenderer()
		{
			return this->renderer;
		}

		Resources::ResourceManager& RenderContext::getResourceManager()
		{
			return this->resource_manager;
		}

		Figures::FigureManager& RenderContext::getFigureManager()
		{
			return this->figure_manager;
		}
		
		Lights::LightManager& RenderContext::getLightManager()
		{
			return this->light_manager;
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
