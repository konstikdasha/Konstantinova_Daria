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
	std::getline(fin, Name);
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
	std::cout << "Сейчас в КС есть " << ShopsCount << " цехов.\n";
	std::cout << "1 - Увеличить количество цехов\n"
			  << "2 - Уменьшить количество цехов\n"
			  << "0 и пр. - Отмена\n";
	int input;
	TryInput(input, "Введите: ");
	switch (input)
	{
	case 1:
		ShopsCount++;
		std::cout << "Количество цехов успешно увеличено до " << ShopsCount << "\n";
		break;
	case 2:
		ShopsCount--;
		if (WorkingShopsCount > ShopsCount)
			WorkingShopsCount = ShopsCount;
		std::cout << "Количество цехов успешно уменьшено до " << ShopsCount << "\n";
	default:
		std::cout << "Вы вышли из режима редактирования.";
		break;
	}
}

void CompressorStation::RecountWorkingShopsCount()
{
	std::cout << "Сейчас в КС работают " << WorkingShopsCount << "/" << ShopsCount << " цехов\n";
	int workingShopsCount;
	TryInput(workingShopsCount, "Введите новое количество работающих цехов: ");
	while (workingShopsCount > ShopsCount)
	{
		std::cout << "Ошибка! Количество работающих цехов не может быть больше общего количества цехов\n";
		TryInput(workingShopsCount, "Введите новое количество работающих цехов: ");
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
	std::cout << "    Имя: " << cs.Name << "\n"
		<< "    Работает " << cs.WorkingShopsCount << "/" << cs.ShopsCount << " цехов" "\n"
		<< "    Эффективность: " << cs.Efficiency << "\n";
	return out;
}

std::istream& operator>>(std::istream& in, CompressorStation& cs)
{
	std::cout << "Введите имя компрессорной станции: ";
	std::cin.ignore();
	std::getline(std::cin, cs.Name);
	TryInput(cs.ShopsCount, "Введите общее кол-во цехов: ");
	TryInput(cs.WorkingShopsCount, "Введите кол-во работающих цехов: ");
	while (cs.WorkingShopsCount > cs.ShopsCount) {
		std::cout << "Ошибка! Кол-во работающих цехов не может быть больше общего кол-ва цехов\n";
		TryInput(cs.WorkingShopsCount, "Пожалуйста, введите корректное кол-во работающих цехов: ");
	}
	TryInput(cs.Efficiency, "Введите эффетивность компрессорной станции: ");
	return in;
}
