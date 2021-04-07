//Contest 7: Problem F
//Neustrioeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/316719/submission/112056101

/*
Продавец аквариумов для кошек хочет объехать n городов, посетив каждый из них ровно один раз.
Помогите ему найти кратчайший путь.

Входные данные
Первая строка входного файла содержит натуральное число n (1⩽n⩽13) — количество городов.
Следующие n строк содержат по n чисел — длины путей между городами.

В i-й строке j-е число — ai,j — это расстояние между городами i и j (0⩽ai,j⩽106; ai,j=aj,i; ai,i=0).

Выходные данные
В первой строке выходного файла выведите длину кратчайшего пути.
Во второй строке выведите n чисел — порядок, в котором нужно посетить города.
*/

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::pair<T, std::vector<size_t>> salesman(const std::vector<std::vector<T>>& dist) {
	size_t n = dist.size();
	std::vector<std::vector<T>> dp(1 << n, std::vector<T>(n, INT_MAX));
	std::vector<std::vector<size_t>> prev(1 << n, std::vector<size_t>(n, 0));

	dp[0] = std::vector<T>(n, 0);
	for (size_t i = 0; i < n; ++i) {
		dp[1 << i] = std::vector<T>(n, 0);
	}

	for (size_t i = 0; i < (1 << n); ++i) {  //search between all masks
		for (size_t j = 0; j < n; ++j) {        //for each mask search between all towns
			if ((1 << j & i) != 0) {         //if town is in mask
				for (size_t k = 0; k < n; ++k) {//searching for other towns in mask
					if (k != j && ((1 << k & i) != 0)) {
						if (dp[i][j] > dp[i - (1 << j)][k] + dist[j][k]) {
							prev[i][j] = k;
						}
						dp[i][j] = std::min(dp[i][j], dp[i - (1 << j)][k] + dist[j][k]);
					}
				}
			}
		}
	}

	T ans = INT_MAX;
	size_t  ans_ind = 0;
	size_t  mask = (1 << n) - 1;

	for (size_t i = 0; i < n; ++i) {
		if (dp[mask][i] < ans) {
			ans = dp[mask][i];
			ans_ind = i;
		}
	}

	std::vector<size_t> sequence;
	for (int i = 0; i < n; ++i) {
		sequence.push_back(ans_ind + 1);
		T current_prev = prev[mask][ans_ind];
		mask -= (1 << ans_ind);
		ans_ind = current_prev;
	}

	std::reverse(sequence.begin(), sequence.end());

	return std::make_pair(ans, sequence);
}

int main() {

	size_t n;
	std::cin >> n;
	std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> dist[i][j];
		}
	}

	std::pair<long long, std::vector<size_t>> answer = salesman(dist);
	std::cout << answer.first << '\n';
	for (size_t i = 0; i < n; ++i) std::cout << answer.second[i] << " ";
}