//Problem D. Contest 1.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/295360/submission/93950734

/*
Гоблины Мглистых гор очень любях ходить к своим шаманам. 
Так как гоблинов много, к шаманам часто образуются очень длинные очереди. 
А поскольку много гоблинов в одном месте быстро образуют шумную толку, 
которая мешает шаманам проводить сложные медицинские манипуляции, 
последние решили установить некоторые правила касательно порядка в очереди.

Обычные гоблины при посещении шаманов должны вставать в конец очереди. 
Привилегированные же гоблины, знающие особый пароль, встают ровно в ее середину, 
причем при нечетной длине очереди они встают сразу за центром.

Так как гоблины также широко известны своим непочтительным отношением ко всяческим правилам и законам, 
шаманы попросили вас написать программу, которая бы отслеживала порядок гоблинов в очереди.

Входные данные
В первой строке входных данный записано число N (1≤N≤105)  − количество запросов. 
Следующие N строк содержат описание запросов в формате:

+ i  − гоблин с номером i (1≤i≤N) встаёт в конец очереди.
* i  − привилегированный гоблин с номером i встает в середину очереди.
-  − первый гоблин из очереди уходит к шаманам. Гарантируется, что на момент такого запроса очередь не пуста.

Выходные данные
Для каждого запроса типа - программа должна вывести номер гоблина, который должен зайти к шаманам.
*/


#include <iostream>
#include <deque>

int main() {
	std::deque <int> first_half; // goblins stay in two deques of almost equal size
	std::deque <int> second_half;
	int n; //number of goblins arriving
	char priority; // each gobling is vip or is not
	int index; //index for counting goblins

	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::cin >> priority; //reading a command
		if (priority == '-') { //if a goblin should be removed
			std::cout << first_half.front() << "\n"; //printing index of removed goblin
			first_half.pop_front(); //removing goblin
			if (first_half.size() < second_half.size()) { //if neaded first goblin of second deque moves to the end of first deque
				first_half.push_back(second_half.front());
				second_half.pop_front();
			}
		}
		else if (priority == '+') { //if an ordinary goblin arrives
			std::cin >> index; //reading goblin's index
			second_half.push_back(index); //goblin is ended to the end of second deque
			if (first_half.size() < second_half.size()) { //if neaded first goblin of second deque moves to the end of first deque
				first_half.push_back(second_half.front());
				second_half.pop_front();
			}
		}
		else if (priority == '*') { //if a vip goblin arrives
			std::cin >> index; //reading goblin's index
			if (first_half.size() == second_half.size()) { //adding to first deque if deques have equal length
				first_half.push_back(index);
			}
			else { //adding to second deque if first was longer
				second_half.push_front(index);
			}

		}
	}
}