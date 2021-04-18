#include "CompressorStation.h"

int CompressorStation::csMaxId = 0;
std::string Name;
int ShopsCount;
int WorkingShopsCount;
float Efficiency;

CompressorStation::CompressorStation()
{
}

CompressorStation::CompressorStation(std::ifstream& fin)
{
	fin.ignore();
	getline(fin, Name);
	fin >> ShopsCount
		>> WorkingShopsCount
		>> Efficiency;
}

std::string CompressorStation::GetName() const
{
	return Name;
}

float CompressorStation::GetPercentUnusedShops() const
{
	return (1 - (WorkingShopsCount * 1.0f / ShopsCount)) * 100;
}

void CompressorStation::RecountShopsCount()
{
	std::cout << "������ � �� ���� " << ShopsCount << " �����.\n";
	std::cout << "1 - ��������� ���������� �����\n"
		<< "2 - ��������� ���������� �����\n"
		<< "0 � ��. - ������\n";
	int input;
	TryInput(input, "�������: ");
	switch (input)
	{
	case 1:
		ShopsCount++;
		std::cout << "���������� ����� ������� ��������� �� " << ShopsCount << "\n";
		break;
	case 2:
		ShopsCount--;
		if (WorkingShopsCount > ShopsCount)
			WorkingShopsCount = ShopsCount;
		std::cout << "���������� ����� ������� ��������� �� " << ShopsCount << "\n";
	default:
		std::cout << "�� ����� �� ������ ��������������.";
		break;
	}
}

void CompressorStation::RecountWorkingShopsCount()
{
	std::cout << "������ � �� �������� " << WorkingShopsCount << "/" << ShopsCount << " �����\n";
	int workingShopsCount;
	TryInput(workingShopsCount, "������� ����� ���������� ���������� �����: ");
	while (workingShopsCount > ShopsCount)
	{
		std::cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
		TryInput(workingShopsCount, "������� ����� ���������� ���������� �����: ");
	}
	WorkingShopsCount = workingShopsCount;
}

void CompressorStation::SaveToFile(std::ofstream& fout)
{
	fout << Name << '\n'
		<< ShopsCount << '\n'
		<< WorkingShopsCount << '\n'
		<< Efficiency << '\n';
}

std::ostream& operator << (std::ostream& out, const CompressorStation& cs)
{
	std::cout << "    ���: " << cs.Name << "\n"
		<< "    �������� " << cs.WorkingShopsCount << "/" << cs.ShopsCount << " �����" "\n"
		<< "    �������������: " << cs.Efficiency << "\n";
	return out;
}

std::istream& operator>>(std::istream& in, CompressorStation& cs)
{
	std::cout << "������� ��� ������������� �������: ";
	std::cin.ignore();
	std::getline(std::cin, cs.Name);
	TryInput(cs.ShopsCount, "������� ����� ���-�� �����: ");
	TryInput(cs.WorkingShopsCount, "������� ���-�� ���������� �����: ");
	while (cs.WorkingShopsCount > cs.ShopsCount) {
		std::cout << "������! ���-�� ���������� ����� �� ����� ���� ������ ������ ���-�� �����\n";
		TryInput(cs.WorkingShopsCount, "����������, ������� ���������� ���-�� ���������� �����: ");
	}
	TryInput(cs.Efficiency, "������� ������������ ������������� �������: ");
	return in;
}
