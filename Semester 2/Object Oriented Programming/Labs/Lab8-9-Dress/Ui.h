#pragma once
#include "AdministratorService.h"
#include "UserService.h"

class Console
{
public:
	Console(AdminService& adminService, UserService& userService);

	void Start();

	void SelectWriterMode();
	void SelectMode();
	void MainLoopAdmin();

	void AddDress();
	void RemoveDress();
	void UpdateDress();
	void UpdateDressSize(std::string photograph, std::string newSize);
	void UpdateDressColor(std::string photograph, std::string newColor);
	void UpdateDressPrice(std::string photograph, size_t newPrice);
	void UpdateDressQuantity(std::string photograph, size_t newQuantity);
	void UpdateDressPhotograph(std::string photograph, std::string newPhotograph);
	void PrintAllDresses();

	void PrintAdminMenu();

	void ReadFromFile(const std::string& file);

	void MainLoopUser();
	void PrintUserMenu();
	void AddShoppingBasketNoFilter();
	void AddShoppingBasketFiter();
	void ViewShoppingBasket();
	void AddShoppingBasket();
	void NoAddShoppingBasket();
	void UserReinitializationShoppingBasket();
	void UserFilterBySize();


private:
	AdminService adminService;
	UserService userService;
};

