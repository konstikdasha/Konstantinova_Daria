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
	//// ������ ���� ���� � ������, � ����� ���������� �� ����� (mvblog.ru/archives/144/)
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
	cout << '\n' << ' ' << title << ' ';
	//SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	cout << endl;
}

int main()
{
	// ������������� ������������� ���� � ����� (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GTN gtn = GTN();
	int edgeCount = 0;

	while (true)
	{
		PrintTitle("����");
		cout << "1 - �������� �����\n"
			<< "2 - �������� ��\n"
			<< "3 - �������� ���� ��������\n"
			<< "4 - ������������� �����\n"
			<< "5 - ������������� ��\n"
			<< "6 - ������� �����\n"
			<< "7 - ������� ��\n"
			<< "8 - ����� ����\n"
			<< "9 - ����� ��\n"
			<< "10 - ���������\n"
			<< "11 - ���������\n"
			<< "12 - ���������� �����\n"
			<< "13 - ������� �����\n"
			<< "14 - ������� ���������������� ����\n"
			<< "15 - ��������� �������������� ����������\n"
			<< "0 � ��. - �����\n";

		int inputMenu;
		TryInput(inputMenu, "��� �� ������ �������: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("�������� �����");
			Pipe p;
			cin >> p;
			gtn.AddPipe(p);
			break;
		}
		case 2:
		{
			PrintTitle("�������� ��");
			CompressorStation cs;
			cin >> cs;
			gtn.AddCs(cs);
			break;
		}
		case 3:
		{
			PrintTitle("�������� ���� ��������");
			cout << gtn;
			break;
		}
		case 4:
		{
			PrintTitle("������������� �����");
			if (gtn.HasPipe())
				gtn.EditPipe();
			else
				cout << "� ��� ��� ���� ��� ��������������.\n";
			break;
		}
		case 5:
		{
			PrintTitle("������������� ��");
			if (gtn.HasCs())
				gtn.EditCs();
			else
				cout << "� ��� ��� �� ��� ��������������.\n";
			break;
		}
		case 6:
		{
			PrintTitle("������� �����");
			if (gtn.HasPipe())
				gtn.DeletePipe();
			else
				cout << "� ��� ��� ����� ��� ��������.\n";
			break;
		}
		case 7:
		{
			PrintTitle("������� ��");
			if (gtn.HasCs())
				gtn.DeleteCs();
			else
				cout << "� ��� ��� �� ��� ��������.\n";
			break;
		}
		case 8:
		{
			PrintTitle("����� ����");
			if (gtn.HasPipe())
				gtn.SearchPipes();
			else
				cout << "� ��� ��� ����� ��� ������.\n";
			break;
		}
		case 9:
		{
			PrintTitle("����� ��");
			if (gtn.HasCs())
				gtn.SearchCss();
			else
				cout << "� ��� ��� �� ��� ������.\n";
			break;
		}
		case 10:
		{
			PrintTitle("���������");
			if (gtn.HasPipe() == false && gtn.HasCs() == false)
			{
				cout << "��������! � ��� �� ����� ����� � ��. �� ������������� ������ ��������� ������?\n";
				int input;
				TryInput(input, "(1 - ��, 0 � ��. - ���): ");
				if (input != 1)
				{
					cout << "������ ����������...\n";
					break;
				}
			}
			string filename;
			cout << "������� ��� ����� ���������� (.txt): ";
			cin >> filename;
			ofstream fout;
			fout.open(filename + ".txt", ios::out);
			if (fout.is_open())
			{
				gtn.SaveToFile(fout);
				fout.close();
				cout << "���� ������� �������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
			}
			break;
		}
		case 11:
		{
			PrintTitle("���������");
			string filename;
			cout << "������� ��� ����� �������� (.txt): ";
			cin >> filename;
			ifstream fin;
			fin.open(filename + ".txt", ios::in);
			if (fin.is_open())
			{
				gtn = GTN(fin);
				fin.close();
				cout << "���� ������� ��������!\n";
			}
			else
			{
				cout << "������ ���������� �����!\n";
			}
			break;
		}
		case 12:
		{
			PrintTitle("���������� �����");
			if (gtn.HasPipe() && gtn.HasCs(2))
				gtn.ConnectPipe();
			else
				cout << "� ��� ��� ���� � �� ��� �����.\n";
			break;
		}
		case 13:
		{
			PrintTitle("������� �����");
			if (gtn.HasPipe() && gtn.HasCs(2))
				gtn.ConnectPipe();
			else
				cout << "� ��� ��� ������\n";
			break;
		}
		case 14:
		{
			PrintTitle("���������������� ����");
			gtn.ShowNetwork();
			break;
		}
		case 15:
		{
			PrintTitle("�������������� ����������");
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