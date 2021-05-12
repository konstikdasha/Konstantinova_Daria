#include "CKC.h"
#include "Cpipe.h"
#include "utility.h"
#include "seti.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <set>

using namespace std;

bool SearchByRepair(const Cpipe& p, int param)
{
	return p.Getpriznak() == param;
}

bool SearchByName(const CKC& k, string name)
{
	return k.Getname() == name;
}

bool SearchByPercent(const CKC& kv, double param)
{

	return ((1.0 / kv.Getkolvo_tsehov()) * kv.Getkolvo_tsehov_v_rabote())*100 <= param;
	/*float effektiv = kv.Geteffektivnost();
	float kolvo = kv.Getkolvo_tsehov();
	float kolvorab = kv.Getkolvo_tsehov_v_rabote();
	float ppp = ((1 / kolvo) * kolvorab);

	return effektiv <= ppp;*/
}

template <typename W, typename T>

using Filter = bool(*)(const W& o, T param);

template <typename W, typename T>

vector<int> FindItemsByFilter(const unordered_map <int, W>& g, Filter <W, T> f, T param)
{
	vector<int>res;
	int i = 0;
	for (const auto& obj : g)
	{
		if (f(obj.second, param))
			res.push_back(i);
		i++;
	}
	if (res.size() == 0)
	{
		cout << "������\n";
	}
	return res;
}

template <typename T>

int GetId(const unordered_map<int, T>& mapp)
{
	int id;
	while (true)
	{
		cin >> id;
		if (id == 0)
		{
			cout << endl << "�����.." << endl;
			return -1;
		}
		else if (mapp.count(id))
		{
			return id;
		}
		cout << endl << "������ id ���.." << endl << "������� id (������ 0): ";
	}
}
//
//void EditPackPipeline(unordered_map<int, Cpipe>& pv)
//{
//	cout << "��������" << endl;
//	cout << "\n1. ����� � ������ \n2. ����� � ������� \n3. �� ID ";
//	switch (Utility::proverka(1, 3))
//	{
//	case 1:
//	{
//		for (int i : FindItemsByFilter(pv, SearchByRepair, 0))
//			pv.find(i)->second.RedaktPipeline();
//	}
//
//	case 2:
//	{
//		for (int i : FindItemsByFilter(pv, SearchByRepair, 1))
//			pv.find(i)->second.RedaktPipeline();
//	}
//
//	case 3:
//	{
//		vector<int> v;
//		while (1)
//		{
//			cout << "������� id, ������� ������ ���������������: ";
//			v.push_back(Utility::proverka(1, Cpipe::MaxId));
//			cout << "������ �� �� ��������������� ���-���� ���? " << endl << "\t0. �� \n1. ��� ";
//			if (Utility::proverka(0, 1) == 1)
//				break;
//		}
//		for (auto i : v)
//		{
//			if (pv.find(i) != pv.end())
//				pv.find(i)->second.RedaktPipeline();
//		}
//		break;
//	}
//	}
//}

void DelPipes(unordered_map<int, Cpipe>& pipes_p)
{
	if (pipes_p.size() != 0)
	{
		cout << "������� ID �����, ������� ������ �������: ";
		int i;
		cin >> i;
		if (pipes_p.find(i) != pipes_p.end())
		{
			pipes_p.erase(i);
			cout << "����� �������";
		}
	}
	else
	{
		cout << "������\n";
	}
}

void DelKC(unordered_map <int, CKC>& cs)
{
	if (cs.size() != 0)
	{
		cout << "������� ID KC, ������� ������ �������: ";
		int i;
		cin >> i;
		if (cs.find(i) != cs.end())
		{
			cs.erase(i);
			cout << "�� �������";
		}
	}
	else
	{
		cout << "������\n";
	}
}


void PrintMenu()
{
	cout << endl;
	cout << "1. �������� �����" << endl
		<< "2. �������� ��" << endl
		<< "3. �������� �������" << endl
		<< "4. ������������� �����" << endl
		<< "5. ������������� ��" << endl
		<< "6. ��������� � ����" << endl
		<< "7. ��������� �� �����" << endl
		<< "8. ����� �� �������" << endl
		<< "9. ������� ����� " << endl
		<< "10. ������� ��" << endl
		<< "11. ��������� �����" << endl
		<< "12. ������� ����" << endl
		<< "13. �������������� ����������" << endl
		<< "14. ����� ������������ �����" << endl
		<< "15. ����� ���������� ����" << endl
		<< "0. �����" << endl
		<< endl << "�������� �������� - " ;
}

