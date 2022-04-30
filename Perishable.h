/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>

#include "Item.h"
#include "Date.h"

namespace sdds 
{
	class Perishable : public Item 
	{
		Date exp_date;
		char* m_instructions{};

	public:
		//default constructor
		Perishable();

		//rule of three
		Perishable(const Perishable& perishable);
		Perishable& operator=(const Perishable& perishable);
		~Perishable();

		operator bool() const;
		const Date& expiry() const;
		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
}

#endif
