/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Status.h"

namespace sdds 
{
	const int max_year_value = 2030;

	class Date
	{
		int year;
		int month;
		int day;
		Status State;
		bool isformatted = true;
		bool validate();
		int uniqueDateValue() const;

	public:
		void setEmpty();
		void set(int Year, int Month, int Day);

		//default constructor
		Date();

		Date(int Year, int Month, int Day);
		bool operator==(const Date& date);
		bool operator!=(const Date& date);
		int getYear() const;
		int getMon() const;
		int getDay() const;
		bool operator<(const Date& date);
		bool operator>(const Date& date);
		bool operator<=(const Date& date);
		bool operator>=(const Date& date);
		const Status& state() const;
		Date& formatted(bool format);
		operator bool() const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};

	std::ostream& operator<<(std::ostream& ostr, const Date& date);
	std::istream& operator>>(std::istream& istr, Date& d);
}

#endif