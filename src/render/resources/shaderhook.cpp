//----LOCAL----
#include "shaderhook.h"
#include "shader.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			ShaderHook::ShaderHook(Shader* shader, std::string name)
			{
				this->gl_id = gl::glGetUniformLocation(shader->getGLID(), name.c_str());
				this->name = name;
			}
		}
	}
}
