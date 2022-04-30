/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>

#include "Utils.h"
#include "Status.h"

using namespace std;

namespace sdds 
{
	void Status::setEmpty()
	{
		sCode = 0;
		status = nullptr;
	}

	Status::Status() 
	{
		setEmpty();
	}

	Status::Status(const Status& stat) 
	{
		sCode = stat.sCode;
		ut.alocpy(status, stat.status);
	}

	Status& Status::operator=(const Status& stat) 
	{
		if (this != &stat)
		{
			sCode = stat.sCode;
			ut.alocpy(status, stat.status);
		}
		return *this;
	}

	Status::~Status() 
	{
		delete[] status;
		status = nullptr;
	}

	Status::Status(const char* stat)
	{
		ut.alocpy(status, stat);
		sCode = 0;
	}

	void Status::operator=(int code) 
	{
		this->sCode = code;
	}

	void Status::operator=(const char* stat) 
	{
		ut.alocpy(status, stat);
	}

	Status::operator int() const 
	{
		return sCode;
	}

	Status::operator const char* () const 
	{
		return status;
	}

	Status::operator bool() const
	{
		if (status == nullptr) 
		{
			return true;
		}

		else 
		{
			return false;
		}
	}

	Status& Status::clear() 
	{
		delete[] status;
		status = nullptr;

		sCode = 0;

		return *this;
	}

	ostream& Status::print(ostream& ostr) const 
	{
		if (sCode != 0) 
		{
			ostr << "ERR#" << sCode << ": ";
		}
		ostr << status << endl;
		return ostr;
	}

	ostream& operator<<(ostream& ostr, const Status& stat) 
	{
		if (!stat)
		{
			stat.print(ostr);
		}
		return ostr;
	}
}
