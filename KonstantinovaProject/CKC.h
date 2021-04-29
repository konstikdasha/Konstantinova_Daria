#pragma once

#include "utility.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CKC
{
	string name;
	int kolvo_tsehov;
	int kolvo_tsehov_v_rabote;
	float effektivnost;
public:
	static int KCMaxId;
	friend ostream& operator <<(std::ostream& out, const CKC& cs);
	friend istream& operator >>(std::istream& in, CKC& cs);
	void Save(ofstream& fout);
	void Load(ifstream& fin);
	string Getname() const;
	int Getkolvo_tsehov() const;
	int Getkolvo_tsehov_v_rabote() const;
	float Geteffektivnost() const;
	friend void EditAllKC(unordered_map<int, CKC>& cs);
	void RedaktKC();
	CKC();
	CKC(std::ifstream& fin);
};



