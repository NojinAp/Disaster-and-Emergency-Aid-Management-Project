/*
    ==================================================
    Disaster and Emergency Aid Management Project
    ==================================================
*/

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds
{
    const int sdds_testYear = 2022;
    const int sdds_testMon = 03;
    const int sdds_testDay = 31;

    class Utils 
    {
        bool m_testMode = false;

    public:
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
        int daysOfMon(int mon, int year)const;
        void testMode(bool testmode = true);
        void alocpy(char*& destination, const char* source);
        int getint();
        int getIntRange(int min, int max);
    };

    extern Utils ut;
}

#endif
