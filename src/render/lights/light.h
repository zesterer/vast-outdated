#ifndef VAST_RENDER_LIGHTS_LIGHT_H
#define VAST_RENDER_LIGHTS_LIGHT_H

//----LOCAL----
#include "common/basictypes.h"

namespace Vast
{
	namespace Render
	{
		namespace Lights
		{
			enum LightType
			{
				Point,
				Spot,
			};
			
			struct Light
			{
				private:
				public:
					LightType type;
					
					Light();
			};
		}
	}
}

#endif
