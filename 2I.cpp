//Problem I. Contest 1.

//Neustroeva Liza 024

// https://codeforces.com/group/R3IJoiTue4/contest/316193/submission/108341421

/*
Дана последовательность целых чисел длины n. Нужно найти количество различных непустых подпоследовательностей.
*/

#include <iostream>
#include <vector>
#include <map>

template<typename T>
size_t DifferentSequences(const std::vector<T>& sequence, size_t MOD) {
	std::vector<size_t> dp(sequence.size());
	dp[0] = 2;

	std::map<T, size_t> values;
	for (size_t i = 0; i < sequence.size(); ++i) {
		values[sequence[i]] = 0;
	}

	//std::vector<long long>current(max + 1, 0);
	values[sequence[0]] = 1;
	for (long long i = 1; i < sequence.size(); ++i) {
		dp[i] = (2 * dp[i - 1] - values[sequence[i]] + MOD) % MOD;
		values[sequence[i]] = dp[i - 1];
	}
	return (dp[sequence.size() - 1] + MOD - 1) % MOD;
}

int main() {
	size_t MOD = 1000000007;
	long long  n;
	std::cin >> n;
	std::vector<long long> sequence(n);
	for (long long i = 0; i < n; ++i) {
		std::cin >> sequence[i];
	}

	std::cout << DifferentSequences<long long>(sequence, MOD);
	return 0;
}
