//Problem E. Contest 1.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/316193/submission/108771528

/*
ƒаны две последовательности. Ќайдите длину их наибольшей общей подпоследовательности
(подпоследовательность Ч это то, что можно получить из данной последовательности вычеркиванием некоторых элементов).
*/

#include <iostream>
#include <vector>

template <typename T>
size_t GratestCommonSequence(const std::vector<T>& N, const std::vector<T>& M) {
	size_t n = N.size();
	size_t m = M.size();

	std::vector<std::vector<size_t>> dp(n + 1);
	for (size_t i = 0; i < n + 1; ++i) {
		dp[i].resize(m + 1, 0);
	}

	//dp[i][j] is GCS on i-prefix of N and j-prefix of M

	for (size_t i = 1; i <= n; ++i) {
		for (size_t j = 1; j <= m; ++j) {
			if (N[i - 1] == M[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return dp[n][m];
}

int main() {
	int n, m;
	std::cin >> n;
	std::vector<int> N(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> N[i];
	}
	std::cin >> m;
	std::vector<int> M(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> M[i];
	}
	std::cout << GratestCommonSequence<int>(N, M);
	return 0;
}