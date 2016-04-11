#include "stdio.h"

#include "util/gltype.h"
#include "app/app.h"

int main(int argc, char* argv[])
{
	Vast::App::App app;
	Vast::App::app_build(app);
	
	return Vast::App::app_run(app);
}
