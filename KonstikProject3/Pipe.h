#pragma once
#include <iostream>
#include "utilities.h"
#include <fstream>

class Pipe
{
	float Length;
	float Diameter;
	bool IsRepairing;

public:
	static int pMaxId;
	int outCsId;
	int inCsId;

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	Pipe();
	Pipe(std::ifstream& fin);
	float GetWeight() const;
	bool GetRepairing() const;
	void Edit();
	void SaveToFile(std::ofstream& fout);
	void Repair();
};