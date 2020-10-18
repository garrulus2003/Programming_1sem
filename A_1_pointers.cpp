//Problem A. Contest 1. Solution via pointers.
//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/295360/submission/95872734

/*
Реализуйте свой стек. Решения, использующие std::stack, получат 1 балл.
Решения, хранящие стек в массиве, получат 1.5 балла. Решения, использующие указатели, получат 2 балла.

Гарантируется, что количество элементов в стеке ни в какой момент времени не превышает 10000.

Обработайте следующие запросы:

push n: добавить число n в конец стека и вывести «ok»;
pop: удалить из стека последний элемент и вывести его значение, либо вывести «error», если стек был пуст;
back: сообщить значение последнего элемента стека, либо вывести «error», если стек пуст;
size: вывести количество элементов в стеке;
clear: опустошить стек и вывести «ok»;
exit: вывести «bye» и завершить работу.
Входные данные
В каждой строке входных данных задана одна операция над стеком в формате, описанном выше.

Выходные данные
В ответ на каждую операцию выведите соответствующее сообщение.
*/


#include <iostream>
#include <string>
#include <cassert>
template <typename T>

class Stack {
public:
	Stack(const Stack& other) = delete;
	Stack(Stack&& other) = delete;
	Stack(); //constructor
	~Stack(); //destructor

	Stack& operator=(const Stack& other) = delete;
	Stack& operator=(Stack&& other) = delete;

	void Push(T value); // creating new node and pushing a value to it
	T Pop(); // pops the top node
	T Back(); // returns the value in top node
	size_t Size(); //returns current stack size
	void Clear(); //clears the stack
	bool IsEmpty(); //returns 1 if the stack is empty and 0 otherwise

private:
	size_t size_; //stack size
	struct Node {
		T Value;
		Node* Next;
		Node(T value, Node* next = nullptr) {
			Value = value;
			Next = next;
		}
	};
	Node* head_;
};

template <typename T>

Stack<T>::Stack() { //constructor
	size_ = 0;
	head_ = nullptr;
}

template <typename T>

Stack<T>::~Stack() { //destructor
	while (head_) {
		Node* next = (*head_).Next;
		delete head_;
		head_ = next;
	}
	size_ = 0;
}

template <typename T>

bool Stack<T>::IsEmpty() { //returns 1 if the stack is empty and 0 otherwise
	return (size_ == 0);
}

template <typename T>

void Stack<T>::Push(T value) { //creating new node and pushing a value to it
	head_ = new Node(value, head_);
	++size_;
}

template <typename T>

T Stack<T>::Pop() {  // pops the top node
	assert(!IsEmpty());
	Node* next = (*head_).Next;
	int value = (*head_).Value;
	delete head_;
	head_ = next;
	--size_;
	return value;
}

template <typename T>

T Stack<T>::Back() {  // returns the value in top node
	assert(!IsEmpty());
	return (*head_).Value;
}

template <typename T>

size_t Stack<T>::Size() { //returns current stack size
	return size_;
}

template <typename T>

void Stack<T>::Clear() { //clears the stack
	while (head_) {
		Node* next = (*head_).Next;
		delete head_;
		head_ = next;
	}
	size_ = 0;
}


int main() {
	Stack<int> s; //creating a stack of integers
	std::string command = "";
	while (command != "exit") { //working while there is no exit
		std::cin >> command;
		if (command == "push") {
			int n;
			std::cin >> n;
			s.Push(n);
			std::cout << "ok" << "\n";
		}
		else if (command == "pop") {
			if (!s.IsEmpty()) {
				std::cout << s.Pop() << "\n";
			}
			else {
				std::cout << "error" << "\n";
			}
		}
		else if (command == "back") {
			if (!s.IsEmpty()) {
				std::cout << s.Back() << "\n";
			}
			else {
				std::cout << "error" << "\n";
			}
		}
		else if (command == "size") {
			std::cout << s.Size() << "\n";
		}
		else if (command == "clear") {
			s.Clear();
			std::cout << "ok" << "\n";
		}
	}
	std::cout << "bye" << "\n";
	return 0;
}
