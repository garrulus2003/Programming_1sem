//Problem A. Contest 1. Solution via dynamic array.
//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/295360/submission/95911674

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
private:
    void Resize(); // redoubles the buffer if it is full

    size_t size_; //# of elements in stack
    size_t capacity_; //size of the buffer

    T* buffer_;

public:
    Stack(const Stack& other) = delete;
    Stack(Stack&& other) = delete;
    Stack(); //constructor
    ~Stack(); //destructor

    Stack& operator=(const Stack& other) = delete;
    Stack& operator=(Stack&& other) = delete;

    bool IsEmpty(); //returns 1 if the buffer is empty and 1 otherwise
    void Push(T value); //pushes back a value
    T Pop(); //pops top value
    T Back(); //returns top value
    size_t Size(); //returns size of the stack
    void Clear(); //deletes the buffer
};

template <typename T>

Stack<T>::Stack() { //constructor
    size_ = 0;
    capacity_ = 2;
    buffer_ = new T[capacity_];
}

template <typename T>

Stack<T>::~Stack() { //destructor
    delete[] buffer_;
}

template <typename T>

bool Stack<T>::IsEmpty() { //checks whether the stack is empty
    return (size_ == 0);
}

template <typename T>

void Stack<T>::Clear() { //deletes the buffer
    delete[] buffer_;
    size_ = 0;
    capacity_ = 2;

    T* new_buffer = new T[capacity_]; //creates new small buffer

    buffer_ = new_buffer;
}

template <typename T>

void Stack<T>::Resize() { //redoubles the buffer
    T* new_buffer = new T[capacity_ * 2]; //new big buffer created
    
    for (size_t i = 0; i < size_; ++i) { //putting data from old buffer to new one
        new_buffer[i] = buffer_[i];
    }

    capacity_ *= 2;

    delete[] buffer_; //deletes old buffer

    buffer_ = new_buffer; //renames new buffer
}

template <typename T>

void Stack<T>::Push(T value) {
    if (capacity_ == size_) { //checks whether there is place to push
        Resize(); //resizes if the buffer is full
    }

    buffer_[size_] = value; //push new value
    ++size_;
}

template <typename T>

T Stack<T>::Pop() { //pops top value if there is one
    assert(!IsEmpty());
    --size_;
    return buffer_[size_];
}

template <typename T>

T Stack<T>::Back() { //returns top value i there is one
    assert(!IsEmpty());
    return buffer_[size_ - 1];
}

template <typename T>

size_t Stack<T>::Size() { //returns buffer size
    return size_;
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