#include "CKC.h"
using namespace std;

string name;
int kolvo_tsehov;
int kolvo_tsehov_v_rabote;
float effektivnost;
int CKC::KCMaxId = 0;

CKC::CKC()
{

}

CKC::CKC(std::ifstream& fin)
{
	fin.ignore();
	std::getline(fin, name);
	fin >> kolvo_tsehov
		>> kolvo_tsehov_v_rabote
		>> effektivnost;
}

istream& operator>>(std::istream& in, CKC& cs)
{
	std::cout << "������� ��� �� n - \n";
	std::cin.ignore();
	std::getline(cin, cs.name);
	cout << "������� ����� ����� ����� - \n";
	cs.kolvo_tsehov = Utility::proverka(0, 1000);
	cout << "������� ����� ����� � ������ - \n";
	cs.kolvo_tsehov_v_rabote = Utility::proverka(0, cs.kolvo_tsehov);
	cs.effektivnost = (1.0f / cs.kolvo_tsehov) * cs.kolvo_tsehov_v_rabote;

	return in;
}
ostream& operator<<(std::ostream& out, const CKC& cs)
{
	out << "\n" << "���: " << cs.name << "\n"
		<< "���-�� ���������� �����: " << cs.kolvo_tsehov_v_rabote << "/" << cs.kolvo_tsehov << endl
		<< "�������������: " << cs.effektivnost << endl;
	return out;

}

void EditAllKC(unordered_map<int, CKC>& cs)
{
	cout << "\n0. ��������� ���� \n1. ���������� ���� \n�������� - ";
	int choice = Utility::proverka(0, 1);
	cout << endl;
	for (auto& i : cs)
	{
		if (choice == 0 && (i.second.kolvo_tsehov > i.second.kolvo_tsehov_v_rabote))
		{
			i.second.kolvo_tsehov_v_rabote += 1;
		}
		else if (i.second.kolvo_tsehov_v_rabote > 0)
		{
			i.second.kolvo_tsehov_v_rabote -= 1;
		}
	}

}

void CKC::Save(ofstream& fout)
{
	fout << name << endl
		<< kolvo_tsehov << endl
		<< kolvo_tsehov_v_rabote << endl
		<< effektivnost << endl;
}

void CKC::Load(ifstream& fin)
{
	fin >> name
		>> kolvo_tsehov
		>> kolvo_tsehov_v_rabote
		>> effektivnost;
}

string CKC::Getname() const
{
	return name;
}

int CKC::Getkolvo_tsehov() const
{
	return kolvo_tsehov;
}

int CKC::Getkolvo_tsehov_v_rabote() const
{
	return kolvo_tsehov_v_rabote;
}

float CKC::Geteffektivnost() const
{
	return effektivnost;
}

void CKC::RedaktKC()
{
	cout << "\n0. ������ ������ ����\n1. ���������� ������ ����\n����� - ";
	if (Utility::proverka(0, 1) == 0)
	{
		if (kolvo_tsehov > kolvo_tsehov_v_rabote)
			kolvo_tsehov_v_rabote += 1;
		effektivnost = (1.0f / kolvo_tsehov) * kolvo_tsehov_v_rabote;
	}
	else
	{
		if (kolvo_tsehov_v_rabote > 0)
			kolvo_tsehov_v_rabote -= 1;
		effektivnost = (1.0f / kolvo_tsehov) * kolvo_tsehov_v_rabote;
	}

}

