﻿//Problem C. Contest 2. 

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/296750/submission/95918060

/*
Даны неотрицательные целые числа N, K и массив целых чисел из диапазона [0,109] размера N. 
Требуется найти K-ю порядковую статистику, т.е. напечатать число, 
которое бы стояло на позиции с индексом K ∈[0,N−1] в отсортированном массиве.

Напишите нерекурсивный алгоритм. Требования к дополнительной памяти: O(1). Требуемое среднее время работы: O(N).

Входные данные
В первой строке записаны N и K.

В N последующих строках записаны числа последовательности.

Выходные данные
K-я порядковая статистика.
*/


#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>

T kth(std::vector<T> vec, int n, int k, bool comparator(T, T)) {

	//the algorithm will step by step reduce the area where kth might be

	//firstly the area ia all the vector
	int left = 0;
	int right = n;

	while (true) { //quasiendless cycle
		if (right - left <= 2) { //kth is found if current area consist of 1 or 2 elements
			if (right - left == 2 && comparator(vec[right - 1], vec[left])) { //if 3 elements, compare them
				std::swap(vec[left], vec[right - 1]);
			}
			return vec[k]; //kth found!
		}

		int pivot = (left + right) / 2; //let the middle of the area be pivot

		std::swap(vec[right - 1], vec[pivot]);  //putting pivot to the most right position of the area

		int i = left; 
		int j = left;


		while (j < right) { //partition procedure in current area with respect to pivot
			if (comparator(vec[right - 1], vec[j])) {
				++j;
			}
			else {
				std::swap(vec[i], vec[j]);
				++i;
				++j;
			}
		}

		//i-1 is current pivot index

		if (i - 1 == k) {
			return vec[k];
		}
		if (i - 1 < k) {
			left = i; //changing left border
		}
		if (i - 1 > k) {
			right = i - 1; //changing right border
		}
	}
}

bool isLess(int a, int b) { //standart less comparator
	return (a < b);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n; //quantity of numbers given
	int k; //number of statistics
	std::vector <int> vec;
	std::cin >> n >> k;
	for (int i = 0; i < n; ++i) { //reading all numbers
		int current;
		std::cin >> current;
		vec.push_back(current);
	}

	std::cout << kth(vec, n, k, isLess); //prints kth
}