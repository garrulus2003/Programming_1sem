//Problem B. Contest 3.
//Neustroeva Liza 024

//https://codeforces.com/group/R3IJoiTue4/contest/301990/submission/98796069

/*
Реализуйте splay-дерево, которое поддерживает множество S целых чисел,
в котором разрешается производить следующие операции:
add(i) — добавить в множество S число i (если он там уже есть, то множество не меняется);
sum(l,r) — вывести сумму всех элементов x из S, которые удовлетворяют неравенству l≤x≤r.
Решения, не использующие splay-деревья, будут игнорироваться.
Решения, не использующие операции split и merge, будут оцениваться в 2 балла. Решения, использующие операции split и merge, оцениваются в 3 балла.
Входные данные
Исходно множество S пусто. Первая строка входного файла содержит n — количество операций (1≤n≤300000).
Следующие n строк содержат операции. Каждая операция имеет вид либо «+ i», либо «? l r».
Операция «? l r» задает запрос sum(l,r).
Если операция «+ i» идет во входном файле в начале или после другой операции «+», то она задает операцию add(i).
Если же она идет после запроса «?», и результат этого запроса был y, то выполняется операция add((i+y)mod109).
Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 10^9.
Выходные данные
Для каждого запроса выведите одно число — ответ на запрос.
*/

#include <iostream>
#include <utility>
#include <string>

template <typename T, bool Comparator(const T&, const T&)>
class SplayTree {
private:
	struct Node {
		T value;
		Node* left;
		Node* right;
		Node* parent;
		size_t sum = 0;
		Node(const T& Value) { value = Value; sum = 0; left = nullptr; right = nullptr; parent = nullptr; }
	};

	Node* root_ = nullptr;

	size_t getSum(Node* node) const;

	Node* search(Node* node, const T& value);
	void newSum(Node* node);
	void zag(Node* node);
	void zig(Node* node);
	void splay(Node* node);

	Node* getMax(Node* node) const;
	Node* getMin(Node* node);
	Node* merge(Node* s, Node* t);
	Node* next(const T& x, Node* current);
	Node* prev(const T& x, Node* current);
	std::pair <Node*, Node*> split(const T& x);
	Node* insert(const T& x, Node* root);
	void erase(const T& x);

public:
	SplayTree(const SplayTree& other) = delete;
	SplayTree(SplayTree&& other) = delete;
	SplayTree() = default; //constructor
	~SplayTree(); //destructor

	SplayTree& operator=(const SplayTree& other) = delete;
	SplayTree& operator=(SplayTree&& other) = delete;

	void next(const T& x);
	void prev(const T& x);
	void insert(const T& x);
	void inOrder(Node* node);
	T sum(const T& l, const T& r);
};

