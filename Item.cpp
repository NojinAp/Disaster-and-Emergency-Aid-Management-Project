/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>

#include "Utils.h"
#include"Item.h"

using namespace std;

namespace sdds 
{
	void Item::setEmpty() 
	{
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_linear = false;
	}

	Item::Item() : iProduct() 
	{
		setEmpty();
	}

	Item::Item(const Item& item) : iProduct(item) 
	{
		if (item) 
		{
			*this = item;
		}
	}

	Item& Item::operator=(const Item& item) 
	{
		if (this != &item) 
		{
			if (item) 
			{
				(iProduct&)*this = item;
				delete[] m_description;
				m_description = nullptr;

				if (item.m_description != nullptr) 
				{
					m_description = new char[strlen(item.m_description) + 1];
					strcpy(m_description, item.m_description);
				}

				m_sku = item.m_sku;
				m_state = item.m_state;
				m_price = item.m_price;
				m_qty = item.m_qty;
				m_qtyNeeded = item.m_qtyNeeded;
				m_linear = item.m_linear;
			}
		}
		return *this;
	}

	Item::~Item() 
	{
		delete[] m_description;
		m_description = nullptr;
	}

	int Item::operator-=(int qty) 
	{
		m_qty -= qty;
		return m_qty;
	}

	int Item::operator+=(int qty) 
	{
		m_qty += qty;
		return m_qty;
	}

	Item::operator double()const 
	{
		return m_price;
	}

	Item::operator bool()const 
	{
		return m_state;
	}

	int Item::qtyNeeded()const 
	{
		return m_qtyNeeded;
	}

	int Item::qty()const 
	{
		return m_qty;
	}

	void Item::linear(bool isLinear) 
	{
		m_linear = isLinear;
	}

	void Item::clear() 
	{
		if (!m_state) 
		{
			m_state.clear();
		}
	}

	bool Item::operator==(int sku)const 
	{
		if (m_sku == sku) 
		{
			return true;
		}
		return false;
	}

	bool Item::operator==(const char* description)const 
	{
		string key = description;
		string descStr = m_description;

		if (!description || !m_description)
		{
			return false;
		}

		if (descStr.find(key) != string::npos) {
			return true;
		}
		else
		{ 
			return false; 
		}
	}

	ofstream& Item::save(ofstream& ofstr) const 
	{
		if (m_state) 
		{
			if (&ofstr) 
			{
				ofstr << m_sku << "\t" << m_description << "\t" << m_qty << "\t" << m_qtyNeeded << "\t" << m_price;
			}
		}
		return ofstr;
	}

	ifstream& Item::load(ifstream& ifstr) 
	{
		char description[1000] = {};

		delete[] m_description;
		m_description = nullptr;

		if (ifstr.fail()) 
		{
			m_state = "Input file stream read failed!";
		}
		else
		{
			ifstr >> m_sku;
			ifstr.ignore();
			ifstr.getline(description, 1000, '\t');
			ut.alocpy(m_description, description);
			ifstr >> m_qty;
			ifstr.ignore();
			ifstr >> m_qtyNeeded;
			ifstr.ignore();
			ifstr >> m_price;
			ifstr.ignore();
		}

		return ifstr;
	}

	ostream& Item::display(ostream& ostr)const 
	{
		if (!m_state) 
		{
			ostr << m_state << endl;
		}
		else 
		{
			if (m_linear) 
			{
				if (strlen(m_description) > 35)
				{
					ostr << setfill(' ') << m_sku << setw(2) << " | ";
					for (int i = 0; i < 35; i++) 
					{
						ostr << m_description[i];
					}

					ostr << setfill(' ') << setw(3) << right << "| " << setw(4) << m_qty << setw(2) << "|" << setw(5) << m_qtyNeeded << setw(2) << "|" << setw(8) << m_price << setw(2) << "|";
				}
				else 
				{
					ostr << setfill(' ') << left << setw(6) << m_sku << setw(2) << '|';
					ostr << setfill(' ') << left << setw(36) << m_description << '|';
					ostr << setfill(' ') << right << fixed << setw(5) << m_qty << setw(2) << '|';
					ostr << setfill(' ') << right << setw(5) << m_qtyNeeded << setw(2) << '|';
					ostr << setfill(' ') << right << setw(8) << setprecision(2) << m_price << setw(2) << '|';
				}
			}
			else 
			{
				double result;
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_description << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qty << endl;
				ostr << "Unit Price: $" << m_price << endl;
				result = m_price * (m_qtyNeeded - m_qty);
				ostr << "Needed Purchase Fund: $" << fixed << setprecision(2) << result << endl;
			}
		}
		return ostr;
	}

	istream& Item::read(istream& istr) 
	{
		int flag = 0;
		string des;
		m_state.clear();

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_sku << endl;
		cout << "Description: ";

		getline(istr, des);
		ut.alocpy(m_description, des.c_str());

		cout << "Quantity Needed: ";
		m_qtyNeeded = ut.getIntRange(1, 9999);

		cout << "Quantity On Hand: ";
		m_qty = ut.getIntRange(0, m_qtyNeeded);

		cout << "Unit Price: $";

		do 
		{
			istr >> m_price;
			if (istr.get() != '\n') 
			{
				cout << "Invalid number, retry: ";
				istr.clear();
				while (istr.get() != '\n');
			}
			else if (m_price < 0.00 || m_price > 9999.00) 
			{
				cout << "Value out of range [0.00<=val<=9999.00]: ";
				istr.clear();
			}
			else 
			{
				flag = 1;
			}
		} while (flag == 0);

		if (istr.fail()) 
		{
			m_state = "Console entry failed!";
		}

		return istr;
	}

	int Item::readSku(istream& istr) 
	{
		cout << "SKU: ";
		m_sku = ut.getIntRange(40000, 99999);

		return m_sku;
	}

	bool Item::returnFlag() const 
	{
		return m_linear;
	}

	istream& operator>>(istream& istr, Item& i) 
	{
		i.read(istr);
		return istr;
	}

	ostream& operator<<(ostream& ostr, const Item& i) 
	{
		i.display(ostr);
		return ostr;
	}
}
