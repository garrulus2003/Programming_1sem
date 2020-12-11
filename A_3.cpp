//Problem A. Contest 3. 

//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/301990/submission/100949285

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

template <typename T, bool Comparator(const T&, const T&)>

class AVL {
private:
	struct Node {
		T value;
		int depth;
		Node* left;
		Node* right;
		Node(const T& Value) { value = Value; depth = 0; left = nullptr; right = nullptr; }
	};

	Node* root;

	//functions updating vertex
	int depth(Node* node) const;
	int delta(Node* node) const;
	void new_depth(Node* node);

	//balancing functions
	Node* sright(Node* node);
	Node* sleft(Node* node);
	Node* balance(Node* node);

	Node* insert(const T& x, Node* current);
	Node* extractMin(Node*);
	Node* extract(const T& x, Node* node);
	Node* getMin(Node* node) const;
	Node* getMax(Node* node) const;


	void inorder(Node* node) const;
	bool exists(const T& x, Node* current) const;
	void deleting(Node* node);
	T next(const T& x, Node* current) const;
	T prev(const T& x, Node* current) const;

public:
	AVL(const AVL& other) = delete;
	AVL(AVL&& other) = delete;

	AVL& operator=(const AVL& other) = delete;
	AVL& operator=(AVL&& other) = delete;

	AVL();
	~AVL();

	void inorder() const;
	bool exists(const T& x) const;
	void insert(const T& x);
	void extract(const T& x);
	void next(const T& x) const;
	void prev(const T& x) const;
};

template <typename T, bool Comparator(const T&, const T&)>
AVL <T, Comparator>::AVL() {
	root = nullptr;
}

template <typename T, bool Comparator(const T&, const T&)>
AVL<T, Comparator>::~AVL() {
	deleting(root);
}

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::deleting(Node* node) {
	if (!node) return;
	deleting(node->left);
	deleting(node->right);
	delete node;
}

template <typename T, bool Comparator(const T&, const T&)>
int AVL<T, Comparator>::depth(Node* node) const{
	return node ? node->depth : 0;
}

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::new_depth(Node* node) {
	if (!node) return;
	node->depth = std::max(depth(node->left), depth(node->right)) + 1;
}

template <typename T, bool Comparator(const T&, const T&)>
int AVL <T, Comparator>::delta(Node* node) const {
	if (!node) return 0;
	return depth(node->left) - depth(node->right);
}

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::sright(Node* node) {
	Node* new_node = node->left;
	node->left = new_node->right;
	new_node->right = node;
	new_depth(node);
	new_depth(new_node);
	return new_node;
}

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::sleft(Node* node) {
	Node* new_node = node->right;
	node->right = new_node->left;
	new_node->left = node;
	new_depth(node);
	new_depth(new_node);
	return new_node;
}

template <typename T, bool Comparator(const T&, const T&)>
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

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::insert(const T& x, Node* current) {
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

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::inorder(Node* node) const {
	if (!node) return;

	inorder(node->left);

	if (node->right) {
		std::cout << "Right son of " << node->value << " is " << node->right->value << std::endl;
	}
	if (node->left) {
		std::cout << "Left son of " << node->value << " is " << node->left->value << std::endl;
	}

	inorder(node->right);
}

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::inorder() const {
	inorder(root);
}

template <typename T, bool Comparator(const T&, const T&)>
bool AVL<T, Comparator>::exists(const T& x, Node* current) const {
	if (!current) return false;
	if (Comparator(x, current->value)) return exists(x, current->left);
	if (!Comparator(x, current->value) && !Comparator(current->value, x)) return true;
	return exists(x, current->right);
}

template <typename T, bool Comparator(const T&, const T&)>
bool AVL<T, Comparator>::exists(const T& x) const {
	return exists(x, root);
}

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::insert(const T& x) {
	if (!exists(x)) {
		root = insert(x, root);
	}
}

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::getMin(Node* node) const {
	return node->left ? getMin(node->left) : node;
}

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::extract(const T& x, Node* node) {
	if (!node) return nullptr;
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

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::extract(const T& x) {
	if (exists(x)) {
		root = extract(x, root);
	}
}

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::getMax(Node* node) const {
	return node->right ? getMax(node->right) : node;
}

template <typename T, bool Comparator(const T&, const T&)>
T AVL<T, Comparator>::next(const T& x, Node* current) const {
	if (Comparator(x, current->value)) {
		if (current->left && Comparator(x, getMax(current->left)->value)) {
			return next(x, current->left);
		}
		return current->value;
	}
	return next(x, current->right);
}

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::next(const T& x) const {
	if (!root || !Comparator(x, getMax(root)->value)) {
		std::cout << "none \n";
	}
	else {
		std::cout << next(x, root) << "\n";
	}
}

template <typename T, bool Comparator(const T&, const T&)>
T AVL<T, Comparator>::prev(const T& x, Node* current) const {
	if (Comparator(current->value, x)) {
		if (current->right && Comparator(getMin(current->right)->value, x)) {
			return prev(x, current->right);
		}
		return current->value;
	}
	return prev(x, current->left);
}

template <typename T, bool Comparator(const T&, const T&)>
void AVL<T, Comparator>::prev(const T& x) const {
	if (!root || !Comparator(getMin(root)->value, x)) {
		std::cout << "none \n";
	}
	else {
		std::cout << prev(x, root) << "\n";
	}
}

template <typename T, bool Comparator(const T&, const T&)>
typename AVL<T, Comparator>::Node* AVL<T, Comparator>::extractMin(AVL::Node* node) {
	if (!node->left) {
		return node->right;
	}
	node->left = extractMin(node->left);
	return balance(node);
}

bool isLess(const long long& a, const long long& b) {
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
