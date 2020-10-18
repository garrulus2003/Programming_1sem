//Problem F. Contest 1.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/295360/problem/F

/*
Напишите программу, которая для заданного массива A=⟨a1,a2,…,an⟩ находит количество пар (i,j) таких, 
что i<j и ai>aj. Обратите внимание на то, что ответ может не влезать в int.

Входные данные
Первая строка входного файла содержит натуральное число n (1⩽n⩽100000) — количество элементов массива. 
Вторая строка содержит n попарно различных элементов массива A — целых неотрицательных чисел, не превосходящих 109.

Выходные данные
В выходной файл выведите одно число — ответ на задачу.
*/

#include <vector>
#include <utility>
#include <fstream>

template <typename T>
long long Merge(std::vector <T>& v, int begin1, int end1, int begin2, int end2, bool comparator(T, T));

template <typename T>
long long MergeSort(std::vector <T>& v, int begin, int end, bool comparator(T, T));

bool isLess(int a, int b) { //standart less comparator 
	return a < b;
}

int main() {
	std::ifstream fin("inverse.in");
	std::ofstream fout("inverse.out");

	int n; //vector length
	int current;
	fin >> n; //reading vector length from file
	std::vector <int> v; //creating a vector to be sorted

	for (int i = 0; i < n; ++i) {  //reading all values from file
		fin >> current;
		v.push_back(current);
	}

	fout << MergeSort (v, 0, n, isLess) << "\n";  //sorting and counting the quantity of inverses
	return 0;
}

template <typename T>

long long MergeSort(std::vector <T>& v, int begin, int end, bool comparator(T, T)) {
	int len = end - begin;
	if (len <= 1) { //if the vector is too short it is already sorted
		return 0;
	}
	int mid = begin + len / 2; //finds the middle of the vector
	long long inv = MergeSort(v, begin, mid, comparator) + MergeSort(v, mid, end, comparator);//sorts 2 halfs and sums inverses
	inv += Merge(v, begin, mid, mid, end, comparator); //merges the halfs and counts crosspartial inverses
	return inv;
}

template <typename T>

long long Merge(std::vector <T>& v, int begin1, int end1, int begin2, int end2, bool comparator(T, T)) {
	int len1 = end1 - begin1;
	int len2 = end2 - begin2;
	std::vector <T> util(len1 + len2); //creates an auxiliary vector
	int i = 0; //iterator for first part
	int j = 0; //iterator for secnd part
	long long inv = 0;
	while (i < len1 && j < len2) { //while in both parts not all the numbers have been checked
		if (comparator(v[i + begin1], v[j + begin2])) {
			util[i + j] = v[i + begin1];
			++i;
		}
		else {
			util[i + j] = v[j + begin2];
			++j;
			inv += (long long) len1 - i;
		}
	}

	while (i < len1) { //if first half have not finished whereas the second did
		util[i + len2] = v[i + begin1];
		++i;
	}

	while (j < len2) { //if second half have not finished whereas the first did
		util[j + len1] = v[j + begin2];
		++j;
	}


	// returning values from the auxiliary vector to those we were sorting

	for (int i = 0; i < len1; ++i) {
		v[i + begin1] = util[i];
	}

	for (int i = len1; i < len1 + len2; ++i) {
		v[i - len1 + begin2] = util[i];
	}

	return inv;
}