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
	out << "Количество труб - " << gtn.pGroup.size() << "\n";
	for (const pair<int, Pipe>& p : gtn.pGroup)
	{
		out << "Труба " << p.first << ".\n";
		out << p.second;
	}
	out << "Количество КС - " << gtn.csGroup.size() << "\n";
	for (const pair<int, CompressorStation>& cs : gtn.csGroup)
	{
		out << "Компрессорная станция " << cs.first << ".\n";
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
		TryInput(id, "Введите ID (0 - выйти): ");
		if (id == 0)
		{
			cout << "Вы вышли из режима поиска по ID.\n";
			return -1;
		}
		else if (objGroup.count(id))
		{
			return id;
		}
		cout << "Такого ID не существует. Пожалуйста, введите существующий ID.\n";
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
		cout << "Внимание! У графа есть цикл, дальнейшие действия невозможны!\n";
		return true;
	}
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
			cout << "КС " << indexVertexes[Stack.top()] << " -> ";
			Stack.pop();
		}
	}
}

int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

void Enque(int x, vector<int>& q, int& tail, vector<int>& color)
{
	q[tail] = x;
	tail++;
	color[x] = 1;
}

int bfs(int start, int end, vector<int>& color, vector<int>& pred, vector<int>& q, vector<vector<int>>& capacity, vector<vector<int>>& flow, int n, int& head, int& tail)
{
	for (int u = 0; u < n; u++)
		color[u] = 0;

	head = 0;
	tail = 0; 
	Enque(start, q, tail, color);
	pred[start] = -1;
	while (head != tail)
	{
		int u = q[head]; 
		head++; 
		color[u] = 2;
		for (int v = 0; v < n; v++)
		{
			if (color[v] == 0 && (capacity[u][v] - flow[u][v]) > 0) {
				Enque(v, q, tail, color);
				pred[v] = u;
			}
		}
	}
	if (color[end] == 2)
		return 0;
	else return 1;
}

void GTN::FindMaxFlow()
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.outCsId);
			vertexes.insert(p.second.inCsId);
		}
	int n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	unordered_map<int, int> indexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector<vector<int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i].push_back(0);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			graph[invertIndexVertexes[p.second.outCsId]][invertIndexVertexes[p.second.inCsId]] = p.second.GetProductivity();

	int start;
	TryInput(start, "Введите ID КС, из которой будет идти поток (0 - выйти): ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "Ошибка! Такой КС нет в сети((";
		return;
	}
	int end;
	TryInput(end, "Введите ID КС, в которую придёт поток (0 - выйти): ");
	if (invertIndexVertexes.find(end) != invertIndexVertexes.end())
		end = invertIndexVertexes[end];
	else
	{
		cout << "Ошибка! Такой КС нет в сети((";
		return;
	}

	int head, tail;
	vector<vector<int>> flow;
	vector<int> color, pred, q;

	int maxflow = 0;
	flow.resize(n);
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++)
			flow[i].push_back(0);
		color.push_back(-1);
		pred.push_back(-1);
		q.push_back(0);
	}
	q.push_back(0); q.push_back(0);
	while (bfs(start, end, color, pred, q, graph, flow, n, head, tail) == 0)  
	{
		int delta = 10000;
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			delta = min(delta, (graph[pred[u]][u] - flow[pred[u]][u]));
		}
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			flow[pred[u]][u] += delta;
			flow[u][pred[u]] -= delta;
		}
		maxflow += delta;
	}
	cout << "Максимальный поток: " << maxflow << endl;
}

void WritePath(int* T, int Start, int Vertex, unordered_map<int, int> indexVertexes)
{
	if (Vertex != Start)
		WritePath(T, Start, T[Vertex], indexVertexes);
	cout << indexVertexes[Vertex] << ' ';
}

void Dijkstra(const vector<vector<int>>& G, int N, int start, unordered_map<int, int> indexVertexes)
{
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
			if ((V[i] == 0) && (G[index][i] != 0) && (D[index] != INT_MAX) && ((D[index] + G[index][i]) < D[i]))
			{
				D[i] = D[index] + G[index][i];
				T[i] = index;
			}

	}
	printf("Кратчайшие пути:\n");
	for (int i = 0; i < N; i++)
		if (D[i] != INT_MAX)
		{
			cout << indexVertexes[start] << " -> " << indexVertexes[i] << " = " << D[i] << '\n';
			cout << "   Путь лежит через вершины: ";
			WritePath(T, start, i, indexVertexes);
			cout << '\n';
		}
		else
		{
			cout << "Путь " << indexVertexes[start] << " -> " << indexVertexes[i] << " не существует\n";
		}
}

