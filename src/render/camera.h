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
				mat4 matrix;
				mat4 matrix_inverse;
				mat4 perspective_matrix;
				
				float fov = 1.0;
				float min_render = 0.01;
				float max_render = 10000.0;
				float screen_ratio = 1.0;
				float fog_distance = 0.0f; //Make equal to 0.0 to remove fog
				
				State state;
			public:
				Camera();
				void update(float screen_ratio);
				void tick();
				
				State& getState();
				mat4& getMatrix();
				mat4& getInverseMatrix();
				mat4& getPerspective();
		};
	}
}

#endif
