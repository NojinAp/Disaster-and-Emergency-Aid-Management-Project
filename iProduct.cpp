/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "iProduct.h"

using namespace std;

namespace sdds 
{
	istream& operator>>(istream& istr, iProduct& P) 
	{
		P.read(istr);
		return istr;
	}

	ostream& operator<<(ostream& ostr, iProduct& P) 
	{
		P.display(ostr);
		return ostr;
	}
}