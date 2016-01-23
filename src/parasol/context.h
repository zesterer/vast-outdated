#ifndef PARASOL_CONTEXT_H
#define PARASOL_CONTEXT_H

//standard
#include "vector"

//local
#include "task.h"
#include "manager.h"

namespace Parasol
{
	class Context
	{
		Manager manager;
		
		std::vector<Task> pipeline;
	};
}

#endif
