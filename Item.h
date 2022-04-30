/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include<iostream>

#include"iProduct.h"
#include"Status.h"

namespace sdds 
{
	class Item : public iProduct 
	{
		double m_price;
		int m_qty;
		int m_qtyNeeded;
		char* m_description{};
		bool m_linear;

	protected:
		Status m_state{};
		int m_sku{};

	public:
		void setEmpty();
		Item();

		//rule of three
		Item(const Item& item);
		Item& operator=(const Item& item);
		~Item();

		int operator-=(int qty);
		int operator+=(int qty);
		operator double()const;
		operator bool()const;
		int qtyNeeded()const;
		int qty()const;
		void linear(bool isLinear);
		void clear();
		bool operator==(int sku)const;
		bool operator==(const char* description)const;
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
		int readSku(std::istream& istr);
		bool returnFlag()const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Item& i);
	std::istream& operator>>(std::istream& istr, Item& i);
}

#endif
