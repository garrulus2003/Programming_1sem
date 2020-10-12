#include <iostream>
#include <string>

class Stack {
private:
    void Resize(); //resizes the buffer if it is full

    long long size_ = 0; //current size
    long long capacity_ = 0; //buffer capacity
    long long tail_ = 0; //current tail

    int* buffer_{ new int[capacity_] };

public:
    Stack() = default; //constructor
    Stack(const Stack& other) = delete;
    Stack(Stack&& other) = delete;
    ~Stack(); //destructor

    Stack& operator=(const Stack& other) = delete;
    Stack& operator=(Stack&& other) = delete;

    void Push(int value);
    int Pop();
    int Back();
    long long Size();
    void Clear();
};

Stack::~Stack() {
    delete[] buffer_;
}

void Stack::Clear() { //clears the buffer and reset all the parameters
    delete[] buffer_;
    size_ = 0;
    capacity_ = 2;
    tail_ = 0;

    int* new_buffer{ new int[capacity_] };

    buffer_ = new_buffer;
}

void Stack::Resize() { //resizes the buffer
    int* new_buffer{ new int[capacity_ * 2] }; //creating new buffer

    for (int i = 0; i < tail_; ++i) { //copy values from old to new buffer
        new_buffer[i] = buffer_[i];
    }

    capacity_ *= 2;

    delete[] buffer_; //deletes previous buffer

    buffer_ = new_buffer;
}

void Stack::Push(int value) { //push in the value
    if (capacity_ == size_) {
        Resize();
    }

    buffer_[tail_] = value;

    ++tail_;
    ++size_;
}

int Stack::Pop() { //pops the tail
    if (size_ == 0) {
        return NULL;
    }
    --size_;
    --tail_;
    return buffer_[tail_];
}

int Stack::Back() { //returns the last value
    if (size_ == 0) {
        return NULL;
    }
    return buffer_[tail_ - 1];
}

long long Stack::Size() { //returns stack size
    return size_;
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
            std::cout << "ok" << "\n";
        }
        else if (command == "pop") {
            if (s.Back() != NULL) {
                std::cout << s.Pop() << "\n";
            }
            else {
                std::cout << "error" << "\n";
            }
        }
        else if (command == "back") {
            if (s.Back() != NULL) {
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