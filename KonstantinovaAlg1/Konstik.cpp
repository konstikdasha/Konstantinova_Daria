#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include "Pipe.h"
#include "CompressorStation.h"
#include "utilities.h"
using namespace std;

void PrintTitle(string title)
{
	cout << '\n' << ' ' << title << ' ';
	cout << endl;
}

template <typename T>
int FindObjById(const vector<T>& objGroup)
{
	while (true)
	{
		int id;
		TryInput(id, "Введите ID (0 - выйти): ");
		if (id == 0)
		{
			cout << "Вы вышли из режима редактирования.\n";
			return -1;
		}
		else
		{
			for (int i = 0; i < objGroup.size(); i++)
				if (id == objGroup[i].GetId())
					return i;
		}
		cout << "Такого ID не существует. Пожалуйста, введите существующий ID.\n";
	}
}

int main()
{
	// Устанавливаем русскоязычный ввод и вывод (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Pipe> pGroup = vector<Pipe>{};
	vector<CompressorStation> csGroup = vector<CompressorStation>{};

	while (true)
	{
		PrintTitle("МЕНЮ");
		cout << "1 - Добавить трубу\n"
			<< "2 - Добавить КС\n"
			<< "3 - Просмотр всех объектов\n"
			<< "4 - Редактировать трубу\n"
			<< "5 - Редактировать КС\n"
			<< "6 - Сохранить\n"
			<< "7 - Загрузить\n"
			<< "0 и пр. - Выход\n";

		int inputMenu;
		TryInput(inputMenu, "Что Вы хотите сделать: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("ДОБАВИТЬ ТРУБУ");
			pGroup.push_back(Pipe(pGroup.size() + 1));

			break;
		}
		case 2:
		{
			PrintTitle("ДОБАВИТЬ КС");
			CompressorStation cs = CompressorStation(csGroup.size() + 1);
			csGroup.push_back(cs);
			break;
		}
		case 3:
		{
			PrintTitle("ПРОСМОТР ВСЕХ ОБЪЕКТОВ");
			cout << "Количество труб - " << pGroup.size() << "\n";
			for (auto& p : pGroup)
				cout << p;
			cout << "Количество КС - " << csGroup.size() << "\n";
			for (auto& cs : csGroup)
				cout << cs;
			break;
		}
		case 4:
		{
			PrintTitle("РЕДАКТИРОВАТЬ ТРУБУ");
			if (pGroup.size() != 0)
			{
				int index = FindObjById(pGroup);
				if (index != -1)
					pGroup[index].Edit();
			}
			else
			{
				cout << "У Вас нет труб для редактирования.\n";
			}
			break;
		}
		case 5:
		{
			PrintTitle("РЕДАКТИРОВАТЬ КС");
			if (csGroup.size() != 0)
			{
				int index = FindObjById(csGroup);
				if (index != -1)
				{
					cout << "\nЧто Вы хотите сделать с КС?\n"
						<< "1 - Увеличить/уменьшить общее количество цехов\n"
						<< "2 - Изменить количество работающих цехов\n"
						<< "0 и пр. - Отмена\n";
					int input;
					TryInput(input, "Введите: ");
					switch (input)
					{
					case 1:
						csGroup[index].RecountShopsCount();
						break;
					case 2:
						csGroup[index].RecountWorkingShopsCount();
						break;
					default:
						cout << "Вы вышли из режима редактирования.";
						break;
					}
				}
			}
			else
			{
				cout << "У Вас нет КС для редактирования.\n";
			}
			break;
		}
		case 6:
		{
			PrintTitle("СОХРАНИТЬ");
			ofstream fout;
			fout.open("data.txt", ios::out);
			if (fout.is_open())
			{
				fout << pGroup.size() << '\n'
					<< csGroup.size() << '\n';
				for (auto& p : pGroup)
					p.SaveToFile(fout);
				for (auto& cs : csGroup)
					cs.SaveToFile(fout);
				fout.close();
				cout << "Файл успешно сохранён!\n";
			}
			else
			{
				cout << "Ошибка сохранения файла!\n";
			}
			break;
		}
		case 7:
		{
			PrintTitle("ЗАГРУЗИТЬ");
			ifstream fin;
			fin.open("data.txt", ios::in);
			if (fin.is_open())
			{
				pGroup.resize(0);
				csGroup.resize(0);
				int pSize;
				int csSize;
				fin >> pSize;
				fin >> csSize;
				while (pSize--)
					pGroup.push_back(Pipe(fin));
				while (csSize--)
					csGroup.push_back(CompressorStation(fin));
				fin.close();
				cout << "Файл успешно загружен!\n";
			}
			else
			{
				cout << "Ошибка сохранения файла!\n";
			}
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
}