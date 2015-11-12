//----STANDARD----
#include "stdio.h"

//----LOCAL----
#include "common/basictypes.h"
#include "settings.h"
#include "application/application.h"

int main(int32 argc, char* argv[])
{
	Vast::Application::Application application(argc, argv);

	return application.run();
}
