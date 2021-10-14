#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iterator>
#include <fstream>
#include <windows.h>
using namespace std;

/// <summary>
/// ���� ������ � ��������� ���� int
/// </summary>
/// <param name="input">���������� ����� int</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
/// <returns></returns>
void TryInput(int& input, string inputText)
{
	cout << inputText;
	cin >> input;
	while (input < 0 || cin.fail()) {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
}

/// <summary>
/// ���� ������ � ��������� ���� float
/// </summary>
/// <param name="input">���������� ����� float</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
/// <returns></returns>
void TryInput(float& input, string inputText)
{
	cout << inputText;
	cin >> input;
	while (input < 0 || cin.fail()) {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
}

/// <summary>
/// ���� ������ � ��������� ���� bool
/// </summary>
/// <param name="input">���������� ����� bool</param>
/// <param name="inputText">�����, ������������� ���� ����������</param>
/// <returns></returns>
void TryInput(bool& input, string inputText)
{
	cout << inputText;
	cin >> input;
	while (cin.fail()) {
		cout << inputText;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
}

/// <summary>
/// ������������� �������
/// </summary>
struct CompressorStation
{
	int ID;
	string Name;
	int ShopsCount;
	int ActiveShopsCount;
	double Efficiency;

	void RecountEfficiency()
	{
		Efficiency = ActiveShopsCount * (1. / ShopsCount);
	}

	CompressorStation(int id, string name, int shopsCount, int activeShopsCount)
	{
		ID = id;
		Name = name;
		ShopsCount = shopsCount;
		ActiveShopsCount = activeShopsCount;
		Efficiency = ActiveShopsCount * (1. / ShopsCount);
	}

	CompressorStation();
};

/// <summary>
/// �����
/// </summary>
struct Pipe
{
	int ID;
	float Length;
	float Diameter;
	bool IsRepairing;

	Pipe(int id, float length, float diameter)
	{
		ID = id;
		Length = length;
		Diameter = diameter;
		IsRepairing = true;
	}

	Pipe();
};

// ��������� ������� �������� ������ ���� � ������������� �������
vector<Pipe> pipeList;
vector<CompressorStation> compStationList;

void AddPipe()
{
	cout << "\n---�������� �����---\n";
	vector<int> currentIds = vector<int>(pipeList.size());
	for (int i = 0; i < pipeList.size(); i++)
	{
		currentIds[i] = pipeList[i].ID;
	}
	int id;
	while (true)
	{
		TryInput(id, "������� ������������� �����: ");
		bool HasId = false;
		for (int i = 0; i < currentIds.size(); i++)
		{
			if (id == currentIds[i])
			{
				HasId = true;
				break;
			}
		}
		if (HasId)
		{
			cout << "����� ID ����� ��� ����. ����������, ������� ������ ID\n";
			continue;
		}
		else
		{
			break;
		}
	}
	float length;
	TryInput(length, "������� ����� �����: ");
	float diameter;
	TryInput(diameter, "������� ������� �����: ");
	Pipe pipe = Pipe(id, length, diameter);
	cout << endl;
	pipeList.push_back(pipe);
}

void AddCompressorStation()
{
	cout << "\n---�������� ������������� �������---\n";
	vector<int> currentIds = vector<int>(compStationList.size());
	for (int i = 0; i < compStationList.size(); i++)
	{
		currentIds[i] = compStationList[i].ID;
	}
	int id;
	while (true)
	{
		TryInput(id, "������� ������������� ������������� �������: ");
		bool HasId = false;
		for (int i = 0; i < currentIds.size(); i++)
		{
			if (id == currentIds[i])
			{
				HasId = true;
				break;
			}
		}
		if (HasId)
		{
			cout << "����� ID �� ��� ����. ����������, ������� ������ ID\n";
			continue;
		}
		else
		{
			break;
		}
	}
	string name;
	cout << "������� ��� ��: ";
	cin >> name;
	int shopsCount;
	int activeShopsCount;
	TryInput(shopsCount, "������� ����� ���������� �����: ");
	TryInput(activeShopsCount, "������� ���������� ���������� �����: ");
	while (activeShopsCount > shopsCount) {
		cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
		TryInput(activeShopsCount, "����������, ������� ���������� ���������� ���������� �����: ");
	}
	CompressorStation cs = CompressorStation(id, name, shopsCount, activeShopsCount);
	cout << endl;
	compStationList.push_back(cs);
}

void ShowAll()
{
	cout << "\n---�������� ���� ��������---\n";
	cout << "���������� ���� - " << pipeList.size() << "\n";
	for (int i = 0; i < pipeList.size(); i++)
	{
		cout << "����� " << pipeList[i].ID << ".\n"
			<< "    �����: " << pipeList[i].Length << "\n"
			<< "    �������: " << pipeList[i].Diameter << "\n";
		if (pipeList[i].IsRepairing)
			cout << "    ��������� � �������" << "\n";
		else
			cout << "    �� ��������� � �������" << "\n";
	}
	cout << "\n���������� ������������� ������� - " << compStationList.size() << "\n";
	for (int i = 0; i < compStationList.size(); i++)
	{
		cout << "������������� ������� " << compStationList[i].ID << ".\n"
			<< "    ���: " << compStationList[i].Name << "\n"
			<< "    �������� " << compStationList[i].ActiveShopsCount << "/" << compStationList[i].ShopsCount << " �����" "\n"
			<< "    �������������: " << compStationList[i].Efficiency << "\n";
	}
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
}

void EditPipe()
{
	cout << "\n---������������� �����---\n";

	if (pipeList.size() == 0)
	{
		cout << "\n� ��� ��� ���� ��� ��������������\n";
	}
	else
	{
		int pipeIndex;
		bool HasId = false;
		while (!HasId)
		{
			int id;
			TryInput(id, "������� ������������� �����: ");
			for (int i = 0; i < pipeList.size(); i++)
			{
				if (id == pipeList[i].ID)
				{
					HasId = true;
					pipeIndex = i;
					break;
				}
			}
			if (!HasId)
			{
				cout << "����� ID ����� �� ����������. ����������, ������� ������������ ID\n";
				continue;
			}
		}
		bool isEditing = true;
		while (isEditing)
		{
			cout << "\n��� �� ������ ������� � ������?\n"
				<< "1 - �������\n"
				<< "2 - ��������/�������\n"
				<< "3 - ������\n";
			int input;
			TryInput(input, "�������: ");
			switch (input)
			{
			case 1:
			{
				// �������������� ��� ������� �������� �� ������ ���������� � ����� metanit.com
				auto iteration = pipeList.cbegin();
				pipeList.erase(iteration + pipeIndex);
				cout << "����� ������� �������\n";
				isEditing = false;
			}
			break;
			case 2:
				pipeList[pipeIndex].IsRepairing = !(pipeList[pipeIndex].IsRepairing);
				if (pipeList[pipeIndex].IsRepairing)
					cout << "����� ������� ������� � ��������� � �������!\n";
				else
					cout << "������ ����� ������� ��������!\n";
				break;
			case 3:
				isEditing = false;
				break;
			}
		}
	}
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
}

void EditCompressorStation()
{
	cout << "\n---������������� ������������� �������---\n";

	if (compStationList.size() == 0)
	{
		cout << "\n� ��� ��� �� ��� ��������������\n";
	}
	else
	{
		int csIndex;
		bool HasId = false;
		while (!HasId)
		{
			int id;
			TryInput(id, "������� ������������� ��: ");
			for (int i = 0; i < compStationList.size(); i++)
			{
				if (id == compStationList[i].ID)
				{
					HasId = true;
					csIndex = i;
					break;
				}
			}
			if (!HasId)
			{
				cout << "����� ID �� �� ����������. ����������, ������� ������������ ID\n";
				continue;
			}
		}
		bool isEditing = true;
		while (isEditing)
		{
			cout << "\n��� �� ������ ������� � ��?\n"
				<< "1 - �������\n"
				<< "2 - ���������/��������� ����� ���������� �����\n"
				<< "3 - �������� ���������� ���������� �����\n"
				<< "4 - ������\n";
			int input;
			TryInput(input, "�������: ");
			switch (input)
			{
			case 1:
			{
				// �������������� ��� ������� �������� �� ������ ���������� � ����� metanit.com
				auto iteration = pipeList.cbegin();
				pipeList.erase(iteration + csIndex);
				cout << "�� ������� �������\n";
				isEditing = false;
			}
			break;
			case 2:
				cout << "������ � �� ���� " << compStationList[csIndex].ShopsCount << " �����.\n";
				cout << "1 - ��������� ���������� �����\n"
					<< "2 - ��������� ���������� �����\n";
				TryInput(input, "");
				switch (input)
				{
				case 1:
					compStationList[csIndex].ShopsCount++;
					cout << "���������� ����� ������� ��������� �� " << compStationList[csIndex].ShopsCount + "\n";
				break;
				case 2:
					compStationList[csIndex].ShopsCount--;
					if (compStationList[csIndex].ActiveShopsCount > compStationList[csIndex].ShopsCount)
						compStationList[csIndex].ActiveShopsCount = compStationList[csIndex].ShopsCount;
					cout << "���������� ����� ������� ��������� �� " << compStationList[csIndex].ShopsCount + "\n";
				default:
					cout << "����� �������� ������. �������� �������������� ��.";
				break;
				compStationList[csIndex].RecountEfficiency();
				}
			break;
			case 3:
				cout << "������ � �� �������� " << compStationList[csIndex].ActiveShopsCount << "/" << compStationList[csIndex].ShopsCount << " �����\n";
				int operationShopsCount;
				TryInput(operationShopsCount, "������� ����� ���������� ���������� �����: ");
				while (operationShopsCount > compStationList[csIndex].ShopsCount)
				{
					cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
					TryInput(operationShopsCount, "������� ����� ���������� ���������� �����: ");
				}
				compStationList[csIndex].ActiveShopsCount = operationShopsCount;
				compStationList[csIndex].RecountEfficiency();
			break;
			case 4:
				isEditing = false;
			break;
			}
		}
	}
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
}

void Save()
{
	cout << "\n---���������---\n";
	ofstream fout;
	fout.open("data.txt");
	fout << pipeList.size() << " " << compStationList.size() << "\n";
	for (int i = 0; i < pipeList.size(); i++)
	{
		fout << pipeList[i].ID << " "
			<< pipeList[i].Length << " "
			<< pipeList[i].Diameter << " "
			<< pipeList[i].IsRepairing << "\n";
	}
	for (int i = 0; i < compStationList.size(); i++)
	{
		fout << compStationList[i].ID << " "
			<< compStationList[i].Name << " "
			<< compStationList[i].ShopsCount << " "
			<< compStationList[i].ActiveShopsCount << "\n";
	}
	cout << "���� ������� �������";
	cout << "\n������� ����� �������, ����� ����������\n";
	_getch();
	fout.close();
}

void Load()
{
	cout << "\n---���������---\n";
	ifstream fin("data.txt");
	int pipeCount;
	int csCount;
	fin >> pipeCount >> csCount;
	pipeList = vector<Pipe>(pipeCount);
	compStationList = vector<CompressorStation>(csCount);
	for (int i = 0; i < pipeCount; i++)
	{
		fin >> pipeList[i].ID
			>> pipeList[i].Length
			>> pipeList[i].Diameter
			>> pipeList[i].IsRepairing;
	}
	for (int i = 0; i < csCount; i++)
	{
		fin >> compStationList[i].ID
			>> compStationList[i].Name
			>> compStationList[i].ShopsCount
			>> compStationList[i].ActiveShopsCount;
		compStationList[i].RecountEfficiency();
	}

}

void Menu()
{
	bool isRunning = true;

	while (isRunning)
	{
		cout << "\n---����---\n"
			 << "1 - �������� �����\n"
			 << "2 - �������� ��\n"
			 << "3 - �������� ���� ��������\n"
			 << "4 - ������������� �����\n"
			 << "5 - ������������� ��\n"
			 << "6 - ���������\n"
			 << "7 - ���������\n"
			 << "8 - �������������"
			 << "0 - �����\n";

		int inputMenu;
		TryInput(inputMenu, "��� �� ������ �������: ");

		switch (inputMenu)
		{
		case 1:
			AddPipe();
			break;
		case 2:
			AddCompressorStation();
			break;
		case 3:
			ShowAll();
			break;
		case 4:
			EditPipe();
			break;
		case 5:
			EditCompressorStation();
			break;
		case 6:
			Save();
			break;
		case 7:
			Load();
			break;
		case 0:
			isRunning = false;
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
}