//Contest 4. Problem H

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/305349/submission/101127372

/*
Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.

Для решения задачи используйте структуру данных Sparse Table. Требуемое время обработки каждого диапазона O(1). 
Время подготовки структуры данных O(nlogn).

Входные данные
В первой строке заданы 2 числа: размер последовательности N и количество диапазонов M.

Следующие N целых чисел задают последовательность. Далее вводятся M пар чисел - границ диапазонов.

Выходные данные
Для каждого из M диапазонов напечатать элемент последовательности - 2ю порядковую статистику. По одному числу в строке.
*/

#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>

static std::pair<size_t, size_t> degMax(size_t n) {
	size_t index = 0;
	size_t exp = 1;
	while (2 * exp < n) {
		++index;
		exp *= 2;
	}
	return std::make_pair(index, exp);
}

template<typename T, bool Comparator(const T&, const T&)>
T min(const T& a, const T& b) {
	return (Comparator(a, b) ? a : b);
}

template<typename T, bool Comparator(const T&, const T&)>
T max(const T& a, const T& b) {
	return (Comparator(b, a) ? a : b);
}

template<typename T, bool Comparator(const T&, const T&)>
struct SparseTable {
	size_t size = 0;
	std::vector<std::vector<T>> ST;

	SparseTable(std::vector<T>& vec);
	SparseTable() : size(0) {};
	T getMin(size_t l, size_t r) const;
};

template<typename T, bool Comparator(const T&, const T&)>
T SparseTable<T, Comparator>::getMin(size_t l, size_t r) const{
	std::pair<size_t, size_t> p = degMax(r - l + 1);
	return min<T, Comparator>(ST[p.first][l - 1], ST[p.first][r - p.second]);
}

template<typename T, bool Comparator(const T&, const T&)>
SparseTable<T, Comparator>::SparseTable(std::vector<T>& vec) {
	size = vec.size();
	std::pair<size_t, size_t> p = degMax(size);
	size_t index = p.first + 1;
	size_t exp = p.second;
	ST.resize(index);

	for (size_t i = 0; i < index; ++i) {
		ST[i].resize(size, 0);
	}

	for (size_t i = 0; i < size; ++i) {
		ST[0][i] = vec[i];
	}

	for (size_t i = 0; i < size - 1; ++i) {
		ST[1][i] = min<T, Comparator>(ST[0][i], ST[0][i + 1]);
	}

	size_t current_exp = 4;

	for (size_t i = 2; i < index; ++i) {
		for (size_t j = 0; j < size - current_exp + 1; ++j) {
			ST[i][j] = min<T, Comparator>(ST[i - 1][j], ST[i - 1][j + current_exp / 2]);
		}
		current_exp *= 2;
	}
}

template<typename T, bool Comparator(const T&, const T&)>
struct SparseTable2 {
	size_t size;
	std::vector<std::vector<long long>> ST;
	SparseTable<T, Comparator> sparse_min;

	SparseTable2(std::vector<long long>& vec);
	SparseTable2() : size(0) {};
	T get2Min(size_t l, size_t r) const;
};

template<typename T, bool Comparator(const T&, const T&)>
SparseTable2<T, Comparator>::SparseTable2(std::vector<long long>& vec) {
	size = vec.size();
	sparse_min = SparseTable<T, Comparator>(vec);
	std::pair<int, int> p = degMax(size);
	size_t index = p.first + 1;
	size_t exp = p.second;
	ST.resize(index);

	for (int i = 0; i < index; ++i) {
		ST[i].resize(size, 0);
	}

	for (int i = 0; i < size; ++i) {
		ST[0][i] = vec[i];
	}

	for (int i = 0; i < size - 1; ++i) {
		ST[1][i] = max<T, Comparator>(sparse_min.ST[0][i], sparse_min.ST[0][i + 1]);
	}

	size_t current_exp = 4;

	T cand1, cand2;
	for (int i = 2; i < index; ++i) {
		for (int j = 0; j < size - current_exp + 1; ++j) {
			cand1 = max<T, Comparator>(sparse_min.ST[i - 1][j], sparse_min.ST[i - 1][j + current_exp / 2]);
			cand2 = min<T, Comparator>(ST[i - 1][j], ST[i - 1][j + current_exp / 2]);
			ST[i][j] = min<T, Comparator>(cand1, cand2);
		}
		current_exp *= 2;
	}
}

template<typename T, bool Comparator(const T&, const T&)>
T SparseTable2<T, Comparator>::get2Min(size_t l, size_t r) const{
	std::pair <size_t, size_t> p;
	p = degMax(r - l + 1);
	if (p.first == 0) {
		return max<T, Comparator>(ST[0][l - 1], ST[0][l]);
	}
	T ans;
	T fir1 = sparse_min.getMin(l, (r + l) / 2);
	T fir2 = sparse_min.getMin((r + l) / 2 + 1, r);
	ans = min<T, Comparator>(max<T, Comparator>(fir1, fir2), min<T, Comparator>(ST[p.first][l - 1], ST[p.first][r - p.second]));
	return ans;
}

bool isLess(const long long& a, const long long& b) {
	return a < b;
}

int main() {
	int n, m;
	std::vector<long long> A;
	std::cin >> n >> m;
	long long current;

	for (int i = 0; i < n; ++i) {
		std::cin >> current;
		A.push_back(current);
	}
	SparseTable2<long long, isLess> ST2(A);
	size_t l, r;

	for (int i = 0; i < m; ++i) {
		std::cin >> l >> r;
		std::cout << ST2.get2Min(l, r) << '\n';
	}
	return 0;
}