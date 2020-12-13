//BigInteger

//Neustroeva Liza 024

//https://contest.yandex.ru/contest/21872/run-report/43485172/

/*
Напишите класс BigInteger для работы с длинными целыми числами. Должны поддерживаться операции:

сложение, вычитание, умножение, деление, остаток по модулю, работающие так же, как и для int; 
составное присваивание с этими операциями. Умножение должно работать за o-малое от n2. 
Деление должно работать не дольше, чем за O(n2).
унарный минус, префиксный и постфиксный инкремент и декремент.
Префиксный инкремент и декремент должны работать за O(1) в среднем.
операторы сравнения == != < > <= >=
вывод в поток и ввод из потока
метод toString(), возвращающий строковое представление числа
конструирование из int (в том числе неявное преобразование, когда это надо)
неявное преобразование в bool, когда это надо (должно работать в условных выражениях)
опционально - литеральный суффикс bi для написания литералов типа BigInteger,
см. справку здесь https://en.cppreference.com/w/cpp/language/user_literal


Используя класс BigInteger, напишите класс Rational для работы с рациональными числами сколь угодно высокой точности. 
Числа Rational должны представляться в виде несократимых обыкновенных дробей, где числитель и знаменатель –
- сколь угодно длинные целые числа. Должны поддерживаться операции:

конструктор из BigInteger, из int
сложение, вычитание, умножение, деление, составное присваивание с этими операциями
унарный минус
операторы сравнения == != < > <= >=
метод toString(), возвращающий строковое представление числа (вида [минус]числитель/знаменатель), где числитель и знаменатель -
- взаимно простые числа; если число на самом деле целое, то знаменатель выводить не надо
метод asDecimal(sizet precision=0), возвращающий строковое представление числа в виде десятичной дроби с precision знаками после запятой
оператор приведения к double

*/



#include <vector>
#include <string>
#include <iostream>

class BigInteger {
private:
	bool is_negative_ = false;
	std::vector <int> digits_;

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

	std::string toString() const;

	friend bool operator < (const BigInteger& n, const BigInteger& m);
	friend std::istream& operator>>(std::istream& in, BigInteger& n);
	friend class Rational;
};

//arithmetic operators

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
		for (size_t i = 0; i < (input.size() - j) / 4; ++i) {
			t = "";
			for (int k = 4; k > 0; --k) {
				t += input[input.size() - k - 4 * i];
			}
			n.digits_.push_back(atoi(t.c_str()));
		}
		t = "";
		for (size_t i = 0; i < (input.size() - j) % 4; ++i) {
			t += input[j + i];
		}
		if (t != "") n.digits_.push_back(atoi(t.c_str()));
	}
	return in;
}

BigInteger::BigInteger(int n) {
	is_negative_ = (n < 0);
	digits_.push_back(abs(n) % 10000);
	if (abs(n) >= 10000) {
		digits_.push_back((abs(n) / 10000) % 10000);
	}
	if (abs(n) >= 100000000) {
		digits_.push_back(abs(n) / 100000000);
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

	for (size_t i = 0; i < max_size; ++i) {
		int first = (i < n.digits_.size() ? n.digits_[i] : 0);
		int second = (i < m.digits_.size() ? m.digits_[i] : 0);

		n.digits_[i] = (is_sum ? first + second + carry : (abs_less ? first - second - carry : second - first - carry));

		if (is_sum && n.digits_[i] >= 10000) {
			n.digits_[i] -= 10000;
			carry = 1;
		}
		else if (n.digits_[i] < 0) {
			n.digits_[i] += 10000;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}

	n.removeLeadingZeroes();
	n.checkZeroSign();
	return n;
}

BigInteger GCD(BigInteger n, BigInteger m)
{
	while (m != 0) {
		n %= m;
		std::swap(n, m);
	}
	return n;
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
	BigInteger result;
	unsigned int carry = 0;

	size_t result_size = digits_.size() + n.digits_.size();

	result.digits_.reserve(result_size + 1);
	result.digits_.clear();

	for (size_t i = 0; i < result_size + 1; ++i) {
		result.digits_.push_back(carry);
		carry = 0;

		for (size_t j = 0; j <= i; ++j) {
			int first = ((j < digits_.size()) ? digits_[j] : 0);
			int second = ((i - j < n.digits_.size()) ? n.digits_[i - j] : 0);

			result.digits_[i] += first * second;

			carry += result.digits_[i] / 10000;
			result.digits_[i] %= 10000;
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
	BigInteger result = 0;
	BigInteger dividend = *this;
	dividend.is_negative_ = false;
	BigInteger divider = n;
	divider.is_negative_ = false;
	BigInteger deg;

	while (dividend >= divider) {
		deg = 1;
		while (dividend >= divider) {
			divider *= 10000;
			deg *= 10000;
		}

		divider.digits_.erase(divider.digits_.begin());
		deg.digits_.erase(deg.digits_.begin());


		while (dividend >= divider) {
			dividend -= divider;
			result += deg;
		}

		divider = n;
		divider.is_negative_ = false;
	}

	result.removeLeadingZeroes();
	result.checkZeroSign();
	bool sign = (is_negative_ != n.is_negative_);
	*this = result;
	is_negative_ = sign;
	checkZeroSign();
	return *this;
}



BigInteger& BigInteger::operator%=(const BigInteger& n) {
	BigInteger quotient = (*this);
	quotient /= n;
	quotient *= n;
	*this -= quotient;
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
	for (size_t i = 0; i < digits_.size(); ++i) {
		int n = digits_[digits_.size() - 1 - i];
		if (i != 0) {
			if (n < 10) s += "000";
			else if (n < 100) s += "00";
			else if (n < 1000) s += "0";
		}
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
	numerator *= r.numerator;
	denominator *= r.denominator;
	Normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& r) {
	numerator *= r.denominator;
	denominator *= r.numerator;
	Normalize();
	return *this;
}

Rational Rational::operator-() const {
	Rational copy = *this;
	if (*this != 0) {
		copy.numerator.is_negative_ = !numerator.is_negative_;
	}
	std::cerr << copy.toString() << "- \n";
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

	if (precision != 0 && frac_part == 0) {             //if it was not integer division although it was divided
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
