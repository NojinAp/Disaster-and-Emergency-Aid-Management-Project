/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds 
{
	const int max_num_options = 15;

	class Menu
	{
		char* list{};
		unsigned int availableOptions;

	public:
		void setEmpty();

		//default constructor
		Menu();

		//rule of three
		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;
		~Menu();

		operator bool() const;
		bool isValid();
		Menu(const char* List, unsigned int AvOptions);
		unsigned int run() const;
		void setMenu(const char* List);
	};
}

#endif 
