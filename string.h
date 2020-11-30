//String

//Neustroeva Liza 024

//https://contest.yandex.ru/contest/21872/run-report/43074639/

/*
В этой задаче запрещено пользоваться какими-либо стандартными контейнерами. 
Выделения памяти нужно делать вручную. Разрешается подключать только <iostream> и <cstring>.

Напишите класс String - упрощенный аналог библиотечного std::string. Необходимо поддержать следующий функционал:

Конструктор от C-style строки (const char*).
Конструктор от двух параметров: число n и символ c - создает строку из n копий символа c.
Конструктор по умолчанию, копирующий конструктор и оператор присваивания.
Оператор ==, позволяющий проверять строки на совпадение.
Квадратные скобки, корректно работающие как для константных, так и для неконстантных строк.
Метод length(), возвращающий размер строки.
Методы push_back(char) и pop_back(). Учетное время работы должно быть O(1).
Методы front() и back(), возвращающие ссылку на начальный и на последний символы строки соответственно.
Оператор +=, позволяющий добавить к строке символ или другую строку. Добавление символа должно работать за амортизированное O(1).
Оператор +, позволяющий складывать строки с символами, символы со строками и строки со строками.
Методы find(substring) и rfind(substring), позволяющие найти самое левое и самое правое вхождение подстроки substring в данную строку. 
Возвращают индекс найденного вхождения. Если вхождений не найдено, нужно вернуть length() (фиктивный индекс).
Метод substr(start, count), возвращающий подстроку начиная с индекса start и состоящую из count символов.
Метод empty(), проверяющий, пуста ли строка. Метод clear(), позволяющий очистить строку.
Операторы вывода в поток « и ввода из потока ».
В вашем файле должна отсутствовать функция main(), а сам файл должен называться string.h. 
В качестве компилятора необходимо указывать Make C++17. 
Ваш код будет вставлен посредством команды #include "string.h" в программу, содержащую тесты; 
вследствие этого код необходимо отправлять в файле со строго соответствующим именем!
*/




#include <iostream>
#include <cstring>

class String {
private:
	size_t size_ = 0;
	size_t capacity_ = 1;
	char* str = nullptr;

	//auxiliary functions
	void swap(String& s);
	void resize(size_t new_capacity);

public:

	//constructors
	String(size_t sz, char c);
	String(char c);
	String(const char* cstr);
	String() = default;

	//the rule of three
	~String();
	String(const String& other);
	String& operator=(String s);

	//operators
	String& operator+=(const String& s);
	String& operator+=(char symbol);
	bool operator == (const String& s) const;
	char& operator[](size_t index);
	char operator[](size_t index) const;

	void push_back(char c);
	void pop_back();
	void clear();

	bool empty() const;

	char& front();
	char front() const;

	char& back();
	char back() const;

	size_t length() const;
	size_t find(const String& substring) const;
	size_t rfind(const String& substring) const;
	String substr(size_t start, size_t count) const;
};

String::String(size_t sz, char symbol) {
	size_ = sz;
	capacity_ = sz + 1;
	str = new char[size_ + 1];
	memset(str, symbol, size_);
}

String::String(char symbol) : String(1, symbol) {}

String::String(const char* cstr) {
	size_ = strlen(cstr);
	capacity_ = strlen(cstr) + 1;
	str = new char[size_ + 1];
	memcpy(str, cstr, size_);
}

String::~String() {
	delete[] str;
}

String::String(const String& other) : String(other.size_, '\0') {
	memcpy(str, other.str, other.size_);
}

void String::swap(String& other) {
	std::swap(size_, other.size_);
	std::swap(str, other.str);
	std::swap(capacity_, other.capacity_);
}

String& String::operator=(String other) {
	swap(other);
	return *this;
}

void String::resize(size_t new_capacity) { //makes the str buffer having new_capacity size
	capacity_ = new_capacity;
	char* new_str = new char[capacity_];
	memcpy(new_str, str, size_);
	delete[] str;
	str = new_str;
}

String& String::operator+=(const String& other) {
	if (size_ + other.size_ >= capacity_) resize((capacity_ + other.size_) * 2);
	memcpy(str + size_, other.str, other.size_);
	size_ += other.size_;
	return *this;
}

void String::push_back(char symbol) {
	if (size_ + 1 == capacity_) resize(capacity_ * 2);
	str[size_] = symbol;
	++size_;
}

String& String::operator+=(char symbol) {
	push_back(symbol);
	return *this;
}

void String::pop_back() {
	--size_;
	if (capacity_ > 0 && size_ < capacity_ / 2) resize(capacity_ / 2);
}

bool String::operator == (const String& other) const {
	if (size_ != other.size_) {
		return false;
	}
	for (size_t i = 0; i < size_; ++i) {
		if (other.str[i] != str[i]) {
			return false;
		}
	}
	return true;
}

size_t String::length() const {
	return size_;
}

bool String::empty() const {
	return size_ == 0;
}

void String::clear() {
	size_ = 0;
	resize(1);
}

char& String::front() {
	return str[0];
}

char String::front() const {
	return str[0];
}

char& String::back() {
	return str[size_ - 1];
}

char String::back() const {
	return str[size_ - 1];
}

char& String::operator[](size_t index) {
	return str[index];
}

char String::operator[](size_t index) const {
	return str[index];
}

size_t String::find(const String& substring) const {
	if (size_ < substring.size_) { // there is no need to search if substr is larger
		return size_;
	}
	for (size_t i = 0; i <= size_ - substring.size_; ++i) { //starting from every element in str
		bool checker = true;
		for (size_t j = 0; j < substring.size_; ++j) {
			if (str[i + j] != substring.str[j]) {
				checker = false;
				break;
			}
		}
		if (checker) { //returns index of first symbol of substring if found
			return i;
		}
	}
	return size_; //returns size if not found
}

size_t String::rfind(const String& substring) const {
	if (size_ < substring.size_) { // there is no need to search if substr is larger
		return size_;
	}
	for (size_t i = size_ - substring.size_; i + 1 > 0; --i) { //starting from every element in reversed
		bool checker = true;
		for (size_t j = 0; j < substring.size_; ++j) {
			if (str[i + j] != substring.str[j]) {
				checker = false;
				break;
			}
		}
		if (checker) {
			return i; //returns index of first symbol of substring if found
		}
	}
	return size_; //returns size if not found
}

String String::substr(size_t start, size_t count) const {
	String s(count, '\0');
	memcpy(s.str, str + start, count);
	return s;
}

String operator+(const String& s1, const String& s2) {
	String copy = s1;
	copy += s2;
	return copy;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
	for (size_t i = 0; i < s.length(); ++i) {
		out << s[i];
	}
	return out;
}

std::istream& operator>>(std::istream& in, String& s) {
	s.clear();
	char c;
	in >> std::noskipws;
	while (in >> c && !isspace(c)) {
		s.push_back(c);
	}
	return in;
}
