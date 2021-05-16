//Contest 10. Problem B (MST via Kruskal)
//https://codeforces.com/group/R3IJoiTue4/contest/325837/submission/116435933
//Neustroeva Liza 024

/*
* Требуется найти в связном графе остовное дерево минимального веса.
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


struct Graph {
public:
	struct Edge;
	Graph(int n) : sz(n) {}
	void read(int m);
	long long kruskal();

private:
	int sz;
	std::vector<Edge> edges;
};

struct Graph::Edge {
	int start;
	int finish;
	long long price;
	Edge(int a, int b, int c) : start(a), finish(b), price(c) {};
	bool operator<(const Edge& other) {
		return price < other.price;
	}
};

void Graph::read(int m) {
	long long start, finish, price;
	for (long long i = 0; i < m; ++i) {
		std::cin >> start >> finish >> price;
		edges.push_back(Edge(start - 1, finish - 1, price));
	}
}

long long Graph::kruskal() {
	std::vector<int> component(sz, -1);
	long long weight = 0;
	int counter = 0;
	std::sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size(); ++i) {
		int s = component[edges[i].start];
		int f = component[edges[i].finish];
		if (s == -1 || f == -1) {
			if (s == -1 && f == -1) {
				component[edges[i].start] = counter;
				component[edges[i].finish] = counter;
				++counter;
			}
			else if (s == -1) {
				component[edges[i].start] = component[edges[i].finish];
			}
			else if (f == -1) {
				component[edges[i].finish] = component[edges[i].start];
			}
			weight += edges[i].price;
		}
		else if (s != f) {
			for (int i = 0; i < sz; ++i) {
				if (component[i] == f) component[i] = s;
			}
			weight += edges[i].price;
		}
	}
	return weight;
}




int main() {
	long long n, m;
	std::cin >> n >> m;
	Graph g(n);
	g.read(m);
	std::cout << g.kruskal();
	return 0;
}