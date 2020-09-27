#include <iostream>
#include <string>

class Stack {
public: // functions' declaration
	void Push(int value);  
	void Pop();
	void Back();
	void Size();
	void Clear();


private:
	int size = 0;  // 'size' keeps nodes quantity in the stack
	struct Node {
		int Value;
		Node* Next; //pointer to next node
		Node(int value, Node* next = nullptr) {
			Value = value;
			Next = next;
		}
	};

	Node* head_ = nullptr;
};

//creating a new node

void Stack::Push(int value) {
	head_ = new Node(value, head_); //adding a node to stack
	++size; //size increases
	std::cout << "ok" << "\n";
}

//popping a node, deleting head

void Stack::Pop() {

	// if stack is not empty, deleting head
	if (size > 0) {

		// creating new head
		Node* next = (*head_).Next; 
		int value = (*head_).Value;
		delete head_; //deleting last head
		head_ = next;
		--size; //reducing size
		std::cout << value << "\n";
	}

	// priniting "error" if the stack is empty

	else {
		std::cout << "error" << "\n";
	}
}

// prints the value in head, or "error" if the head is empty

void Stack::Back() {
	if (size != 0) {
		std::cout << (*head_).Value << "\n"; //prints value in head if the stack is not empty
	}
	else {
		std::cout << "error" << "\n"; //prints "error" if the stack is empty
	}
}

// prints size

void Stack::Size() {
	std::cout << size << "\n";
}

//clears the stack, deletes all data

void Stack::Clear() {
	while (head_) {
		Node* next = (*head_).Next;
		delete head_;
		head_ = next;
	}
	size = 0;
}


int main() {
	Stack s;
	std::string command = ""; //variable for command
	while (command != "exit") { //program works until "exit" is entered
		std::cin >> command; //reads the command
		if (command == "push") {
			int n;
			std::cin >> n;
			s.Push(n);
		}
		else if (command == "pop") {
			s.Pop();
		}
		else if (command == "back") {
			s.Back();
		}
		else if (command == "size") {
			s.Size();
		}
		else if (command == "clear") {
			s.Clear();
			std::cout << "ok" << "\n";
		}
	}
	std::cout << "bye" << "\n"; //prints "bye" if the comman if "exit"
	s.Clear(); //deletes all data
	return 0;
}