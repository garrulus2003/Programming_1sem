//Problem D. Contest 2.

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/296750/submission/99940324

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
#include <cassert>

template <typename T>

class SimpleArray {
private:
	size_t size_;
	size_t capacity_;
	T* buffer_;

public:
	SimpleArray(const SimpleArray& other) = delete;
	SimpleArray(SimpleArray&& other) = delete;

	SimpleArray& operator=(const SimpleArray& other) = delete;
	SimpleArray& operator=(SimpleArray&& other) = delete;

	SimpleArray(); //condtructor
	~SimpleArray(); //destructor

	T& operator[](size_t index) { 
		return buffer_[index];
	}

	void Resize();
	size_t getSize() { return size_; }
	size_t getCapacity() { return capacity_; }

	void Push(T Value);
	void Pop();
};

template <typename T>

SimpleArray<T>::SimpleArray() { //constructor
	size_ = 0;
	capacity_ = 10;
	buffer_ = new T[capacity_];
}

template <typename T>

SimpleArray<T>::~SimpleArray() { //destructor
	delete[] buffer_;
}

template <typename T>

void SimpleArray<T>::Resize() {
	T* new_buffer = new T[capacity_ * 2]; //new big buffer created

	for (size_t i = 0; i < size_; ++i) { //putting data from old buffer to new one
		new_buffer[i] = buffer_[i];
	}

	capacity_ *= 2;

	delete[] buffer_; //deletes old buffer

	buffer_ = new_buffer; //renames new buffer
}

template <typename T>

void SimpleArray<T>::Push(T value) {
	if (capacity_ == size_) { //checks whether there is place to push
		Resize(); //resizes if the buffer is full
	}

	buffer_[size_] = value; //push new value
	++size_;
}

template <typename T>

void SimpleArray<T>::Pop() { //pops top value if there is one
	assert(!(size_ == 0));
	--size_;
}

class Heap {
private:
	SimpleArray<long long> heap_;
	SimpleArray<long long> values_;
	SimpleArray<long long> place_;
	void siftDown(int i);
	void siftUp(int i);

public:
	Heap(const Heap& other) = delete;
	Heap(Heap&& other) = delete;

	Heap& operator=(const Heap& other) = delete;
	Heap& operator=(Heap&& other) = delete;

	Heap() = default; //constructor
	~Heap() = default; //destructor

	void insert(long long value, int index); //inserts an element
	long long getMin(); //returns minimum in heap
	void extractMin(); //extracts minimum
	void decreaseKey(int pointer, long long delta); //decreases (pointer) element by delta

};


void Heap::siftUp(int i) { // changes kid and parent while all conditions are done
	while (i > 1 && (values_[heap_[i]] < values_[heap_[i / 2]])) {
		std::swap(place_[heap_[i]], place_[heap_[i / 2]]);
		std::swap(heap_[i], heap_[i / 2]);
		i /= 2;
	}
}

void Heap::siftDown(int i) { // changes kid and parent while all conditions are done
	while (2 * i <= heap_.getSize()) {
		int j = -1;

		if (values_[heap_[2 * i]] < values_[heap_[i]]) {
			j = 2 * i;
		}

		if (((2 * i + 1 <= heap_.getSize()) && (values_[heap_[2 * i + 1]] < values_[heap_[i]]))
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
	heap_.Push(value);
	while (values_.getSize() <= index) { values_.Resize(); place_.Resize(); }
	values_[index] = value; //new element value olaced to values_
	place_[index] = heap_.getSize(); //indexes position in heap is the last one
	siftUp(heap_.getSize());
}

long long Heap::getMin() {
	return values_[heap_[1]]; //returns minimum
}

void Heap::extractMin() {
	heap_[1] = heap_[heap_.getSize()]; //heap_'s big value placed at first place and sift down
	place_[heap_[heap_.getSize()]] = 1;
	place_[heap_[1]] = -1;
	heap_.Pop();
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
