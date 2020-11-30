//Problem A. Contest 3. 

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/301990/submission/99957797

/*
Реализуйте AVL-дерево. Решения с использованием других структур засчитываться не будут.
Входные данные
Входной файл содержит описание операций с деревом. Операций не больше 105.
В каждой строке находится одна из следующих операций:
insert x — добавить в дерево ключ x.
delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо.
exists x — если ключ x есть в дереве, вывести «true», иначе «false»
next x — минимальный элемент в дереве, больший x, или «none», если такого нет.
prev x — максимальный элемент в дереве, меньший x, или «none», если такого нет.
Все числа во входном файле целые и по модулю не превышают 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev.
Следуйте формату выходного файла из примера.
*/


#include <cassert>
#include <string>
#include <iostream>

template <typename T, bool Comparator(T&, T&)>

class AVL {
private:
	struct Node {
		T value;
		int depth;
		Node* left;
		Node* right;
		Node(T Value) { value = Value; depth = 0; left = nullptr; right = nullptr; }
	};

	Node* root;

	int depth(Node* node);
	void new_depth(Node* node);
	int delta(Node* node);
	Node* sright(Node* node);
	Node* sleft(Node* node);
	Node* balance(Node* node);
	Node* insert(T x, Node* current);
	Node* extractMin(Node*);
	Node* getMin(Node* node);
	Node* getMax(Node* node);
	Node* extract(T x, Node* node);


	void inorder(Node* node);
	bool exists(T x, Node* current);
	T next(T x, Node* current);
	T prev(T x, Node* current);

public:
	AVL(const AVL& other) = delete;
	AVL(AVL&& other) = delete;

	AVL& operator=(const AVL& other) = delete;
	AVL& operator=(AVL&& other) = delete;

	AVL();
	~AVL();

	void inorder();
	bool exists(T x);
	void insert(T x);
	void extract(T x);
	void next(T x);
	void prev(T x);
};

template <typename T, bool Comparator(T&, T&)>

AVL <T, Comparator>::AVL() {
	root = nullptr;
}

template <typename T, bool Comparator(T&, T&)>

AVL<T, Comparator>::~AVL() {
	while (root) {
		root = extractMin(root);
	}
}

template <typename T, bool Comparator(T&, T&)>

