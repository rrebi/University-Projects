#define _CRT_SECURE_NO_WARNINGS

#include "Ui.h"
#include <iostream>
#include <windows.h>

Console::Console(AdminService& adminService, UserService& userService):
	adminService{ adminService }, userService{ userService }
{
	adminService.InitializeRepo();
}

void Console::SelectMode()
{
	bool done = false;

	while (!done)
	{
		std::cout << "Open application in:\n";
		std::cout << "1.Administrator mode\n";
		std::cout << "2.User mode\n";
		std::string mode;
		std::cin >> mode;

		if (mode.size() != 1)
		{
			std::cout << "Invalid mode!\n";
			return;
		}
		switch (mode[0])
		{
		case '1':
		{
			MainLoopAdmin();
		}
		case '2':
		{
			MainLoopUser();
		}
		default:
		{
			done = true;
			break;
		}
		}
	}
}

void Console::MainLoopAdmin()
{
	std::string command;
	bool done = false;

	while (!done)
	{
		PrintAdminMenu();
		std::cout << "\nPlease input your command:\n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout << "Invalid command!\n";
		else {
			try {
				switch (command[0])
				{
				case '1':
				{
					AddDress();
					break;
				}
				case '2':
				{
					RemoveDress();
					break;
				}
				case '3':
				{
					UpdateDress();
					break;
				}
				case '4':
				{
					PrintAllDresses();
					break;
				}
				case '0':
				{
					done = true;
					break;
				}
				default:
				{
					std::cout << "Invalid command!\n";
					break;
				}
				}

			}
			catch (std::exception& e)
			{
				std::cout << e.what() << "\n";
			}
		}
	}
}

void Console::AddDress()
{
	std::string size, color, photograph;
	size_t price, quantity;
	std::cout << "Enter the size, color, price, quantity and photograph:\n";
	std::cin >> size;
	std::cin >> color;
	std::cin >> price;
	std::cin >> quantity;
	std::cin >> photograph;

	this->adminService.AddDress(size, color, price, quantity, photograph);

}

void Console::RemoveDress()
{
	std::string photo;
	std::cout << "Enter the color of the dress you want to remove:\n";
	std::cin >> photo;

	this->adminService.RemoveDress(photo);
}

void Console::UpdateDress()
{
	std::string photo;
	std::cout << "Enter the color of the dress you want to update:\n";
	std::cin >> photo;
	std::cout << "Enter the attribute you would like to modify: "
		<< "S-size, C-color, P-price, Q-quantity, L-photograph\n";

	std::string updateAttribute;
	std::cin >> updateAttribute;

	if (updateAttribute.size() != 1)
	{
		std::cout << "Invalid command!\n";
		return;
	}
	switch (updateAttribute[0])
	{
	case 's':
	case 'S':
	{
		std::string newSize;
		std::cout << "Enter the new size of the dress:\n";
		std::cin >> newSize;
		UpdateDressSize(photo, newSize);
		break;
	}
	case 'c':
	case 'C':
	{
		std::string newColor;
		std::cout << "Enter the new color of the dress:\n";
		std::cin >> newColor;
		UpdateDressColor(photo, newColor);
		break;
	}
	case 'p':
	case 'P':
	{
		size_t newPrice;
		std::cout << "Enter the new price of the dress:\n";
		std::cin >> newPrice;
		UpdateDressPrice(photo, newPrice);
		break;
	}
	case 'q':
	case 'Q':
	{
		size_t newQuantity;
		std::cout << "Enter the new quantity of dresses:\n";
		std::cin >> newQuantity;
		UpdateDressQuantity(photo, newQuantity);
		break;
	}
	case 'l':
	case 'L':
	{
		std::string newPhoto;
		std::cout << "Enter the new photograph of the dress:\n";
		std::cin >> newPhoto;
		UpdateDressPhotograph(photo, newPhoto);
		break;
	}
	default:
	{
		std::cout << "Invalid attribute!\n";
		break;
	}
	}
}

void Console::UpdateDressSize(std::string photograph, std::string newSize)
{
	this->adminService.UpdateDressSize(photograph, newSize);
}

void Console::UpdateDressColor(std::string photograph, std::string newColor)
{
	this->adminService.UpdateDressColor(photograph, newColor);
}

void Console::UpdateDressPrice(std::string photograph, size_t newPrice)
{
	this->adminService.UpdateDressPrice(photograph, newPrice);
}

void Console::UpdateDressQuantity(std::string photograph, size_t newQuantity)
{
	this->adminService.UpdateDressQuantity(photograph, newQuantity);
}

void Console::UpdateDressPhotograph(std::string photograph, std::string newPhotograph)
{
	this->adminService.UpdateDressPhotograph(photograph, newPhotograph);
}

