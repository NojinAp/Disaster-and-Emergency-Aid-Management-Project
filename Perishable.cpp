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
#include <cstring>
#include <string>
#include <iomanip>

#include "Utils.h"
#include "Perishable.h"

using namespace std;

namespace sdds 
{

	Perishable::Perishable() : Item() 
	{
		m_instructions = nullptr;
		exp_date.setEmpty();
	}

	Perishable::Perishable(const Perishable& perishable) : Item(perishable) 
	{
		if (perishable) 
		{
			*this = perishable;
		}
	}

	Perishable& Perishable::operator=(const Perishable& perishable) 
	{
		if (this != &perishable) 
		{
			if (perishable) 
			{
				(Item&)*this = perishable;
				delete[] m_instructions;
				m_instructions = nullptr;
				if (perishable.m_instructions) 
				{
					ut.alocpy(m_instructions, perishable.m_instructions);
				}
				exp_date = perishable.exp_date;
			}
		}

		return *this;
	}

	Perishable::~Perishable() 
	{
		delete[] m_instructions;
		m_instructions = nullptr;
	}

	Perishable::operator bool() const
	{
		if ((m_sku >= 10000 && m_sku <= 39999) && m_state)
		{
			return true;
		}
		return false;
	}

	const Date& Perishable::expiry() const 
	{
		return exp_date;
	}

	int Perishable::readSku(istream& istr) 
	{
		int flag = 0;

		cout << "SKU: ";
		m_sku = ut.getIntRange(10000, 39999);

		return m_sku;
	}

	ofstream& Perishable::save(ofstream& ofstr) const 
	{
		if (m_state) 
		{
			if (&ofstr) 
			{
				Item::save(ofstr);
				ofstr << "\t";
				if (m_instructions) 
				{
					ofstr << m_instructions;
				}
				ofstr << "\t" << exp_date.getYear() << exp_date.getMon() << exp_date.getDay();
			}
		}
		return ofstr;
	}

	ifstream& Perishable::load(ifstream& ifstr) 
	{
		char instruction[1000] = {};

		Item::load(ifstr);

		delete[] m_instructions;
		m_instructions = nullptr;

		if (ifstr.fail()) 
		{
			m_state = "Input file stream read (perishable) failed!";
		}
		else
		{
			ifstr.getline(instruction, 1000, '\t');
			ut.alocpy(m_instructions, instruction);
			ifstr >> exp_date;
			ifstr.ignore();
		}

		return ifstr;
	}

	ostream& Perishable::display(ostream& ostr) const 
	{
		if (m_state) 
		{
			if (returnFlag()) 
			{
				Item::display(ostr);

				if (m_instructions && strcmp(m_instructions, "")) 
				{
					ostr << "*" << exp_date;
				}
				else 
				{
					ostr << " " << exp_date;
				}
			}
			else 
			{
				ostr << "Perishable ";

				Item::display(ostr);

				ostr << "Expiry date: " << exp_date << endl;
				if (m_instructions)
				{
					ostr << "Handling Instructions: " << m_instructions << endl;
				}
			}
		}
		else 
		{
			ostr << m_state << endl;
		}

		return ostr;
	}

	istream& Perishable::read(istream& istr) 
	{
		string ins;
		Item::read(istr);

		delete[] m_instructions;
		m_instructions = nullptr;

		cout << "Expiry date (YYMMDD): ";
		istr >> exp_date;
		cout << "Handling Instructions, ENTER to skip: ";
		istr.ignore();

		if (istr.peek() != '\n') 
		{
			getline(istr, ins);
			ut.alocpy(m_instructions, ins.c_str());
		}

		if (istr.fail()) 
		{
			m_state = "Perishable console date entry failed!";
		}

		return istr;
	}
}