/*
	==================================================
	Disaster and Emergency Aid Management Project
	==================================================
	Name   : Nozhin Azarpanah
	Date   : April 11, 2022

*/

#include <iostream>
#include <fstream>

#include "AidMan.h"
#include "Utils.h"

using namespace sdds;
using namespace std;

void copyfile(const char* to, const char* from);
void displayFile(const char* file);

int main() 
{
	copyfile("newdata.dat", "data.dat");
	ut.testMode();
	AidMan().run();
	displayFile("data.dat");
	cout << endl << "------------------------------------------------" << endl;
	displayFile("shippingOrder.txt");
	return 0;
}

void displayFile(const char* file) 
{
	ifstream in(file);
	char ch;
	cout << "File: " << file << endl;
	while (in.get(ch)) cout << ch;
}

void copyfile(const char* to, const char* from) 
{
	std::ifstream in(from);
	std::ofstream out(to);
	char ch;
	while (in.get(ch)) out.put(ch);
}