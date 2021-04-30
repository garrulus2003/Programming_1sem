//Contest 9. Problem D.
//https://codeforces.com/group/R3IJoiTue4/contest/321664/submission/113483152
//Neustroeva Liza 024

/*
* Дан взвешенный ориентированный граф и вершина s в нем. 
Требуется для каждой вершины u найти длину кратчайшего пути из s в u.
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>

std::vector<bool> marked;

struct Graph {
	Graph() = default;
	Graph(int v) {
		graph.resize(v);
	}

	struct Edge {
		Edge(long long s, long long f, long long p) : start(s), finish(f), price(p) {};
		long long start;
		long long finish;
		long long price;
	};

	std::vector<std::vector<Edge>> graph;
	std::vector<Edge> edges;
	void read_graph(int edges);
	void dfs(int vertex, std::vector<bool>& marked);
	std::vector<long long> ford_bellman(int start);
};

void Graph::read_graph(int edges_quantity) {
	int start, finish, price;
	for (int i = 0; i < edges_quantity; ++i) {
		std::cin >> start >> finish >> price;
		Edge edge(start - 1, finish - 1, price);
		graph[start - 1].push_back(edge);
		edges.push_back(edge);
	}
}

std::vector<long long> Graph::ford_bellman(int start) {
	std::vector<long long> distances(graph.size(), LLONG_MAX);
	distances[start] = 0;

	for (int i = 0; i < graph.size() - 1; ++i) {
		for (int j = 0; j < edges.size(); ++j) {
			if (distances[edges[j].start] < LLONG_MAX) {
				distances[edges[j].finish] = std::min(distances[edges[j].finish], distances[edges[j].start] + edges[j].price);
			}
		}
	}

	std::vector<long long> distances2 = distances;

	for (int j = 0; j < edges.size(); ++j) {
		if (distances[edges[j].start] < LLONG_MAX) {
			if (distances[edges[j].start] + edges[j].price < distances[edges[j].finish]) {
				distances2[edges[j].finish] = LLONG_MIN;
			}
		}
	}

	std::vector<bool> marked(graph.size());
	for (int i = 0; i < graph.size(); ++i) {
		if (distances2[i] == LLONG_MIN) {
			dfs(i, marked);
		}
	}

	for (int j = 0; j < graph.size(); ++j) {
		if (marked[j]) distances[j] = LLONG_MIN;
	}
	return distances;
}

void Graph::dfs(int vertex, std::vector<bool>& marked) {
	marked[vertex] = true;
	for (int i = 0; i < graph[vertex].size(); ++i) {
		if (!marked[graph[vertex][i].finish]) dfs(graph[vertex][i].finish, marked);
	}
}

int main() {
	long long vertices, edges, start;
	std::cin >> vertices >> edges >> start;
	--start;
	Graph g(vertices);
	g.read_graph(edges);

	std::vector<long long> ans = g.ford_bellman(start);

	for (int i = 0; i < vertices; ++i) {
		if (ans[i] == LLONG_MIN) std::cout << "-" << '\n';
		else if (ans[i] == LLONG_MAX) std::cout << "*" << '\n';
		else std::cout << ans[i] << '\n';
	}
}