int AVL<T, Comparator>::depth(Node* node) {
	return node ? node->depth : 0;
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::new_depth(Node* node) {
	if (!node) {
		std::cout << "0";
		return;
	}
	else {
		node->depth = (depth(node->left) > depth(node->right) ? depth(node->left) : depth(node->right)) + 1;
	}
}

template <typename T, bool Comparator(T&, T&)>

int AVL <T, Comparator>::delta(Node* node) {
	if (!node) {
		std::cout << "0";
		return 0;
	}
	else {
		return depth(node->left) - depth(node->right);
	}
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::sright(Node* node) {
	Node* new_node = node->left;
	node->left = new_node->right;
	new_node->right = node;
	new_depth(node);
	new_depth(new_node);
	return new_node;
}

template <typename T, bool Comparator(T&, T&)>


typename AVL<T, Comparator>::Node* AVL<T, Comparator>::sleft(Node* node) {
	Node* new_node = node->right;
	node->right = new_node->left;
	new_node->left = node;
	new_depth(node);
	new_depth(new_node);
	return new_node;
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::balance(Node* node)
{
	new_depth(node);
	if (delta(node) == -2)
	{
		if (delta(node->right) > 0)
			node->right = sright(node->right);
		return sleft(node);
	}
	if (delta(node) == 2)
	{
		if (delta(node->left) < 0)
			node->left = sleft(node->left);
		return sright(node);
	}
	return node;
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::insert(T x, Node* current) {
	if (!current) {
		return new Node(x);
	}
	if (Comparator(x, current->value)) {
		current->left = insert(x, current->left);
	}
	else {
		current->right = insert(x, current->right);
	}
	return balance(current);
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::inorder(Node* node) {
	if (!node) {
		return;
	}
	inorder(node->left);
	if (node->right) {
		std::cout << "Right son of " << node->value << " is " << node->right->value << std::endl;
	}
	if (node->left) {
		std::cout << "Left son of " << node->value << " is " << node->left->value << std::endl;
	}
	inorder(node->right);
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::inorder() {
	inorder(root);
}

template <typename T, bool Comparator(T&, T&)>

bool AVL<T, Comparator>::exists(T x, Node* current) {
	if (!current) {
		return false;
	}
	if (Comparator(x, current->value)) {
		return exists(x, current->left);
	}
	else if (!Comparator(x,current->value) && !Comparator(current->value, x)) {
		return true;
	}
	else {
		return exists(x, current->right);
	}
}

template <typename T, bool Comparator(T&, T&)>

bool AVL<T, Comparator>::exists(T x) {
	return exists(x, root);
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::insert(T x) {
	if (!exists(x)) {
		root = insert(x, root);
	}
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::getMin(Node* node)
{
	return node->left ? getMin(node->left) : node;
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::extract(int T, Node* node)
{
	if (!node) {
		return nullptr;
	}
	if (Comparator(x, node->value)) {
		node->left = extract(x, node->left);
	}
	else if (Comparator(node->value, x)) {
		node->right = extract(x, node->right);
	}
	else
	{
		Node* Left = node->left;
		Node* Right = node->right;
		delete node;
		if (!Right) {
			return Left;
		}
		Node* min = getMin(Right);
		min->right = extractMin(Right);
		min->left = Left;
		return balance(min);
	}
	return balance(node);
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::extract(T x) {
	if (exists(x)) {
		root = extract(x, root);
	}
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::getMax(Node* node)
{
	return node->right ? getMax(node->right) : node;
}

template <typename T, bool Comparator(T&, T&)>

T AVL<T, Comparator>::next(T x, Node* current) {
	if (Comparator(x, current->value)) {
		if (current->left && Comparator(x, getMax(current->left)->value)) {
			return next(x, current->left);
		}
		else {
			return current->value;
		}
	}
	if (!Comparator(x, current->value)) {
		return next(x, current->right);
	}
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::next(T x) {
	if (!root || !Comparator(x, getMax(root)->value)) {
		std::cout << "none \n";
	}
	else {
		std::cout << next(x, root) << "\n";
	}
}

template <typename T, bool Comparator(T&, T&)>

T AVL<T, Comparator>::prev(T x, Node* current) {
	if (Comparator (current->value, x)) {
		if (current->right && Comparator(getMin(current->right)->value, x)) {
			return prev(x, current->right);
		}
		else {
			return current->value;
		}
	}
	if (!Comparator(current->value, x)) {
		return prev(x, current->left);
	}
}

template <typename T, bool Comparator(T&, T&)>

void AVL<T, Comparator>::prev(T x) {
	if (!root || !Comparator(getMin(root)->value, x) {
		std::cout << "none \n";
	}
	else {
		std::cout << prev(x, root) << "\n";
	}
}

template <typename T, bool Comparator(T&, T&)>

typename AVL<T, Comparator>::Node* AVL<T, Comparator>::extractMin(AVL::Node* node)
{
	if (!node->left) {
		return node->right;
	}
	node->left = extractMin(node->left);
	return balance(node);
}

bool isLess(long long& a, long long& b) {
	return a < b;
}


int main() {
	AVL <long long, isLess> t;
	int num;
	std::string command;
	while (std::cin >> command) {
		std::cin >> num;
		if (command == "insert") {
			t.insert(num);
		}
		else if (command == "delete") {
			t.extract(num);
		}
		else if (command == "exists") {
			if (t.exists(num)) {
				std::cout << "true \n";
			}
			else {
				std::cout << "false \n";
			}
		}
		else if (command == "next") {
			t.next(num);
		}
		else if (command == "prev") {
			t.prev(num);
		}
	}
}