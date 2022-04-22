/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

#include "Utils.h"
#include "AidMan.h"
#include "Perishable.h"
#include "Item.h"
#include "Date.h"

using namespace std;

namespace sdds
{
	AidMan::AidMan()
	{
		m_menu.setMenu("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n");
		fileName = nullptr;
	}

	AidMan::~AidMan()
	{
		delete[] fileName;
		fileName = nullptr;

		m_noOfProducts = 0;

		for (int i = 0; i < m_noOfProducts; i++)
		{
			delete m_product[i];
		}
	}

	unsigned int AidMan::menu()
	{
		Date C;
		cout << "Aid Management System" << endl;
		cout << "Date: " << C << endl;
		if (fileName)
		{
			cout << "Data file: " << fileName << endl;
		}
		else
		{
			cout << "Data file: No file" << endl;
		}
		cout << "---------------------------------" << endl;
		int selection = m_menu.run();
		return selection;
	}

	void AidMan::run()
	{
		int selection, items, row = 0;
		string userDescription1, userDescription2;
		char* decrip1 = nullptr;
		char* decrip2 = nullptr;

		do 
		{
			selection = menu();

			if (fileName == nullptr && selection != 0 && selection != 7) {
				selection = 7;
			}

			switch (selection) {
			case 1:
				if (m_noOfProducts > 0)
				{
					cout << endl << "****List Items****" << endl;

					items = list();

					if (items > 1)
					{
						cout << "Enter row number to display details or <ENTER> to continue:\n> ";
						cin.clear();
						row = cin.get();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						if (row == '\n')
						{
							break;
						}

						row -= 48;

						if (row > m_noOfProducts || row == 0)
						{
							cout << "The list is emtpy!" << endl << endl;
							break;
						}

						m_product[row - 1]->linear(false);
						cout << *m_product[row - 1] << endl;
					}
				}
				else
				{
					cout << "The list is emtpy!" << endl << endl;
				}
				break;
			case 2:
				cout << endl << "****Add Item****" << endl;
				add();
				break;
			case 3:
				int index1;
				cout << endl << "****Remove Item****" << endl;
				cout << "Item description: ";
				cin >> userDescription1;
				ut.alocpy(decrip1, userDescription1.c_str());

				if (list(decrip1) > 0)
				{
					cout << "Enter SKU: ";
					index1 = search(ut.getint());

					if (index1 != -1)
					{
						int option1;
						cout << "Following item will be removed: " << endl;
						m_product[index1]->linear(false);
						cout << *m_product[index1] << endl;
						cout << "Are you sure?\n";
						cout << "1- Yes!\n";
						cout << "0- Exit\n";
						cout << ">";
						option1 = ut.getIntRange(0, 1);

						if (option1 == 1)
						{
							remove(index1);
							cout << "Item removed!" << endl << endl;
							delete[] decrip1;
						}
						else
						{
							cout << "Aborted!" << endl << endl;
							break;
						}

					}
					else
					{
						cout << "SKU not found!" << endl << endl;
					}
				}
				else
				{
					cout << "The list is emtpy!" << endl << endl;
				}
				break;
			case 4:
				int index2;
				decrip2 = nullptr;
				cout << endl << "****Update Quantity****" << endl;
				cout << "Item description: ";
				cin >> userDescription2;
				ut.alocpy(decrip2, userDescription2.c_str());

				if (list(decrip2) > 0)
				{
					cout << "Enter SKU: ";
					index2 = search(ut.getint());

					if (index2 != -1)
					{
						int option2;
						cout << "1- Add\n";
						cout << "2- Reduce\n";
						cout << "0- Exit\n";
						cout << "> ";
						option2 = ut.getIntRange(0, 2);

						if (option2 == 1)
						{
							int quantity1 = 0;

							if (m_product[index2]->qtyNeeded() == m_product[index2]->qty())
							{
								cout << "Quantity Needed already fulfilled!" << endl << endl;
							}
							else
							{
								cout << "Quantity to add: ";
								addQuantity(quantity1, index2);
							}
						}
						else if (option2 == 2)
						{
							int quantity2 = 0;

							if (m_product[index2]->qty() == 0)
							{
								cout << "Quaintity on hand is zero!" << endl << endl;
							}
							else
							{
								cout << "Quantity to reduce: ";

								reduceQuantity(quantity2, index2);
							}
						}
						else
						{
							cout << "Aborted!" << endl << endl;
						}
					}
					else
					{
						cout << "SKU not found!" << endl << endl;
					}
				}
				delete[] decrip2;

				break;
			case 5:
				cout << endl << "****Sort****" << endl;
				sort();
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl;
				shipped();
				break;
			case 7:
				cout << endl << "****New/Open Aid Database****" << endl;
				cout << "Enter file name: ";
				string file;
				cin >> file;
				ut.alocpy(fileName, file.c_str());

				if (load() == 2)
				{
					cout << m_noOfProducts << " records loaded!" << endl << endl;
				}
				else if (load() == 1) 
				{
					cout << "Failed to open " << fileName << " for reading!" << endl << endl;
				}
				else
				{
					cout << "File is empty!" << endl << endl;
				}

				break;
			}

		} while (selection != 0);

		save();
		cout << "Exiting Program!" << endl;
	}

