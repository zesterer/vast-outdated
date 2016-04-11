#include "app/app.h"

#include "util/io.h"

namespace Vast
{
	namespace App
	{
		id app_id_count = 0;
		
		i32 app_run(App& app)
		{
			app._id = app_gen_id();
			
			// Debug info
			Util::output("Built new App instance with id '" + std::to_string(app._id) + "'");
			
			return 0; // No error
		}
		
		id app_gen_id()
		{
			app_id_count ++;
			return app_id_count - 1;
		}
	}
}