int main()
{
	SetConsoleCP(1251); // ������ ��������� ��� ������ �������� �� �����
	SetConsoleOutputCP(1251); // ������ ��������� ��� ����� �������� � ���������� � �������
	unordered_map<int, Cpipe> pv;
	unordered_map<int, CKC> kv;

	while (1)
	{
		PrintMenu();

		switch (Utility::proverka(0, 15))
		{

		case 1:
		{
			Cpipe p;
			cin >> p;
			pv.insert(pair<int, Cpipe>(++Cpipe::MaxId, p));
			break;
		}

		case 2:
		{
			CKC k;
			cin >> k;
			kv.insert(pair<int, CKC>(++CKC::KCMaxId, k));
			break;
		}

		case 3:
		{
			if (pv.size() > 0)
			{
				cout << "�����: " << endl;

				for (const auto& p : pv)
				{
					cout << p.first << ':' << p.second << endl;
				}
			}
			else
			{
				cout << "��� ���������� � ������ \n";
			}
			if (kv.size() > 0)
			{
				cout << "KC: " << endl;
				for (const auto& k : kv)
				{
					cout << k.first << ':' << k.second << endl;
				}
			}
			else
			{
				cout << "��� ���������� � �� \n";
			}
			break;
		}

		case 4:
		{
			if (pv.size() > 0)
			{
				cout << "������� ID, ������� �� ������ ��������: ";
				int k = GetId(pv);
				if (k != -1)
					pv[k].RedaktPipeline();
			}
			else
			{
				cout << "��� ���������� � ������ \n";
			}
			break;
		}

		case 5:
		{
			if (kv.size() > 0)
			{
				cout << "������� ID, ������� �� ������ ��������: ";
				int k = GetId(kv);
				if (k != -1)
					kv[k].RedaktKC();
			}
			else
				cout << "��� ���������� � KC \n";
			break;
		}

		case 6:
		{
			if ((pv.size() != 0) && (kv.size() != 0))
			{
				ofstream fout;
				string nameoffile;
				cout << "������� ��� �����.txt - ";
				cin.ignore();
				getline(cin, nameoffile);
				fout.open(nameoffile + ".txt", ios::out);
				if (fout.is_open())
				{
					fout << pv.size() << endl;
					fout << kv.size() << endl
						<< Cpipe::MaxId << endl
						<< CKC::KCMaxId << endl;

					for (auto& p : pv)
					{
						fout << p.first << endl;
						p.second.Save(fout);
					}
					for (auto& k : kv)
					{
						fout << k.first << endl;
						k.second.Save(fout);
					}
					fout.close();
				}
			}
			else
			{
				cout << "������\n ";
			}
			break;
		}

		case 7:
		{
			ifstream fin;
			string nameoffile;
			cout << "������� ��� �����.txt - ";
			cin.ignore();
			getline(cin, nameoffile);
			fin.open(nameoffile + ".txt", ios::in);
			if (fin.is_open())
			{
				pv.clear();
				kv.clear();
				int count1;
				int count2;
				fin >> count1;
				fin >> count2;
				fin >> Cpipe::MaxId;
				fin >> CKC::KCMaxId;
				while (count1--)
				{
					int id;
					fin >> id;
					Cpipe p;
					p.Load(fin);
					pv.insert(make_pair(id, p));
				}
				while (count2--)
				{
					int id;
					fin >> id;
					CKC k;
					k.Load(fin);
					kv.insert(make_pair(id, k));
				}
				fin.close();
			}
			else
				cout << "���� �� ������\n";
			break;
		}


		case 8:
		{
			cout << "�������� �� ������ ������� ����� �����: \n1. ����� \n2. KC \n";

			if (Utility::proverka(1, 2) == 1)
			{
				cout << "\n����� ������ ����� ��� ����������: \n1. ��������� � ������� \n2. �� ��������� � ������� \n";

				if (Utility::proverka(1, 2) == 1) 
				{
					for (int i : FindItemsByFilter(pv, SearchByRepair, 1))
					{
						cout << "����� " << i << ".\n";
						cout << pv[i];
					}
				}

				else
				{
					for (int i : FindItemsByFilter(pv, SearchByRepair, 0))
					{
						cout << "����� " << i << ".\n";
						cout << pv[i];
					}
				}
			}

			else
			{
				cout << "\n�������� �� ������ ������� ����� ����� ��: \n1. �� ����� \n2. �� �������� ����������������� ����� � ������ (����� �������� �� � ��������� ������ ����������) \n";

				if (Utility::proverka(1, 2) == 1)
				{
					string name;
					cout << "\n������� ��� KC: ";
					cin.ignore(1000, '\n');
					getline(cin, name);
					for (int i : FindItemsByFilter(kv, SearchByName, name))
						cout << kv[i + 1];
				}


				else
				{
					cout << "\n������� �������: ";
					for (int i : FindItemsByFilter(kv, SearchByPercent, Utility::proverka(0.00, 100.00)))
						cout << kv[i + 1];
				}
			}
			break;
		}

		case 9:
		{
			DelPipes(pv);
			break;
		}

		case 10:
		{
			DelKC(kv);
			break;
		}

		case 11:
		{
			if (pv.size())
			{
				int id = GetId(pv);
				if (id != -1)
				{
					cout << "�� ����� �� ������� �����: ";
					int in = GetId(kv);
					cout << "� ����� �� ������ �����: ";
					int out = GetId(kv);
					if (in != out)
						pv[id].Svyazat(in, out);

					else
						cout << "������" << endl;
				}
			}
			break;
		}

		case 12:
		{
			if (pv.size() > 0 && kv.size() > 1)
			{
				for (const pair<int, Cpipe>& p : pv)
					if (p.second.CanIspolzovat())
						p.second.ShowSvyaz(p.first);
			}
			break;
		}

		case 13:
		{
			unordered_map<int, int> indexVershin;
			int n;
			set<int> vershini;
			for (const auto& p : pv)
				if (p.second.CanIspolzovat() && kv.count(p.second.in) && kv.count(p.second.out))
				{
					vershini.insert(p.second.out);
					vershini.insert(p.second.in);
				}
			n = vershini.size();
			unordered_map<int, int> IndexVershinNaoborot;
			int i = 0;
			for (const int& vershina : vershini)
			{
				indexVershin.insert(make_pair(i, vershina));
				IndexVershinNaoborot.insert(make_pair(vershina, i++));
			}
			vector<vector<int>> rebra;
			rebra.resize(n);
			for (const auto& p : pv)
				if (p.second.CanIspolzovat())
					rebra[IndexVershinNaoborot[p.second.out]].push_back(IndexVershinNaoborot[p.second.in]);

			seti net(rebra);
			if (net.HasCicl() == false)
				net.topologicalSort(indexVershin);
			else
				cout << "� ����� ���� ���� " << endl;
			break;
		}

		case 14:
		{
			set<int> vershii;
			for (const auto& p : pv)
				if (p.second.CanIspolzovat())
				{
					vershii.insert(p.second.out);
					vershii.insert(p.second.in);
				}
			int n = vershii.size();
			unordered_map<int, int> indexVershinNaoborot;
			unordered_map<int, int> indexVershin;
			int i = 0;
			for (const int& vershina : vershii)
			{
				indexVershin.insert(make_pair(i, vershina));
				indexVershinNaoborot.insert(make_pair(vershina, i++));
			}
			vector<vector<int>> rebra;
			rebra.resize(n);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					rebra[i].push_back(0);
			for (const auto& p : pv)
				if (p.second.CanIspolzovat())
					rebra[indexVershinNaoborot[p.second.out]][indexVershinNaoborot[p.second.in]] = p.second.Getdlina();

			int start;
			cout << "������� id ��, �� ������� ����� ���� �����: ";
			cin >> start;
			if (indexVershinNaoborot.find(start) != indexVershinNaoborot.end())
				start = indexVershinNaoborot[start];
			else
			{
				cout << "����� �� ��� � ���� ";
				break;
			}
			int end;
			cout << "������� id ��, � ������� ����� �����: ";
			cin >> end;
			if (indexVershinNaoborot.find(end) != indexVershinNaoborot.end())
				end = indexVershinNaoborot[end];
			else
			{
				cout << "����� �� ��� � ���� ";
				break;
			}
			seti net = seti(rebra);
			cout << "������������ �����: " << net.FindMaxPotok(start, end) << endl;

			break;
		}

		case 15:
		{
			set<int> vershii;
			for (const auto& p : pv)
				if (p.second.CanIspolzovat())
				{
					vershii.insert(p.second.out);
					vershii.insert(p.second.in);
				}
			int n = vershii.size();
			unordered_map<int, int> indexVershinNaoborot;
			unordered_map<int, int> indexVershin;
			int i = 0;
			for (const int& vershina : vershii)
			{
				indexVershin.insert(make_pair(i, vershina));
				indexVershinNaoborot.insert(make_pair(vershina, i++));
			}
			vector<vector<int>> rebra;
			rebra.resize(n);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					rebra[i].push_back(0);
			for (const auto& p : pv)
				if (p.second.CanIspolzovat())
					rebra[indexVershinNaoborot[p.second.out]][indexVershinNaoborot[p.second.in]] = p.second.Getdlina();

			int start;
			cout << "������� id ��, �� ������� ����� ��������� ����: ";
			cin >> start;
			if (indexVershinNaoborot.find(start) != indexVershinNaoborot.end())
				start = indexVershinNaoborot[start];
			else
			{
				cout << "����� �� ��� � ���� ";
				break;
			}
			seti net = seti(rebra);
			net.FindKratchaishiPut(start, indexVershin);
			break;
		}

		case 0:
		{
			return 0;
		}

		default:
		{
			cout << "������" << endl; 
		}
		}
	}
	return 0;
}