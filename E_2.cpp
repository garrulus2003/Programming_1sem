//Problem E. Contest 2.
//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/296750/submission/96604113

/*
Дана очень длинная последовательность целых чисел длины N.
Требуется вывести в отсортированном виде её наименьшие K элементов. Последовательность может не помещаться в память.
Время работы O(N⋅logK), память O(K). 1≤N≤105, 1≤K≤

Входные данные
В первой строке записаны N и K.

В следующей строке через пробел записана последовательность целых чисел.

Выходные данные
K наименьших элементов последовательности в отсортированном виде.
*/


#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>

template <typename T, bool Comparator(const T&, const T&)>

class Heap {
private:
	int size_; //quantity of elements in heap
	long long heap_capacity_; //capacity of the heap
	T* heap_; // a dynamic array where heap is contained

	void resizeHeap(); //doubles the array if it is too short

public:
	Heap(const Heap& other) = delete;
	Heap(Heap&& other) = delete;

	Heap& operator=(const Heap& other) = delete;
	Heap& operator=(Heap&& other) = delete;

	Heap(); //condtructor
	~Heap(); //destructor

	void insert(T value); //inserts a value
	T getMin(); //returns minimal element
	void extractMin(); //extracts the minimal element
	void siftDown(int i);
	void siftUp(int i);
	int getSize(); //returns size of the heap
};

template <typename T, bool Comparator(const T&, const T&)>

void Heap<T, Comparator>::resizeHeap() {
	T* new_heap = new T[heap_capacity_ * 2]; //creates a new array which is twice bigger
	for (size_t i = 0; i < size_ + 1; ++i) { //copies all values from old buffer to new one
		new_heap[i] = heap_[i];
	}
	heap_capacity_ *= 2; //endoubles the capacity
	delete[] heap_; //deletes old buffer
	heap_ = new_heap;
}

template <typename T, bool Comparator(const T&, const T&)>

Heap<T, Comparator>::Heap() { //constructor
	size_ = 0;
	heap_capacity_ = 10;
	heap_ = new T[heap_capacity_];
}

template <typename T, bool Comparator(const T&, const T&)>

Heap<T, Comparator>::~Heap() { //destructor
	delete[] heap_;
}

template <typename T, bool Comparator(const T&, const T&)>

void Heap<T, Comparator>::siftUp(int i) { //changes the kid and parent vertexes until heap condition is done
	while (i > 1 && (Comparator(heap_[i], heap_[i / 2]))) {
		std::swap(heap_[i], heap_[i / 2]);
		i /= 2;
	}
}

template <typename T, bool Comparator(const T&, const T&)>

void Heap<T, Comparator>::siftDown(int i) { //changes the kid and parent vertexes until heap condition is done
	while (2 * i <= size_) {
		int j = -1;

		if (Comparator(heap_[2 * i], heap_[i])) {
			j = 2 * i;
		}

		if (((2 * i + 1 <= size_) && (Comparator(heap_[2 * i + 1], heap_[i])))
			&& (j == -1 || (Comparator(heap_[2 * i + 1], heap_[2 * i])))) {
			j = 2 * i + 1;
		}

		if (j == -1) {
			break;
		}
		else {
			std::swap(heap_[i], heap_[j]);
			i = j;
		}
	}
}

template <typename T, bool Comparator(const T&, const T&)>

void Heap<T, Comparator>::insert(T value) { //inserts a T-type value
	if (size_ >= heap_capacity_ - 1) { //if the heap is full -> resize
		resizeHeap();
	}

	++size_;
	heap_[size_] = value;
	siftUp(size_);
}

template <typename T, bool Comparator(const T&, const T&)>

T Heap<T, Comparator>::getMin() { //returns minimal value
	return heap_[1];
}

template <typename T, bool Comparator(const T&, const T&)>

void Heap<T, Comparator>::extractMin() { //extracts minimal value
	heap_[1] = heap_[size_]; //exchanges minimal value with one of the biggest
	--size_;
	siftDown(1); //returns this big value to it's proper place
}

template <typename T, bool Comparator(const T&, const T&)>

int Heap<T, Comparator>::getSize() { //returns size of the heap
	return size_;
}

bool isGreater(const long long& a, const long long& b) { //standart 'less' comparator
	return a > b;
}

int main() {
	int n; //length of the array
	int k; //number of smallest elements to return
	std::cin >> n >> k;
	Heap<long long, isGreater> h; //heap which contains k smallest values, biggest in the top
	int current;
	for (int i = 0; i < n; ++i) {
		std::cin >> current;
		if (i < k) { //if heap is not full, insert element
			h.insert(current);
		}
		else {
			int cur_min = h.getMin();
			if (current < cur_min) { //if current is less tham kth -> insert
				h.extractMin();
				h.insert(current);
			}
		}
	}

	int size = h.getSize();

	std::vector <int> vec; //an array where all k elements would be ordered but reversed
	for (int i = 0; i < size; ++i) {
		vec.push_back(h.getMin());
		h.extractMin();
	}


	for (int i = 0; i < size; ++i) { //printing k smallest
		std::cout << vec[vec.size() - 1 - i] << " ";
	}
	return 0;
}
