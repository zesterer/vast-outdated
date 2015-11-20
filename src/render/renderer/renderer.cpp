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
				gl::glActiveTexture(gl::GL_TEXTURE0);
				glid tex_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "RENDER_TEXTURE");
				gl::glUniform1i(tex_id, 0);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->draw_buffer.getTextureGLID());

				//Ready the depth texture
				//gl::glActiveTexture(gl::GL_TEXTURE1);
				//glid depth_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "DEPTH_TEXTURE");
				//gl::glUniform1i(depth_id, 1);
				//gl::glBindTexture(gl::GL_TEXTURE_2D, this->draw_buffer.getDepthGLID());
				
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

			//Render a single part
			void Renderer::renderPart(Figures::Part& part, RenderContext& context)
			{
				//What is the buffer array composed of?
				int attribute_array[] = {sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec2), sizeof(glm::vec3), sizeof(glm::vec3)};
				
				//Make sure the part mesh is buffered
				if (part.hasTexture())
					part.getMesh().buffer();
				else
					return;
				
				//Bind the vertex buffer
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, part.getMesh().getGLID());
				
				//Set up the vertex attributes
				glid offset = 0;
				for (glid array_id = 0; array_id < 6; array_id ++)
				{
					gl::glEnableVertexAttribArray(array_id);
					gl::glVertexAttribPointer(array_id, attribute_array[array_id] / sizeof(gl::GLfloat), gl::GL_FLOAT, gl::GL_FALSE, sizeof(Structures::Vertex), (void*)(unsigned long)offset);
					offset += attribute_array[array_id];
				}
				
				//Bind the relevant data to the shader uniforms
				this->bindContextData(context);
				this->bindPartData(part, context);
				this->bindCameraData();
				
				//Assign the current time
				this->bindIntegerWithUniform(context.getTime(), "TIME", this->standard_shader);
				
				//Draw the part
				glDrawArrays(part.getMesh().getMode(), 0, part.getMesh().getSize() * 3);
				
				//Disable all the vertex attribute arrays again
				for (int i = 0; i < 4; i ++)
					gl::glDisableVertexAttribArray(i);
			}
			
			void Renderer::setCamera(Camera& camera)
			{
				this->camera = &camera;
			}
			
			void Renderer::bindMatrixWithUniform(mat4* matrix, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniformMatrix4fv(uniform_id, 1, gl::GL_FALSE, (const gl::GLfloat*)matrix);
			}
			
			void Renderer::bindIntegerWithUniform(int32 integer, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform1i(uniform_id, integer);
			}
			
			void Renderer::bindFloatWithUniform(float float_number, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform1f(uniform_id, float_number);
			}
			
			void Renderer::bindVec3WithUniform(glm::vec3 vec3_value, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform3f(uniform_id, vec3_value.x, vec3_value.y, vec3_value.z);
			}
			
			void Renderer::bindVec4WithUniform(glm::vec4 vec4_value, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform4f(uniform_id, vec4_value.x, vec4_value.y, vec4_value.z, vec4_value.w);
			}
			
			void Renderer::bindContextData(RenderContext& context)
			{
				//Bind sun details
				this->bindVec3WithUniform(context.getSun().direction, "SUN_DIRECTION", this->standard_shader);
				this->bindVec3WithUniform(context.getSun().colour, "SUN_COLOUR", this->standard_shader);
				this->bindFloatWithUniform(context.getSun().ambiance, "SUN_AMBIANCE", this->standard_shader);
			}
			
			void Renderer::bindCameraData()
			{
				//Assign the perspective matrix
				this->bindMatrixWithUniform(&this->camera->getPerspective(), "PERSPECTIVE_MATRIX", this->standard_shader);

				//Assign the camera matrix
				this->bindMatrixWithUniform(&this->camera->getMatrix(), "CAMERA_MATRIX", this->standard_shader);
				
				//Assign the camera inverse matrix
				this->bindMatrixWithUniform(&this->camera->getInverseMatrix(), "CAMERA_INVERSE_MATRIX", this->standard_shader);
			}
			
			void Renderer::bindPartData(Figures::Part& part, RenderContext& context)
			{
				if (part.hasTexture()) //Ready the colour texture
					part.getTexture().bindToWithUniform(0, "TEXTURE_TEXTURE", *this->standard_shader);
				else
					context.getNullTexture().bindToWithUniform(0, "TEXTURE_TEXTURE", *this->standard_shader);
				
				if (part.hasNormalMap()) //Ready the normal map texture
					part.getNormalMap().bindToWithUniform(1, "NORMAL_TEXTURE", *this->standard_shader);
				else
					context.getNullTexture().bindToWithUniform(1, "NORMAL_TEXTURE", *this->standard_shader);
				
				//Assign the model matrix
				State modified = part.getParent().getState();
				modified.position -= this->camera->getState().position;
				modified.update();
				mat4 sum = glm::f32mat4(1.0f);
				sum = (glm::f32mat4)modified.matrix * (glm::f32mat4)part.getState().matrix * sum;
				this->bindMatrixWithUniform(&sum, "MODEL_MATRIX", this->standard_shader);
				
				//Assign the part information (Tells the shader which resources the part has available)
				this->bindIntegerWithUniform(part.getInfoInt(), "RESOURCE_INFO", this->standard_shader);
			}
		}
	}
}
