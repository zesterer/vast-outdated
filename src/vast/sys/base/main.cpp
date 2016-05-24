#include "stdio.h"

#include "vast/com/atomic/gltype.h"
#include "vast/sys/app/app.h"
#include "vast/com/resource/manager.h"

int main(int argc, char* argv[])
{
	Vast::Sys::App::App app;
	app.build();

	Vast::Com::Resource::Manager manager;

	Vast::Com::Resource::Box<int>* int_box = manager.add<int>(7).val();
	*manager.get<int>(int_box->get_id()).val() -= 3;

	Vast::Com::Resource::Box<std::string>* str_box = manager.add<std::string>("Hello, ").val();
	*str_box->ptr() += "Test ";
	*manager.get<std::string>(str_box->get_id()).val() += "World!";

	//manager.dealloc(str_box->get_id());

	printf("n = %i\n", *manager.get<int>(int_box->get_id()).val());

	Vast::Result<std::string*> v = manager.get<std::string>(str_box->get_id());
	if (v.is_valid())
		printf("%s!\n", v.val()->c_str());
	else
		printf("Invalid!\n");

	return app.run();
}
