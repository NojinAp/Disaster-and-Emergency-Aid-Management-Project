/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <iostream>

namespace sdds 
{
	class Status
	{
		char* status{};
		int sCode;

	public:
		void setEmpty();

		//default constructor
		Status();

		//rule of three
		Status(const Status& stat);
		Status& operator=(const Status& stat);
		~Status();

		Status(const char* stat);
		void operator=(int code);
		void operator=(const char* stat);
		operator int() const;
		operator const char* () const;
		operator bool() const;
		Status& clear();
		std::ostream& print(std::ostream& ostr) const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Status& stat);
}

#endif 