template <typename T, bool Comparator(const T&, const T&)>
SplayTree<T, Comparator>::~SplayTree() {
	while (root_) {
		erase(root_->value);
	}
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::search(Node* node, const T& value) {
	if (node == nullptr) return nullptr;
	if (value == node->value) return node;
	if (Comparator(value, node->value)) return search(node->left, value);
	return search(node->right, value);
}

template <typename T, bool Comparator(const T&, const T&)>
size_t SplayTree<T, Comparator>::getSum(Node* node) const {
	return node ? node->sum : 0;
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::newSum(Node* node) {
	if (node) {
		node->sum = (getSum(node->right) + getSum(node->left) + node->value);
	}
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::zag(Node* node) {
	Node* new_node = node->right;
	node->right = new_node->left;
	if (new_node->left != nullptr) {
		new_node->left->parent = node;
	}
	new_node->parent = node->parent;
	if (node->parent == nullptr) {
		this->root_ = new_node;
	}
	else if (node == node->parent->left) {
		node->parent->left = new_node;
	}
	else {
		node->parent->right = new_node;
	}
	new_node->left = node;
	node->parent = new_node;
	newSum(new_node->left);
	newSum(new_node->right);
	newSum(new_node);
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::zig(Node* node) {
	Node* new_node = node->left;
	node->left = new_node->right;
	if (new_node->right != nullptr) {
		new_node->right->parent = node;
	}
	new_node->parent = node->parent;
	if (node->parent == nullptr) {
		this->root_ = new_node;
	}
	else if (node == node->parent->right) {
		node->parent->right = new_node;
	}
	else {
		node->parent->left = new_node;
	}
	new_node->right = node;
	node->parent = new_node;
	newSum(new_node->left);
	newSum(new_node->right);
	newSum(new_node);
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::splay(Node* node) {
	while (node->parent) {
		if (!node->parent->parent) {
			if (node == node->parent->left) {
				zig(node->parent);
			}
			else {
				zag(node->parent);
			}
		}
		else if (node == node->parent->left && node->parent == node->parent->parent->left) {
			zig(node->parent->parent);
			zig(node->parent);
		}
		else if (node == node->parent->right && node->parent == node->parent->parent->right) {
			zag(node->parent->parent);
			zag(node->parent);
		}
		else if (node == node->parent->right && node->parent == node->parent->parent->left) {
			zag(node->parent);
			zig(node->parent);
		}
		else {
			zig(node->parent);
			zag(node->parent);
		}
	}
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::getMax(SplayTree<T, Comparator>::Node* node) const{
	while (node->right) { node = node->right; }
	return node;
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::getMin(Node* node) {
	while (node->left) { node = node->left; }
	return node;
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::merge(Node* s, Node* t) {
	if (!s) return t;
	if (!t) return s;
	Node* x = getMax(s);
	splay(x);
	x->right = t;
	t->parent = x;
	return x;
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::next(const T& x, Node* current) {
	if (Comparator(x, current->value)) {
		if (current->left && Comparator(x, getMax(current->left)->value)) {
			return next(x, current->left);
		}
		return current;
	}
	return next(x, current->right);
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::next(const T& x) {
	if (!root_ || !Comparator(x, getMax(root_)->value)) {
		std::cout << "none \n";
	}
	else {
		std::cout << next(x, root_) << "\n";
	}
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::prev(const T& x, Node* current) {
	if (Comparator(current->value, x)) {
		if (current->right && Comparator(getMin(current->right)->value, x)) {
			return prev(x, current->right);
		}
		return current;
	}
	return prev(x, current->left);
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::prev(const T& x) {
	if (!root_ || !Comparator(getMin(root_)->value, x)) {
		std::cout << "none \n";
	}
	else {
		std::cout << prev(x, root_) << "\n";
	}
}

template <typename T, bool Comparator(const T&, const T&)>
std::pair <typename SplayTree<T, Comparator>::Node*, typename SplayTree<T, Comparator>::Node*> SplayTree<T, Comparator>::split(const T& x) {
	if (!root_) return std::make_pair(root_, nullptr);
	if (!Comparator(x, getMax(root_)->value)) return std::make_pair(root_, nullptr);
	Node* node = search(root_, x);
	if (node) {
		splay(search(root_, x));
	}
	else {
		splay(next(x, root_));
	}

	Node* left = root_->left;
	root_->left = nullptr;

	if (left) {
		newSum(left->left);
		newSum(left->right);
		newSum(left);
	}

	if (root_) {
		newSum(root_->left);
		newSum(root_->right);
		newSum(root_);
	}
	return std::make_pair(left, root_);
}

template <typename T, bool Comparator(const T&, const T&)>
typename SplayTree<T, Comparator>::Node* SplayTree<T, Comparator>::insert(const T& x, Node* root) {
	std::pair<Node*, Node*> p;
	Node* node = new Node(x);
	p = split(x);
	node->left = p.first;
	if (p.first) {
		p.first->parent = node;
	}
	node->right = p.second;
	if (p.second) {
		p.second->parent = node;
	}
	node->value = x;
	newSum(node->left);
	newSum(node->right);
	newSum(node);
	return node;
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::insert(const T& x) {
	if (!search(root_, x)) {
		root_ = insert(x, root_);
	}
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::erase(const T& x) {
	if (search(root_, x)) {
		std::pair <Node*, Node*> current_pair;
		current_pair = split(x);
		delete root_;
		root_ = merge(current_pair.first, current_pair.second);
	}
}

template <typename T, bool Comparator(const T&, const T&)>
void SplayTree<T, Comparator>::inOrder(Node* node) {
	if (!node) return;
	inOrder(node->left);
	if (node->parent) {
		std::cout << node->value << " is son of " << node->parent->value << '\n';
	}
	else {
		std::cout << node->value << " is the root \n";
	}
	std::cout << "downsum of " << node->value << " is " << node->sum << "\n";
	inOrder(node->right);
}

template <typename T, bool Comparator(const T&, const T&)>
T SplayTree<T, Comparator>::sum(const T& l, const T& r) {
	T result;
	if (!root_) {
		result = 0;
		std::cout << 0;
	}
	else if (!Comparator(getMin(root_)->value, l)) {
		if (!Comparator(r, getMax(root_)->value)) {
			result = root_->sum;
		}
		else {
			SplayTree::Node* node_next = next(r, root_);
			splay(node_next);
			T greater = (getSum(root_->right) + node_next->value);
			result = (root_->sum - greater);
		}
	}
	else if (!Comparator(r, getMax(root_)->value)) {
		SplayTree::Node* node_prev = prev(l, root_);
		splay(node_prev);
		T less = (getSum(root_->left) + node_prev->value);
		result = (root_->sum - less);
	}
	else {
		SplayTree::Node* node_prev = prev(l, root_);
		splay(node_prev);
		T less = (getSum(root_->left) + node_prev->value);
		SplayTree::Node* node_next = next(r, root_);
		splay(node_next);
		T greater = (getSum(root_->right) + node_next->value);
		result = (root_->sum - less - greater);
	}
	return result;
}

bool isLess(const long long& a, const long long& b) {
	return a < b;
}

int main() {
	SplayTree <long long, isLess> t;
	int n;
	int num;
	int l;
	int r;
	bool was = false;
	size_t notforget;
	std::cin >> n;
	std::string command;
	for (int i = 0; i < n; ++i) {
		std::cin >> command;
		if (command == "+") {
			std::cin >> num;
			if (was) {
				num = (num + notforget) % 1000000000;
			}
			t.insert(num);
			was = false;
		}
		else {
			std::cin >> l >> r;
			notforget = t.sum(l, r);
			std::cout << notforget << "\n";
			was = true;
		}
	}
}