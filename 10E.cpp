//Contest 10. Problem E.
//https://codeforces.com/group/R3IJoiTue4/contest/325837/submission/116437153
//Neustroeva Liza 024

/*
* Требуется построить в двудольном графе минимальное контролирующее множество, если дано максимальное паросочетание.
*/

#include <iostream>
#include <vector>
#include <map>
#include <deque>

struct BipartiteGraph {
	BipartiteGraph(int m, int n);
	void read();
	void bfs_for_min_control(int v, std::vector<bool>& marked, const std::vector<int>& max_pair) const;
	std::vector<bool> get_min_control(const std::vector<int>& max_pair) const;
	void print_min_control(const std::vector<int>& max_pair) const;

private:
	int l, r;
	std::vector<std::vector<int>> graph;
};

BipartiteGraph::BipartiteGraph(int m, int n) : l(m), r(n) {
	graph.resize(l + r);
}

void BipartiteGraph::read() {
	int degree, connected;
	for (int i = 0; i < l; ++i) {
		std::cin >> degree;
		for (int j = 0; j < degree; ++j) {
			std::cin >> connected;
			graph[i].push_back(connected + l - 1);
			graph[connected + l - 1].push_back(i);
		}
	}
}

std::vector<int> read_max_pair(int m, int n) {
	std::vector<int> max_pair(m + n, 0);
	for (int i = 0; i < m; ++i) {
		std::cin >> max_pair[i];
		max_pair[i] += m - 1;
		max_pair[max_pair[i]] = i;
	}
	return max_pair;
}


void BipartiteGraph::bfs_for_min_control(int v, std::vector<bool>& marked, const std::vector<int>& max_pair) const {
	std::deque<int> d;
	d.push_back(v);
	marked[v] = true;
	while (!d.empty()) {
		for (int i = 0; i < graph[d[0]].size(); ++i) {
			if (((d[0] < l) ^ !(max_pair[d[0]] != graph[d[0]][i])) && !marked[graph[d[0]][i]]) {
				marked[graph[d[0]][i]] = true;
				d.push_back(graph[d[0]][i]);
			}
		}
		d.pop_front();
	}
}

std::vector<bool> BipartiteGraph::get_min_control(const std::vector<int>& max_pair) const {
	std::vector<bool> marked(l + r);
	for (int i = 0; i < l; ++i) {
		if (!marked[i] && max_pair[i] == l - 1) {
			bfs_for_min_control(i, marked, max_pair);
		}
	}
	for (int i = 0; i < l; ++i) marked[i] = !marked[i];
	return marked;
}

void BipartiteGraph::print_min_control(const std::vector<int>& max_pair) const {
	auto marked = get_min_control(max_pair);
	int ans_l = 0;
	int ans_r = 0;
	for (int i = 0; i < l; ++i) {
		if (marked[i]) ++ans_l;
	}

	for (int i = 0; i < r; ++i) {
		if (marked[i + l]) ++ans_r;
	}

	std::cout << ans_l + ans_r << '\n';

	std::cout << ans_l << " ";
	for (int i = 0; i < l; ++i) {
		if (marked[i]) std::cout << i + 1 << " ";
	}
	std::cout << '\n';
	std::cout << ans_r << " ";
	for (int i = 0; i < r; ++i) {
		if (marked[i + l]) std::cout << i + 1 << " ";
	}
}
int main() {
	int n, m;
	std::cin >> m >> n;
	BipartiteGraph g(m, n);
	g.read();
	auto max_pair = read_max_pair(m, n);
	g.print_min_control(max_pair);
}

#include <iostream>
#include <vector>
#include <map>
#include <deque>

struct BipartiteGraph {
	BipartiteGraph(int m, int n);
	void read();
	void bfs_for_min_control(int v, std::vector<bool>& marked, const std::vector<int>& max_pair) const;
	std::vector<bool> get_min_control(const std::vector<int>& max_pair) const;
	void print_min_control(const std::vector<int>& max_pair) const;

private:
	int l, r;
	std::vector<std::vector<int>> graph;
};

BipartiteGraph::BipartiteGraph(int m, int n) : l(m), r(n) {
	graph.resize(l + r);
}

void BipartiteGraph::read() {
	int degree, connected;
	for (int i = 0; i < l; ++i) {
		std::cin >> degree;
		for (int j = 0; j < degree; ++j) {
			std::cin >> connected;
			graph[i].push_back(connected + l - 1);
			graph[connected + l - 1].push_back(i);
		}
	}
}

std::vector<int> read_max_pair(int m, int n) {
	std::vector<int> max_pair(m + n, 0);
	for (int i = 0; i < m; ++i) {
		std::cin >> max_pair[i];
		max_pair[i] += m - 1;
		max_pair[max_pair[i]] = i;
	}
	return max_pair;
}


void BipartiteGraph::bfs_for_min_control(int v, std::vector<bool>& marked, const std::vector<int>& max_pair) const {
	std::deque<int> d;
	d.push_back(v);
	marked[v] = true;
	while (!d.empty()) {
		for (int i = 0; i < graph[d[0]].size(); ++i) {
			if (((d[0] < l) ^ !(max_pair[d[0]] != graph[d[0]][i])) && !marked[graph[d[0]][i]]) {
				marked[graph[d[0]][i]] = true;
				d.push_back(graph[d[0]][i]);
			}
		}
		d.pop_front();
	}
}

std::vector<bool> BipartiteGraph::get_min_control(const std::vector<int>& max_pair) const {
	std::vector<bool> marked(l + r);
	for (int i = 0; i < l; ++i) {
		if (!marked[i] && max_pair[i] == l - 1) {
			bfs_for_min_control(i, marked, max_pair);
		}
	}
	for (int i = 0; i < l; ++i) marked[i] = !marked[i];
	return marked;
}

void BipartiteGraph::print_min_control(const std::vector<int>& max_pair) const {
	auto marked = get_min_control(max_pair);
	int ans_l = 0;
	int ans_r = 0;
	for (int i = 0; i < l; ++i) {
		if (marked[i]) ++ans_l;
	}

	for (int i = 0; i < r; ++i) {
		if (marked[i + l]) ++ans_r;
	}

	std::cout << ans_l + ans_r << '\n';

	std::cout << ans_l << " ";
	for (int i = 0; i < l; ++i) {
		if (marked[i]) std::cout << i + 1 << " ";
	}
	std::cout << '\n';
	std::cout << ans_r << " ";
	for (int i = 0; i < r; ++i) {
		if (marked[i + l]) std::cout << i + 1 << " ";
	}
}
int main() {
	int n, m;
	std::cin >> m >> n;
	BipartiteGraph g(m, n);
	g.read();
	auto max_pair = read_max_pair(m, n);
	g.print_min_control(max_pair);
}