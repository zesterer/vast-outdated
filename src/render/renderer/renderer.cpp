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

				//Initialise and set up everything
				glbinding::Binding::initialize();
				this->draw_buffer.initialise();

				this->bufferScreenQuad();

				//Set up the default shaders
				this->standard_shader = &context.getResourceManager().newShaderFromFiles("../data/shaders/standard.vert", "../data/shaders/standard.frag");
				this->postprocess_shader = &context.getResourceManager().newShaderFromFiles("../data/shaders/postprocess.vert", "../data/shaders/postprocess.frag");
			}
			
			void Renderer::update(uint32 width, uint32 height)
			{
				this->width = width;
				this->height = height;
				
				this->draw_buffer.setSize(this->width, this->height);
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
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_screen_quad_id);

				//Tell the shaders what different parts of the buffer mean using the above array
				gl::glEnableVertexAttribArray(0);
				gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(gl::GLfloat) * 3, (void*)(unsigned long)0);

				//Ready the COLOUR texture
				glid tex_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "RENDER_TEXTURE");
				gl::glUniform1i(tex_id, 0);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->draw_buffer.getTextureGLID());

				//Ready the depth texture
				//glid depth_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "DEPTH_TEXTURE");
				//gl::glActiveTexture(gl::GL_TEXTURE1);
				//gl::glUniform1i(depth_id, 0);
				//gl::glBindTexture(gl::GL_TEXTURE_DEPTH, this->draw_buffer.getDepthGLID());
				
				//Send the current time
				glid time_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "TIME");
				gl::glUniform1ui(time_id, time);

				gl::glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

				gl::glDrawArrays(gl::GL_TRIANGLES, 0, sizeof(gl::GLfloat) * 6 * 3);

				gl::glDisableVertexAttribArray(0);
			}
			
			void Renderer::preRender(RenderMethod method)
			{
				switch (method)
				{
					case (RenderMethod::Standard):
					{
						//Enable backface culling
						gl::glDisable(gl::GL_CULL_FACE);
						
						//For transparency
						gl::glEnable(gl::GL_BLEND);
						gl::glBlendFunc(gl::GL_SRC_ALPHA, gl::GL_ONE_MINUS_SRC_ALPHA);

						//Enable the depth buffer
						gl::glEnable(gl::GL_DEPTH_TEST);
						gl::glDepthFunc(gl::GL_LESS);

						// Render to our framebuffer
						gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, this->draw_buffer.getGLID());
						gl::glViewport(0, 0, this->width, this->height);
						
						//Blank the screen
						gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
						gl::glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
						
						this->standard_shader->enable();
					}
					break;
					
					case (RenderMethod::PostProcess):
					{
						//Disable backface culling
						gl::glEnable(gl::GL_CULL_FACE);
						
						//No transparency
						gl::glDisable(gl::GL_BLEND);

						//Disable the depth buffer
						gl::glDisable(gl::GL_DEPTH_TEST);
						gl::glDepthFunc(gl::GL_NONE);

						//Bind the framebuffer ready
						gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
						//Set up the viewport
						gl::glViewport(0, 0, this->width, this->height);
						
						this->postprocess_shader->enable();
						
						//Blank the screen
						//gl::glClearColor(0.0f, 0.4f, 0.0f, 0.0f);
						//gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
					}
					break;
				}
			}

			void Renderer::renderPart(Figures::Part& part, uint32 time)
			{
				//What is the buffer array composed of?
				int attribute_array[] = {sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec2)};
				
				//Make sure the part mesh is buffered
				part.getMesh().buffer();
				
				//Bind the vertex buffer
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, part.getMesh().getGLID());
				//gl::glBindTexture(gl::GL_TEXTURE_2D, this->draw_buffer.getTextureGLID());
				
				//Set up the vertex attributes
				glid offset = 0;
				for (glid array_id = 0; array_id < 4; array_id ++)
				{
					gl::glEnableVertexAttribArray(array_id);
					gl::glVertexAttribPointer(array_id, attribute_array[array_id] / sizeof(gl::GLfloat), gl::GL_FLOAT, gl::GL_FALSE, sizeof(Structures::Vertex), (void*)(unsigned long)offset);
					offset += attribute_array[array_id];
				}
				
				//Ready the COLOUR texture
				//gl::glActiveTexture(gl::GL_TEXTURE0);
				//glid texture_id = gl::glGetUniformLocation(this->standard_shader->getGLID(), "TEXTURE_TEXTURE");
				//gl::glUniform1i(texture_id, 0);
				gl::glBindTexture(gl::GL_TEXTURE_2D, part.getTexture().getGLID());
				
				//Find the uniform camera matrix, then assign it
				glid perspective_matrix_id = gl::glGetUniformLocation(this->standard_shader->getGLID(), "PERSPECTIVE_MATRIX");
				gl::glUniformMatrix4fv(perspective_matrix_id, 1, gl::GL_FALSE, &this->camera->getPerspective()[0][0]);

				//Find the uniform camera matrix, then assign it
				glid camera_matrix_id = gl::glGetUniformLocation(this->standard_shader->getGLID(), "CAMERA_MATRIX");
				gl::glUniformMatrix4fv(camera_matrix_id, 1, gl::GL_FALSE, &this->camera->getMatrix()[0][0]);
				
				//Find the uniform camera inverse matrix, then assign it
				glid camera_inverse_matrix_id = gl::glGetUniformLocation(this->standard_shader->getGLID(), "CAMERA_INVERSE_MATRIX");
				gl::glUniformMatrix4fv(camera_inverse_matrix_id, 1, gl::GL_FALSE, &this->camera->getMatrixInverse()[0][0]);
				
				//Find the uniform model vector, then assign it
				glid model_matrix_id = gl::glGetUniformLocation(this->standard_shader->getGLID(), "MODEL_MATRIX");
				State modified = part.getParent().getState();
				modified.position -= this->camera->getState().position;
				modified.update();
				mat4 sum = glm::f32mat4(1.0f);
				sum = (glm::f32mat4)modified.matrix * (glm::f32mat4)part.getState().matrix * sum;
				gl::glUniformMatrix4fv(model_matrix_id, 1, gl::GL_FALSE, &sum[0][0]);
				
				//Send the current time
				glid time_id = gl::glGetUniformLocation(this->standard_shader->getGLID(), "TIME");
				gl::glUniform1ui(time_id, time);
				
				//Draw the part
				glDrawArrays(part.getMesh().getMode(), 0, part.getMesh().getSize() * 3);
				
				//Disable all the vertex attribute arrays again
				for (int i = 0; i < 4; i ++)
					gl::glDisableVertexAttribArray(i);
			}

			void Renderer::renderFigures(Figures::FigureManager& figure_manager, uint32 time)
			{
				for (uint32 figure_count = 0; figure_count < figure_manager.getNumber(); figure_count ++)
				{
					Figures::Figure& current_figure = figure_manager.getFigure(figure_count);
					
					for (uint32 part_count = 0; part_count < current_figure.getPartNumber(); part_count ++)
					{
						Figures::Part& part = current_figure.getPart(part_count);
						
						if (part.getVisible())
							this->renderPart(part, time);
					}
				}
			}
			
			void Renderer::setCamera(Camera& camera)
			{
				this->camera = &camera;
			}
		}
	}
}
