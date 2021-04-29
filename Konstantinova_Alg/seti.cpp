#include "seti.h"

using namespace std;

vector<vector<int>> rebra;

void seti::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	visited[v] = true;

	vector<int>::iterator i;
	for (i = rebra[v].begin(); i != rebra[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	Stack.push(v);
}

seti::seti(const vector<vector<int>>& r)
{
	rebra = r;
}

bool dfs(int v, vector<char>& cl, vector<int>& p, int& cycle_st, const vector<vector<int>>& adj) {
	cl[v] = 1;
	for (size_t i = 0; i < adj[v].size(); ++i) {
		int to = adj[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (dfs(to, cl, p, cycle_st, adj))
				return true;
		}
		else if (cl[to] == 1) {
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

void seti::topologicalSort(unordered_map<int, int>& indexVershin)
{
	stack<int> Stack;
	int n = rebra.size();
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	for (int i = 0; i < n; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	while (Stack.empty() == false)
	{
		cout << "КС " << indexVershin[Stack.top()] << " - ";
		Stack.pop();
	}
	cout << endl;
}

bool seti::HasCicl()
{
	int n = rebra.size();
	vector<char> cl;
	vector<int> p;
	int cycle_st;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_st = -1;
	for (int i = 0; i < n; ++i)
		if (dfs(i, cl, p, cycle_st, rebra))
			break;
	if (cycle_st == -1)
		return false;
	else
		return true;
}
int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

void Enque(int x, vector<int>& q, int& konec, vector<int>& pometki)
{
	q[konec] = x;
	konec++;
	pometki[x] = 1;
}

int bfs(int start, int end, vector<int>& pometki, vector<int>& pred, vector<int>& q, vector<vector<int>>& capacity, vector<vector<int>>& flow, int n, int& nachalo, int& konec)
{
	for (int u = 0; u < n; u++)
		pometki[u] = 0;

	nachalo = 0;
	konec = 0;
	Enque(start, q, konec, pometki);
	pred[start] = -1;
	while (nachalo != konec)
	{
		int u = q[nachalo];
		nachalo++;
		pometki[u] = 2;
		for (int v = 0; v < n; v++)
		{
			if (pometki[v] == 0 && (capacity[u][v] - flow[u][v]) > 0) {
				Enque(v, q, konec, pometki);
				pred[v] = u;
			}
		}
	}
	if (pometki[end] == 2)
		return 0;
	else return 1;
}
int seti::FindMaxPotok(int start, int end)
{
	int nachalo, konec;
	vector<vector<int>> potok;
	vector<int> pometki, pred, q;
	int n = rebra.size();

	int maxpotok = 0;
	potok.resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			potok[i].push_back(0);
		pometki.push_back(-1);
		pred.push_back(-1);
		q.push_back(0);
	}
	q.push_back(0); q.push_back(0);
	while (bfs(start, end, pometki, pred, q, rebra, potok, n, nachalo, konec) == 0)
	{
		int delta = 10000;
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			delta = min(delta, (rebra[pred[u]][u] - potok[pred[u]][u]));
		}
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			potok[pred[u]][u] += delta;
			potok[u][pred[u]] -= delta;
		}
		maxpotok += delta;
	}
	return maxpotok;
}
void PrintPut(int* t, int start, int vertex, unordered_map<int, int> indexVershin)
{
	if (vertex != start)
		PrintPut(t, start, t[vertex], indexVershin);
	cout << indexVershin[vertex] << ' ';
}
void seti::FindKratchaishiPut(int start, unordered_map<int, int> indexVershin)
{
	int N = rebra.size();
	int min, index;
	int* D;
	int* V;
	int* T;
	V = (int*)malloc(N * sizeof(int));
	D = (int*)malloc(N * sizeof(int));
	T = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		V[i] = 0;
		D[i] = INT_MAX;
		T[i] = -1;
	}
	T[start] = 0;
	D[start] = 0;
	for (int count = 0; count < N - 1; count++)
	{
		min = INT_MAX;
		for (int i = 0; i < N; i++)
			if ((V[i] == 0) && (D[i] <= min))
			{
				min = D[i];
				index = i;
			}
		V[index] = 1;
		for (int i = 0; i < N; i++)
			if ((V[i] == 0) && (rebra[index][i] != 0) && (D[index] != INT_MAX) && ((D[index] + rebra[index][i]) < D[i]))
			{
				D[i] = D[index] + rebra[index][i];
				T[i] = index;
			}
	}
	cout << "Все кратчайшие пути из этой вершины: " << endl;
	for (int i = 0; i < N; i++)
		if (D[i] != INT_MAX)
		{
			cout << indexVershin[start] << " - " << indexVershin[i] << " = " << D[i] << '\n';
			cout << "Путь: ";
			PrintPut(T, start, i, indexVershin);
			cout << endl;
		}
		else
		{
			cout << "Пути из " << indexVershin[start] << " в " << indexVershin[i] << " нет" << endl;
		}
}

