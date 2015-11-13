#ifndef VAST_RENDER_CAMERA_H
#define VAST_RENDER_CAMERA_H

//----LOCAL----
#include "common/state.h"

namespace Vast
{
	namespace Render
	{
		class Camera
		{
			private:
				State state;
			public:
				Camera();
				void update();
				void tick();
		};
	}
}

#endif
