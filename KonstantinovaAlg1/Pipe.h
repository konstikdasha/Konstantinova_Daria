#pragma once
#include <iostream>
#include "utilities.h"
#include <fstream>

class Pipe
{
	int Id1;
	float Length;
	float Diameter;
	bool IsRepairing;

public:
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	Pipe();
	Pipe(int id);
	Pipe(std::ifstream& fin);
	int GetId() const;
	void Edit();
	void SaveToFile(std::ofstream& fout);
};