	void AidMan::save() const {
		if (fileName && m_noOfProducts > 0)
		{
			ofstream ofstr;
			ofstr.open(fileName, ios::out);

			for (int i = 0; i < m_noOfProducts; i++)
			{
				m_product[i]->save(ofstr);
				ofstr << endl;
			}
			ofstr.close();
		}
	}

	void AidMan::deallocate()
	{
		m_noOfProducts = 0;

		for (int i = 0; i < m_noOfProducts; i++) {
			delete m_product[i];
		}
	}

	int AidMan::load() 
	{
		int result = 0;
		save();
		deallocate();
		ifstream fstr;
		fstr.open(fileName, ios::in);

		if (fstr.fail()) 
		{
			result = 1;
		}
		else {
			while (!fstr.fail()) {
				int unitNumebr;
				ifstream newstr;
				unitNumebr = fstr.peek() - 48;

				if (unitNumebr < 4 && unitNumebr > 0) {

					m_product[m_noOfProducts] = new Perishable;
				}
				else if (unitNumebr < 10 && unitNumebr > 3) {

					m_product[m_noOfProducts] = new Item;
				}
				else {

					fstr.setstate(ios::failbit);
					continue;
				}
				if (m_product[m_noOfProducts]) {

					m_product[m_noOfProducts]->load(fstr);
					m_noOfProducts++;
				}
			}
		}

		if (m_noOfProducts > 0) {
			result = 2;
		}

		return result;
	}

	int AidMan::list(const char* sub_desc) 
	{
		int count = 0;

		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		if (sub_desc)
		{
			for (int i = 0; i < m_noOfProducts; i++)
			{
				if (m_product[i]->operator == (sub_desc))
				{
					m_product[i]->linear(true);
					cout << right << setw(4) << setfill(' ') << i + 1 << " | " << *m_product[i] << endl;
					count += 1;
				}

			}
		}
		else
		{
			for (int i = 0; i < m_noOfProducts; i++)
			{
				m_product[i]->linear(true);
				cout << right << setw(4) << setfill(' ') << i + 1 << " | " << *m_product[i] << endl;

			}
			count = m_noOfProducts;

		}
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		return m_noOfProducts;
	}

	int AidMan::search(int sku) const 
	{
		int index = -1;

		for (int i = 0; i < m_noOfProducts; i++)
		{
			if (*m_product[i] == sku)
			{
				index = i;
			}
		}
		return index;
	}

	void AidMan::add() 
	{
		if (m_noOfProducts >= sdds_max_num_items) 
		{
			cout << "Database full!" << endl;
		}

		else 
		{
			iProduct* pro = {};
			cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
			int choice = ut.getIntRange(0, 2);

			if (choice == 0) 
			{
				cout << "Aborted\n";
			}
			else 
			{
				if (choice == 1) 
				{
					pro = new Perishable();
				}
				if (choice == 2) 
				{
					pro = new Item();
				}

				int sku;
				sku = pro->readSku(cin);

				if (search(sku) != -1) 
				{
					cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl << endl;
					delete pro;
				}
				else 
				{
					cin >> *pro;
					cout << endl;
					if (pro)
					{
						m_product[m_noOfProducts] = pro;
						m_noOfProducts += 1;
					}
				}
			}
		}
	}

	void AidMan::remove(int index)
	{
		delete m_product[index];

		for (int i = index; i < m_noOfProducts; i++)
		{
			m_product[i] = m_product[i + 1];
		}
		m_noOfProducts -= 1;

	}

	void AidMan::addQuantity(int amount, int index)
	{
		amount = ut.getIntRange(1, m_product[index]->qtyNeeded() - m_product[index]->qty());
		*m_product[index] += amount;
		cout << amount << " items added!" << endl << endl;
	}

	void AidMan::reduceQuantity(int amount, int index)
	{
		amount = ut.getIntRange(1, m_product[index]->qty());
		*m_product[index] -= amount;
		cout << amount << " items removed!" << endl << endl;

	}

	void AidMan::sort() 
	{
		for (int i = 0; i < m_noOfProducts; i++)
		{
			for (int j = i + 1; j < m_noOfProducts; j++)
			{
				if ((m_product[j]->qtyNeeded() - m_product[j]->qty()) > (m_product[i]->qtyNeeded() - m_product[i]->qty()))
				{
					iProduct& temp = *m_product[i];
					m_product[i] = m_product[j];
					m_product[j] = &temp;
				}
			}
		}
		cout << "Sort completed!" << endl << endl;
	}

	void AidMan::shipped() 
	{
		ofstream ofstr;
		Date C;
		int count = 0;
		int index = -1;

		ofstr.open("shippingOrder.txt", ios::out);
		ofstr << "Shipping Order, Date: " << C << endl;
		ofstr << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		for (int i = 0; i < m_noOfProducts; i++)
		{
			if (m_product[i]->qty() == m_product[i]->qtyNeeded()) 
			{
				m_product[i]->linear(true);
				ofstr << right << setw(4) << setfill(' ') << count + 1 << " | " << *m_product[i] << endl;
				count++;
				index = i;
				remove(index);
			}
		}

		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;	
		cout << "Shipping Order for " << count << " times saved!" << endl << endl;
	}
}