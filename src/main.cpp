#include "stdio.h"

#include "util/gltype.h"
#include "app/app.h"
#include "res/manager.h"

int main(int argc, char* argv[])
{
	Vast::App::App app;
	Vast::App::app_build(app);

	Vast::Res::ResManager manager;

	Vast::Res::ResBox<std::string> str_box = manager.add<std::string>("Hello, ").value();
	*str_box.ptr() += "testing ";
	*manager.get<std::string>(str_box._id).value().ptr() += "World!";
	//manager.dealloc(str_box._id);

	Vast::Util::Result<Vast::Res::ResBox<std::string>> v = manager.get<std::string>(str_box._id);
	if (v.is_valid())
		printf("%s!\n", v.value().ptr()->c_str());
	else
		printf("Invalid!\n");

	return Vast::App::app_run(app);
}
