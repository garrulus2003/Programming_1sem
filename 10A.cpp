//Contest 10. Problem A (MST vis Prima)
//https://codeforces.com/group/R3IJoiTue4/contest/325837/submission/116435510
//Neustroeva Liza 024

/*
* Требуется найти в связном графе остовное дерево минимального веса.
*/

#include <iostream>
#include <set>
#include <vector>

struct Graph {
private:
	std::vector<std::vector<std::pair<long long, long long>>> graph;
	int sz;


public:
	Graph(int n);
	void read(int edges);
	long long prima() const;
};

Graph::Graph(int n) : sz(n) {
	graph.resize(n);
}

void Graph::read(int edges) {
	long long start, finish, price;
	for (long long i = 0; i < edges; ++i) {
		std::cin >> start >> finish >> price;
		graph[start - 1].push_back(std::make_pair(finish - 1, price));
		graph[finish - 1].push_back(std::make_pair(start - 1, price));
	}
}

long long Graph::pryma() const {
	long long weight = 0;
	std::vector<long long> distances(sz, INT_MAX);
	std::set<std::pair<long long, long long>> current_dist;
	std::vector<bool> marked(sz);
	distances[0] = 0;
	marked[0] = true;

	for (long long i = 1; i < sz; ++i) {
		current_dist.insert(std::make_pair(INT_MAX, i));
	}

	auto p = std::make_pair(0, 0);
	while (!current_dist.empty()) {
		for (long long i = 0; i < graph[p.second].size(); ++i) {
			long long v = graph[p.second][i].first;
			long long w = graph[p.second][i].second;
			if (!marked[v] && distances[v] > w) {
				current_dist.erase(std::make_pair(distances[v], v));
				distances[v] = w;
				current_dist.insert(std::make_pair(distances[v], v));
			}
		}
		p = *current_dist.begin();
		current_dist.erase(p);
		weight += p.first;
		marked[p.second] = true;
	}

	return weight;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	Graph g(n);
	g.read(m);
	std::cout << g.pryma();
	return 0;
}