//Contest 4. Problem B.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/305349/submission/100993195

/*
Реализуйте структуру данных из n элементов a1,a2…an, поддерживающую следующие операции:

присвоить элементу ai значение j;
найти знакочередующуюся сумму на отрезке от l до r включительно (al−al+1+al+2−…±ar).
Входные данные
В первой строке входного файла содержится натуральное число n (1≤n≤105) — длина массива. 
Во второй строке записаны начальные значения элементов (неотрицательные целые числа, не превосходящие 104).

В третьей строке находится натуральное число m (1≤m≤105) — количество операций. 
В последующих m строках записаны операции:

операция первого типа задается тремя числами 0 i j (1≤i≤n, 1≤j≤104).
операция второго типа задается тремя числами 1 l r (1≤l≤r≤n).

Выходные данные
Для каждой операции второго типа выведите на отдельной строке соответствующую знакочередующуюся сумму.
*/


#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>

template <typename T>
struct Fenwick {
	size_t size_ = 0;
	std::vector <T> arr;
	std::vector <T> fenwick_arr;

	Fenwick();
	Fenwick(size_t size);

	void update(size_t pos, const T& value);
	long long sum(size_t right) const;
	long long sum(size_t left, size_t right) const;
};

template <typename T>
Fenwick<T>::Fenwick() {
	size_ = 0;
	arr.resize(0);
	fenwick_arr.resize(0);
}

template <typename T>
Fenwick<T>::Fenwick(size_t size) {
	size_ = size;
	arr.resize(size, 0);
	fenwick_arr.resize(size, 0);
}

template <typename T>
void Fenwick<T>::update(size_t pos, const T& value) {
	long long delta = value - arr[pos];
	arr[pos] = value;
	for (; pos < size_; pos = (pos | (pos + 1))) {
		fenwick_arr[pos] += delta;
	}
}

template <typename T>
long long Fenwick<T>::sum(size_t right) const{
	long long result = 0;
	for (; right + 1 >= 1; right = (right & (right + 1)) - 1) {
		result += fenwick_arr[right];
	}
	return result;
}

template <typename T>
long long Fenwick<T>::sum(size_t left, size_t right) const {
	return sum(right) - sum(left - 1);
}

template <typename T>
struct MyStruct {
private:
	int size_;
	Fenwick<T> odd;
	Fenwick<T> even;

public:
	MyStruct(const MyStruct& other) = delete;
	MyStruct(MyStruct&& other) = delete;

	MyStruct& operator=(const MyStruct& other) = delete;
	MyStruct& operator=(MyStruct&& other) = delete;

	MyStruct(size_t size);
	~MyStruct() = default;

	void update(size_t pos, const T& value);
	T getAlternating(size_t left, size_t right) const;
};

template <typename T>
MyStruct<T>::MyStruct(size_t size) {
	size_ = size;
	odd = Fenwick<T>(size / 2 + size % 2);
	even = Fenwick<T>(size / 2);
}

template <typename T>
void MyStruct<T>::update(size_t pos, const T& value) {
	if (pos % 2 == 0) {
		even.update(pos / 2 - 1, value);
	}
	else {
		odd.update(pos / 2, value);
	}
}

template <typename T>
T MyStruct<T>::getAlternating(size_t left, size_t right) const{
	T positive;
	T negative;
	if (left % 2 == 1) {
		positive = odd.sum(left / 2, right / 2 - 1 + right % 2);
		negative = even.sum(left / 2, right / 2 - 1);
	}
	else {
		negative = odd.sum(left / 2, right / 2 - 1 + right % 2);
		positive = even.sum(left / 2 - 1, right / 2 - 1);
	}
	return positive - negative;;
}

int main() {
	int n;
	int m;
	int left_boarder;
	int right_boarder;
	long long current;
	std::cin >> n;
	MyStruct<long long> S(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> current;
		S.update(i + 1, current);
	}
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		std::cin >> current >> left_boarder >> right_boarder;
		if (current == 0) S.update(left_boarder, right_boarder);
		if (current == 1) std::cout << S.getAlternating(left_boarder, right_boarder) << '\n';
	}

	return 0;
}