//Problem B. Contest 1.

//Neustroeva Liza 024

// https://codeforces.com/group/R3IJoiTue4/contest/316193/submission/108779611

/*
Вам требуется написать программу, которая по заданной последовательности находит максимальную невозрастающую её подпоследовательность
(т.е такую последовательность чисел ai1,ai2,…,aik (i1<i2<…<ik), что ai1≥ai2≥…≥aik и не существует последовательности с теми же свойствами длиной k+1).
*/

#include <iostream>
#include<vector>
#include <algorithm>

template <typename T, bool comparator(const T&, const T&)>
std::vector<T> GreatestMonotoneous(const std::vector<T>& values, size_t best, size_t worst) {
	size_t n = values.size() - 1;
	std::vector<std::pair<int, int>> max_end(n + 1, std::make_pair(worst, 0));
	//pair of the greatest end of the prefix monotoneous sequence and it's index
	std::vector<int> prev_ind(n + 1, 0);
	max_end[0] = std::make_pair(best, 0);

	for (size_t i = 1; i < n + 1; ++i) {
		size_t l = 0;
		size_t r = n;
		while (r - l > 1) {
			size_t m = (r + l) / 2;
			if (comparator(max_end[m].first, values[i])) {
				l = m;
			}
			else {
				r = m;
			}
		}

		if (comparator(max_end[l].first, values[i])) {
			l = r;
		}

		if (!comparator(max_end[l].first, values[i]) && comparator(max_end[l - 1].first, values[i])) {
			prev_ind[i] = max_end[l - 1].second;
			max_end[l].first = values[i];
			max_end[l].second = i;
		}
	}

	int max_length = 0;
	while (max_length < n + 1 && max_end[max_length].first != worst) ++max_length;
	--max_length;

	int index = max_end[max_length].second;
	std::vector<int> answer;
	while (index > 0) {
		answer.push_back(index);
		index = prev_ind[index];
	}
	std::reverse(answer.begin(), answer.end());
	return answer;
}

bool isGreater(const int& a, const int& b) {
	return a > b;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n;
	std::cin >> n;
	std::vector<int> values(n + 1);
	values[0] = INT_MIN;
	for (int i = 0; i < n; ++i) {
		std::cin >> values[i + 1];
	}

	std::vector<int> answer = GreatestMonotoneous<int, isGreater>(values, INT_MAX, INT_MIN);
	std::cout << answer.size() << '\n';
	for (int i = 0; i < answer.size(); ++i) {
		std::cout << answer[i] << " ";
	}
}
