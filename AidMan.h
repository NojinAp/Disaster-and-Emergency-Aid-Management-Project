/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include <iostream>

#include "Menu.h"
#include "iProduct.h"

namespace sdds
{
	const int sdds_max_num_items = 100;

	class AidMan
	{
		iProduct* m_product[sdds_max_num_items];
		Menu m_menu;
		int m_noOfProducts{};
		char* fileName;
		unsigned int menu();

	public:
		//default constructor
		AidMan();

		//rule of three
		AidMan(const AidMan& aid) = delete;
		AidMan& operator=(const AidMan& aid) = delete;
		~AidMan();

		void run();
		void save() const;
		void deallocate();
		int load();
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void add();
		void remove(int index);
		void addQuantity(int amount, int index);
		void reduceQuantity(int amount, int index);
		void sort();
		void shipped();
	};
}

#endif