#ifndef VAST_RENDER_RESOURCES_SHADERHOOK_H
#define VAST_RENDER_RESOURCES_SHADERHOOK_H

//----STANDARD----
#include "string"

//----LOCAL----
#include "common/basictypes.h"
#include "resource.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Shader;
			
			struct ShaderHook : public Resource
			{
				private:
					glid gl_id;
					std::string name;
				public:
					ShaderHook(Shader* shader, std::string name);
					
					glid getGLID() { return this->gl_id; }
					std::string getName() { return this->name; }
			};
		}
	}
}

#endif
