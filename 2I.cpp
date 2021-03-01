#include <iostream>
#include <vector>

int main() {
	long long MOD = 1000000007;
	long long  n;
	long long max = INT_MIN;
	std::cin >> n;
	std::vector<long long> sequence(n);
	for (long long i = 0; i < n; ++i) {
		std::cin >> sequence[i];
		max = (sequence[i] > max) ? sequence[i] : max;
	}
	std::vector<long long> dp(n);
	dp[0] = 2;
	std::vector<long long>current(max + 1, 0);
	current[sequence[0]] = 1;
	for (long long i = 1; i < n; ++i) {
		dp[i] = (2 * dp[i - 1] - current[sequence[i]] + MOD) % MOD;
		current[sequence[i]] = dp[i - 1];
	}
	std::cout << (dp[n - 1] + MOD - 1) % MOD;
	return 0;
}