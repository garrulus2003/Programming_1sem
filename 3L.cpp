//Contest 7: Problem L
//Neustroeva Liza 024
//https://codeforces.com/group/R3IJoiTue4/contest/316719/submission/110033789

#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <array>

class BigInteger;

class Rational;

// 
//
//Big Integer and Rational arithmetics
//
//

static int BASE = 1000000000;
static int BASE_LOG = 9;
int mod;

class BigInteger {
private:
	bool is_negative_ = false;
	std::vector<int> digits_;

private:
	void removeLeadingZeroes();
	void checkZeroSign();
	bool absLess(const BigInteger& n, const BigInteger& m) const;
	BigInteger& sumAndDif(BigInteger& n, const BigInteger& m, bool sign, bool is_sum);

public:

	//constructors
	BigInteger(int n);
	BigInteger() = default;

	//the three rule
	BigInteger(const BigInteger& other) = default;
	BigInteger& operator=(const BigInteger& other) = default;
	~BigInteger() = default;

	explicit operator bool();

	BigInteger& operator++();
	BigInteger operator++(int);
	BigInteger& operator--();
	BigInteger operator--(int);

	BigInteger operator-() const;

	BigInteger& operator+=(const BigInteger& n);
	BigInteger& operator-=(const BigInteger& n);
	BigInteger& operator*=(const BigInteger& n);
	BigInteger& operator/=(const BigInteger& n);
	BigInteger& operator%=(const BigInteger& n);

	bool isEven() const;
	BigInteger& halved();
	BigInteger& twice();

	std::string toString() const;

	friend bool operator < (const BigInteger& n, const BigInteger& m);
	friend std::istream& operator>>(std::istream& in, BigInteger& n);
	friend class Rational;
	friend BigInteger GCD(BigInteger n, BigInteger m);
};

//arithmetic operators

bool BigInteger::isEven() const {
	return (digits_[0] % 2 == 0);
}

