#ifndef PARASOL_TASK_H
#define PARASOL_TASK_H

//standard
#include "vector"

//local
#include "hook.h"

namespace Parasol
{
	class Task
	{
		std::vector<Hook> hooks;
	};
}

#endif
