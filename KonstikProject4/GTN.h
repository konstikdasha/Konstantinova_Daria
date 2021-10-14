#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "Pipe.h"
#include "CompressorStation.h"
#include <unordered_map>
#include "utilities.h"
#include <set>
using namespace std;

class GTN
{
    unordered_map<int, Pipe> pGroup;
    unordered_map<int, CompressorStation> csGroup;

    vector<vector<int>> GetEdgesAndVertexes(unordered_map<int, int>& indexVertexes, int& n);

public:
    GTN();
    GTN(ifstream& fin);
    friend ostream& operator << (ostream& out, const GTN& gtn);
    void SaveToFile(ofstream& fout);
    void AddPipe();
    void AddCs();
    bool HasPipe() const;
    bool HasCs(int count = 1) const;
    void EditPipe();
    void EditCs();
    void DeletePipe();
    void DeleteCs();
    void SearchPipes();
    void SearchCss();
    void ConnectPipe();
    void DisonnectPipe();
    bool CanBeUsed(const Pipe& p) const;
    void ShowNetwork();
    void TopologicalSort();
    void FindMaxFlow();
    void FindShortestPath();
};