#ifndef VAST_RENDER_BUFFERABLE_H
#define VAST_RENDER_BUFFERABLE_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		class Bufferable
		{
			private:
			public:
				glid gl_id;
				bool buffered = false;

				virtual void buffer();
				virtual void discard();
		};
	}
}

#endif
