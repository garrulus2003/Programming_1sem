//Problem H. Contest 2.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/296750/submission/95920328

/*
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 10^6. 
Отсортировать массив методом поразрядной сортировки LSD по байтам.

Входные данные
В первой строке вводится количество чисел в массиве N. На следующей строке через пробел вводятся N неотрицательных чисел.

Выходные данные
Выведите этот массив, отсортированный в порядке возрастания, в одну строчку через пробел.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::vector <long long> vec;
	int n; //quantity of numbers to be sorted
	long long digit; //counter for the number of byte which is being sorted now
	std::cin >> n;


	for (int i = 0; i < n; ++i) {
		long long x;
		std::cin >> x;
		vec.push_back(x);
	}


	for (int j = 0; j < 8; ++j) { //in a cycle for each byte
		if (j == 0) {
			digit = 1; //digit eguals 256^(current_byte_number - 1)
		}
		else {
			digit *= 256;
		}

		std::vector <long long> value_counter; //creating a value_counter vector of 256 zeros
		for (int i = 0; i < 256; ++i) {
			value_counter.push_back(0);
		}

		for (int i = 0; i < n; ++i) { //counting how many bytes of each value are there between j-bytes of all numbers
			++value_counter[(vec[i] / digit) % 256];
		}

		std::vector <long long> prefix_sum(256);
		prefix_sum[0] = 0;
		for (int i = 1; i < 256; ++i) { //creating a vector of prefix sums 
			prefix_sum[i] = value_counter[i - 1] + prefix_sum[i - 1]; //elements with j-byte = i take places with numbers from prefix_sum[i]
		}

		std::vector <long long> placed(256); // creating a vector of 256 zeros. Further placed[i] will mean 
											 //the number of correctly placed numbers with j-byte = i
		for (int i = 1; i < 256; ++i) {
			placed[i] = 0;
		}

		std::vector <long long> new_vec(n); //creating a vector where we are going to place values in correct order

		for (int i = 0; i < n; ++i) {
			//placing vec[i] to a correct position in respect to j-byte
			new_vec[prefix_sum[(vec[i] / digit) % 256] + placed[(vec[i] / digit) % 256]] = vec[i]; 
			++placed[(vec[i] / digit) % 256]; //+1 to number of correctle placed elements with j-byte same as of just placed
		}

		for (int i = 0; i < n; ++i) { //replacing element from new_vec to vec, correct order remains
			vec[i] = new_vec[i];
		}

	}

	for (int i = 0; i < n; ++i) { //printing a sorted vector
		std::cout << vec[i] << " ";
	}
}