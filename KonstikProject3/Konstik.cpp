#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include "GTN.h"
#include "utilities.h"
#include "Pipe.h"
#include "CompressorStation.h"
using namespace std;

void PrintTitle(string title)
{
	//// Меняем цвет фона и шрифта, а потом возвращаем на место (mvblog.ru/archives/144/)
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
	cout << '\n' << ' ' << title << ' ';
	//SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	cout << endl;
}

int main()
{
	// Устанавливаем русскоязычный ввод и вывод (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GTN gtn = GTN();
	int edgeCount = 0;

	while (true)
	{
		PrintTitle("МЕНЮ");
		cout << "1 - Добавить трубу\n"
			<< "2 - Добавить КС\n"
			<< "3 - Просмотр всех объектов\n"
			<< "4 - Редактировать трубу\n"
			<< "5 - Редактировать КС\n"
			<< "6 - Удалить трубу\n"
			<< "7 - Удалить КС\n"
			<< "8 - Поиск труб\n"
			<< "9 - Поиск КС\n"
			<< "10 - Сохранить\n"
			<< "11 - Загрузить\n"
			<< "12 - Установить связь\n"
			<< "13 - Удалить связь\n"
			<< "14 - Вывести газотранспортную сеть\n"
			<< "15 - Выполнить топологическую сортировку\n"
			<< "0 и пр. - Выход\n";

		int inputMenu;
		TryInput(inputMenu, "Что Вы хотите сделать: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("ДОБАВИТЬ ТРУБУ");
			Pipe p;
			cin >> p;
			gtn.AddPipe(p);
			break;
		}
		case 2:
		{
			PrintTitle("ДОБАВИТЬ КС");
			CompressorStation cs;
			cin >> cs;
			gtn.AddCs(cs);
			break;
		}
		case 3:
		{
			PrintTitle("ПРОСМОТР ВСЕХ ОБЪЕКТОВ");
			cout << gtn;
			break;
		}
		case 4:
		{
			PrintTitle("РЕДАКТИРОВАТЬ ТРУБУ");
			if (gtn.HasPipe())
				gtn.EditPipe();
			else
				cout << "У Вас нет труб для редактирования.\n";
			break;
		}
		case 5:
		{
			PrintTitle("РЕДАКТИРОВАТЬ КС");
			if (gtn.HasCs())
				gtn.EditCs();
			else
				cout << "У Вас нет КС для редактирования.\n";
			break;
		}
		case 6:
		{
			PrintTitle("УДАЛИТЬ ТРУБУ");
			if (gtn.HasPipe())
				gtn.DeletePipe();
			else
				cout << "У Вас нет трубы для удаления.\n";
			break;
		}
		case 7:
		{
			PrintTitle("УДАЛИТЬ КС");
			if (gtn.HasCs())
				gtn.DeleteCs();
			else
				cout << "У Вас нет КС для удаления.\n";
			break;
		}
		case 8:
		{
			PrintTitle("ПОИСК ТРУБ");
			if (gtn.HasPipe())
				gtn.SearchPipes();
			else
				cout << "У Вас нет трубы для поиска.\n";
			break;
		}
		case 9:
		{
			PrintTitle("ПОИСК КС");
			if (gtn.HasCs())
				gtn.SearchCss();
			else
				cout << "У Вас нет КС для поиска.\n";
			break;
		}
		case 10:
		{
			PrintTitle("СОХРАНИТЬ");
			if (gtn.HasPipe() == false && gtn.HasCs() == false)
			{
				cout << "Внимание! У Вас ни одной трубы и КС. Вы действительно хотите сохранить данные?\n";
				int input;
				TryInput(input, "(1 - да, 0 и пр. - нет): ");
				if (input != 1)
				{
					cout << "Отмена сохранения...\n";
					break;
				}
			}
			string filename;
			cout << "Введите имя файла сохранения (.txt): ";
			cin >> filename;
			ofstream fout;
			fout.open(filename + ".txt", ios::out);
			if (fout.is_open())
			{
				gtn.SaveToFile(fout);
				fout.close();
				cout << "Файл успешно сохранён!\n";
			}
			else
			{
				cout << "Ошибка сохранения файла!\n";
			}
			break;
		}
		case 11:
		{
			PrintTitle("ЗАГРУЗИТЬ");
			string filename;
			cout << "Введите имя файла загрузки (.txt): ";
			cin >> filename;
			ifstream fin;
			fin.open(filename + ".txt", ios::in);
			if (fin.is_open())
			{
				gtn = GTN(fin);
				fin.close();
				cout << "Файл успешно загружен!\n";
			}
			else
			{
				cout << "Ошибка сохранения файла!\n";
			}
			break;
		}
		case 12:
		{
			PrintTitle("УСТАНОВИТЬ СВЯЗЬ");
			if (gtn.HasPipe() && gtn.HasCs(2))
				gtn.ConnectPipe();
			else
				cout << "У Вас нет труб и КС для связи.\n";
			break;
		}
		case 13:
		{
			PrintTitle("УДАЛИТЬ СВЯЗЬ");
			if (gtn.HasPipe() && gtn.HasCs(2))
				gtn.ConnectPipe();
			else
				cout << "У Вас нет связей\n";
			break;
		}
		case 14:
		{
			PrintTitle("ГАЗОТРАНСПОРТНАЯ СЕТЬ");
			gtn.ShowNetwork();
			break;
		}
		case 15:
		{
			PrintTitle("ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА");
			gtn.TopologicalSort();
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
}