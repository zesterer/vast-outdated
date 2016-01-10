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
				this->postprocess_shader = &context.getResourceManager().newShaderFromFiles("../data/shaders/postprocess.vert", "../data/shaders/postprocess.frag");
			}
			
			void Renderer::update(glm::ivec2 dimensions)
			{
				this->dimensions = dimensions;
				
				this->draw_buffer.setSize(this->dimensions);
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

			void Renderer::renderPostProcess(RenderContext& context)
			{
				this->postprocess_shader->enable();
				
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_screen_quad_id);

				//Tell the shaders what different parts of the buffer mean using the above array
				gl::glEnableVertexAttribArray(0);
				gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(gl::GLfloat) * 3, (void*)(unsigned long)0);

				//Ready the COLOUR texture
				gl::glActiveTexture(gl::GL_TEXTURE0);
				glid tex_id = gl::glGetUniformLocation(this->postprocess_shader->getGLID(), "RENDER_TEXTURE");
				gl::glUniform1i(tex_id, 0);
				gl::glBindTexture(gl::GL_TEXTURE_2D, this->draw_buffer.getTextureGLID());

				//Send the current time
				this->bindIntegerWithUniform(context.getTime(), "TIME", this->postprocess_shader);

				gl::glDrawArrays(gl::GL_TRIANGLES, 0, sizeof(gl::GLfloat) * 6 * 3);

				gl::glDisableVertexAttribArray(0);
			}
			
			void Renderer::preRender(RenderMethod method, glid framebuffer_output)
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
						gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, framebuffer_output);
						gl::glViewport(0, 0, this->dimensions.x, this->dimensions.y);
						
						//Blank the screen
						gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
						gl::glClearColor(0.0f, 0.0f, 0.03f, 1.0f);
						
						//this->standard_shader->enable();
					}
					break;
					
					case (RenderMethod::PostProcess):
					{
						//Disable backface culling
						gl::glDisable(gl::GL_CULL_FACE);
						
						//No transparency
						gl::glDisable(gl::GL_BLEND);

						//Disable the depth buffer
						gl::glDisable(gl::GL_DEPTH_TEST);
						gl::glDepthFunc(gl::GL_NONE);

						//Bind the framebuffer ready
						gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, framebuffer_output);
						gl::glViewport(0, 0, this->dimensions.x, this->dimensions.y);
					}
					break;
				}
			}

			//Render a single part
			void Renderer::renderPart(Figures::Part& part, RenderContext& context)
			{
				Resources::Shader* shader = nullptr;
				if (part.hasShader())
					shader = &part.getShader();
				else //The shader index 0 is always filled with a default
					shader = &context.getResourceManager().getShader(-1);
				shader->enable();
				
				//What is the buffer array composed of?
				int attribute_array[] = {sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec3), sizeof(glm::vec2), sizeof(glm::vec3), sizeof(glm::vec3)};
				
				//Make sure the part mesh is buffered
				part.getMesh().buffer();
				
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
				this->bindContextData(context, shader);
				this->bindPartData(part, context, shader);
				this->bindCameraData(shader);
				
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
			
			void Renderer::bindVec3ArrayWithUniform(glm::vec3* vec3_array, int32 number, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform3fv(uniform_id, number, &vec3_array[0][0]);
			}
			
			void Renderer::bindFloatArrayWithUniform(float* float_array, int32 number, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform1fv(uniform_id, number, float_array);
			}
			
			void Renderer::bindIntegerArrayWithUniform(int* integer_array, int32 number, std::string uniform_name, Resources::Shader* shader)
			{
				glid uniform_id = gl::glGetUniformLocation(shader->getGLID(), uniform_name.c_str());
				gl::glUniform1iv(uniform_id, number, integer_array);
			}
			
			void Renderer::bindContextData(RenderContext& context, Resources::Shader* shader)
			{
				//Bind sun details
				this->bindVec3WithUniform(context.getLightManager().getSun().direction, "SUN_DIRECTION", shader);
				this->bindVec3WithUniform(context.getLightManager().getSun().colour, "SUN_COLOUR", shader);
				this->bindFloatWithUniform(context.getLightManager().getSun().ambiance, "SUN_AMBIANCE", shader);
				
				this->bindIntegerWithUniform(std::min((int)context.getLightManager().getNumber(), MAX_LIGHT_NUMBER), "LIGHT_NUMBER", shader);
				
				this->bindVec3ArrayWithUniform(context.getLightManager().getPriorityArrayPosition(), MAX_LIGHT_NUMBER * 3, "LIGHT_POSITION", shader);
				this->bindVec3ArrayWithUniform(context.getLightManager().getPriorityArrayColour(), MAX_LIGHT_NUMBER * 3, "LIGHT_COLOUR", shader);
				this->bindVec3ArrayWithUniform(context.getLightManager().getPriorityArrayDirection(), MAX_LIGHT_NUMBER * 3, "LIGHT_DIRECTION", shader);
				
				this->bindIntegerArrayWithUniform(context.getLightManager().getPriorityArrayType(), MAX_LIGHT_NUMBER * 3, "LIGHT_TYPE", shader);
				this->bindFloatArrayWithUniform(context.getLightManager().getPriorityArraySpotAngle(), MAX_LIGHT_NUMBER * 3, "LIGHT_SPOT_ANGLE", shader);
				this->bindFloatArrayWithUniform(context.getLightManager().getPriorityArrayAmbiance(), MAX_LIGHT_NUMBER * 3, "LIGHT_AMBIANCE", shader);
				
				//Assign the current time
				this->bindIntegerWithUniform(context.getTime(), "TIME", shader);
			}
			
			void Renderer::bindCameraData(Resources::Shader* shader)
			{
				//Assign the perspective matrix
				this->bindMatrixWithUniform(&this->camera->getPerspective(), "PERSPECTIVE_MATRIX", shader);

				//Assign the camera matrix
				this->bindMatrixWithUniform(&this->camera->getMatrix(), "CAMERA_MATRIX", shader);
				
				//Assign the camera inverse matrix
				this->bindMatrixWithUniform(&this->camera->getInverseMatrix(), "CAMERA_INVERSE_MATRIX",shader);
			}
			
			void Renderer::bindPartData(Figures::Part& part, RenderContext& context, Resources::Shader* shader)
			{
				//Bind the texture
				Resources::Texture* texture = nullptr;
				if (part.hasTexture())
					texture = &part.getTexture();
				else
					texture = &context.getResourceManager().getTexture(-1);
				texture->buffer();
				
				texture->bindToWithUniform(0, "TEXTURE_TEXTURE", *shader);
				
				//Bind the normal map
				Resources::Texture* normal_map = nullptr;
				if (part.hasNormalMap())
					normal_map = &part.getNormalMap();
				else
					normal_map = &context.getResourceManager().getTexture(-1);
				normal_map->buffer();
				
				normal_map->bindToWithUniform(1, "NORMAL_TEXTURE", *shader);
				
				//Assign the model matrix
				State modified = part.getParent().getState();
				modified.position -= this->camera->getState().position;
				modified.update();
				mat4 sum = glm::f32mat4(1.0f);
				sum = (glm::f32mat4)modified.matrix * (glm::f32mat4)part.getState().matrix * sum;
				this->bindMatrixWithUniform(&sum, "MODEL_MATRIX", shader);
				
				//Bind the material info
				Resources::Material* material = nullptr;
				if (part.hasMaterial())
					material = &part.getMaterial();
				else
					material = &context.getResourceManager().getMaterial(-1);
				
				this->bindVec3WithUniform(material->getAmbientColour(), "MATERIAL_AMBIENT_COLOUR", shader);
				this->bindVec3WithUniform(material->getDiffuseColour(), "MATERIAL_DIFFUSE_COLOUR", shader);
				this->bindVec3WithUniform(material->getSpecularColour(), "MATERIAL_SPECULAR_COLOUR", shader);
				
				this->bindFloatWithUniform(material->getSmoothness(), "MATERIAL_SMOOTHNESS", shader);
				this->bindFloatWithUniform(material->getShininess(), "MATERIAL_SHININESS", shader);
				
				this->bindFloatWithUniform(material->getTransparency(), "MATERIAL_TRANSPARENCY", shader);
			}
			
			Resources::Texture* Renderer::applyFilterToTexture(Resources::Shader* shader, Resources::Texture* in_texture, Resources::Texture* out_texture)
			{
				printf("APPLYING FILTER!\n");
				
				//Since OpenGL can't implement a texture as both an input and a target, we need to check for this
				if (in_texture == out_texture)
				{
					IO::output("Tried to apply filter to texture from the same texture", IO::OutputType::Error);
					return nullptr;
				}
				
				//Resources::Texture* out_texture = new Resources::Texture();
				DrawBuffer d_buffer(out_texture);
				d_buffer.initialise();
				
				this->preRender(RenderMethod::PostProcess, d_buffer.getGLID());
				
				shader->enable();
				
				//Bind the screen quad
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_screen_quad_id);
				//Tell the shaders what different parts of the buffer mean using the above array
				gl::glEnableVertexAttribArray(0);
				gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, sizeof(gl::GLfloat) * 3, (void*)(unsigned long)0);

				//Ready the COLOUR texture
				gl::glActiveTexture(gl::GL_TEXTURE0);
				glid tex_id = gl::glGetUniformLocation(shader->getGLID(), "COLOUR_TEXTURE");
				gl::glUniform1i(tex_id, 0);
				gl::glBindTexture(gl::GL_TEXTURE_2D, in_texture->getGLID());

				//Send the current time
				//this->bindIntegerWithUniform(context.getTime(), "TIME", this->postprocess_shader);

				gl::glDrawArrays(gl::GL_TRIANGLES, 0, sizeof(gl::GLfloat) * 6 * 3);

				gl::glDisableVertexAttribArray(0);
				
				printf("APPLIED FILTER!\n");
				
				return out_texture;
			}
		}
	}
}
