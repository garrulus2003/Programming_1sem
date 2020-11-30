//Problem C. Contest 3. 

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/301990/submission/98401154

/*
На вступительном контесте в пилотную группу по программированию Вашему другу предложили реализовать структуру данных 
для хранения множеств чисел. Так как он специализируется на истории литературы, данную структуру придётся реализовать Вам.

Структура должна хранить m+1 множеств чисел от 0 до n, пронумерованных от 0 до m включительно, 
при этом одно число может принадлежать сразу нескольким множествам. Изначально все множества пустые.

Вы должны реализовать следующие операции на этой структуре:

ADD e s
Добавить в множество №s (0≤s≤m) число e (0≤e≤n).

DELETE e s
Удалить из множества №s (0≤s≤m) число e (0≤e≤n). Гарантируется, что до этого число e было помещено в множество

CLEAR s
Очистить множество №s (0≤s≤m).

LISTSET s
Показать содержимое множества №s (0≤s≤m) в возрастающем порядке, либо −1, если множество пусто.

LISTSETSOF e
Показать множества, в которых лежит число e (0≤e≤n), либо −1, если этого числа нет ни в одном множестве.

Входные данные
Сначала вводятся числа N (1≤N≤9223372036854775807), M (1≤M≤100000) и K (0≤K≤100000)  — максимальное число, 
номер максимального множества и количество запросов к структуре данных. Далее следуют K строк указанного формата запросов.

Выходные данные
На каждый запрос LISTSET Ваша программа должна вывести числа  — содержимое запрошенного множества или −1, 
если множество пусто.

На каждый запрос LISTSETSOF Ваша программа должна вывести числа  — номера множеств, содержащих запрошенное число, или −1, 
если таких множеств не существует.

На прочие запросы не должно быть никакого вывода.

Гарантируется, что правильный вывод программы не превышает одного мегабайта.
*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

template <typename T>

class Polyset {
private:
	int m;
	std::vector<std::set<T>> v;
	std::map<size_t, std::set<T>> map_;

public:
	Polyset(int M) {
		m = M;
		std::vector<std::set<T>> q(m + 1);
		v = q;
	}
	void add(const T& element, size_t set);
	void erase(const T& element, size_t set);
	void clear(size_t set);
	void listSet(size_t set);
	void listSetOf(const T& element);
};

template <typename T>

void Polyset<T>::add(const T& element, size_t set) {
	v[set].insert(element);
	map_[element].insert(set);
}

template <typename T>

void Polyset<T>::erase(const T& element, size_t set) {
	T t = v[set].erase(element);
	t = map_[element].erase(set);
}

template <typename T>

void Polyset<T>::clear(size_t set) {
	for (auto element : v[set]) {
		map_[element].erase(set);
	}
	v[set].clear();
}

template <typename T>

void Polyset<T>::listSet(size_t set) {
	if (v[set].empty()) {
		std::cout << "-1";
	}
	else {
		for (auto element : v[set]) {
			std::cout << element << " ";
		}
	}
	std::cout << '\n';
}

template <typename T>

void Polyset<T>::listSetOf(const T& element) {
	if (map_[element].empty()) {
		std::cout << "-1";
	}
	else {
		for (auto set : map_[element]) {
			std::cout << set << " ";
		}
	}
	std::cout << '\n';
}

int main() {
	size_t n;
	int m;
	int k;
	std::string command;
	size_t element;
	size_t set;
	std::cin >> n >> m >> k;
	Polyset<size_t>poly (m);
	for (int i = 0; i < k; ++i) {
		std::cin >> command;
		if (command == "ADD") {
			std::cin >> element >> set;
			poly.add(element, set);
		}
		else if (command == "DELETE") {
			std::cin >> element >> set;
			poly.erase(element, set);
		}
		else if (command == "CLEAR") {
			std::cin >> set;
			poly.clear(set);
		}
		else if (command == "LISTSET") {
			std::cin >> set;
			poly.listSet(set);
		}
		else { //command == "LISTSETOF"
			std::cin >> element;
			poly.listSetOf(element);
		}
	}
}