//Contest 4. Problem E. Online solution

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/305349/submission/100997160

/*
* Нужно отвечать на запросы вида
• + x – добавить в мультимножество число x.
• ? x – посчитать сумму чисел не больших x.
Формат входных данных
В первой строке содержится число запросов 1 6 q 6 105
.
Далее каждая строка содержит один запрос.
Все числа x целые от 0 до 109 − 1.
Формат выходных данных
Ответы на все запросы вида “? x”.
*/


#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>


template <typename T>
struct SegTree {
private:
	size_t size;
	size_t degree;
	std::vector<T> values;

public:
	SegTree() : SegTree(0) {};
	SegTree(size_t Size);

	T getSum(size_t l, size_t r) const;
	void update(size_t pos, const T& value);
};

template <typename T>
SegTree<T>::SegTree(size_t Size) {
	size = Size;
	degree = 1;
	while (degree < Size) degree *= 2;
	values.resize(2 * degree);
}

template <typename T>
T SegTree<T>::getSum(size_t l, size_t r) const{
	T sum = 0;
	l += degree - 1;
	r += degree - 1;
	while (l <= r) {
		if (l % 2 != 0) sum += values[l];
		if (r % 2 == 0) sum += values[r];
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	}
	return sum;
}

template <typename T>
void SegTree<T>::update(size_t pos, const T& value) {
	pos += degree - 1;
	values[pos] = value;
	while (pos > 1) {
		pos /= 2;
		values[pos] = values[2 * pos] + values[2 * pos + 1];
	}
}



struct MyStruct {
private:
	size_t base_;
	std::vector <std::map <long long, long long>> array;
	SegTree<long long> seg_tree;

public:
	MyStruct(size_t base);
	void update(long long value);
	long long getSum(size_t r) const;
};

MyStruct::MyStruct(size_t base) {
	base_ = base;
	array.resize(base_ * base_);
	seg_tree = SegTree<long long>(base_ * base_);
}

void MyStruct::update(long long value) {
	array[value / base_][value] += value;
	long long current = seg_tree.getSum(value / base_ + 1, value / base_ + 1);
	seg_tree.update(value / base_ + 1, current + value);
}

long long MyStruct::getSum(size_t r) const{
	long long sum = 0;
	sum += seg_tree.getSum(1, r / base_);
	for (auto& c : array[r / base_]) {
		if (c.first <= r) {
			sum += c.second;
		}
	}
	return sum;
}

int main() {
	int q;
	char command;
	int x;
	MyStruct S(1000);

	std::cin >> q;

	for (int i = 0; i < q; ++i) {
		std::cin >> command >> x;
		if (command == '?') {
			std::cout << S.getSum(x) << '\n';
		}
		else { //command = '+'
			S.update(x);
		}
	}
}