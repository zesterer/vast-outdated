#ifndef VAST_RENDER_RENDERER_RENDERER_H
#define VAST_RENDER_RENDERER_RENDERER_H

//----LOCAL----
#include "common/basictypes.h"
#include "figures/part.h"
#include "resources/shader.h"
#include "drawbuffer.h"
#include "camera.h"

namespace Vast
{
	namespace Render
	{
		class RenderContext;

		namespace Renderer
		{
			enum RenderMethod
			{
				Standard,
				PostProcess
			};
			
			class Renderer
			{
				private:
					glid gl_screen_quad_id;
					
					Camera* camera = nullptr;

					Resources::Shader* postprocess_shader;
					
					glm::ivec2 dimensions = glm::ivec2(1, 1);
					
					DrawBuffer draw_buffer;
				public:
					Renderer();
					void initiate(RenderContext& context);
					void bufferScreenQuad();
					
					void update(glm::ivec2 dimensions);

					void preRender(RenderMethod method, glid framebuffer_output = 0);
					
					DrawBuffer& getDrawBuffer() { return this->draw_buffer; }

					void renderPart(Figures::Part& part, RenderContext& context);
					void renderPostProcess(RenderContext& context);
					
					void bindMatrixWithUniform(mat4* matrix, std::string uniform_name, Resources::Shader* shader);
					void bindIntegerWithUniform(int32 integer, std::string uniform_name, Resources::Shader* shader);
					void bindFloatWithUniform(float float_number, std::string uniform_name, Resources::Shader* shader);
					void bindVec3WithUniform(glm::vec3 vec3_value, std::string uniform_name, Resources::Shader* shader);
					void bindVec4WithUniform(glm::vec4 vec4_value, std::string uniform_name, Resources::Shader* shader);
					
					void bindVec3ArrayWithUniform(glm::vec3* vec3_array, int32 number, std::string uniform_name, Resources::Shader* shader);
					void bindFloatArrayWithUniform(float* float_array, int32 number, std::string uniform_name, Resources::Shader* shader);
					void bindIntegerArrayWithUniform(int* integer_array, int32 number, std::string uniform_name, Resources::Shader* shader);
					
					void bindContextData(RenderContext& context, Resources::Shader* shader);
					void bindCameraData(Resources::Shader* shader);
					void bindPartData(Figures::Part& part, RenderContext& context, Resources::Shader* shader);
					
					void setCamera(Camera& camera);
					
					Resources::Texture* applyFilterToTexture(Resources::Shader* shader, Resources::Texture* in_texture, Resources::Texture* out_texture);
			};
		}
	}
}

#endif
