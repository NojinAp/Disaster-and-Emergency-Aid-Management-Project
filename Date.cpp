/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

#include "Date.h"
#include "Utils.h"

using namespace std;

namespace sdds 
{
	bool Date::validate()
	{
		bool flag;
		int currentYearValue;
		ut.getSystemDate(&currentYearValue);

		if (year < 2022 || year > max_year_value)
		{
			State = "Invalid year in date";
			State = 1;
			flag = false;
		}
		else if (month < 1 || month > 12)
		{
			State = "Invalid month in date";
			State = 2;
			flag = false;
		}
		else if (day < 1 || day > ut.daysOfMon(month, year))
		{
			State = "Invalid day in date";
			State = 3;
			flag = false;
		}
		else
		{
			State.clear();
			flag = true;
		}
		return flag;
	}

	int Date::uniqueDateValue() const
	{
		return year * 372 + month * 31 + day;
	}

	void Date::setEmpty()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	void Date::set(int Year, int Month, int Day)
	{
		year = Year;
		month = Month;
		day = Day;
	}

	Date::Date()
	{
		ut.getSystemDate(&year, &month, &day);
	}

	Date::Date(int Year, int Month, int Day)
	{
		set(Year, Month, Day);
		this->validate();
	}

	bool Date::operator==(const Date& date)
	{
		return (this->uniqueDateValue() == date.uniqueDateValue());
	}

	bool Date::operator!=(const Date& date)
	{
		return (this->uniqueDateValue() != date.uniqueDateValue());
	}	

	int Date::getYear() const 
	{
		return (this->year - 2000);
	}

	int Date::getMon() const 
	{
		return this->month;
	}

	int Date::getDay() const 
	{
		return this->day;
	}

	bool Date::operator<(const Date& date) 
	{
		return (this->uniqueDateValue() < date.uniqueDateValue());
	}

	bool Date::operator>(const Date& date) 
	{
		return (this->uniqueDateValue() > date.uniqueDateValue());
	}

	bool Date::operator<=(const Date& date) 
	{
		return (this->uniqueDateValue() <= date.uniqueDateValue());
	}

	bool Date::operator>=(const Date& date) 
	{
		return (this->uniqueDateValue() >= date.uniqueDateValue());
	}

	const Status& Date::state() const 
	{
		return State;
	}

	Date& Date::formatted(bool format) 
	{
		if (format) {
			isformatted = true;
		}
		else {
			isformatted = false;
		}
		return *this;
	}

	Date::operator bool() const 
	{
		if (State == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
		return State;
	}

	ostream& Date::write(ostream& ostr) const 
	{
		if (isformatted)
		{
			ostr << year << '/';
			ostr << setw(2) << setfill('0') << month << '/';
			ostr << setw(2) << setfill('0') << day;
		}
		else 
		{
			string yr = to_string(year);
			ostr << yr[2] << yr[3] << setw(2) << setfill('0') << month << day;
		}
		return ostr;
	}

	istream& Date::read(istream& istr) 
	{
		int value = -1;
		istr >> value;
		if (istr) 
		{
			if (value > 99 && value < 10000) 
			{
				time_t t = std::time(NULL);
				tm lt = *localtime(&t);
				month = int(value / 100);
				day = value - (month * 100);
				year = lt.tm_year + 1900;
			}
			else if (value > 9999 && value < 999999) 
			{
				year = 2000 + (int(value / 10000));
				month = int((value - ((year - 2000) * 10000)) / 100);
				day = value - (((year - 2000) * 10000) + (month * 100));
			}
			else if (value >= 0 && value < 100) 
			{
				year = 2022;
				month = 0;
				day = 1;
			}
			if (!validate()) 
			{
				istr.setstate(ios::failbit);
			}
		}
		else 
		{
			cout << "Invalid date value!" << endl;
		}
		return istr;
	}

	istream& operator>>(istream& istr, Date& date) 
	{
		date.read(istr);
		return istr;
	}

	ostream& operator<<(ostream& ostr, const Date& date) 
	{
		if (!date.operator bool()) 
		{
			ostr << "Bad name" << endl;
		}
		else 
		{
			date.write(ostr);
		}
		return ostr;
	}
}