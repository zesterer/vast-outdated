//----LOCAL----
#include "camera.h"

namespace Vast
{
	namespace Render
	{
		Camera::Camera()
		{
			this->state.orientation = quat(glm::vec3(0.0, 3.141592 / 2.0, 3.141592 / 1.0));
		}

		void Camera::update(float screen_ratio)
		{
			this->screen_ratio = screen_ratio;
			
			//Update the internal state
			this->state.update();
			
			this->matrix = mat4(1.0);

			//Normalize the camera quaternion
			glm::normalize(this->state.orientation);
			this->matrix = glm::toMat4(this->state.orientation) * this->matrix;

			//This is no longer done due to new coordinate system!
			//Position
			//this->matrix = translate(this->matrix, glm::vec3(-this->state.position.x, -this->state.position.y, -this->state.position.z));

			//Perspective / projection
			this->perspective_matrix = glm::perspective(this->fov, this->screen_ratio, this->min_render, this->max_render);
		}

		void Camera::tick()
		{
			this->state.tick();
		}
		
		State& Camera::getState()
		{
			return this->state;
		}
		
		mat4& Camera::getMatrix()
		{
			return this->matrix;
		}
		
		mat4& Camera::getPerspective()
		{
			return this->perspective_matrix;
		}
	}
}
