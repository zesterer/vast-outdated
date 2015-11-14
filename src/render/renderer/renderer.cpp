//----LOCAL----
#include "renderer.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Renderer
		{
			Renderer::Renderer()
			{
				IO::output("Created renderer");
			}

			void Renderer::initiate()
			{
				IO::output("Initiating renderer");

				glbinding::Binding::initialize();

				this->bufferScreenQuad();
			}

			void Renderer::bufferScreenQuad()
			{
				//Generate vertex arrays to store the screen quad
				gl::glGenVertexArrays(1, &this->gl_screen_quad_id);
				gl::glBindVertexArray(this->gl_screen_quad_id);

				//The bi-polygon array for deferred rendering
				const gl::GLfloat gl_screen_quad_data[] =
				{
					-1.0, -1.0,  0.0,
					 1.0, -1.0,  0.0,
					-1.0,  1.0,  0.0,
					-1.0,  1.0,  0.0,
					 1.0, -1.0,  0.0,
					 1.0,  1.0,  0.0,
				};

				//Generate a buffer to store the vertex data
				gl::glGenBuffers(1, &this->gl_screen_quad_id);
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_screen_quad_id);
				gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(gl_screen_quad_data), gl_screen_quad_data, gl::GL_STATIC_DRAW);

				IO::output("Buffered screen quad array");
			}

			void Renderer::renderFigure(Figures::Figure& figure)
			{
				//Render figure
			}

			void Renderer::renderPart(Figures::Part& part)
			{
				//Render part
			}

			void Renderer::renderFigureMultiple(std::vector<Figures::Figure>& figures)
			{
				//Render multiple figures
			}
		}
	}
}
