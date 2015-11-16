//----LOCAL----
#include "state.h"

namespace Vast
{
	void State::update()
	{
		this->matrix = glm::f64mat4(1.0f);
		
		this->matrix = glm::translate(this->matrix, this->position);
		this->matrix *= glm::toMat4(this->orientation);
		this->matrix = glm::scale(this->matrix, this->scale);
	}

	void State::tick()
	{
		this->position += this->velocity;

		glm::normalize(this->spin);
		this->orientation = this->spin * this->orientation;
	}
}
