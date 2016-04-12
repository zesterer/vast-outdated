#include "stdio.h"

#include "util/gltype.h"
#include "app/app.h"
#include "res/manager.h"

int main(int argc, char* argv[])
{
	Vast::App::App app;
	Vast::App::app_build(app);

	Vast::Res::ResManager manager;
	Vast::Res::ResBox<int> int_box = manager.alloc<int>().value();
	*int_box.value() = 5;
	*manager.get<int>(int_box._id).value().value() += 7;
	//manager.dealloc(int_box._id);

	auto v = manager.get<int>(int_box._id);

	if (v.is_valid())
		printf("%i!\n", *v.value().value());
	else
		printf("Invalid!\n");

	return Vast::App::app_run(app);
}
