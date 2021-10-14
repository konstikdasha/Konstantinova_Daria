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
		TryInput(id, "������� ID (0 - �����): ");
		if (id == 0)
		{
			cout << "�� ����� �� ������ ������ �� ID.\n";
			return -1;
		}
		else if (objGroup.find(id) != objGroup.end())
		{
			return id;
		}
		cout << "������ ID �� ����������. ����������, ������� ������������ ID.\n";
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
	// ������������� ������������� ���� � ����� (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unordered_map<int, Pipe> pGroup = unordered_map<int, Pipe>{};
	unordered_map<int, CompressorStation> csGroup = unordered_map<int, CompressorStation>{};

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
			pGroup.insert(make_pair(++Pipe::pMaxId, p));
			break;
		}
		case 2:
		{
			PrintTitle("�������� ��");
			CompressorStation cs;
			cin >> cs;
			csGroup.insert(make_pair(++CompressorStation::csMaxId, cs));
			break;
		}
		case 3:
		{
			PrintTitle("�������� ���� ��������");
			cout << "���������� ���� - " << pGroup.size() << "\n";
			for (const pair<int, Pipe>& p : pGroup)
			{
				cout << "����� " << p.first << ".\n";
				cout << p.second;
			}
			cout << "���������� �� - " << csGroup.size() << "\n";
			for (const pair<int, CompressorStation>& cs : csGroup)
			{
				cout << "������������� ������� " << cs.first << ".\n";
				cout << cs.second;
			}
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
			PrintTitle("������� �����");
			if (pGroup.size() != 0)
			{
				int id = FindObjById(pGroup);
				if (id != -1)
				{
					pGroup.erase(id);
					cout << "����� ������� �������!\n";
				}
			}
			else
			{
				cout << "� ��� ��� ����� ��� ��������.\n";
			}
			break;
		}
		case 7:
		{
			PrintTitle("������� ��");
			if (csGroup.size() != 0)
			{
				int id = FindObjById(csGroup);
				if (id != -1)
				{
					csGroup.erase(id);
					cout << "�� ������� �������!\n";
				}
			}
			else
			{
				cout << "� ��� ��� �� ��� ��������.\n";
			}
			break;
		}
		case 8:
		{
			PrintTitle("����� ����");
			if (pGroup.size() != 0)
			{
				int input;
				TryInput(input, "���� ����� � �������? (1 - ��, 2 - ���, ��. - �����)\n");
				switch (input)
				{
				case 1:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, true))
					{
						cout << "����� " << i << ".\n";
						cout << pGroup[i];
					}
					break;
				}
				case 2:
				{
					for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, false))
					{
						cout << "����� " << i << ".\n";
						cout << pGroup[i];
					}
					break;
				}
				default:
					cout << "����� �� ������ ������ ����\n";
					break;
				}
				/*cout << "\n�� ������ ��������������� ��� �����?\n"
					<< "1 - ��������/������� ���\n"
					<< "0 � ��. - �����\n";*/
				/*int input;
				TryInput(input, "�������: ");
				switch (input)
				{
				case 1:
				{
					p.IsRepairing = !p.IsRepairing;
					if (p.IsRepairing)
						std::cout << "����� ������� ������� � ��������� � �������!\n";
					else
						std::cout << "������ ����� ������� ��������!\n";
					break;
				}
				default:
				{
					std::cout << "�� ����� �� ������ ��������������.\n";
					break;
				}*/
				//}
				//TryInput(input, "�������: ");
				//
				//if (input == 1)
				//{
				//	int index = FindObjById(pGroup);	
				//	if (index != -1)
				//		pGroup[index].Edit();
				///*	}
				//	for (pair<int, Pipe> p : pGroup)
				//		p.second.Repair();
				//	cout << "��� ��������� ����� ������� ��������!\n";*/
				//}
			}
			else
			{
				cout << "� ��� ��� ����� ��� ������.\n";
			}
			break;
		}
		case 9:
		{
			PrintTitle("����� ��");
			if (csGroup.size() != 0)
			{
				int input;
				cout << "�� ������ ������� ���� ��?\n";
				TryInput(input, "(1 - �� ��������, 2 - �� �������� ����������������� �����, ��. - �����): ");
				switch (input)
				{
				case 1:
				{
					string name;
					cout << "������� ��� �� ��� ����������: ";
					cin.ignore();
					getline(cin, name);
					for (int i : FindObjByFilter(csGroup, CheckCsByName, name))
					{
						cout << "������������� ������� " << i << ".\n";
						cout << csGroup[i];
					}
					break;
				}
				case 2:
				{
					float percent;
					TryInput(percent, "������� ������� ��� ���������� (��������� �� � ��������� ������ ����������): ");
					for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
					{
						cout << "������������� ������� " << i << ".\n";
						cout << csGroup[i];
					}
					break;
				}
				default:
					cout << "����� �� ������ ������ ����\n";
					break;
				}
			}
			else
			{
				cout << "� ��� ��� �� ��� ������.\n";
			}
			break;
		}
		case 10:
		{
			PrintTitle("���������");
			if (pGroup.size() == 0 && csGroup.size() == 0)
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