#pragma once

#include "lib.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Cpipe
{

	float dlina;
	float diametr;
	bool priznak;
public:
	int out;
	int in;
	static int MaxId;
	void Save(ofstream& out);
	void Load(ifstream&);
	bool Getpriznak() const;
	float Getdlina() const;
	float Getdiametr() const;
	string checkRepair() const;
	void RedaktPipeline();
	friend std::ostream& operator << (ostream& out, const Cpipe& p);
	friend std::istream& operator >> (istream& in, Cpipe& p);
	//	friend void EditAllPipes(unordered_map<int, Cpipe>& pipes);
	void Svyazat(int out, int in);
	bool CanIspolzovat() const;
	void ShowSvyaz(int id) const;
	Cpipe();
	Cpipe(std::ifstream& fin);
};



