#include <iostream>
#include <string>
#include <unordered_map>
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
int FindObjById(const unordered_map<int, T>& objGroup)
{
	while (true)
	{
		int id;
		TryInput(id, "Введите ID (0 - выйти): ");
		if (id == 0)
		{
			cout << "Вы вышли из режима поиска по ID.\n";
			return -1;
		}
		else if (objGroup.find(id) != objGroup.end())
		{
			return id;
		}
		cout << "Такого ID не существует. Пожалуйста, введите существующий ID.\n";
	}
}

template <typename TParam, typename TObj>
using Filter = bool(*)(const TObj& obj, TParam param);

bool CheckPipeByRepairing(const Pipe& p, bool param)
{
	return p.GetRepairing() == param;
}

bool CheckCsByName(const CompressorStation& cs, string param)
{
	return cs.GetName() == param;
}

bool CheckCsByUnusedShops(const CompressorStation& cs, float param)
{
	return cs.GetPercentUnusedShops() <= param;
}

template <typename TFilter, typename TObj>
vector<int> FindObjByFilter(const unordered_map<int, TObj>& group, Filter<TFilter, TObj> f, TFilter param)
{
	vector <int> res;
	for (const pair<int, TObj>& obj : group)
		if (f(obj.second, param))
			res.push_back(obj.first);
	return res;
}

int main()
{
	// Устанавливаем русскоязычный ввод и вывод (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unordered_map<int, Pipe> pGroup = unordered_map<int, Pipe>{};
	unordered_map<int, CompressorStation> csGroup = unordered_map<int, CompressorStation>{};

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
			pGroup.insert(make_pair(++Pipe::pMaxId, p));
			break;
		}
		case 2:
		{
			PrintTitle("ДОБАВИТЬ КС");
			CompressorStation cs;
			cin >> cs;
			csGroup.insert(make_pair(++CompressorStation::csMaxId, cs));
			break;
		}
		case 3:
		{
			PrintTitle("ПРОСМОТР ВСЕХ ОБЪЕКТОВ");
			cout << "Количество труб - " << pGroup.size() << "\n";
			for (const pair<int, Pipe>& p : pGroup)
			{
				cout << "Труба " << p.first << ".\n";
				cout << p.second;
			}
			cout << "Количество КС - " << csGroup.size() << "\n";
			for (const pair<int, CompressorStation>& cs : csGroup)
			{
				cout << "Компрессорная станция " << cs.first << ".\n";
				cout << cs.second;
			}
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
			PrintTitle("УДАЛИТЬ ТРУБУ");
			if (pGroup.size() != 0)
			{
				int id = FindObjById(pGroup);
				if (id != -1)
				{
					pGroup.erase(id);
					cout << "Труба успешно удалена!\n";
				}
			}
			else
			{
				cout << "У Вас нет трубы для удаления.\n";
			}
			break;
		}
		case 7:
		{
			PrintTitle("УДАЛИТЬ КС");
			if (csGroup.size() != 0)
			{
				int id = FindObjById(csGroup);
				if (id != -1)
				{
					csGroup.erase(id);
					cout << "КС успешно удалена!\n";
				}
			}
			else
			{
				cout << "У Вас нет КС для удаления.\n";
			}
			break;
		}
		case 8:
		{
			PrintTitle("ПОИСК ТРУБ");
			if (pGroup.size() != 0)
			{
				int input;
				TryInput(input, "Ищем трубу в ремонте? (1 - да, 2 - нет, пр. - выйти)\n");
				switch (input)
				{
				case 1:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, true))
					{
						cout << "Труба " << i << ".\n";
						cout << pGroup[i];
					}
					break;
				}
				case 2:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, false))
					{
						cout << "Труба " << i << ".\n";
						cout << pGroup[i];
					}
					break;
				}
				default:
					cout << "Выход из режима поиска труб\n";
					break;
				}
				/*cout << "\nВы хотите отредактировать эти трубы?\n"
					<< "1 - Починить/Сломать все\n"
					<< "0 и пр. - Выйти\n";*/
				/*int input;
				TryInput(input, "Введите: ");
				switch (input)
				{
				case 1:
				{
					p.IsRepairing = !p.IsRepairing;
					if (p.IsRepairing)
						std::cout << "Труба успешно сломана и находится в ремонте!\n";
					else
						std::cout << "Ремонт трубы успешно завершён!\n";
					break;
				}
				default:
				{
					std::cout << "Вы вышли из режима редактирования.\n";
					break;
				}*/
				//}
				//TryInput(input, "Введите: ");
				//
				//if (input == 1)
				//{
				//	int index = FindObjById(pGroup);	
				//	if (index != -1)
				//		pGroup[index].Edit();
				///*	}
				//	for (pair<int, Pipe> p : pGroup)
				//		p.second.Repair();
				//	cout << "Все выбранные трубы успешно починены!\n";*/
				//}
			}
			else
			{
				cout << "У Вас нет трубы для поиска.\n";
			}
			break;
		}
		case 9:
		{
			PrintTitle("ПОИСК КС");
			if (csGroup.size() != 0)
			{
				int input;
				cout << "По какому фильтру ищем КС?\n";
				TryInput(input, "(1 - по названию, 2 - по проценту незадействованных цехов, пр. - выйти): ");
				switch (input)
				{
				case 1:
				{
					string name;
					cout << "Введите имя КС для фильтрации: ";
					cin.ignore();
					getline(cin, name);
					for (int i : FindObjByFilter(csGroup, CheckCsByName, name))
					{
						cout << "Компрессорная станция " << i << ".\n";
						cout << csGroup[i];
					}
					break;
				}
				case 2:
				{
					float percent;
					TryInput(percent, "Введите процент для фильтрации (покажутся КС с процентом меньше указанного): ");
					for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
					{
						cout << "Компрессорная станция " << i << ".\n";
						cout << csGroup[i];
					}
					break;
				}
				default:
					cout << "Выход из режима поиска труб\n";
					break;
				}
			}
			else
			{
				cout << "У Вас нет КС для поиска.\n";
			}
			break;
		}
		case 10:
		{
			PrintTitle("СОХРАНИТЬ");
			if (pGroup.size() == 0 && csGroup.size() == 0)
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
				int pCount;
				fout << pGroup.size() << '\n'
					<< csGroup.size() << '\n'
					<< Pipe::pMaxId << '\n'
					<< CompressorStation::csMaxId << '\n';
				for (pair<int, Pipe> p : pGroup)
				{
					fout << p.first << '\n';
					p.second.SaveToFile(fout);
				}
				for (pair<int, CompressorStation> cs : csGroup)
				{
					fout << cs.first << '\n';
					cs.second.SaveToFile(fout);
				}
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
				pGroup.clear();
				csGroup.clear();
				int pSize;
				int csSize;
				fin >> pSize;
				fin >> csSize;
				fin >> Pipe::pMaxId;
				fin >> CompressorStation::csMaxId;
				while (pSize--)
				{
					int id;
					fin >> id;
					pGroup.insert(make_pair(id, Pipe(fin)));
				}
				while (csSize--)
				{
					int id;
					fin >> id;
					csGroup.insert(make_pair(id, CompressorStation(fin)));
				}
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