#pragma once
#include <string>
#include <iostream>
#include "utilities.h"
#include <fstream>

class CompressorStation
{
	int Id;
	std::string Name;
	int ShopsCount;
	int WorkingShopsCount;
	float Efficiency;
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& cs);
public:
	CompressorStation();
	CompressorStation(int id);
	CompressorStation(std::ifstream& fin);
	int GetId() const;
	void RecountShopsCount();
	void RecountWorkingShopsCount();
	void SaveToFile(std::ofstream& fout);
};