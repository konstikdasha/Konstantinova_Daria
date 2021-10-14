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
		std::cout << "\nО, нет! Труба сломана!\n";
	else
		std::cout << "\nТруба не нуждается в ремонте.\n";
	std::cout << "Что Вы хотите сделать с трубой?\n"
		<< "1 - Починить/Сломать\n"
		<< "0 и пр. - Отмена\n";
	int input;
	TryInput(input, "Введите: ");
	switch (input)
	{
	case 1:
	{
		IsRepairing = !IsRepairing;
		if (IsRepairing)
			std::cout << "Труба успешно сломана и находится в ремонте!\n";
		else
			std::cout << "Ремонт трубы успешно завершён!\n";
		break;
	}
	default:
	{
		std::cout << "Вы вышли из режима редактирования.\n";
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
	out << "    Длина: " << p.Length << '\n'
		<< "    Диаметр: " << p.Diameter << '\n';
	if (p.IsRepairing)
		out << "    Находится в ремонте" << '\n';
	else
		out << "    Не нуждается в ремонте" << '\n';
	return out;
}

std::istream& operator >> (std::istream& in, Pipe& p)
{
	TryInput(p.Length, "Введите длину трубы (в метрах): ");
	TryInput(p.Diameter, "Введите диаметр трубы (в миллиметрах): ");
	p.IsRepairing = true;
	p.outCsId = -1;
	p.inCsId = -1;
	return in;
}
