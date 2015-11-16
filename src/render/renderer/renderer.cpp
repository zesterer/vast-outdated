//----LOCAL----
#include "renderer.h"
#include "common/io.h"
#include "rendercontext.h"

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

			void Renderer::initiate(RenderContext& context)
			{
				IO::output("Initiating renderer");

				glbinding::Binding::initialize();

				this->bufferScreenQuad();

				//Set up the default shaders
				this->standard_shader = &context.getResourceManager().newShaderFromFiles("../data/shaders/standard.vert", "../data/shaders/standard.frag");
				this->postprocess_shader = &context.getResourceManager().newShaderFromFiles("../data/shaders/postprocess.vert", "../data/shaders/postprocess.frag");
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

			void Renderer::renderPostProcess(uint32 time)
			{
				//Disable backface culling
				gl::glDisable(gl::GL_CULL_FACE);

				//Disable the depth buffer
				gl::glDisable(gl::GL_DEPTH_TEST);
				gl::glDepthFunc(gl::GL_NONE);

				//Bind the framebuffer ready
				gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
				gl::glViewport(0, 0, 640 * 1.4, 480 * 1.4); // Render on the whole framebuffer, complete from the lower left corner to the upper right

				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_screen_quad_id);

				//Tell the shaders what different parts of the buffer mean using the above array
				gl::glEnableVertexAttribArray(0);
				gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(gl::GLfloat) * 3, (void*)(unsigned long)0);

				//GLuint tex_id = glGetUniformLocation(framebuffer->shader->gl_id, "RENDER_TEXTURE");
				//glUniform1i(tex_id, 0);
				//glBindTexture(GL_TEXTURE_2D, framebuffer->gl_tex_id);

				//GLuint depth_id = glGetUniformLocation(framebuffer->shader->gl_id, "RENDER_DEPTH");
				//glUniform1i(depth_id, 0);
				//glBindTexture(GL_TEXTURE_2D, framebuffer->gl_depth_id);
				
				gl::GLuint time_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "TIME");
				gl::glUniform1ui(time_id, time);

				this->postprocess_shader->enable();

				gl::glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

				gl::glDrawArrays(gl::GL_TRIANGLES, 0, sizeof(gl::GLfloat) * 6 * 3);

				gl::glDisableVertexAttribArray(0);
			}

			void Renderer::renderPart(Figures::Part& part)
			{
				//Render part
			}

			void Renderer::renderFigures(Figures::FigureManager& figure_manager)
			{
				std::vector<Figures::Figure>& figures = figure_manager.getFigures();
				
				for (uint32 figure_count = 0; figure_count < figures.size(); figure_count ++)
				{
					Figures::Figure& current_figure = figures[figure_count];
					std::vector<Figures::Part>& parts = current_figure.getParts();
					
					for (uint32 part_count = 0; part_count < parts.size(); part_count ++)
					{
						this->renderPart(parts[part_count]);
					}
				}
			}
		}
	}
}
