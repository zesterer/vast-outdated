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
		private:
			Manager manager;
		public:
			int initiate();
			int renderTask(Task* task);
	};
}

#endif
