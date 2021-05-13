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
		TryInput(id, "������� ID (0 - �����): ");
		if (id == 0)
		{
			cout << "�� ����� �� ������ ��������������.\n";
			return -1;
		}
		else
		{
			for (int i = 0; i < objGroup.size(); i++)
				if (id == objGroup[i].GetId())
					return i;
		}
		cout << "������ ID �� ����������. ����������, ������� ������������ ID.\n";
	}
}

int main()
{
	// ������������� ������������� ���� � ����� (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Pipe> pGroup = vector<Pipe>{};
	vector<CompressorStation> csGroup = vector<CompressorStation>{};

	while (true)
	{
		PrintTitle("����");
		cout << "1 - �������� �����\n"
			<< "2 - �������� ��\n"
			<< "3 - �������� ���� ��������\n"
			<< "4 - ������������� �����\n"
			<< "5 - ������������� ��\n"
			<< "6 - ���������\n"
			<< "7 - ���������\n"
			<< "0 � ��. - �����\n";

		int inputMenu;
		TryInput(inputMenu, "��� �� ������ �������: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("�������� �����");
			pGroup.push_back(Pipe(pGroup.size() + 1));

			break;
		}
		case 2:
		{
			PrintTitle("�������� ��");
			CompressorStation cs = CompressorStation(csGroup.size() + 1);
			csGroup.push_back(cs);
			break;
		}
		case 3:
		{
			PrintTitle("�������� ���� ��������");
			cout << "���������� ���� - " << pGroup.size() << "\n";
			for (auto& p : pGroup)
				cout << p;
			cout << "���������� �� - " << csGroup.size() << "\n";
			for (auto& cs : csGroup)
				cout << cs;
			break;
		}
		case 4:
		{
			PrintTitle("������������� �����");
			if (pGroup.size() != 0)
			{
				int index = FindObjById(pGroup);
				if (index != -1)
					pGroup[index].Edit();
			}
			else
			{
				cout << "� ��� ��� ���� ��� ��������������.\n";
			}
			break;
		}
		case 5:
		{
			PrintTitle("������������� ��");
			if (csGroup.size() != 0)
			{
				int index = FindObjById(csGroup);
				if (index != -1)
				{
					cout << "\n��� �� ������ ������� � ��?\n"
						<< "1 - ���������/��������� ����� ���������� �����\n"
						<< "2 - �������� ���������� ���������� �����\n"
						<< "0 � ��. - ������\n";
					int input;
					TryInput(input, "�������: ");
					switch (input)
					{
					case 1:
						csGroup[index].RecountShopsCount();
						break;
					case 2:
						csGroup[index].RecountWorkingShopsCount();
						break;
					default:
						cout << "�� ����� �� ������ ��������������.";
						break;
					}
				}
			}
			else
			{
				cout << "� ��� ��� �� ��� ��������������.\n";
			}
			break;
		}
		case 6:
		{
			PrintTitle("���������");
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
				cout << "���� ������� �������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
			}
			break;
		}
		case 7:
		{
			PrintTitle("���������");
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
				cout << "���� ������� ��������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
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