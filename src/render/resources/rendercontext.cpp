//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "rendercontext.h"
#include "common/io.h"
#include "shaders/postprocessvertexGLSL.h"

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
			this->renderer.initiate();

			//Set up the default shaders
			this->getResourceManager().newShadersFromFiles("../data/shaders/postprocess.vert", "../data/shaders/postprocess.frag");

			///Testing
			auto tex = this->resource_manager.newTextureFromFile("/home/barry/Documents/Projects/starclock/bowser.bmp");
			auto mesh = this->resource_manager.newMeshFromFile("/home/barry/Documents/Projects/starclock/bowser.obj");

			auto part = this->figure_manager.newFigure().newPart();
			part.setMesh(&mesh);
			part.setTexture(&tex);
			part.bufferAll();
			///Testing
		}

		bool RenderContext::render()
		{
			if (this->time % 60 == 0)
				IO::output("Rendering context, time = " + std::to_string(this->time) + ".");
			bool closed = false;

			//Update the camera
			this->camera.update();

			//Rendering goes here
			gl::glClearColor(0.0f, 0.4f, 0.0f, 1.0f);
			gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

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
