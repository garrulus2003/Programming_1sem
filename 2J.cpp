//Problem J. Contest 1.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/316193/submission/108770604

/*
Найдите максимальный вес золота, который можно унести в рюкзаке вместительностью S, если есть N золотых слитков с заданными весами.
*/

#include <iostream>
#include <vector>

template <typename T, T binop(const T&, const T&)>
size_t backpack(const std::vector<T>& mass, const T& capacity) {
	size_t quantity = mass.size();
	std::vector<std::vector<T>> dp(quantity + 1);

	for (size_t i = 0; i < quantity + 1; ++i) {
		dp[i].resize(capacity + 1);
	}
	// dp[i][j] = maximum weight of a backpack not greater than j using first i elements of a sequence

	for (size_t i = 1; i < quantity + 1; ++i) {
		for (size_t j = 0; j < capacity + 1 && j < mass[i - 1]; ++j) {
			dp[i][j] = dp[i - 1][j];
		}
		for (size_t j = mass[i - 1]; j < capacity + 1; ++j) {
			dp[i][j] = (dp[i - 1][j] > binop(dp[i - 1][j - mass[i - 1]], mass[i - 1])) ? dp[i - 1][j] :
				binop(dp[i - 1][j - mass[i - 1]], mass[i - 1]);
		}
	}
	return dp[quantity][capacity];
}

size_t sum(const size_t& a, const size_t& b) {
	return a + b;
}

int main() {
	size_t S, N;
	std::cin >> S >> N;
	std::vector<size_t> mass(N);

	for (size_t i = 0; i < N; ++i) {
		std::cin >> mass[i];
	}

	std::cout << backpack<size_t, sum>(mass, S);
	return 0;
}