//Contest 9. Problem F.
//https://codeforces.com/group/R3IJoiTue4/contest/321664/submission/114725112
//Neustroeva Liza 024

/*
* Дан взвешенный неориентированный граф. Требуется найти вес минимального пути между двумя вершинами.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <math.h>
#include <string>
#include <set>

struct Graph {
	int MAX = 20000000;
	Graph() = default;
	Graph(int v) {
		graph.resize(v);
	}

	struct Edge {
		Edge(int s, int f, int p) : start(s), finish(f), price(p) {};
		int start;
		int finish;
		int price;
	};

	std::vector<std::vector<Edge>> graph;
	void read_graph(int edges);
	std::vector<int> dijkstra(int start) const;
};

void Graph::read_graph(int edges) {
	int start, finish, price;
	for (int i = 0; i < edges; ++i) {
		std::cin >> start >> finish >> price;
		graph[start - 1].push_back(Edge(start - 1, finish - 1, price));
		graph[finish - 1].push_back(Edge(finish - 1, start - 1, price));
	}
}

std::vector<int> Graph::dijkstra(int start) const {
	std::set<std::pair<int, int>> current_dist;
	std::vector<int> distances(graph.size(), MAX);
	distances[start] = 0;

	for (int i = 0; i < graph.size(); ++i) {
		current_dist.insert(std::make_pair(MAX, i));
	}

	current_dist.erase(std::make_pair(MAX, start));
	current_dist.insert(std::make_pair(0, start));
	while (!current_dist.empty() && (current_dist.begin()->first) != MAX) {
		std::pair<int, int> p = *current_dist.begin();
		for (int i = 0; i < graph[p.second].size(); ++i) {
			int vertex = graph[p.second][i].finish;
			if (current_dist.find(std::make_pair(distances[vertex], vertex)) != current_dist.end()) {
				current_dist.erase(std::make_pair(distances[vertex], vertex));
				distances[vertex] = std::min(distances[vertex], p.first + graph[p.second][i].price);
				current_dist.insert(std::make_pair(distances[vertex], vertex));
			}
		}
		current_dist.erase(p);
	}

	return distances;
}

int main() {
	int MAX = 20000000;
	int vertices, edges, start, finish, a, b, c;
	std::cin >> vertices >> edges >> start >> finish;
	--start;
	--finish;
	Graph g(vertices);
	g.read_graph(edges);

	int distance = g.dijkstra(start)[finish];

	if (distance != MAX) std::cout << distance;
	else std::cout << -1;

	return 0;
}