//Problem A. Contest 3. 

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/301990/submission/99940708

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


class AVL {
private:
	struct Node {
		int value;
		int depth;
		Node* left;
		Node* right;
		Node(int Value) { value = Value; depth = 0; left = nullptr; right = nullptr; }
	};

	Node* root;

	int depth(Node* node);
	void new_depth(Node* node);
	int delta(Node* node);
	Node* sright(Node* node);
	Node* sleft(Node* node);
	Node* balance(Node* node);
	Node* insert(int x, Node* current);
	Node* extractMin(Node*);
	Node* getMin(Node* node);
	Node* getMax(Node* node);
	Node* extract(int x, Node* node);


	void inorder(Node* node);
	bool exists(int x, Node* current);
	int next(int x, Node* current);
	int prev(int x, Node* current);

public:
	AVL(const AVL& other) = delete;
	AVL(AVL&& other) = delete;

	AVL& operator=(const AVL& other) = delete;
	AVL& operator=(AVL&& other) = delete;

	AVL();
	~AVL();

	void inorder();
	bool exists(int x);
	void insert(int x);
	void extract(int x);
	void next(int x);
	void prev(int x);
};


AVL::AVL() {
	root = nullptr;
}

AVL::~AVL() {
	while (root) {
		root = extractMin(root);
	}
}

int AVL::depth(Node* node) {
	return node ? node->depth : 0;
}

void AVL::new_depth(Node* node) {
	if (!node) {
		std::cout << "0";
		return;
	}
	else {
		node->depth = (depth(node->left) > depth(node->right) ? depth(node->left) : depth(node->right)) + 1;
	}
}

int AVL::delta(Node* node) {
	if (!node) {
		std::cout << "0";
		return 0;
	}
	else {
		return depth(node->left) - depth(node->right);
	}
}

AVL::Node* AVL::sright(Node* node) {
	Node* new_node = node->left;
	node->left = new_node->right;
	new_node->right = node;
	new_depth(node);
	new_depth(new_node);
	return new_node;
}

AVL::Node* AVL::sleft(Node* node) {
	Node* new_node = node->right;
	node->right = new_node->left;
	new_node->left = node;
	new_depth(node);
	new_depth(new_node);
	return new_node;
}

AVL::Node* AVL::balance(Node* node)
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

AVL::Node* AVL::insert(int x, Node* current) {
	if (!current) {
		return new Node(x);
	}
	if (x < current->value) {
		current->left = insert(x, current->left);
	}
	else {
		current->right = insert(x, current->right);
	}
	return balance(current);
}

void AVL::inorder(Node* node) {
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

void AVL::inorder() {
	inorder(root);
}

bool AVL::exists(int x, Node* current) {
	if (!current) {
		return false;
	}
	if (x < current->value) {
		return exists(x, current->left);
	}
	else if (x == current->value) {
		return true;
	}
	else {
		return exists(x, current->right);
	}
}

bool AVL::exists(int x) {
	return exists(x, root);
}

void AVL::insert(int x) {
	if (!exists(x)) {
		root = insert(x, root);
	}
}

AVL::Node* AVL::getMin(Node* node)
{
	return node->left ? getMin(node->left) : node;
}

AVL::Node* AVL::extract(int x, Node* node)
{
	if (!node) {
		return nullptr;
	}
	if (x < node->value) {
		node->left = extract(x, node->left);
	}
	else if (x > node->value) {
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

void AVL::extract(int x) {
	if (exists(x)) {
		root = extract(x, root);
	}
}

AVL::Node* AVL::getMax(Node* node)
{
	return node->right ? getMax(node->right) : node;
}

int AVL::next(int x, Node* current) {
	if (x < current->value) {
		if (current->left && x < getMax(current->left)->value) {
			return next(x, current->left);
		}
		else {
			return current->value;
		}
	}
	if (x >= current->value) {
		return next(x, current->right);
	}
}

void AVL::next(int x) {
	if (!root || x >= getMax(root)->value) {
		std::cout << "none \n";
	}
	else {
		std::cout << next(x, root) << "\n";
	}
}

int AVL::prev(int x, Node* current) {
	if (x > current->value) {
		if (current->right && x > getMin(current->right)->value) {
			return prev(x, current->right);
		}
		else {
			return current->value;
		}
	}
	if (x <= current->value) {
		return prev(x, current->left);
	}
}

void AVL::prev(int x) {
	if (!root || x <= getMin(root)->value) {
		std::cout << "none \n";
	}
	else {
		std::cout << prev(x, root) << "\n";
	}
}

AVL::Node* AVL::extractMin(AVL::Node* node)
{
	if (!node->left) {
		return node->right;
	}
	node->left = extractMin(node->left);
	return balance(node);
}

int main() {
	AVL t;
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