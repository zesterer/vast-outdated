#ifndef VAST_APP_APP
#define VAST_APP_APP

#include "util/type.h"

namespace Vast
{
	namespace App
	{
		struct App
		{
			id _id;
		};
		
		i32 app_run(App& app);
		id app_gen_id();
	}
}

#endif
