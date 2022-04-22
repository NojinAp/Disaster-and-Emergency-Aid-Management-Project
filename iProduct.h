/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H

#include <iostream>

namespace sdds 
{
	class iProduct 
	{

	public:
		//destructor
		virtual ~iProduct() {};

		virtual int readSku(std::istream& istr) = 0;
		virtual int operator-=(int qty) = 0;
		virtual int operator+=(int qty) = 0;
		virtual operator double()const = 0;
		virtual operator bool()const = 0;
		virtual int qtyNeeded()const = 0;
		virtual int qty()const = 0;
		virtual void linear(bool isLinear) = 0;
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0;
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		virtual std::ostream& display(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual bool operator==(int sku)const = 0;
		virtual bool operator==(const char* description)const = 0;

	};

	std::ostream& operator<<(std::ostream& ostr, iProduct& P);
	std::istream& operator>>(std::istream& istr, iProduct& P);
}

#endif