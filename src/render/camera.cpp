//----LOCAL----
#include "camera.h"

namespace Vast
{
	namespace Render
	{
		Camera::Camera()
		{
			//Constructor
		}

		void Camera::update()
		{
			this->state.update();
		}

		void Camera::tick()
		{
			this->state.tick();
		}
	}
}
