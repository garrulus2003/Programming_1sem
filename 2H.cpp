//Problem H. Contest 1.

//Neustroeva Liza 024

// https://codeforces.com/group/R3IJoiTue4/contest/316193/submission/108772092

/*
Даны две последовательности чисел — a и b. Нужно найти наибольшую общую возрастающую подпоследовательность.
Более формально: такие 1≤i1<i2<⋯<ik≤a.n и 1≤j1<j2⋯<jk≤b.n, что ∀t:ait=bjt,ait<ait+1 и k максимально.
*/

#include <iostream>
#include <vector>

template <typename T, bool comparator(const T&, const T&)>
size_t GreatestCommonMonotoneous(const std::vector<T>& N, const std::vector<T>& M) {
	size_t n = N.size();
	size_t m = M.size();

	std::vector<std::vector<size_t>> dp(n + 1);
	for (size_t i = 0; i < n + 1; ++i) {
		dp[i].resize(m + 1, 0);
	}

	for (size_t i = 1; i <= n; ++i) {
		size_t cur_max = 0;
		size_t cur_max_ind = 0;
		for (size_t j = 1; j <= m; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (N[i - 1] == M[j - 1] && dp[i - 1][j] < cur_max + 1) {
				dp[i][j] = cur_max + 1;
			}
			if (comparator(N[i - 1], M[j - 1]) && dp[i - 1][j] > cur_max) {
				cur_max = dp[i - 1][j];
				cur_max_ind = j;
			}
		}
	}
	size_t ans = 0;
	for (size_t i = 0; i < n + 1; ++i) {
		for (size_t j = 0; j < m + 1; ++j) {
			ans = std::max(ans, dp[i][j]);
		}
	}
	return ans;
}

bool isGreater(const int& a, const int& b) {
	return a > b;
}

int main() {
	int m, n;
	std::cin >> n >> m;
	std::vector<int> N(n);
	std::vector<int> M(m);

	for (int i = 0; i < n; ++i) {
		std::cin >> N[i];
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> M[i];
	}

	std::cout << GreatestCommonMonotoneous<int, isGreater>(N, M);
	return 0;
}