void GTN::FindShortestPath()
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.outCsId);
			vertexes.insert(p.second.inCsId);
		}
	int n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	unordered_map<int, int> indexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector<vector<int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i].push_back(0);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			graph[invertIndexVertexes[p.second.outCsId]][invertIndexVertexes[p.second.inCsId]] = p.second.GetLength();
	
	int start;
	TryInput(start, "Введите ID КС, из которой нужно посчитать пути (0 - выйти): ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "Ошибка! Такой КС нет в сети((";
		return;
	}
	Dijkstra(graph, n, start, indexVertexes);
}

void GTN::AddPipe()
{
	Pipe p;
	cin >> p;
	pGroup.insert(make_pair(++Pipe::pMaxId, p));
}

void GTN::AddCs()
{
	CompressorStation cs;
	cin >> cs;
	csGroup.insert(make_pair(++CompressorStation::csMaxId, cs));
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
		cout << "\nЧто Вы хотите сделать с КС?\n"
			<< "1 - Увеличить/уменьшить общее количество цехов\n"
			<< "2 - Изменить количество работающих цехов\n"
			<< "0 и пр. - Отмена\n";
		int input;
		TryInput(input, "Введите: ");
		switch (input)
		{
		case 1:
			csGroup[id].RecountShopsCount();
			break;
		case 2:
			csGroup[id].RecountWorkingShopsCount();
			break;
		default:
			cout << "Вы вышли из режима редактирования.";
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
		cout << "Труба успешно удалена!\n";
	}
}

void GTN::DeleteCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
	{
		csGroup.erase(id);
		cout << "КС успешно удалена!\n";
	}
}

void GTN::SearchPipes()
{
	int input;
	TryInput(input, "Ищем трубу в ремонте? (1 - да, 2 - нет, пр. - выйти)\n");
	switch (input)
	{
	case 1:
	{
		for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, true))
		{
			cout << "Труба " << i << ".\n";
			cout << pGroup[i];
		}
		break;
	}
	case 2:
	{
		for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, false))
		{
			cout << "Труба " << i << ".\n";
			cout << pGroup[i];
		}
		break;
	}
	default:
		cout << "Выход из режима поиска труб\n";
		break;
	}
	cout << "\nВы хотите отредактировать эти трубы?\n"
		<< "1 - Починить все\n"
		<< "0 и пр. - Выйти\n";
	TryInput(input, "Введите: ");
	if (input == 1)
	{
		for (pair<int, Pipe> p : pGroup)
			p.second.Repair();
		cout << "Все выбранные трубы успешно починены!\n";
	}
}

void GTN::SearchCss()
{
	int input;
	cout << "По какому фильтру ищем КС?\n";
	TryInput(input, "(1 - по названию, 2 - по проценту незадействованных цехов, пр. - выйти): ");
	switch (input)
	{
	case 1:
	{
		string name;
		cout << "Введите имя КС для фильтрации: ";
		cin.ignore();
		getline(cin, name);
		for (int i : FindObjByFilter(csGroup, CheckCsByName, name))
		{
			cout << "Компрессорная станция " << i << ".\n";
			cout << csGroup[i];
		}
		break;
	}
	case 2:
	{
		float percent;
		TryInput(percent, "Введите процент для фильтрации (покажутся КС с процентом меньше указанного): ");
		for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
		{
			cout << "Компрессорная станция " << i << ".\n";
			cout << csGroup[i];
		}
		break;
	}
	default:
		cout << "Выход из режима поиска труб\n";
		break;
	}
}

void GTN::ConnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		cout << "КС, из которой выходит труба:\n";
		int outCsId = GetInputId(csGroup);
		cout << "КС, в которую входит труба:\n";
		int inCsId = GetInputId(csGroup);
		while (inCsId == outCsId)
		{
			cout << "Труба не может входить в ту же самую КС! Введите другой Id:\n";
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
		cout << "Выход из режима связи трубы с КС...\n";
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
		cout << "Выход из режима связи трубы с КС...\n";
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
			cout << "КС " << p.second.outCsId << " -- Труба " << p.first << " -> КС " << p.second.inCsId << '\n';
}
