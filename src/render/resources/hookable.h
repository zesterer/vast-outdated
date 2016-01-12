#ifndef VAST_RENDER_RESOURCES_HOOKABLE_H
#define VAST_RENDER_RESOURCES_HOOKABLE_H

//----LOCAL----
#include "globject.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			//Forward declarations
			class Shader;
			class ShaderHook;
			
			//Hookable objects are GLObjects that have the ability to be hooked into a shader uniform
			class Hookable : public GLObject
			{
				private:
				public:
					hookTo(Shader* shader, ShaderHook* hook);
			};
		}
	}
}

#endif
