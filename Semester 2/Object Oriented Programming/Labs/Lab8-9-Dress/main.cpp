#include "Ui.h"
#include <iostream>

int main()
{
	
	/*DressTests::TestAllDresses();
	RepositoryTests::TestAllRepo();
	AdminServicesTests::TestAllAdm();
	UserServicesTests::TestAllUser();*/
	
	Repository* repo = new FileRepository("file.txt");
	AdminService* adminService = new AdminService(*repo);
	UserService* userService = new UserService(*repo);
	Console* console = new Console(*adminService, *userService);

	console->Start();

	delete console;
	delete adminService;
	delete userService;
	delete repo;
	/*int c = _CrtDumpMemoryLeaks();
	std::cout << c << "\n";
	system("pause");*/
	return 0;
}