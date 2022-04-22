/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
    Name   : Nozhin Azarpanah
    Date   : April 11, 2022

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <cstring>

#include "Utils.h"

using namespace std;

namespace sdds 
{
    Utils ut;

    void Utils::testMode(bool testmode) 
    {
        m_testMode = testmode;
    }

    void Utils::getSystemDate(int* year, int* mon, int* day)
    {
        if (m_testMode) 
        {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else 
        {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }

    int Utils::daysOfMon(int month, int year) const 
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Utils::alocpy(char*& destination, const char* source)
    {
        delete[] destination;
        destination = nullptr;

        if (source != nullptr)
        {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }

    int Utils::getint()
    {
        int value;
        int flag = 0;
        do
        {
            flag = 0;
            cin >> value;

            if (cin.get() != '\n')
            {
                cout << "Invalid Integer, retry: ";
                cin.clear();
                while (cin.get() != '\n');
                flag = 1;
            }

        } while (flag == 1);

        return value;
    }

    int Utils::getIntRange(int min, int max)
    {
        int value;
        int flag = 1;
        value = getint();

        do
        {
            if (value < min || value > max)
            {
                cout << "Value out of range " << "[" << min << "<=val<=" << max << "]: ";
                value = getint();
            }
            else
            {
                flag = 0;
            }
        } while (flag == 1);;

        return value;
    }
}