BigInteger& BigInteger::twice() {
	size_t size = digits_.size();
	int carry = 0;
	digits_.push_back(0);
	for (size_t i = 0; i < size; ++i) {
		digits_[i] *= 2;
		digits_[i] += carry;
		if (digits_[i] >= BASE) {
			digits_[i] -= BASE;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}
	digits_[size] += carry;
	removeLeadingZeroes();
	checkZeroSign();
	return *this;
}

BigInteger& BigInteger::halved() {
	size_t size = digits_.size();
	int carry = 0;
	for (size_t i = size - 1; i + 1 > 0; --i) {
		digits_[i] += carry;
		if (digits_[i] % 2 == 1) {
			carry = BASE;
		}
		else {
			carry = 0;
		}
		digits_[i] /= 2;
	}
	removeLeadingZeroes();
	checkZeroSign();
	return *this;
}

BigInteger operator+(const BigInteger& n, const BigInteger& m) {
	BigInteger copy = n;
	copy += m;
	return copy;
}

BigInteger operator-(const BigInteger& n, const BigInteger& m) {
	BigInteger copy = n;
	copy -= m;
	return copy;
}

BigInteger operator*(const BigInteger& n, const BigInteger& m) {
	BigInteger copy = n;
	copy *= m;
	return copy;
}

BigInteger operator/(const BigInteger& n, const BigInteger& m) {
	BigInteger copy = n;
	copy /= m;
	return copy;
}

BigInteger operator%(const BigInteger& n, const BigInteger& m) {
	BigInteger copy = n;
	copy %= m;
	return copy;
}


//comparation operators
bool operator < (const BigInteger& n, const BigInteger& m) {
	if (n.is_negative_ != m.is_negative_) {
		return n.is_negative_;
	}

	if (n.digits_.size() != m.digits_.size()) {
		return (n.digits_.size() < m.digits_.size()) ^ n.is_negative_;
	}

	size_t size_ = n.digits_.size();
	for (size_t i = 0; i < size_; ++i) {
		if (n.digits_[size_ - i - 1] != m.digits_[size_ - i - 1]) {
			return (n.digits_[size_ - i - 1] < m.digits_[size_ - i - 1]) ^ n.is_negative_;
		}
	}

	return false;
}

bool operator > (const BigInteger& n, const BigInteger& m) {
	return m < n;
}

bool operator == (const BigInteger& n, const BigInteger& m) {
	return !(n < m || m < n);
}

bool operator != (const BigInteger& n, const BigInteger& m) {
	return !(n == m);
}

bool operator <= (const BigInteger& n, const BigInteger& m) {
	return !(n > m);
}

bool operator >= (const BigInteger& n, const BigInteger& m) {
	return !(n < m);
}


//input and output operators
std::ostream& operator<<(std::ostream& out, const BigInteger& n) {
	std::string s = n.toString();
	out << s;
	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& n) {
	std::string input;
	in >> input;
	n.digits_.clear();
	size_t j = 0;
	while (input[j] == '-' || input[j] == '0') ++j;
	if (j == input.size()) {
		n.is_negative_ = false;
		n.digits_.push_back(0);
	}

	else {
		n.is_negative_ = (input[0] == '-');
		std::string t;
		for (size_t i = 0; i < (input.size() - j) / BASE_LOG; ++i) {
			t = "";
			for (int k = BASE_LOG; k > 0; --k) {
				t += input[input.size() - k - BASE_LOG * i];
			}
			n.digits_.push_back(atoi(t.c_str()));
		}
		t = "";
		for (size_t i = 0; i < (input.size() - j) % BASE_LOG; ++i) {
			t += input[j + i];
		}
		if (t != "") n.digits_.push_back(atoi(t.c_str()));
	}
	return in;
}

BigInteger::BigInteger(int n) {
	is_negative_ = (n < 0);
	if (n == 0) {
		digits_.push_back(0);
		return;
	}
	n = abs(n);
	while (n > 0) {
		digits_.push_back(n % BASE);
		n /= BASE;
	}
};


BigInteger::operator bool() {
	return *this != 0;
}

BigInteger& BigInteger::operator++() {
	*this += 1;
	return *this;
}

BigInteger BigInteger::operator++(int) {
	BigInteger copy = *this;
	*this += 1;
	return copy;
}

BigInteger& BigInteger::operator--() {
	*this -= 1;
	return *this;
}

BigInteger BigInteger::operator--(int) {
	BigInteger copy = *this;
	*this -= 1;
	return copy;
}

BigInteger BigInteger::operator-() const {
	BigInteger copy = *this;
	if (*this != 0) {
		copy.is_negative_ = !is_negative_;
	}
	return copy;
}


void BigInteger::removeLeadingZeroes() {
	while (digits_.size() > 1 && digits_.back() == 0) digits_.pop_back();
}

void BigInteger::checkZeroSign() {
	if (digits_.size() == 1 && digits_[0] == 0) {
		is_negative_ = false;
	}
}

bool BigInteger::absLess(const BigInteger& n, const BigInteger& m) const {
	if (n.digits_.size() != m.digits_.size()) {
		return n.digits_.size() < m.digits_.size();
	}
	else {
		size_t size_ = n.digits_.size();
		for (size_t i = 0; i < size_; ++i) {
			if (n.digits_[size_ - i - 1] != m.digits_[size_ - i - 1]) {
				return n.digits_[size_ - i - 1] < m.digits_[size_ - i - 1];
			}
		}
		return false;
	}

}

BigInteger& BigInteger::sumAndDif(BigInteger& n, const BigInteger& m, bool sign, bool is_sum) {
	bool abs_less = absLess(m, n);

	size_t max_size = m.digits_.size() > n.digits_.size() ? m.digits_.size() : n.digits_.size();

	n.is_negative_ = sign;

	while (n.digits_.size() < max_size + 1) n.digits_.push_back(0);

	int carry = 0;

	if (is_sum) {
		for (size_t i = 0; i < max_size; ++i) {
			int first = (i < n.digits_.size() ? n.digits_[i] : 0);
			int second = (i < m.digits_.size() ? m.digits_[i] : 0);

			n.digits_[i] = first + second + carry;

			if (is_sum && n.digits_[i] >= BASE) {
				n.digits_[i] -= BASE;
				carry = 1;
			}
			else {
				carry = 0;
			}
		}
	}
	else {
		if (abs_less) {
			for (size_t i = 0; i < max_size; ++i) {
				int first = (i < n.digits_.size() ? n.digits_[i] : 0);
				int second = (i < m.digits_.size() ? m.digits_[i] : 0);

				n.digits_[i] = first - second - carry;

				if (n.digits_[i] < 0) {
					n.digits_[i] += BASE;
					carry = 1;
				}
				else {
					carry = 0;
				}
			}
		}
		else {
			for (size_t i = 0; i < max_size; ++i) {
				int first = (i < n.digits_.size() ? n.digits_[i] : 0);
				int second = (i < m.digits_.size() ? m.digits_[i] : 0);

				n.digits_[i] = second - first - carry;

				if (n.digits_[i] < 0) {
					n.digits_[i] += BASE;
					carry = 1;
				}
				else {
					carry = 0;
				}
			}
		}
	}
	n.removeLeadingZeroes();
	n.checkZeroSign();
	return n;
}


BigInteger GCD(BigInteger n, BigInteger m)
{
	BigInteger gcd = 1;
	n.is_negative_ = false;
	m.is_negative_ = false;
	bool bn = false;
	bool bm = false;
	while (n) {
		bn = n.isEven();
		bm = m.isEven();
		if (bn && bm) {
			gcd.twice();
		}
		if (bn) n.halved();
		if (bm) m.halved();
		if (m >= n) std::swap(m, n);
		n -= m;
	}
	return gcd * m;
}

BigInteger& BigInteger::operator+=(const BigInteger& n) {
	if (is_negative_ == n.is_negative_) {
		return BigInteger::sumAndDif(*this, n, is_negative_, true);
	}
	if (!absLess(*this, n)) {
		return BigInteger::sumAndDif(*this, n, is_negative_, false);
	}
	else {
		return BigInteger::sumAndDif(*this, n, n.is_negative_, false);
	}
}

BigInteger& BigInteger::operator-=(const BigInteger& n) {
	if (is_negative_ != n.is_negative_) {
		return BigInteger::sumAndDif(*this, n, is_negative_, true);
	}

	if (!absLess(*this, n)) {
		return BigInteger::sumAndDif(*this, n, is_negative_, false);
	}
	else {
		return BigInteger::sumAndDif(*this, n, (!n.is_negative_), false);
	}
}


BigInteger& BigInteger::operator*=(const BigInteger& n) {
	if (*this == 0 || n == 0) {
		*this = 0;
		return *this;
	}
	BigInteger result;
	size_t result_size = digits_.size() + n.digits_.size();

	result.digits_.resize(result_size);

	for (size_t i = 0; i < result_size; ++i) {
		for (size_t j = 0; j < result_size; ++j) {
			long long fir = ((j < digits_.size()) ? digits_[j] : 0);
			long long sec = ((i - j < n.digits_.size()) ? n.digits_[i - j] : 0);
			long long ans = result.digits_[i] + fir * sec;
			if (ans >= BASE) {
				result.digits_[i + 1] += ans / BASE;
				ans %= BASE;
			}
			result.digits_[i] = ans;
		}
	}
	bool sign = (is_negative_ != n.is_negative_);
	*this = result;
	removeLeadingZeroes();
	is_negative_ = sign;
	checkZeroSign();
	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& n) {

	if (*this == n) {
		*this = 1;
		return *this;
	}

	bool sign = (is_negative_ != n.is_negative_);

	if (digits_.size() == 1) {
		if (n.digits_.size() > 1) {
			*this = 0;
			return *this;
		}
		else {
			digits_[0] /= n.digits_[0];
			checkZeroSign();
			return *this;
		}
	}

	BigInteger divider = n;
	divider.is_negative_ = false;
	BigInteger answer, curr_dividend;
	answer.digits_.resize(digits_.size());
	curr_dividend = 0;
	for (size_t i = digits_.size() - 1; i + 1 >= 1; --i) {
		curr_dividend.digits_.push_back(digits_[i]);
		for (size_t j = curr_dividend.digits_.size() - 1; j + 1 > 1; --j) {
			std::swap(curr_dividend.digits_[j], curr_dividend.digits_[j - 1]);
		}
		curr_dividend.removeLeadingZeroes();
		BigInteger current_multiplication;
		size_t current_digit = 0;
		size_t l = 0;
		size_t r = BASE;
		while (l <= r) {
			size_t m = (l + r) / 2;
			BigInteger temporary = divider * m;
			if (temporary <= curr_dividend) {
				current_digit = m;
				current_multiplication = temporary;
				l = m + 1;
			}
			else {
				r = m - 1;
			}
		}
		answer.digits_[i] = current_digit;
		curr_dividend -= current_multiplication;
	}

	*this = answer;
	removeLeadingZeroes();
	is_negative_ = sign;
	checkZeroSign();
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& n) {
	if (*this == n) {
		*this = 0;
		return *this;
	}

	bool sign = is_negative_;
	is_negative_ = false;
	BigInteger result = 0;
	BigInteger divider = n;
	divider.is_negative_ = false;

	BigInteger deg;
	BigInteger current = n;
	current.is_negative_ = false;

	if (*this < divider) {
		is_negative_ = sign;
		return *this;
	}

	while (*this >= divider) {
		divider *= 10;
		while (*this > divider) {
			divider *= 10;
			current *= 10;
		}
		while (divider > *this) {
			divider -= current;
		}
		*this -= divider;

		divider = n;
		current = n;
		divider.is_negative_ = false;
		current.is_negative_ = false;

	}

	//result.removeLeadingZeroes();
	//result.checkZeroSign();
	//*this = result;
	is_negative_ = sign;
	checkZeroSign();
	return *this;
}


std::string BigInteger::toString() const {
	std::string s = "";
	if (digits_.size() == 1 && digits_[0] == 0) {
		return "0";
	}
	if (is_negative_) {
		s += "-";
	}
	s += std::to_string(digits_[digits_.size() - 1]);
	for (size_t i = 1; i < digits_.size(); ++i) {
		int n = digits_[digits_.size() - 1 - i];
		if (n < 10) s += "00000000";
		else if (n < 100) s += "0000000";
		else if (n < 1000) s += "000000";
		else if (n < 10000) s += "00000";
		else if (n < 100000) s += "0000";
		else if (n < 1000000) s += "000";
		else if (n < 10000000) s += "00";
		else if (n < 100000000) s += "0";
		s += std::to_string(n);
	}
	return s;
}



//
//
//
//Rational
//
//
//


class Rational {
private:
	BigInteger numerator = 0;
	BigInteger denominator = 1;

private:
	void Normalize();

public:
	//constructors
	Rational() = default;
	Rational(int n);
	Rational(const BigInteger& n);
	Rational(const BigInteger& n, const BigInteger& m);

	//rule of three
	Rational(const Rational& other) = default;
	Rational& operator=(const Rational& other) = default;
	~Rational() = default;

	explicit operator double();

	//arithmetic operators
	Rational& operator+=(const Rational& r);
	Rational& operator-=(const Rational& r);
	Rational& operator*=(const Rational& r);
	Rational& operator/=(const Rational& r);
	Rational operator-() const;

	std::string toString() const;
	std::string asDecimal(size_t precision = 0) const;

	friend std::istream& operator>>(std::istream& in, Rational& n);
	friend bool operator < (const Rational& n, const Rational& m);
};

bool operator < (const Rational& n, const Rational& m) {
	return (n.numerator * m.denominator < m.numerator* n.denominator);
}

bool operator > (const Rational& n, const Rational& m) {
	return m < n;
}

bool operator == (const Rational& n, const Rational& m) {
	return !(n < m || m < n);
}

bool operator != (const Rational& n, const Rational& m) {
	return !(n == m);
}

bool operator <= (const Rational& n, const Rational& m) {
	return !(n > m);
}

bool operator >= (const Rational& n, const Rational& m) {
	return !(n < m);
}

Rational operator+(const Rational& n, const Rational& m) {
	Rational copy = n;
	copy += m;
	return copy;
}

Rational operator-(const Rational& n, const Rational& m) {
	Rational copy = n;
	copy -= m;
	return copy;
}

Rational operator*(const Rational& n, const Rational& m) {
	Rational copy = n;
	copy *= m;
	return copy;
}

Rational operator/(const Rational& n, const Rational& m) {
	Rational copy = n;
	copy /= m;
	return copy;
}

Rational::Rational(int n) {
	numerator = n;
	denominator = 1;
}

Rational::Rational(const BigInteger& n) {
	numerator = n;
	denominator = 1;
}

Rational::Rational(const BigInteger& n, const BigInteger& m) {
	numerator = n;
	denominator = m;
	Normalize();
}

void Rational::Normalize() {
	//std::cerr << numerator << " " << denominator << " ";
	if (numerator == 0) {
		numerator.is_negative_ = false;
		denominator = 1;
	}
	else {
		BigInteger gcd = GCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
		numerator.is_negative_ = (numerator.is_negative_ != denominator.is_negative_);
		denominator.is_negative_ = false;
	}
	//std::cerr << numerator << " " << denominator << '\n';
}

Rational& Rational::operator+=(const Rational& r) {
	numerator = numerator * r.denominator + denominator * r.numerator;
	denominator *= r.denominator;
	Normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& r) {
	numerator = numerator * r.denominator - denominator * r.numerator;
	denominator *= r.denominator;
	Normalize();
	return *this;
}

Rational& Rational::operator*=(const Rational& r) {
	if (*this == 0 || r == 0) {
		*this = 0;
		return *this;
	}
	BigInteger gcd1 = GCD(numerator, r.denominator);
	BigInteger gcd2 = GCD(denominator, r.numerator);
	BigInteger a, b;
	numerator /= gcd1;
	denominator /= gcd2;
	a = r.numerator / gcd2;
	b = r.denominator / gcd1;
	numerator *= a;
	denominator *= b;
	numerator.is_negative_ = (numerator.is_negative_ != denominator.is_negative_);
	denominator.is_negative_ = false;
	return *this;
}

Rational& Rational::operator/=(const Rational& r) {
	if (*this == 0) return *this;
	BigInteger gcd1 = GCD(numerator, r.numerator);
	BigInteger gcd2 = GCD(denominator, r.denominator);
	BigInteger a, b;
	numerator /= gcd1;
	denominator /= gcd2;
	a = r.numerator / gcd1;
	b = r.denominator / gcd2;
	numerator *= b;
	denominator *= a;
	numerator.is_negative_ = (numerator.is_negative_ != denominator.is_negative_);
	denominator.is_negative_ = false;
	return *this;
}

Rational Rational::operator-() const {
	Rational copy = *this;
	if (*this != 0) {
		copy.numerator.is_negative_ = !numerator.is_negative_;
	}
	return copy;
}

std::string Rational::toString() const {
	std::string s;
	if (denominator == 1) {
		return numerator.toString();
	}
	else {
		return numerator.toString() + "/" + denominator.toString();
	}
}



std::string Rational::asDecimal(size_t precision) const {
	std::string answer;
	if (numerator < 0) {
		answer += "-";
	}
	BigInteger int_part = numerator / denominator;
	BigInteger frac_part = numerator % denominator;
	int_part.is_negative_ = false;
	frac_part.is_negative_ = false;
	answer += int_part.toString();

	if (precision != 0 && frac_part == 0) {
		answer += ".";
		for (size_t i = 0; i < precision; ++i) {
			answer += "0";
		}
	}

	if (precision != 0 && frac_part != 0) {
		answer += ".";
		size_t j = 0;
		frac_part *= 10;

		while (frac_part < denominator) {
			answer += "0";
			frac_part *= 10;
			++j;
		}
		for (size_t i = j; i < precision - 1; ++i) {
			frac_part *= 10;
		}
		frac_part /= denominator;
		answer += frac_part.toString();
	}
	return answer;
}


Rational::operator double() {
	return std::stod(asDecimal(100));
}

std::istream& operator>>(std::istream& in, Rational& n) {
	BigInteger num;
	in >> num;
	n.numerator = num;
	n.denominator = 1;
	return in;
}

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
Matrix<T> pow(const Matrix<T>& m, BigInteger s) {
	if (s == 0) return Matrix<T>(m.rows);
	if (s % 2 == 1) {
		return m * pow(m, s - 1);
	}
	Matrix<T> k = pow(m, s / 2);
	return k * k;
}

bool bit(int mask, int pos) {
	return (mask / (1 << pos)) % 2;
}

bool is_compatible(int mask, int other_mask, int length) {
	bool compatible = true;
	for (int k = 1; k < length; ++k) {
		bool similar_first = bit(mask, k - 1) == bit(other_mask, k - 1);
		bool similar_second = bit(mask, k) == bit(other_mask, k);
		bool similar_column = bit(other_mask, k - 1) == bit(mask, k) % 2;
		if (similar_first && similar_second && similar_column) {
			compatible = false;
		}
	}
	return compatible;
}

int main() {
	BigInteger n;
	int m;
	std::cin >> n >> m >> mod;
	std::vector<std::vector<int>> possible(1 << m, std::vector<int>(1 << m, 0));
	std::vector<int> possibilities(1 << m, 0);

	//std::cout << n << '\n';
	for (int i = 0; i < 1 << m; ++i) {
		for (int j = 0; j < 1 << m; ++j) {
			possible[i][j] = is_compatible(i, j, m);
		}
	}

	Matrix<int> matr(possible);
	matr = pow(matr, n - 1);

	int ans = 0;
	for (int i = 0; i < 1 << m; ++i) {
		for (int j = 0; j < 1 << m; ++j) {
			ans += matr.matrix[i][j];
			ans %= mod;
		}
	}
	std::cout << ans;

	return 0;
}