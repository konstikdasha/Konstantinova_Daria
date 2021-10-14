#include "Pipe.h"

int Pipe::pMaxId = 0;
float Length;
float Diameter;
bool IsRepairing;
int outCsId;
int inCsId;

Pipe::Pipe()
{
}

Pipe::Pipe(std::ifstream& fin)
{
	fin >> Length
		>> Diameter
		>> IsRepairing
		>> outCsId
		>> inCsId;
}

float Pipe::GetWeight() const
{
	return 4 * 3.14 * Diameter / Length;
}

bool Pipe::GetRepairing() const
{
	return IsRepairing;
}

void Pipe::Edit()
{
	if (IsRepairing)
		std::cout << "\n�, ���! ����� �������!\n";
	else
		std::cout << "\n����� �� ��������� � �������.\n";
	std::cout << "��� �� ������ ������� � ������?\n"
		<< "1 - ��������/�������\n"
		<< "0 � ��. - ������\n";
	int input;
	TryInput(input, "�������: ");
	switch (input)
	{
	case 1:
	{
		IsRepairing = !IsRepairing;
		if (IsRepairing)
			std::cout << "����� ������� ������� � ��������� � �������!\n";
		else
			std::cout << "������ ����� ������� ��������!\n";
		break;
	}
	default:
	{
		std::cout << "�� ����� �� ������ ��������������.\n";
		break;
	}
	}
}

void Pipe::SaveToFile(std::ofstream& fout)
{
	fout << Length << '\n'
		<< Diameter << '\n'
		<< IsRepairing << '\n'
		<< outCsId << '\n'
		<< inCsId << '\n';
}

void Pipe::Repair()
{
	IsRepairing = true;
}

std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "    �����: " << p.Length << '\n'
		<< "    �������: " << p.Diameter << '\n';
	if (p.IsRepairing)
		out << "    ��������� � �������" << '\n';
	else
		out << "    �� ��������� � �������" << '\n';
	return out;
}

std::istream& operator >> (std::istream& in, Pipe& p)
{
	TryInput(p.Length, "������� ����� ����� (� ������): ");
	TryInput(p.Diameter, "������� ������� ����� (� �����������): ");
	p.IsRepairing = true;
	p.outCsId = -1;
	p.inCsId = -1;
	return in;
}