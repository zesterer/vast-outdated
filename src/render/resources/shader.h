#ifndef VAST_RENDER_RESOURCES_SHADER_H
#define VAST_RENDER_RESOURCES_SHADER_H

//----STANDARD----
#include "string"

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Shader
			{
				private:
					glid gl_id;
				public:
					void enable();
					void loadFromFiles(std::string vertex_file_path, std::string fragment_file_path);
					void loadFromStrings(std::string vertex_shader_code, std::string fragment_shader_code);
			};
		}
	}
}

#endif
