//Contest 8 : Problem I
//Neustroeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/319476/submission/116435085

/*
* Дан неориентированный граф без петель и кратных рёбер. 
Требуется найти все точки сочленения в нем.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — 
количество вершин и ребер графа соответственно (n≤20000,m≤200000).

Следующие m строк содержат описание ребер по одному на строке. 
Ребро номер i описывается двумя натуральными числами bi,ei — номерами концов ребра (1≤bi,ei≤n).

Выходные данные
Первая строка выходного файла должна содержать одно натуральное число k — 
количество точек сочленения в заданном графе. 
На следующей строке выведите k целых чисел — номера вершин, 
которые являются точками сочленения, в возрастающем порядке.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Graph {
	int vertices;
	std::vector<std::vector<int>> edges;

public:
	Graph(std::vector<std::vector<int>> graph) : vertices(graph.size()), edges(graph) {}

	Graph(int n) : vertices(n) {
		edges.resize(vertices);
	}

	void read(int edges_quantity);
	void dfs_articulation_points(int vertex, int parent, int& t, std::vector<bool>& marked, std::vector<int>& tin, 
		std::vector<int>& ret, std::set<int>& articulation_points);
	std::set<int> find_articulation_points();
};

void Graph::read(int edges_quantity) {
	for (int i = 0; i < edges_quantity; ++i) {
		int x, y;
		std::cin >> x >> y;
		edges[x - 1].push_back(y - 1);
		edges[y - 1].push_back(x - 1);
	}
}

void Graph::dfs_articulation_points(int vertex, int parent, int& t, std::vector<bool>& marked, std::vector<int>& tin,
	std::vector<int>& ret, std::set<int>& articulation_points) {
	tin[vertex] = t++;
	ret[vertex] = tin[vertex];
	marked[vertex] = true;
	int cnt = 0;
	for (int i = 0; i < edges[vertex].size(); ++i) {
		if (edges[vertex][i] == parent) continue;
		if (marked[edges[vertex][i]]) {
			ret[vertex] = std::min(ret[vertex], tin[edges[vertex][i]]);
		}
		else {
			dfs_articulation_points(edges[vertex][i], vertex, t, marked, tin, ret, articulation_points);
			++cnt;
			if (parent != -1) {
				if (ret[edges[vertex][i]] >= tin[vertex]) {
					articulation_points.insert(vertex);
				}
			}
			ret[vertex] = std::min(ret[vertex], ret[edges[vertex][i]]);
		}
	}
	if (parent == -1 && cnt > 1) articulation_points.insert(vertex);
}

std::set<int> Graph::find_articulation_points() {
	std::vector<bool> marked(vertices, false);
	std::vector<int> tin(vertices);
	std::vector<int>ret(vertices);
	std::set<int> articulation_points;
	int t = 0;
	for (int i = 0; i < vertices; ++i) {
		if (!marked[i]) {
			dfs_articulation_points(i, -1, t, marked, tin, ret, articulation_points);
		}
	}
	return articulation_points;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph g(n);
	g.read(m);

	std::set<int> ans = g.find_articulation_points();

	std::cout << ans.size() << '\n';
	for (auto vertex : ans) std::cout << vertex + 1 << " ";
}