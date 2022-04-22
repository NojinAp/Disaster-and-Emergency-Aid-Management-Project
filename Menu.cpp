/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <cstring>

#include "Utils.h"
#include "Menu.h"

using namespace std;

namespace sdds 
{
	void Menu::setEmpty()
	{
		list = nullptr;
		availableOptions = -1;
	}

	Menu::Menu() 
	{
		setEmpty();
	}

	Menu::~Menu()
	{
		delete[] list;
		list = nullptr;
	}

	Menu::operator bool() const 
	{
		if (availableOptions > max_num_options || list == nullptr) 
		{
			return false;
		}
		return true;
	}

	bool Menu::isValid() 
	{
		if (availableOptions > max_num_options || list == nullptr) 
		{
			return false;
		}
		return true;
	}

	Menu::Menu(const char* List, unsigned int AvOptions) 
	{
		if (isValid()) 
		{
			availableOptions = AvOptions;
			ut.alocpy(list, List);
		}
		else 
		{
			operator bool();
			setEmpty();
		}
	}

	unsigned int Menu::run() const 
	{
		unsigned int numOfOptions = -1;
		unsigned int value;

		for (unsigned int i = 0; i < strlen(list); i++) 
		{
			if (list[i] != '\n') 
			{
				cout << list[i];
			}
			else 
			{
				cout << '\n';
				numOfOptions++;
			}
		}
		cout << "0- Exit" << endl << "> ";

		value = ut.getIntRange(0, numOfOptions);
		return value;
	}

	void Menu::setMenu(const char* List)
	{
		ut.alocpy(list, List);
	}
}