#ifndef VAST_RENDER_RESOURCES_BUFFEREDMESH_H
#define VAST_RENDER_RESOURCES_BUFFEREDMESH_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "structures/polygon.h"
#include "render/bufferable.h"
#include "resource.h"
#include "globject.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class BufferedMesh : public GLObject, public Resource
			{
				private:
					glid gl_buffer_id = 0;
					
					gl::GLenum mode = gl::GL_TRIANGLES;
				public:
					BufferedMesh(std::vector<Structures::Polygon> polygons);
					virtual ~BufferedMesh();
					
					gl::GLenum getMode() { return this->mode; };
					void setMode(gl::GLenum mode) { this->mode = mode; }
					
					glid getBufferGLID() { return this->gl_buffer_id; };
					
					void discard() override;
			};
		}
	}
}

#endif
