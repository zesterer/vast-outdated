#include "stdio.h"

#include "util/gltype.h"
#include "app/app.h"
#include "res/manager.h"

int main(int argc, char* argv[])
{
	Vast::App::App app;
	Vast::App::app_build(app);

	Vast::Res::Manager manager;

	Vast::Res::Box<int>* int_box = manager.add<int>(7).val();
	*manager.get<int>(int_box->get_id()).val()->get_ptr() -= 3;

	Vast::Res::Box<std::string>* str_box = manager.add<std::string>("Hello, ").val();
	*str_box->get_ptr() += "Test ";
	*manager.get<std::string>(str_box->get_id()).val()->get_ptr() += "World!";

	//manager.dealloc(str_box->get_id());

	printf("n = %i\n", *manager.get<int>(int_box->get_id()).val()->get_ptr());

	Vast::Util::Result<Vast::Res::Box<std::string>*> v = manager.get<std::string>(str_box->get_id());
	if (v.is_valid())
		printf("%s!\n", v.val()->get_ptr()->c_str());
	else
		printf("Invalid!\n");

	return Vast::App::app_run(app);
}
