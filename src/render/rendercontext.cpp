//----LOCAL----
#include "rendercontext.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		RenderContext::RenderContext()
		{
            IO::output("Creating render context");
		}

		bool RenderContext::render()
		{
			IO::output("Rendering context");

			bool closed = false;

			//Rendering goes here

			return closed;
		}

		void RenderContext::close()
		{
			IO::output("Closing render context");
		}
	}
}
