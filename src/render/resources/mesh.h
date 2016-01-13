#ifndef VAST_RENDER_RESOURCES_MESH_H
#define VAST_RENDER_RESOURCES_MESH_H

//----STANDARD----
#include "vector"

//----LOCAL----
#include "structures/polygon.h"
#include "render/bufferable.h"
#include "resource.h"
#include "structures/face.h"
#include "bufferedmesh.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			class Mesh : public Bufferable, public Resource
			{
				private:
					glid gl_buffer_id = 0;
					
					std::vector<Structures::Polygon> polygons;
					
					gl::GLenum mode = gl::GL_TRIANGLES;
				public:
					Mesh();
					virtual ~Mesh();
					Mesh(std::string filename);
					void addPolygon(Structures::Polygon polygon);
					bool loadFromFile(std::string filename);
					
					void setMode(gl::GLenum mode);
					
					glid getBufferGLID();
					gl::GLenum getMode();
					uint32 getSize();

					void buffer(bool force = false) override;
					void discard() override;
					
					/* REWRITE METHODS */
					
					BufferedMesh* bufferToGLObject();
			};
		}
	}
}

#endif