void Console::PrintAllDresses()
{
	std::cout << adminService.GetRepo();
}

void Console::PrintAdminMenu()
{
	std::cout << "1.Add a new dress\n";
	std::cout << "2.Remove a dress by color\n";
	std::cout << "3.Update a dress\n";
	std::cout << "4.Print all available dresses\n";
	std::cout << "0.Exit\n";
}

void Console::MainLoopUser()
{
	std::string command;
	bool done = false;

	while (!done)
	{
		PrintUserMenu();
		std::cout << "\nPlease input your command:\n";
		std::cin >> command;
		if (command.size() != 1)
			std::cout << "Invalid command!\n";
		else {
			try {
				switch (command[0])
				{
				case '1':
				{
					AddShoppingBasketNoFilter();
					break;
				}
				case '2':
				{
					AddShoppingBasketFiter();
					break;
				}
				case '3':
				{
					ViewShoppingBasket();
					break;
				}
				case '0':
				{
					done = true;
					break;
				}
				default:
				{
					break;
				}
				}

			}
			catch (std::exception& e)
			{
				std::cout << e.what() << "\n";
			}
		}
	}
}

void Console::PrintUserMenu()
{
	std::cout << "1.View all available dresses\n";
	std::cout << "1.View all available dresses by size\n";
	std::cout << "3.View shopping basket\n";
	std::cout << "0.Exit\n";
}

void Console::AddShoppingBasketNoFilter()
{
	userService.ReinitializeDressList();
	std::string command;
	bool done = false;

	while (!done)
	{
		std::cout << userService.GetCurrentDress();
		std::string photo = userService.GetCurrentDress().GetPhotograph();
		/*char* arr = new char[100];
		strcpy(arr, "start ");
		strcpy(arr, photo.c_str());
		system(arr);*/
		ShellExecuteA(NULL, NULL, "chrome.exe", userService.GetCurrentDress().GetPhotograph().c_str(), NULL, SW_SHOWMAXIMIZED);
		std::cout << "Would you like to add this dress to the shopping basket? (Y-yes, N-no, E-exit)\n";
		std::cin >> command;

		if (command.size() != 1) std::cout << "Invalid command!\n";
		else {
			try {
				switch (command[0])
				{
				case 'y':
				case 'Y':
				{
					AddShoppingBasket();
					std::cout << "Total sum: " << userService.GetSum();
					std::cout << '\n';
					break;
				}
				case 'n':
				case 'N':
				{
					NoAddShoppingBasket();
					break;
				}
				case 'e':
				case 'E':
				{
					done = true;
					break;
				}
				default:
					break;
				}
			}
			catch (std::exception& e)
			{
				std::cout << e.what();
			}
		}

	}
}

void Console::AddShoppingBasketFiter()
{
	UserReinitializationShoppingBasket();
	UserFilterBySize();
	std::string command;
	bool done = false;

	while (!done)
	{
		std::cout << userService.GetCurrentDress();
		std::string photo = userService.GetCurrentDress().GetPhotograph();
		/*char* arr = new char[100];
		strcpy(arr, "start ");
		strcpy(arr, photo.c_str());
		system(arr);*/
		ShellExecuteA(NULL, NULL, "chrome.exe", userService.GetCurrentDress().GetPhotograph().c_str(), NULL, SW_SHOWMAXIMIZED);
		std::cout << "Would you like to add this dress to the shopping basket? (Y-yes, N-no, E-exit)\n";
		std::cin >> command;

		if (command.size() != 1) std::cout << "Invalid command!\n";
		else {
			try {
				switch (command[0])
				{
				case 'y':
				case 'Y':
				{
					AddShoppingBasket();
					std::cout << "Total sum: " << userService.GetSum();
					std::cout << '\n';
					break;
				}
				case 'n':
				case 'N':
				{
					NoAddShoppingBasket();
					break;
				}
				case 'e':
				case 'E':
				{
					done = true;
					break;
				}
				default:
					break;
				}
			}
			catch (std::exception& e)
			{
				std::cout << e.what();
			}
		}

	}
}

void Console::ViewShoppingBasket()
{
	std::cout << userService.GetDressList();
	std::cout << "Total sum: " << userService.GetSum();
	std::cout << '\n';
}

void Console::AddShoppingBasket()
{
	userService.AddToShoppingBasket(userService.GetCurrentDress());
}

void Console::NoAddShoppingBasket()
{
	userService.GoToNextDress();
}

void Console::UserReinitializationShoppingBasket()
{
	userService.ReinitializeDressList();
}

void Console::UserFilterBySize()
{
	std::string size;
	std::cout << "Enter the size you like to filter by:\n";
	std::cin >> size;
	userService.FilterBySize(size);
}
