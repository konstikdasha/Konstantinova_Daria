#include "GTN.h"

unordered_map<int, Pipe> pGroup = unordered_map<int, Pipe>{};
unordered_map<int, CompressorStation> csGroup = unordered_map<int, CompressorStation>{};

GTN::GTN() { }

GTN::GTN(ifstream& fin)
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
}

void GTN::SaveToFile(ofstream& fout)
{
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
}

ostream& operator << (ostream& out, const GTN& gtn)
{
	out << "���������� ���� - " << gtn.pGroup.size() << "\n";
	for (const pair<int, Pipe>& p : gtn.pGroup)
	{
		out << "����� " << p.first << ".\n";
		out << p.second;
	}
	out << "���������� �� - " << gtn.csGroup.size() << "\n";
	for (const pair<int, CompressorStation>& cs : gtn.csGroup)
	{
		out << "������������� ������� " << cs.first << ".\n";
		out << cs.second;
	}
	return out;
}

template <typename T>
int GetInputId(const unordered_map<int, T>& objGroup)
{
	int id;
	while (true)
	{
		TryInput(id, "������� ID (0 - �����): ");
		if (id == 0)
		{
			cout << "�� ����� �� ������ ������ �� ID.\n";
			return -1;
		}
		else if (objGroup.count(id))
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

vector<vector<int>> GTN::GetEdgesAndVertexes(unordered_map<int, int>& indexVertexes, int& n)
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.outCsId);
			vertexes.insert(p.second.inCsId);
		}
	n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector<vector<int>> edges;
	edges.resize(n);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			edges[invertIndexVertexes[p.second.outCsId]].push_back(invertIndexVertexes[p.second.inCsId]);
	return edges;
}

void topologicalSortUtil(int v, bool visited[], stack<int>& Stack, vector<vector<int>>& edges)
{
	visited[v] = true;

	vector<int>::iterator i;
	for (i = edges[v].begin(); i != edges[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack, edges);

	Stack.push(v);
}

bool dfs(int v, vector<char>& cl, vector<int>& p, int& cycle_st, const vector<vector<int>>& edges) {
	cl[v] = 1;
	for (size_t i = 0; i < edges[v].size(); ++i) {
		int to = edges[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (dfs(to, cl, p, cycle_st, edges))
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

bool HasCycle(vector<vector<int>>& edges, int n)
{
	vector<char> cl;
	vector<int> p;
	int cycle_st;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_st = -1;
	for (int i = 0; i < n; ++i)
		if (dfs(i, cl, p, cycle_st, edges))
			break;
	if (cycle_st == -1)
	{
		return false;
	}
	else
	{
		cout << "��������! � ����� ���� ����, ���������� �������� ����������!\n";
		return true;
	}
}

void GTN::AddPipe(const Pipe& p)
{
	pGroup.insert(make_pair(++Pipe::pMaxId, p));
}

void GTN::AddCs(const CompressorStation& cs)
{
	csGroup.insert(make_pair(++CompressorStation::csMaxId, cs));
}

void GTN::TopologicalSort()
{
	unordered_map<int, int> indexVertexes;
	int n;
	vector<vector<int>> edges = GetEdgesAndVertexes(indexVertexes, n);
	if (HasCycle(edges, n) == false)
	{
		stack<int> Stack;

		bool* visited = new bool[n];
		for (int i = 0; i < n; i++)
			visited[i] = false;

		for (int i = 0; i < n; i++)
			if (visited[i] == false)
				topologicalSortUtil(i, visited, Stack, edges);

		while (Stack.empty() == false)
		{
			cout << "�� " << indexVertexes[Stack.top()] << " -> ";
			Stack.pop();
		}
	}
}

bool GTN::HasPipe() const
{
	return pGroup.size() != 0;
}

bool GTN::HasCs(int count) const
{
	return csGroup.size() >= count;
}

void GTN::EditPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
		pGroup[id].Edit();
}

void GTN::EditCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
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
			csGroup[id].RecountShopsCount();
			break;
		case 2:
			csGroup[id].RecountWorkingShopsCount();
			break;
		default:
			cout << "�� ����� �� ������ ��������������.";
			break;
		}
	}
}

void GTN::DeletePipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup.erase(id);
		cout << "����� ������� �������!\n";
	}
}

void GTN::DeleteCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
	{
		csGroup.erase(id);
		cout << "�� ������� �������!\n";
	}
}

void GTN::SearchPipes()
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
	cout << "\n�� ������ ��������������� ��� �����?\n"
		<< "1 - �������� ���\n"
		<< "0 � ��. - �����\n";
	TryInput(input, "�������: ");
	if (input == 1)
	{
		for (pair<int, Pipe> p : pGroup)
			p.second.Repair();
		cout << "��� ��������� ����� ������� ��������!\n";
	}
}

void GTN::SearchCss()
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

void GTN::ConnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		cout << "��, �� ������� ������� �����:\n";
		int outCsId = GetInputId(csGroup);
		cout << "��, � ������� ������ �����:\n";
		int inCsId = GetInputId(csGroup);
		while (inCsId == outCsId)
		{
			cout << "����� �� ����� ������� � �� �� ����� ��! ������� ������ Id:\n";
			int inCsId = GetInputId(csGroup);
		}
		if (outCsId != -1 && inCsId != -1)
		{
			pGroup[id].outCsId = outCsId;
			pGroup[id].inCsId = inCsId;
		}
	}
	else
	{
		cout << "����� �� ������ ����� ����� � ��...\n";
	}
}

void GTN::DisonnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup[id].outCsId = -1;
		pGroup[id].inCsId = -1;
	}
	else
	{
		cout << "����� �� ������ ����� ����� � ��...\n";
	}
}

bool GTN::CanBeUsed(const Pipe& p) const
{
	return p.inCsId > 0 &&
		p.outCsId > 0 &&
		!p.GetRepairing() &&
		csGroup.find(p.inCsId) != csGroup.end()
		&& csGroup.find(p.outCsId) != csGroup.end();
}

void GTN::ShowNetwork()
{
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			cout << "�� " << p.second.outCsId << " -- ����� " << p.first << " -> �� " << p.second.inCsId << '\n';
}
