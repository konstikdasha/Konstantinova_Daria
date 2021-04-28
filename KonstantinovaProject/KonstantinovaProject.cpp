﻿#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iterator>
#include <fstream>
#include <windows.h>
#include "lr34.h"
#include "utilit.h"

using namespace std;

void PrintTitle(string title)
{
	// Меняем цвет фона и шрифта, а потом возвращаем на место (mvblog.ru/archives/144/)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
	cout << '\n' << ' ' << title << ' ';
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	cout << endl;
}

int main()
{
	// Устанавливаем русскоязычный ввод и вывод (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	lr34 lr = lr34();
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
			<< "16 - Найти максимальный поток\n"
			<< "17 - Найти кратчайшие пути\n"
			<< "0 и пр. - Выход\n";

		int inputMenu;
		TryInput(inputMenu, "Что Вы хотите сделать: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("ДОБАВИТЬ ТРУБУ");
			lr.AddPipe();
			break;
		}
		case 2:
		{
			PrintTitle("ДОБАВИТЬ КС");
			lr.AddCs();
			break;
		}
		case 3:
		{
			PrintTitle("ПРОСМОТР ВСЕХ ОБЪЕКТОВ");
			cout << lr;
			break;
		}
		case 4:
		{
			PrintTitle("РЕДАКТИРОВАТЬ ТРУБУ");
			if (lr.HasPipe())
				lr.EditPipe();
			else
				cout << "У Вас нет труб для редактирования.\n";
			break;
		}
		case 5:
		{
			PrintTitle("РЕДАКТИРОВАТЬ КС");
			if (lr.HasCs())
				lr.EditCs();
			else
				cout << "У Вас нет КС для редактирования.\n";
			break;
		}
		case 6:
		{
			PrintTitle("УДАЛИТЬ ТРУБУ");
			if (lr.HasPipe())
				lr.DeletePipe();
			else
				cout << "У Вас нет трубы для удаления.\n";
			break;
		}
		case 7:
		{
			PrintTitle("УДАЛИТЬ КС");
			if (lr.HasCs())
				lr.DeleteCs();
			else
				cout << "У Вас нет КС для удаления.\n";
			break;
		}
		case 8:
		{
			PrintTitle("ПОИСК ТРУБ");
			if (lr.HasPipe())
				lr.SearchPipes();
			else
				cout << "У Вас нет трубы для поиска.\n";
			break;
		}
		case 9:
		{
			PrintTitle("ПОИСК КС");
			if (lr.HasCs())
				lr.SearchCss();
			else
				cout << "У Вас нет КС для поиска.\n";
			break;
		}
		case 10:
		{
			PrintTitle("СОХРАНИТЬ");
			if (lr.HasPipe() == false && lr.HasCs() == false)
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
				lr.SaveToFile(fout);
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
				lr = lr34(fin);
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
			if (lr.HasPipe() && lr.HasCs(2))
				lr.ConnectPipe();
			else
				cout << "У Вас нет труб и КС для связи.\n";
			break;
		}
		case 13:
		{
			PrintTitle("УДАЛИТЬ СВЯЗЬ");
			if (lr.HasPipe() && lr.HasCs(2))
				lr.ConnectPipe();
			else
				cout << "У Вас нет связей\n";
			break;
		}
		case 14:
		{
			PrintTitle("ГАЗОТРАНСПОРТНАЯ СЕТЬ");
			lr.ShowNetwork();
			break;
		}
		case 15:
		{
			PrintTitle("ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА");
			lr.TopologicalSort();
			break;
		}
		case 16:
		{
			PrintTitle("НАЙТИ МАКСИМАЛЬНЫЙ ПОТОК");
			lr.FindMaxFlow();
			break;
		}
		case 17:
		{
			PrintTitle("НАЙТИ КРАТЧАЙШИЕ ПУТИ");
			lr.FindShortestPath();
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
}

//int main()
//{
//	setlocale(LC_ALL, "ru");
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	Menu();
//}
//
///// <summary>
///// Ввод данных с проверкой типа int
///// </summary>
///// <param name="input">Переменная ввода int</param>
///// <param name="inputText">Текст, запрашивающий ввод переменной</param>
///// <returns></returns>
//void TryInput(int& input, string inputText)
//{
//	cout << inputText;
//	cin >> input;
//	while (input < 0 || cin.fail()) {
//		cout << inputText;
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cin >> input;
//	}
//}
//
///// <summary>
///// Ввод данных с проверкой типа float
///// </summary>
///// <param name="input">Переменная ввода float</param>
///// <param name="inputText">Текст, запрашивающий ввод переменной</param>
///// <returns></returns>
//void TryInput(float& input, string inputText)
//{
//	cout << inputText;
//	cin >> input;
//	while (input < 0 || cin.fail()) {
//		cout << inputText;
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cin >> input;
//	}
//}
//
///// <summary>
///// Ввод данных с проверкой типа bool
///// </summary>
///// <param name="input">Переменная ввода bool</param>
///// <param name="inputText">Текст, запрашивающий ввод переменной</param>
///// <returns></returns>
//void TryInput(bool& input, string inputText)
//{
//	cout << inputText;
//	cin >> input;
//	while (cin.fail()) {
//		cout << inputText;
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cin >> input;
//	}
//}
//
///// <summary>
///// Компрессорная станция
///// </summary>
//struct CompressorStation
//{
//	int ID;
//	string Name;
//	int ShopsCount;
//	int ActiveShopsCount;
//	double Efficiency;
//
//	void RecountEfficiency()
//	{
//		Efficiency = ActiveShopsCount * (1. / ShopsCount);
//	}
//
//	CompressorStation(int id, string name, int shopsCount, int activeShopsCount)
//	{
//		ID = id;
//		Name = name;
//		ShopsCount = shopsCount;
//		ActiveShopsCount = activeShopsCount;
//		Efficiency = ActiveShopsCount * (1. / ShopsCount);
//	}
//
//	CompressorStation();
//};
//
///// <summary>
///// Труба
///// </summary>
//struct Pipe
//{
//	int ID;
//	float Length;
//	float Diameter;
//	bool IsRepairing;
//
//	Pipe(int id, float length, float diameter)
//	{
//		ID = id;
//		Length = length;
//		Diameter = diameter;
//		IsRepairing = true;
//	}
//
//	Pipe();
//};
//
//// Объявляем векторы текущего списка труб и компрессорных станций
//vector<Pipe> pipeList;
//vector<CompressorStation> compStationList;
//
//void AddPipe()
//{
//	cout << "\n---Добавить трубу---\n";
//	vector<int> currentIds = vector<int>(pipeList.size());
//	for (int i = 0; i < pipeList.size(); i++)
//	{
//		currentIds[i] = pipeList[i].ID;
//	}
//	int id;
//	while (true)
//	{
//		TryInput(id, "Введите идентификатор трубы: ");
//		bool HasId = false;
//		for (int i = 0; i < currentIds.size(); i++)
//		{
//			if (id == currentIds[i])
//			{
//				HasId = true;
//				break;
//			}
//		}
//		if (HasId)
//		{
//			cout << "Такой ID трубы уже есть. Пожалуйста, введите другой ID\n";
//			continue;
//		}
//		else
//		{
//			break;
//		}
//	}
//	float length;
//	TryInput(length, "Введите длину трубы: ");
//	float diameter;
//	TryInput(diameter, "Введите диаметр трубы: ");
//	Pipe pipe = Pipe(id, length, diameter);
//	cout << endl;
//	pipeList.push_back(pipe);
//}
//
//void AddCompressorStation()
//{
//	cout << "\n---Добавить компрессорную станцию---\n";
//	vector<int> currentIds = vector<int>(compStationList.size());
//	for (int i = 0; i < compStationList.size(); i++)
//	{
//		currentIds[i] = compStationList[i].ID;
//	}
//	int id;
//	while (true)
//	{
//		TryInput(id, "Введите идентификатор компрессорной станции: ");
//		bool HasId = false;
//		for (int i = 0; i < currentIds.size(); i++)
//		{
//			if (id == currentIds[i])
//			{
//				HasId = true;
//				break;
//			}
//		}
//		if (HasId)
//		{
//			cout << "Такой ID КС уже есть. Пожалуйста, введите другой ID\n";
//			continue;
//		}
//		else
//		{
//			break;
//		}
//	}
//	string name;
//	cout << "Введите имя КС: ";
//	cin >> name;
//	int shopsCount;
//	int activeShopsCount;
//	TryInput(shopsCount, "Введите общее количество цехов: ");
//	TryInput(activeShopsCount, "Введите количество работающих цехов: ");
//	while (activeShopsCount > shopsCount) {
//		cout << "Ошибка! Количество работающих цехов не может быть больше общего количества цехов\n";
//		TryInput(activeShopsCount, "Пожалуйста, введите корректное количество работающих цехов: ");
//	}
//	CompressorStation cs = CompressorStation(id, name, shopsCount, activeShopsCount);
//	cout << endl;
//	compStationList.push_back(cs);
//}
//
//void ShowAll()
//{
//	cout << "\n---Просмотр всех объектов---\n";
//	cout << "Количество труб - " << pipeList.size() << "\n";
//	for (int i = 0; i < pipeList.size(); i++)
//	{
//		cout << "Труба " << pipeList[i].ID << ".\n"
//			<< "    Длина: " << pipeList[i].Length << "\n"
//			<< "    Диаметр: " << pipeList[i].Diameter << "\n";
//		if (pipeList[i].IsRepairing)
//			cout << "    Находится в ремонте" << "\n";
//		else
//			cout << "    Не нуждается в ремонте" << "\n";
//	}
//	cout << "\nКоличество компрессорных станций - " << compStationList.size() << "\n";
//	for (int i = 0; i < compStationList.size(); i++)
//	{
//		cout << "Компрессорная станция " << compStationList[i].ID << ".\n"
//			<< "    Имя: " << compStationList[i].Name << "\n"
//			<< "    Работает " << compStationList[i].ActiveShopsCount << "/" << compStationList[i].ShopsCount << " цехов" "\n"
//			<< "    Эффективность: " << compStationList[i].Efficiency << "\n";
//	}
//	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
//	_getch();
//}
//
//void EditPipe()
//{
//	cout << "\n---Редактировать трубу---\n";
//
//	if (pipeList.size() == 0)
//	{
//		cout << "\nУ Вас нет труб для редактирования\n";
//	}
//	else
//	{
//		int pipeIndex;
//		bool HasId = false;
//		while (!HasId)
//		{
//			int id;
//			TryInput(id, "Введите идентификатор трубы: ");
//			for (int i = 0; i < pipeList.size(); i++)
//			{
//				if (id == pipeList[i].ID)
//				{
//					HasId = true;
//					pipeIndex = i;
//					break;
//				}
//			}
//			if (!HasId)
//			{
//				cout << "Такой ID трубы не существует. Пожалуйста, введите существующий ID\n";
//				continue;
//			}
//		}
//		bool isEditing = true;
//		while (isEditing)
//		{
//			cout << "\nЧто Вы хотите сделать с трубой?\n"
//				<< "1 - Удалить\n"
//				<< "2 - Починить/Сломать\n"
//				<< "3 - Отмена\n";
//			int input;
//			TryInput(input, "Введите: ");
//			switch (input)
//			{
//			case 1:
//			{
//				// Нижеприведённые две строчки написаны на основе информации с сайта metanit.com
//				auto iteration = pipeList.cbegin();
//				pipeList.erase(iteration + pipeIndex);
//				cout << "Труба успешно удалена\n";
//				isEditing = false;
//			}
//			break;
//			case 2:
//				pipeList[pipeIndex].IsRepairing = !(pipeList[pipeIndex].IsRepairing);
//				if (pipeList[pipeIndex].IsRepairing)
//					cout << "Труба успешно сломана и находится в ремонте!\n";
//				else
//					cout << "Ремонт трубы успешно завершён!\n";
//				break;
//			case 3:
//				isEditing = false;
//				break;
//			}
//		}
//	}
//	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
//	_getch();
//}
//
//void EditCompressorStation()
//{
//	cout << "\n---Редактировать компрессорную станцию---\n";
//
//	if (compStationList.size() == 0)
//	{
//		cout << "\nУ Вас нет КС для редактирования\n";
//	}
//	else
//	{
//		int csIndex;
//		bool HasId = false;
//		while (!HasId)
//		{
//			int id;
//			TryInput(id, "Введите идентификатор КС: ");
//			for (int i = 0; i < compStationList.size(); i++)
//			{
//				if (id == compStationList[i].ID)
//				{
//					HasId = true;
//					csIndex = i;
//					break;
//				}
//			}
//			if (!HasId)
//			{
//				cout << "Такой ID КС не существует. Пожалуйста, введите существующий ID\n";
//				continue;
//			}
//		}
//		bool isEditing = true;
//		while (isEditing)
//		{
//			cout << "\nЧто Вы хотите сделать с КС?\n"
//				<< "1 - Удалить\n"
//				<< "2 - Увеличить/уменьшить общее количество цехов\n"
//				<< "3 - Изменить количество работающих цехов\n"
//				<< "4 - Отмена\n";
//			int input;
//			TryInput(input, "Введите: ");
//			switch (input)
//			{
//			case 1:
//			{
//				// Нижеприведённые две строчки написаны на основе информации с сайта metanit.com
//				auto iteration = compStationList.cbegin();
//				compStationList.erase(iteration + csIndex);
//				cout << "КС успешно удалена\n";
//				isEditing = false;
//			}
//			break;
//			case 2:
//				cout << "Сейчас в КС есть " << compStationList[csIndex].ShopsCount << " цехов.\n";
//				cout << "1 - Увеличить количество цехов\n"
//					<< "2 - Уменьшить количество цехов\n";
//				TryInput(input, "");
//				switch (input)
//				{
//				case 1:
//					compStationList[csIndex].ShopsCount++;
//					cout << "Количество цехов успешно увеличено до " << compStationList[csIndex].ShopsCount + "\n";
//					break;
//				case 2:
//					compStationList[csIndex].ShopsCount--;
//					if (compStationList[csIndex].ActiveShopsCount > compStationList[csIndex].ShopsCount)
//						compStationList[csIndex].ActiveShopsCount = compStationList[csIndex].ShopsCount;
//					cout << "Количество цехов успешно уменьшено до " << compStationList[csIndex].ShopsCount + "\n";
//				default:
//					cout << "Введён неверный символ. Закрытие редактирования КС.";
//					break;
//					compStationList[csIndex].RecountEfficiency();
//				}
//			break;
//			case 3:
//				cout << "Сейчас в КС работают " << compStationList[csIndex].ActiveShopsCount << "/" << compStationList[csIndex].ShopsCount << " цехов\n";
//				int operationShopsCount;
//				TryInput(operationShopsCount, "Введите новое количество работающих цехов: ");
//				while (operationShopsCount > compStationList[csIndex].ShopsCount)
//				{
//					cout << "Ошибка! Количество работающих цехов не может быть больше общего количества цехов\n";
//					TryInput(operationShopsCount, "Введите новое количество работающих цехов: ");
//				}
//				compStationList[csIndex].ActiveShopsCount = operationShopsCount;
//				compStationList[csIndex].RecountEfficiency();
//				break;
//			case 4:
//				isEditing = false;
//				break;
//			}
//		}
//	}
//	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
//	_getch();
//}
//
//void Save()
//{
//	cout << "\n---Сохранить---\n";
//	ofstream fout;
//	fout.open("data.txt");
//	fout << pipeList.size() << "\n" << compStationList.size() << "\n";
//	for (int i = 0; i < pipeList.size(); i++)
//	{
//		fout << pipeList[i].ID << "\n"
//			<< pipeList[i].Length << "\n"
//			<< pipeList[i].Diameter << "\n"
//			<< pipeList[i].IsRepairing << "\n";
//	}
//	for (int i = 0; i < compStationList.size(); i++)
//	{
//		fout << compStationList[i].ID << "\n"
//			<< compStationList[i].Name << "\n"
//			<< compStationList[i].ShopsCount << "\n"
//			<< compStationList[i].ActiveShopsCount << "\n";
//	}
//	cout << "Файл успешно сохранён";
//	cout << "\nНажмите любую клавишу, чтобы продолжить\n";
//	_getch();
//	fout.close();
//}
//
//void Load()
//{
//	cout << "\n---Загрузить---\n";
//	ifstream fin("data.txt");
//	int pipeCount;
//	int csCount;
//	fin >> pipeCount 
//		>> csCount;
//	pipeList = vector<Pipe>(pipeCount);
//	compStationList = vector<CompressorStation>(csCount);
//	for (int i = 0; i < pipeCount; i++)
//	{
//		fin >> pipeList[i].ID
//			>> pipeList[i].Length
//			>> pipeList[i].Diameter
//			>> pipeList[i].IsRepairing;
//	}
//	for (int i = 0; i < csCount; i++)
//	{
//		fin >> compStationList[i].ID
//			>> compStationList[i].Name
//			>> compStationList[i].ShopsCount
//			>> compStationList[i].ActiveShopsCount;
//	}
//
//}
//
//void Menu()
//{
//	bool isRunning = true;
//
//	while (isRunning)
//	{
//		cout << "\n---МЕНЮ---\n"
//			<< "1 - Добавить трубу\n"
//			<< "2 - Добавить КС\n"
//			<< "3 - Просмотр всех объектов\n"
//			<< "4 - Редактировать трубу\n"
//			<< "5 - Редактировать КС\n"
//			<< "6 - Сохранить\n"
//			<< "7 - Загрузить\n"
//			<< "8 - Отфильтровать\n"
//			<< "0 - Выход\n";
//
//		int inputMenu;
//		TryInput(inputMenu, "Что Вы хотите сделать: ");
//
//		switch (inputMenu)
//		{
//		case 1:
//			AddPipe();
//			break;
//		case 2:
//			AddCompressorStation();
//			break;
//		case 3:
//			ShowAll();
//			break;
//		case 4:
//			EditPipe();
//			break;
//		case 5:
//			EditCompressorStation();
//			break;
//		case 6:
//			Save();
//			break;
//		case 7:
//			Load();
//			break;
//		case 0:
//			isRunning = false;
//			break;
//		}
//	}
//}
