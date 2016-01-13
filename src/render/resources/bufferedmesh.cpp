//----STANDARD----
#include "stdlib.h"
#include "stdio.h"
#include "fstream"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "mesh.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			BufferedMesh::~BufferedMesh()
			{
				//Destructor
			}

			BufferedMesh::BufferedMesh(std::vector<Structures::Polygon> polygons)
			{
				//Set resource type
				this->setResourceType(ResourceType::BUFFERED_MESH);
				
				//Buffer the polygons
				gl::glGenVertexArrays(1, &this->gl_id);
				gl::glBindVertexArray(this->gl_id);

				gl::glGenBuffers(1, &this->gl_buffer_id);
				gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->gl_buffer_id);

				gl::glBufferData(gl::GL_ARRAY_BUFFER, polygons.size() * sizeof(Structures::Polygon), &polygons[0], gl::GL_STATIC_DRAW);

				IO::output("Created BufferedMesh object with " + std::to_string(polygons.size()) + " polygons.");
			}

			void BufferedMesh::discard()
			{
				gl::glDeleteBuffers(1, &this->gl_buffer_id);
			}
		}
	}
}
