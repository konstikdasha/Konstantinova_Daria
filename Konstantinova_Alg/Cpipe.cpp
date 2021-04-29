#include "Cpipe.h"
using namespace std;

int Cpipe::MaxId = 0;
float dlina;
float diametr;
bool priznak;
int out;
int in;


Cpipe::Cpipe()
{
	dlina = 0;
	diametr = 0;
	priznak = false;
	out = -1;
	in = -1;
}

Cpipe::Cpipe(std::ifstream& fin)
{
	fin >> dlina
		>> diametr
		>> priznak
		>> out
		>> in;
}

void Cpipe::Svyazat(int out, int in)
{
	this->out = out;
	this->in = in;
}

bool Cpipe::CanIspolzovat() const
{
	return in > 0 && out > 0 && priznak == false;
}

void Cpipe::ShowSvyaz(int id) const
{
	cout << "�� " << out << " - ����� " << id << " - �� " << in << endl;
}

void Cpipe::Save(ofstream& fout)
{
	fout << dlina << '\n'
		<< diametr << '\n'
		<< priznak << '\n'
		<< out << '\n'
		<< in << '\n';
}

void Cpipe::Load(ifstream& fin)
{
	fin >> dlina
		>> diametr
		>> priznak
		>> out
		>> in;
}

bool Cpipe::Getpriznak() const
{
	return priznak;
}

float Cpipe::Getdlina() const
{
	return dlina;
}

float Cpipe::Getdiametr() const
{
	return diametr;
}

string Cpipe::checkRepair() const
{
	return (priznak) ? "�� � ������ \n" : "� ������ \n";
}

void Cpipe::RedaktPipeline()
{
	cout << "0. ����� � ������ \n1. ����� �� � ������ \n�������� - ";
	int choice = Utility::proverka(0, 1);
	priznak = choice;
	cout << endl;
}

ostream& operator<<(std::ostream& out, const Cpipe& p)
{
	out << endl << "�����: " << p.dlina << endl;
	out << "�������: " << p.diametr << endl;
	if (p.priznak)
		out << " ��������� � �������" << '\n';
	else
		out << " �� ��������� � �������" << '\n';
	return out;
}

istream& operator>>(istream& in, Cpipe& p)
{
	cout << "������� �����(�): ";
	p.dlina = Utility::proverka<double>(0, 1000);
	std::cout << "\n������� �������(��): ";
	p.diametr = Utility::proverka<double>(1, 1000);
	cout << endl;
	return in;
}


void EditAllPipes(unordered_map<int, Cpipe>& pipes)
{
	cout << "0. ����� � ������ \n1. ����� �� � ������ \n�������� - ";
	int choice = Utility::proverka(0, 1);
	cout << endl;
	for (auto& i : pipes)
	{
		i.second.priznak = choice;
	}

}
