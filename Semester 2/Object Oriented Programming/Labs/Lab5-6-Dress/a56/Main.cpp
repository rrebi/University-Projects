#include "Ui.h"
#include <iostream>

int main()
{
	/*
	DynamicVectorTests::TestAll();
	DressTests::TestAllDresses();
	RepositoryTests::TestAllRepo();
	AdminServicesTests::TestAllAdm();
	UserServicesTests::TestAllUser();
	*/
	Repository* repo = new Repository(8);
	AdminService* adminService = new AdminService(*repo);
	UserService* userService = new UserService(*repo);
	Console* console = new Console(*adminService, *userService);

	console->SelectMode();

	delete console;
	delete adminService;
	delete userService;
	delete repo;
	
	return 0;
	
}