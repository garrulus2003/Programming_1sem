//Problem D. Contest 2.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/296750/submission/96634623

/*

Реализуйте двоичную кучу.

Обработайте запросы следующих видов:

insert x: вставить целое число x в кучу;
getMin: вывести значение минимального элемента в куче (гарантируется, что к этому моменту куча не пуста);
extractMin: удалить минимальный элемент из кучи (гарантируется, что к этому моменту куча не пуста);
decreaseKey i Δ: уменьшить число, вставленное на i-м запросе, на целое число Δ≥0 
(гарантируется, что i-й запрос был осуществлён ранее, являлся запросом добавления, 
а добавленное на этом шаге число всё ещё лежит в куче).
Можете считать, что в любой момент времени все числа, хранящиеся в куче, попарно различны, а их количество не превышает 105.

Входные данные
В первой строке содержится число q (1≤q≤106), означающее число запросов.

В следующих q строках содержатся запросы в описанном выше формате. 
Добавляемые числа x и поправки Δ лежат в промежутке [−109,109], а Δ≥0.

Выходные данные
На каждый запрос вида getMin выведите ответ в отдельной строке.
*/

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

class Heap {
private:
	int size_; //quantity of elements in the heap
	int values_capacity_; //capacity of values_
	int place_capacity_; //capacity of place_
	int values_size_; //max index of inserted element
	long long heap_capacity_; //capacity of heap_

	long long* values_; //an array containing values by indexes
	int* heap_; //a heap, but elements are indexes
	int* place_; //an array containing places in heap by indexes


	//resize functions for all the arrays

	void resizeValues();
	void resizeHeap();
	void resizePlace();

public:
	Heap(const Heap& other) = delete;
	Heap(Heap&& other) = delete;

	Heap& operator=(const Heap& other) = delete;
	Heap& operator=(Heap&& other) = delete;

	Heap(); //constructor
	~Heap(); //destructor

	void insert(long long value, int index); //inserts an element
	long long getMin(); //returns minimum in heap
	void extractMin(); //extracts minimum
	void decreaseKey(int pointer, long long delta); //decreases (pointer) element by delta
	void siftDown(int i);
	void siftUp(int i);
};


void Heap::resizeHeap() { //endoubles the heap_ array
	int* new_heap = new int[heap_capacity_ * 2];
	for (size_t i = 0; i < size_ + 1; ++i) {
		new_heap[i] = heap_[i];
	}
	heap_capacity_ *= 2;
	delete[] heap_;
	heap_ = new_heap;
}

void Heap::resizeValues() { //endoubles the values_ array
	long long* new_values = new long long[values_capacity_ * 2];
	for (size_t i = 1; i < values_size_ + 1; ++i) {
		new_values[i] = values_[i];
	}
	values_capacity_ *= 2;
	delete[] values_;
	values_ = new_values;
}


void Heap::resizePlace() { //endoubles the place_ array
	int* new_place = new int[place_capacity_ * 2];
	for (size_t i = 1; i < values_size_ + 1; ++i) {
		new_place[i] = place_[i];
	}
	place_capacity_ *= 2;
	delete[] place_;
	place_ = new_place;
}


Heap::Heap() { //constructor
	size_ = 0;
	values_size_ = 0;
	heap_capacity_ = 10;
	values_capacity_ = 10;
	place_capacity_ = 10;
	values_ = new long long[values_capacity_];
	heap_ = new int[heap_capacity_];
	place_ = new int[place_capacity_];
}

Heap::~Heap() { //destructor
	delete[] values_;
	delete[] heap_;
	delete[] place_;
}

void Heap::siftUp(int i) { // changes kid and parent while all conditions are done
	while (i > 1 && (values_[heap_[i]] < values_[heap_[i / 2]])) {
		std::swap(place_[heap_[i]], place_[heap_[i / 2]]);
		std::swap(heap_[i], heap_[i / 2]);
		i /= 2;
	}
}

void Heap::siftDown(int i) { // changes kid and parent while all conditions are done
	while (2 * i <= size_) {
		int j = -1;

		if (values_[heap_[2 * i]] < values_[heap_[i]]) {
			j = 2 * i;
		}

		if (((2 * i + 1 <= size_) && (values_[heap_[2 * i + 1]] < values_[heap_[i]]))
			&& (j == -1 || (values_[heap_[2 * i]] > values_[heap_[2 * i + 1]]))) {
			j = 2 * i + 1;
		}

		if (j == -1) {
			break;
		}
		else {
			std::swap(place_[heap_[i]], place_[heap_[j]]);
			std::swap(heap_[i], heap_[j]);
			i = j;
		}
	}
}

void Heap::insert(long long value, int index) { //inserts an element
	if (size_ >= heap_capacity_ - 1) { //resize the heap_ if full
		resizeHeap();
	}

	values_size_ = index;

	if (values_size_ >= values_capacity_ - 2) { //resize the values_ and place_ if full
		resizeValues();
		resizePlace();
	}

	++size_; //one more element in heap_
	values_[index] = value; //new element value olaced to values_
	heap_[size_] = index; //new element index placed to heap_'s last position
	place_[index] = size_; //indexes position in heap is the last one
	siftUp(size_);
}

long long Heap::getMin() {
	return values_[heap_[1]]; //returns minimum
}

void Heap::extractMin() {
	heap_[1] = heap_[size_]; //heap_'s big value placed at first place and sift down
	place_[heap_[size_]] = 1;
	place_[heap_[1]] = -1;
	--size_; //one element is deleated
	siftDown(1);
}

void Heap::decreaseKey(int pointer, long long delta) {
	values_[pointer] -= delta; //decreases value
	siftUp(place_[pointer]);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int q; //number of commands that will be given
	std::cin >> q;
	std::string command;
	Heap h;
	for (int i = 0; i < q; ++i) {
		std::cin >> command;
		if (command == "insert") {
			long long x;
			std::cin >> x;
			h.insert(x, i + 1);
		}
		else if (command == "getMin") {
			std::cout << h.getMin() << '\n';
		}
		else if (command == "extractMin") {
			h.extractMin();
		}
		else if (command == "decreaseKey") {
			int pointer;
			long long delta;
			std::cin >> pointer >> delta;
			h.decreaseKey(pointer, delta);
		}
	}
}