/* https://codeforces.com/group/R3IJoiTue4/contest/295360/submission/94524070 */

/*F. Инверсии
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводinverse.in
выводinverse.out
Напишите программу, которая для заданного массива A=⟨a1,a2,…,an⟩ находит количество пар (i,j) таких, что i<j и ai>aj. 
Обратите внимание на то, что ответ может не влезать в int.

Входные данные
Первая строка входного файла содержит натуральное число n (1⩽n⩽100000) — количество элементов массива.
Вторая строка содержит n попарно различных элементов массива A — целых неотрицательных чисел, не превосходящих 109.

Выходные данные
В выходной файл выведите одно число — ответ на задачу.*/

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

long long Merge(std::vector <int>& v, std::vector <int>& util, int begin1, int end1, int begin2, int end2); 
// merges two parts of the vector v : (begin1; end1) and (begin2; end2) and counts crosspartial inverses
long long MergeSort(std::vector <int>& v, std::vector <int>& util, int begin, int end);
// sorts the part of v (begin; end) and coubts # of inverses

int main() {
	std::ifstream fin("inverse.in"); // input file
	std::ofstream fout("inverse.out"); // output file
	int n; //length of the vector
	fin >> n;
	std::vector <int> v(n); // a vector given
	std::vector <int> util(2 * n); // memory space do to everything
	for (int i = 0; i < n; ++i) { //reading the vextor given
		fin >> v[i];
	}

	fout << MergeSort(v, util, 0, n) << "\n";
	return 0;
}

long long MergeSort(std::vector <int>& v, std::vector <int>& util, int begin, int end) {
	int len = end - begin;
	if (len <= 1) { // the vector is already sorted
		return 0;
	}
	int mid = begin + len / 2;
	long long inv = MergeSort(v, util, begin, mid) + MergeSort(v, util, mid, end); //divide in 2 parts and MergeSort them
	inv += Merge(v, util, begin, mid, mid, end); //add crosspartial inverses
	return inv;
}

long long Merge(std::vector <int>& v, std::vector <int>& util, int begin1, int end1, int begin2, int end2) {
	int len1 = end1 - begin1;
	int len2 = end2 - begin2;
	int i = 0;
	int j = 0;
	long long inv = 0;
	while (i < len1 && j < len2) { //merges vectors while both of them did not finish
		if (v[i + begin1] < v[j + begin2]) {
			util[i + j] = v[i + begin1];
			++i;
		} else {
			util[i + j] = v[j + begin2];
			++j;
			inv += len1 - i; //inverse counter
		}
	}
	while (i < len1) { //add elements of first vector that were not used
		util[i + len2] = v[i + begin1];
		++i;
	}
	while (j < len2) { //add elements of second vector that were not used
		util[j + len1] = v[j + begin2];
		++j;
	}
	for (int i = 0; i < len1; ++i) { //writes the merged vector to the place it was taken from
		v[i + begin1] = util[i];
	}
	for (int i = len1; i < len1 + len2; ++i) {
		v[i - len1 + begin2] = util[i];
	}
	return inv;
}
