#include "Pipe.h"

int Id1;
float Length;
float Diameter;
bool IsRepairing;

Pipe::Pipe()
{
}

Pipe::Pipe(int id)
{
	Id1 = id;
	TryInput(Length, "������� ����� ����� (� ������): ");
	TryInput(Diameter, "������� ������� ����� (� �����������): ");
	IsRepairing = true;
}

Pipe::Pipe(std::ifstream& fin)
{
	fin >> Id1
		>> Length
		>> Diameter
		>> IsRepairing;
}

int Pipe::GetId() const
{
	return Id1;
}

void Pipe::Edit()
{
	if (IsRepairing)
		std::cout << "\n����� �������!\n";
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
	fout << Id1 << '\n'
		<< Length << '\n'
		<< Diameter << '\n'
		<< IsRepairing << '\n';
}

std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "����� " << p.Id1 << ".\n"
		<< "    �����: " << p.Length << '\n'
		<< "    �������: " << p.Diameter << '\n';
	if (p.IsRepairing)
		out << "    ��������� � �������" << '\n';
	else
		out << "    �� ��������� � �������" << '\n';
	return out;
}