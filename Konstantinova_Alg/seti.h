#pragma once

#include"utility.h"
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class seti
{
    vector<vector<int>> rebra;
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);

public:
    seti(const vector<vector<int>>& r);
    void topologicalSort(unordered_map<int, int>& indexVershin);
    bool HasCicl();
    int FindMaxPotok(int start, int end);
    void FindKratchaishiPut(int start, unordered_map<int, int> indexVershin);
};