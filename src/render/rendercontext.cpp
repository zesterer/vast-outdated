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
			glbinding::Binding::initialize();
		}

		bool RenderContext::render()
		{
			if (this->time % 60 == 0)
				IO::output("Rendering context, time = " + std::to_string(this->time) + ".");
			bool closed = false;

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
	}
}
