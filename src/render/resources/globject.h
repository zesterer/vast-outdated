#ifndef VAST_RENDER_GLOBJECT_H
#define VAST_RENDER_GLOBJECT_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		class GLObject
		{
			private:
			protected:
				glid gl_id = -1;
			public:
				virtual glid getGLID() { return this->gl_id; };

				virtual void discard() = 0;
		};
	}
}

#endif
