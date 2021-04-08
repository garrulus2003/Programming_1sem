//Contest 8: Problem B
//Neustroeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/319476/submission/112270203

/*
Напишите программу, которая для двух вершин дерева определяет, является ли одна из них предком другой.

Входные данные
Первая строка входного файла содержит натуральное число n(1≤n≤100000) — количество вершин в дереве.

Во второй строке находится n чисел.При этом i - е число второй строки определяет 
непосредственного родителя вершины с номером i.Если номер родителя равен нулю, 
то вершина является корнем дерева.

В третьей строке находится число m(1≤m≤100000)  — количество запросов.Каждая из следующих 
m строк содержит два различных числа a и b(1≤a, b≤n).

Выходные данные
Для каждого из m запросов выведите на отдельной строке число 1, 
если вершина a является одним из предков вершины b, и 0 в противном случае.
*/
#include <iostream>
#include <vector>

void dfs(int vertex, int& t, std::vector<int>& in, std::vector<int>& out, 
	std::vector<std::vector<int>>& graph) {
	++t;
	in[vertex] = t;
	for (int i = 0; i < graph[vertex].size(); ++i) {
		if (in[graph[vertex][i]] == -1) dfs(graph[vertex][i], t, in, out, graph);
	}
	++t;
	out[vertex] = t;
}

void tree_reading(int n, std::vector<std::vector<int>>& graph) {
	graph.resize(n + 1);
	std::vector<int> parents(n + 1);
	for (int i = 0; i < n; ++i) {
		std::cin >> parents[i];
		graph[parents[i]].push_back(i + 1);
	}
}

int main() {
	int n, m, x, y;
	std::cin >> n;

	int t = 0;
	std::vector<int> in(n + 1, -1);
	std::vector<int> out(n + 1, -1);
	std::vector<std::vector<int>> graph (n + 1);

	tree_reading(n, graph);
	dfs(0, t, in, out, graph);

	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		std::cin >> x >> y;
		if (in[x] < in[y] && out[x] > out[y]) { //checking whether one is parent of another
			std::cout << 1 << '\n';
		}
		else {
			std::cout << 0 << '\n';
		}
	}
}