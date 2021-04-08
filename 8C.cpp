//Contest 8 : Problem C
//Neustroeva Lia 024
//https://codeforces.com/group/R3IJoiTue4/contest/319476/submission/112270851

/*
* Дан ориентированный невзвешенный граф без петель и кратных рёбер. 
Необходимо определить есть ли в нём циклы, и если есть, то вывести любой из них.

Входные данные
В первой строке входного файла находятся два натуральных числа N и M (1⩽N⩽100000, M⩽100000)
— количество вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. 
Каждое ребро задаётся парой чисел  — номерами начальной и конечной вершин соответственно.

Выходные данные
Если в графе нет цикла, то вывести «NO», иначе  — «YES» и затем перечислить все вершины в порядке обхода цикла.
*/
#include <iostream>
#include <vector>


void dfs(int vertex, bool& is_cyclic, std::vector<int>& marked, std::vector<int>& sequence, 
	std::vector<std::vector<int>>& graph) {
	if (marked[vertex] == 1) {
		is_cyclic = true;
		sequence.push_back(vertex);
		return;
	}

	marked[vertex] = 1;
	sequence.push_back(vertex);

	for (int i = 0; i < graph[vertex].size(); ++i) {
		if (marked[graph[vertex][i]] != -1 && is_cyclic == false) {
			dfs(graph[vertex][i], is_cyclic, marked, sequence, graph);
		}
	}

	if (!is_cyclic) sequence.pop_back();
	marked[vertex] = 2;
}

void graph_reading(int m, std::vector<std::vector<int>>& graph) {
	for (int i = 0; i < m; ++i) {
		int x, y;
		std::cin >> x >> y;
		graph[x - 1].push_back(y - 1);
	}
}

int main() {
	int n, m, x, y;
	bool is_cyclic = false;
	int end = -1;

	std::cin >> n >> m;

	std::vector<int> sequence;
	std::vector<int> marked(n, -1);
	std::vector<std::vector<int>> graph (n);

	graph_reading(m, graph);

	for (int i = 0; i < n; ++i) {
		if (marked[i] == -1 && !is_cyclic) {
			dfs(i, is_cyclic, marked, sequence, graph);
		}
	}

	if (!is_cyclic) {
		std::cout << "NO";
		return 0;
	}

	std::cout << "YES" << '\n';

	std::vector<int> ans;
	int index = sequence.size() - 1;
	ans.push_back(sequence[index] + 1);
	--index;
	while (sequence[index] != sequence[sequence.size() - 1]) {
		ans.push_back(sequence[index] + 1);
		--index;
	}

	for (int i = 0; i < ans.size(); ++i) {
		std::cout << ans[ans.size() - 1 - i] << " ";
	}
	return 0;
}