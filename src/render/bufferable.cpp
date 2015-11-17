//----LOCAL----
#include "bufferable.h"

namespace Vast
{
	namespace Render
	{
		void Bufferable::buffer(bool force)
		{
			//Buffer any data to the GPU
		}

		void Bufferable::discard()
		{
			//Discard any data buffered to the GPU
		}
		
		void Bufferable::setGLID(glid gl_id)
		{
			this->gl_id = gl_id;
		}
		
		glid Bufferable::getGLID()
		{
			return this->gl_id;
		}
	}
}
