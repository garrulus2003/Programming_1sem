//Contest 8: Problem J
//Neustroeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/319476/submission/112274542

/*
* В состав Галактической империи входит N планет. Между большинством из них существуют гиперканалы. 
Новый император повелел, чтобы с любой планеты можно было попасть на любую другую, 
пройдя только через один гиперканал. Каналы устроены так, 
что позволяют путешествовать только в одну сторону. 
Единственный оставшийся прокладчик гиперканалов расположен на базе около планеты с номером A. 
К сожалению, он не может путешествовать по уже существующим каналам, он всегда прокладывает новый. 
А наличие двух каналов в одном направлении между двумя планетами существенно осложняет навигацию. 
Ваша задача – найти такой маршрут для прокладчика, чтобы все необходимые каналы были построены, 
и не было бы построено лишних. В конце своего маршрута прокладчик должен оказаться на своей родной базе, 
с которой он начал движение.
*/

#include <iostream>
#include <vector>
#include <map>


class Graph_euler {
	int vertices;
	std::vector<std::vector<int>> graph;
	std::vector<int> cycle;
	std::map<std::pair<int, int>, bool> marked_edges;

public:
	Graph_euler(int n) : vertices(n) {
		graph.resize(n);
	}

	void read_antigraph();
	void euler(int v);
	std::vector<int> get_euler(int v);
};

void Graph_euler::read_antigraph() {
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			bool are_connected;
			std::cin >> are_connected;;
			if (!are_connected && i != j) {
				graph[i].push_back(j);
			}
			marked_edges[std::make_pair(i, j)] = false;
		}
	}
}

void Graph_euler::euler(int v) {
	while (graph[v].size() != 0) {
		int u = graph[v][graph[v].size() - 1];
		if (marked_edges[std::make_pair(v, u)]) {
			graph[v].pop_back();
			continue;
		}
		marked_edges[std::make_pair(v, u)] = true;
		euler(u);
	}
	cycle.push_back(v + 1);
}

std::vector<int> Graph_euler::get_euler(int v) {
	euler(v);
	return cycle;
}

int main() {
	int n, start;
	std::cin >> n >> start;
	Graph_euler g(n);
	g.read_antigraph();

	std::vector<int> ans = g.get_euler(start - 1);

	for (int i = ans.size() - 1; i > 0; --i) {
		std::cout << ans[i] << " " << ans[i - 1] << '\n';
	}
}