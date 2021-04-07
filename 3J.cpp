//Contest 7: Problem J
//Neustroeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/316719/submission/109649028

/*
* International Biology Manufacturer (IBM) обнаружили, что органический материал на Марсе имеет ДНК,
состоящий из 5 символов(a,b,c,d,e), вместо четырех компонентов ДНК на Земле.
Однако в строке не может встречаться ни одна из следующих пар в качестве подстроки: cd, ce, ed и ee.

IBM заинтересовались сколько правильных Марсианских строк ДНК длины n возможно составить?
*/

#include <iostream>
#include <vector>
#include <string>

long long MOD = 999999937;

template <typename T>
struct Matrix {
	size_t rows;
	size_t columns;
	std::vector<std::vector<T>> matrix;
	Matrix(size_t r);
	Matrix(const std::vector<std::vector<T>>& vec);
};

template <typename T>
Matrix<T>::Matrix(size_t r) {
	rows = r;
	columns = r;
	matrix.resize(r, std::vector<T>(r, 0));
	for (size_t i = 0; i < r; ++i) matrix[i][i] = 1;
}

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec) {
	rows = vec.size();
	columns = vec[0].size();
	matrix = vec;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& m, const Matrix<T>& n) {
	size_t t = m.rows;
	Matrix<T> ans = Matrix<T>(m.rows);

	for (size_t i = 0; i < t; ++i) ans.matrix[i][i] = 0;
	for (size_t i = 0; i < t; ++i) {
		for (size_t j = 0; j < t; ++j) {
			for (size_t k = 0; k < t; ++k) {
				ans.matrix[i][j] += (m.matrix[i][k] * n.matrix[k][j]) % MOD;
				ans.matrix[i][j] %= MOD;
			}
		}
	}
	return ans;
}

template <typename T>
Matrix<T> pow(const Matrix<T>& m, size_t s) {
	if (s == 0) return Matrix<T>(m.rows);
	if (s % 2 == 1) {
		return m * pow(m, s - 1);
	}
	Matrix<T> k = pow(m, s / 2);
	return k * k;
}


int main() {
	Matrix<long long> m(2);
	m.matrix[0][0] = 3;
	m.matrix[0][1] = 2;
	m.matrix[1][0] = 2;
	m.matrix[1][1] = 1;
	Matrix<long long> answer(2);
	long long n = 1;
	std::cin >> n;
	while (n != 0) {
		answer = pow(m, n - 1);
		long long a = (answer.matrix[0][0] + answer.matrix[0][1]) % MOD;
		long long b = (answer.matrix[1][0] + answer.matrix[1][1]) % MOD;
		std::cout << (3 * a + 2 * b) % MOD << '\n';
		std::cin >> n;
	}
	return 0;
}