//Unordred Map
//https://contest.yandex.ru/contest/21872/run-report/51368259/
//Neustroeva Liza 024

/*
* В этой задаче Вам предлагается реализовать упрощенный аналог одного из популярных контейнеров STL - unordered_map’а. 
Вам может пригодиться List, написанный ранее. 
Кроме того, в вашем контейнере нужно будет правильно поддержать нужные виды итераторов и move-семантику.

Напишите шаблонный класс UnorderedMap<Key, Value, Hash, Equal, Alloc> - упрощенный аналог std::unordered_map. 
Здесь Key - тип ключа, Value - тип значения, Hash - используемая хеш-функция (по умолчанию std::hash<Key>, реализовывать hash не надо), 
Equal - используемый сравниватель (по умолчанию - std::equal_to<Key>), 
Alloc - используемый аллокатор (по умолчанию - std::allocator<std::pair<const Key, Value»). 
Типы Key и Value не обязаны иметь конструкторы по умолчанию, копирующий конструктор и копирующий оператор присваивания. 
Для создания UnorderedMap с ними должно быть достаточно, чтобы они имели лишь move-конструктор и move-оператор присваивания. 
Внутри UnorderedMap публично определим тип NodeType как std::pair<const Key, Value>. 
(В std::unordered_map аналогичный тип называется value_type.) Должна быть реализована следующая функциональность:

Конструкторы (в т.ч. копирования и перемещения), деструктор, копирующий и перемещающий операторы присваивания.
Методы [] и at(key), работающие в среднем за O(1). 
Метод [] определен только для неконстантных объектов, он создает Value по умолчанию, если по данному ключу ничего не было. 
Метод at(key) в таком случае кидает исключение.
Метод size(), за O(1) возвращающий текущее количество элементов в контейнере.
Внутренние типы Iterator и ConstIterator, удовлетворяющие требованиям ForwardIterator. 
Разыменование константного итератора не должно позволять поменять объект под ним.
Методы begin(), end(), cbegin(), cend(). Данные методы должны быть реализованы так, 
чтобы код for (auto it = m.begin(); it != m.end(); ++it); позволял пройтись по всем лежащим 
в контейнере элементам за линейное время от количества этих элементов. Инкрементация любого 
итератора должна происходить за гарантированное O(1).
Метод insert, принимающий ссылку на NodeType и возвращающий pair<Iterator, bool>, 
где bool означает “произошла ли вставка”, а Iterator указывает на элемент с данным ключом в контейнере 
(либо уже лежавший там, либо только что вставленный). 
Метод insert должен эффективно обрабатывать как lvalue, так и rvalue: не копировать переданную ему NodeType, если она была rvalue! 
Вставка элемента должна работать за O(1) в среднем.
Метод insert от пары InputIterator’ов на NodeType, делающий вставку всего данного диапазона в контейнер.
Метод emplace(Args&&... args), который самостоятельно конструирует NodeType от переданных аргументов 
(без их копирования, если это возможно) и, не копируя, вставляет полученный объект NodeType в контейнер, если это возможно. 
Возвращаемый тип - такой же, как у insert от NodeType. Конструировать NodeType нужно с помощью правильного аллокатора 
(то есть Alloc, если он был указан, а точнее, через allocator_traits от него)!
Метод erase от итератора, а также от пары итераторов (удаляющие один элемент и диапазон элементов соответственно). 
Итераторы на элементы, которые не были удалены, должны не инвалидироваться после вызова erase. 
Удаление одного элемента должно работать за O(1) в среднем.
Метод find по ключу, возвращающий итератор на найденный элемент или end(), если элемент не был найден. 
Поиск должен работать в среднем за O(1).
Методы reserve, max_size, load_factor и max_load_factor, аналогичные методам STL, позволяющие управлять размером хеш-таблицы.
В вашем файле должна отсутствовать функция main(), а сам файл должен называться unordered_map.h; 
в качестве компилятора необходимо указывать GCC C++17 make. Ваш код будет вставлен посредством команды 
#include "unordered_map.h" в программу, содержащую тесты; вследствие этого, 
код необходимо отправлять в файле со строго соответствующим именем!
*/


#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <math.h>

template <typename T, typename Allocator = std::allocator<T>>
class List {
public:
	struct Node;

	template <typename iter_type>
	class BaseIter;

	size_t sz = 0;
	Node* start = nullptr;
	Node* finish = nullptr;
	Allocator alloc;

public:

	using iterator = BaseIter<T>;
	using const_iterator = BaseIter<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	using node_alloc_type = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using alloc_traits = std::allocator_traits<node_alloc_type>;

	node_alloc_type node_alloc;

	explicit List(const Allocator& Alloc = Allocator());
	List(size_t new_size, const Allocator& alloc = Allocator());
	List(size_t new_size, const T& element, const Allocator& alloc = Allocator());
	List(const List& other);
	List(List&& other);

	List& operator=(const List& other);
	List& operator=(List&& other);
	~List();

	Allocator get_allocator() const;
	size_t size() const;

	void push_back(const T& element);
	void push_back(T&& element);
	void push_front(const T& element);
	void push_front(T&& element);
	void pop_back();
	void pop_front();

	template <typename iter_type>
	void insert(BaseIter<iter_type> it, const T&);

	template <typename iter_type>
	void insert(BaseIter<iter_type> it, T&&);

	template <typename iter_type>
	void erase(BaseIter<iter_type> it);
};

template<typename T, typename Allocator>
template<typename iter_type>
class List<T, Allocator>::BaseIter {
public:
	List<T, Allocator>::Node* node;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = iter_type;
	using difference_type = std::ptrdiff_t;
	using pointer = iter_type*;
	using reference = iter_type&;

	BaseIter(Node* new_node) : node(new_node) {};

	BaseIter(const BaseIter<const T>& other) : node(other.node) {};

	operator BaseIter<const iter_type>() {
		return BaseIter<const iter_type>(node);
	};


	BaseIter& operator++();
	BaseIter operator++(int);
	BaseIter& operator--();
	BaseIter operator--(int);

	iter_type& operator*() const;
	iter_type* operator->() const;

	bool operator==(const BaseIter& other) const;
	bool operator!=(const BaseIter& other) const;
};

template <typename T, typename Allocator>
struct List<T, Allocator>::Node {
	Node* prev = nullptr;
	Node* next = nullptr;
	T value;
	Node() = default;
	Node(const T& Value) : value(Value) {};
	Node(T&& Value) : value(std::move(Value)) {};
};

template <typename T, typename Allocator>
List<T, Allocator>::List(const Allocator& Alloc) : alloc(Alloc) {
	start = alloc_traits::allocate(node_alloc, 1);
	finish = alloc_traits::allocate(node_alloc, 1);
	start->next = finish;
	finish->prev = start;
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_t new_size, const Allocator& alloc) : List(alloc) {
	for (size_t i = 0; i < new_size; ++i) {
		Node* new_node = alloc_traits::allocate(node_alloc, 1);
		alloc_traits::construct(node_alloc, new_node);
		new_node->next = finish;
		new_node->prev = finish->prev;
		(finish->prev)->next = new_node;
		finish->prev = new_node;
		++sz;
	}
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_t new_size, const T& element, const Allocator& alloc) : List(alloc) {
	for (size_t i = 0; i < new_size; ++i) push_back(element);
}

template <typename T, typename Allocator>
List<T, Allocator>::List(const List<T, Allocator>& other) :
	List(std::allocator_traits<Allocator>::select_on_container_copy_construction(other.alloc)) {
	Node* current = (other.start)->next;
	for (size_t i = 0; i < other.size(); ++i) {
		push_back(current->value);
		current = current->next;
	}
}

template <typename T, typename Allocator>
List<T, Allocator>::List(List<T, Allocator>&& other) : sz(std::move(other.sz)), start(std::move(other.start)), 
finish(std::move(other.finish)), alloc(std::move(other.alloc)), node_alloc(std::move(other.node_alloc)) {
	other.sz = 0;
	other.start = alloc_traits::allocate(other.node_alloc, 1);
	other.finish = alloc_traits::allocate(other.node_alloc, 1);
	other.start->next = other.finish;
	other.finish->prev = other.start;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(const List<T, Allocator>& other) {
	if (this == &other) return *this;
	if (std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value)
	{
		alloc = other.alloc;
	}
	while (sz > 0) pop_back();
	Node* current = (other.start)->next;
	for (size_t i = 0; i < other.size(); ++i) {
		push_back(current->value);
		current = current->next;
	}
	return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(List<T, Allocator>&& other) {
	if (this == &other) return *this;
	sz = other.sz;
	start = other.start;
	finish = other.finish;
	alloc = std::move(other.alloc);
	node_alloc = std::move(other.node_alloc);
	other.sz = 0;
	
	other.start = alloc_traits::allocate(other.node_alloc, 1);
	other.finish = alloc_traits::allocate(other.node_alloc, 1);
	other.start->next = other.finish;
	other.finish->prev = other.start;
	return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>::~List() {
	while (sz > 0) pop_back();
	alloc_traits::deallocate(node_alloc, start, 1);
	alloc_traits::deallocate(node_alloc, finish, 1);
}

template <typename T, typename Allocator>
Allocator List<T, Allocator>::get_allocator() const {
	return alloc;
}

template <typename T, typename Allocator>
size_t List<T, Allocator>::size() const {
	return sz;
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back(const T& element) {
	insert(end(), element);
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(const T& element) {
	insert(begin(), element);
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back(T&& element) {
	insert(end(), element);
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(T&& element) {
	insert(begin(), element);
}


template <typename T, typename Allocator>
void List<T, Allocator>::pop_back() {
	iterator it = end();
	--it;
	erase(it);
}

template <typename T, typename Allocator>
void List<T, Allocator>::pop_front() {
	erase(begin());
}

template <typename T, typename Allocator>
template <typename iter_type>
void List<T, Allocator>::insert(BaseIter<iter_type> it, const T& element) {
	Node* inserting = it.node;
	Node* new_node = alloc_traits::allocate(node_alloc, 1);
	alloc_traits::construct(node_alloc, new_node, element);
	new_node->next = inserting;
	new_node->prev = inserting->prev;
	inserting->prev = new_node;
	(new_node->prev)->next = new_node;
	++sz;
}

template <typename T, typename Allocator>
template <typename iter_type>
void List<T, Allocator>::insert(BaseIter<iter_type> it, T&& element) {
	Node* inserting = it.node;
	Node* new_node = alloc_traits::allocate(node_alloc, 1);
	alloc_traits::construct(node_alloc, new_node, std::move(element));
	new_node->next = inserting;
	new_node->prev = inserting->prev;
	inserting->prev = new_node;
	(new_node->prev)->next = new_node;
	++sz;
}

template <typename T, typename Allocator>
template <typename iter_type>
void List<T, Allocator>::erase(BaseIter<iter_type> it) {
	Node* erasing = it.node;
	(erasing->prev)->next = (erasing->next);
	(erasing->next)->prev = (erasing->prev);
	alloc_traits::destroy(node_alloc, erasing);
	alloc_traits::deallocate(node_alloc, erasing, 1);
	--sz;
}


template <typename T, typename Allocator>
template <typename iter_type>
typename List<T, Allocator>::template BaseIter<iter_type>& List<T, Allocator>::BaseIter<iter_type>::operator++() {
	node = node->next;
	return *this;
}


template <typename T, typename Allocator>
template <typename iter_type>
typename List<T, Allocator>::template BaseIter<iter_type> List<T, Allocator>::BaseIter<iter_type>::operator++(int) {
	auto copy = *this;
	++(*this);
	return copy;
}


template <typename T, typename Allocator>
template <typename iter_type>
typename List<T, Allocator>::template BaseIter<iter_type>& List<T, Allocator>::BaseIter<iter_type>::operator--() {
	node = node->prev;
	return *this;
}


template <typename T, typename Allocator>
template <typename iter_type>
typename List<T, Allocator>::template BaseIter<iter_type> List<T, Allocator>::BaseIter<iter_type>::operator--(int) {
	auto copy = *this;
	--(*this);
	return copy;
}

template <typename T, typename Allocator>
template <typename iter_type>
iter_type& List<T, Allocator>::BaseIter<iter_type>::operator*() const {
	return node->value;
}


template <typename T, typename Allocator>
template <typename iter_type>
iter_type* List<T, Allocator>::BaseIter<iter_type>::operator->() const {
	return &(node->value);
}

template<typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::begin() {
	return iterator(start->next);
}

template<typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::end() {
	return iterator(finish);
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::begin() const {
	return cbegin();
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::end() const {
	return cend();
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::cbegin() const {
	return const_iterator(start->next);
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::cend() const {
	return const_iterator(finish);
}

template<typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator List<T, Allocator>::rbegin() {
	return reverse_iterator(end());
}

template<typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator List<T, Allocator>::rend() {
	return reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::rbegin() const {
	return crbegin();
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::rend() const {
	return crend();
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::crbegin() const {
	return const_reverse_iterator(end());
}

template<typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::crend() const {
	return const_reverse_iterator(begin());
}

template<typename T, typename Allocator>
template<typename iter_type>
bool List<T, Allocator>::BaseIter<iter_type>::operator==(const BaseIter& other) const {
	return node == other.node;
}

template<typename T, typename Allocator>
template<typename iter_type>
bool List<T, Allocator>::BaseIter<iter_type>::operator!=(const BaseIter& other) const {
	return node != other.node;
}

//
//
//
//Unoredered Map
//
//
//


template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Equal = std::equal_to<Key>, 
	typename Alloc = std::allocator<std::pair<const Key, Value>>>
class UnorderedMap {
public:
	template <typename iter_type>
	class BaseIter;

public:
	using NodeType = std::pair<const Key, Value>;
	using Iterator = BaseIter<NodeType>;
	using ConstIterator = BaseIter<const NodeType>;

public:
	template <typename iter_type>
	class BaseIter;

	using ListAllocator = typename std::allocator_traits<Alloc>::template rebind_alloc<NodeType*>;
	using ListIterator = typename List<NodeType*, ListAllocator>::iterator;
	using ConstListIterator = typename List<NodeType*, ListAllocator>::const_iterator;
	using ListIterAllocator = typename std::allocator_traits<Alloc>::template rebind_alloc<ListIterator>;
	using ListNode = typename List<NodeType, ListAllocator>::Node;
	using NodeAllocator = typename std::allocator_traits<Alloc>::template rebind_alloc<NodeType>;
	using node_alloc_traits = std::allocator_traits<NodeAllocator>;
	using PointerAllocator = typename std::allocator_traits<Alloc>::template rebind_alloc<ListIterator*>;

	size_t sz;
	size_t table_sz;
	float max_lf;
	List<NodeType*, ListAllocator> nodes;
	std::vector<ListIterator, ListIterAllocator> bucket_starts;

	Hash hash;
	Equal equal;
	Alloc alloc;

	void rehash_if_needed();
	void rehash(size_t);

public:
	UnorderedMap();
	UnorderedMap(const UnorderedMap&);
	UnorderedMap(UnorderedMap&&);

	UnorderedMap& operator=(const UnorderedMap&);
	UnorderedMap& operator=(UnorderedMap&&);

	~UnorderedMap();

	Value& operator[](const Key&);
	Value& at(const Key&);
	Value at(const Key&) const;

	size_t size() const;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	Iterator find(const Key&) const;

	std::pair<Iterator, bool> insert(const NodeType&);

	template <typename iterator>
	void insert(iterator, iterator);

	template<class MovingInsertion>
	std::pair<Iterator, bool> insert(MovingInsertion&&);

	template<class... Args>
	std::pair<Iterator, bool> emplace(Args&&...);

	Iterator erase(Iterator);
	Iterator erase(Iterator, Iterator);

	void reserve(size_t);
	float load_factor() const;
	float max_load_factor() const;
	void max_load_factor(float);
	size_t max_size() const;
};

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
void UnorderedMap<Key, Value, Hash, Equal, Alloc>::rehash_if_needed() {
	if (load_factor() > max_lf) rehash(2 * table_sz);
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
void UnorderedMap<Key, Value, Hash, Equal, Alloc>::rehash(size_t new_table_sz) {
	auto moved = std::move(nodes);
	table_sz = new_table_sz;
	bucket_starts.clear();
	bucket_starts.resize(table_sz, nodes.end());
	for (auto it = moved.begin(); it != moved.end(); ++it) {
		size_t hash_ = hash((*it)->first) % table_sz;
		if (bucket_starts[hash_] != nodes.end()) {
			nodes.insert(bucket_starts[hash_], *it);
		}
		else {
		nodes.push_back(*it);
		bucket_starts[hash_] = nodes.end();
		}
	--bucket_starts[hash_];
	}
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
void UnorderedMap<Key, Value, Hash, Equal, Alloc>::reserve(size_t new_sz) {
	if (new_sz > sz) rehash(std::round(new_sz / max_lf) + 1);
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
float UnorderedMap<Key, Value, Hash, Equal, Alloc>::load_factor() const {
	return static_cast<float>(sz) / table_sz;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
float UnorderedMap<Key, Value, Hash, Equal, Alloc>::max_load_factor() const {
	return max_lf;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
void UnorderedMap<Key, Value, Hash, Equal, Alloc>::max_load_factor(float new_lf) {
	max_lf = new_lf;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
size_t UnorderedMap<Key, Value, Hash, Equal, Alloc>::max_size() const {
	return 666666666;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
UnorderedMap<Key, Value, Hash, Equal, Alloc>::UnorderedMap() : sz(0), table_sz(1), max_lf(0.75) {
	bucket_starts.resize(1, nodes.end());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
UnorderedMap<Key, Value, Hash, Equal, Alloc>::~UnorderedMap() {
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		delete *it;
	}
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
UnorderedMap<Key, Value, Hash, Equal, Alloc>::UnorderedMap(const UnorderedMap& other) : sz(other.sz), table_sz(other.table_sz),
	max_lf(other.max_lf), hash(other.hash), equal(other.equal), alloc(other.alloc)
{
	while (nodes.size() > 0) nodes.pop_back();
	for (auto it = other.nodes.begin(); it != other.nodes.end(); ++it) {
		NodeType* new_node = node_alloc_traits::allocate(alloc, 1);
		node_alloc_traits::construct(alloc, new_node, *(*it));
		nodes.push_back(new_node);
	}
	bucket_starts.resize(table_sz, nodes.end());
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		size_t hash_ = hash((*it)->first) % table_sz;
		if (bucket_starts[hash_] == nodes.end()) bucket_starts[hash_] = it;
	}
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
UnorderedMap<Key, Value, Hash, Equal, Alloc>::UnorderedMap(UnorderedMap&& other) : sz(std::move(other.sz)), 
	table_sz(std::move(other.table_sz)), max_lf(std::move(other.max_lf)), 
	nodes(std::move(other.nodes)), bucket_starts(std::move(other.bucket_starts)), 
	hash(std::move(other.hash)), equal(std::move(other.equal)), alloc(std::move(other.alloc)) {}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
UnorderedMap<Key, Value, Hash, Equal, Alloc>& UnorderedMap<Key, Value, Hash, Equal, Alloc>::operator=(const UnorderedMap& other) {
	if (this == &other) return *this;
	std::cout << 1;
	UnorderedMap copy(other);
	*this = std::move(copy);
	return *this;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
UnorderedMap<Key, Value, Hash, Equal, Alloc>& UnorderedMap<Key, Value, Hash, Equal, Alloc>::operator=(UnorderedMap&& other) {
	if (this == &other) return *this;
	bucket_starts = std::move(other.bucket_starts);
	sz = std::move(other.sz);
	table_sz = std::move(other.table_sz);
	max_lf = std::move(other.max_lf);
	hash = std::move(other.hash);
	equal = std::move(other.equal);
	alloc = std::move(other.alloc);
	nodes = std::move(other.nodes);
	return *this;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
size_t UnorderedMap<Key, Value, Hash, Equal, Alloc>::size() const {
	return sz;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator 
		UnorderedMap<Key, Value, Hash, Equal, Alloc>::find(const Key& key) const {
	size_t hash_ = hash(key) % table_sz;
	for (auto it = bucket_starts[hash_]; it != ListIterator(nodes.end()) && hash_ == hash((*it)->first) % table_sz; ++it) {
		if (equal(key, (*it)->first)) return Iterator(it);
	}
	return Iterator(nodes.end());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
std::pair<typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator, bool> 
		UnorderedMap<Key, Value, Hash, Equal, Alloc>::insert(const NodeType& pair) {
	auto place = find(pair.first);
	if (place != end()) return std::make_pair(place, false);
	++sz;
	size_t hash_ = hash(pair.first) % table_sz;
	auto cur_first = bucket_starts[hash_];
	NodeType* new_node = node_alloc_traits::allocate(alloc, 1);
	node_alloc_traits::construct(alloc, new_node, pair);
	nodes.insert(cur_first, new_node);
	--cur_first;
	bucket_starts[hash_] = cur_first;
	rehash_if_needed();
	return std::make_pair(Iterator(bucket_starts[hash_]), true);
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<class MovingInsertion>
std::pair<typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator, bool> 
		UnorderedMap<Key, Value, Hash, Equal, Alloc>::insert(MovingInsertion&& m) {
	auto t =  emplace(std::forward<MovingInsertion>(m));
	return t;
}


template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template <typename iterator>
void UnorderedMap<Key, Value, Hash, Equal, Alloc>::insert(iterator it1, iterator it2) {
	while (it1 != it2) {
		insert(*it1);
		++it1;
	}
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<class... Args>
std::pair<typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator, bool> 
		UnorderedMap<Key, Value, Hash, Equal, Alloc>::emplace(Args&&... args) {
	NodeType* new_node = node_alloc_traits::allocate(alloc, 1);
	node_alloc_traits::construct(alloc, new_node, std::forward<Args>(args)...);
	auto place = find(new_node->first);
	if (place != end()) return std::make_pair(place, false);
	++sz;
	size_t hash_ = hash(new_node->first) % table_sz;
	auto cur_first = bucket_starts[hash_];
	nodes.insert(cur_first, new_node);
	--cur_first;
	bucket_starts[hash_] = cur_first;
	rehash_if_needed();
	hash_ = hash(new_node->first) % table_sz;
	auto p = std::make_pair(Iterator(bucket_starts[hash_]), true);
	return p;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::erase(typename
	UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator it) {
	--sz;
	size_t hash_ = hash(it->first) % table_sz;
	auto next_iter = it;
	++next_iter;
	if (bucket_starts[hash_] == it.list_iter) {
		if (next_iter.list_iter != nodes.end() && hash(next_iter->first) % table_sz == hash_) {
			bucket_starts[hash_] = next_iter.list_iter;
		}
		bucket_starts[hash_] = nodes.end();
	}
	node_alloc_traits::destroy(alloc, it.list_iter.node->value);
	node_alloc_traits::deallocate(alloc, it.list_iter.node->value, 1);
	nodes.erase(it.list_iter);
	return Iterator(next_iter);
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::erase(typename
	UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator it1, typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator it2) {
	while (it1 != it2) {
		it1 = erase(it1);
	}
	return it2;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
Value& UnorderedMap<Key, Value, Hash, Equal, Alloc>::operator[](const Key& key) {
	try {
		return at(key);
	}
	catch (std::out_of_range&){
		return insert(std::make_pair(key, Value())).first.list_iter.node->value->second;
	}
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
Value& UnorderedMap<Key, Value, Hash, Equal, Alloc>::at(const Key& key) {
	auto it = find(key);
	if (it != end()) return it->second;
	throw std::out_of_range("No element corresponds this key");
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
Value UnorderedMap<Key, Value, Hash, Equal, Alloc>::at(const Key& key) const {
	auto it = find(key);
	if (it != end()) return it->second;
	throw std::out_of_range("No element corresponds this key");
}




//
//
//
//ITERATORS
//
//
//

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
class UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter {
public:
	ListIterator list_iter;

private:
	explicit BaseIter(const ConstListIterator& other) : list_iter(ListIterator(other)) {};

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = iter_type;
	using difference_type = std::ptrdiff_t;
	using pointer = iter_type*;
	using reference = iter_type&;


	explicit BaseIter(const ListIterator&  other) : list_iter(other) {};
	explicit operator BaseIter<const iter_type>() {
		return BaseIter<const iter_type>(list_iter);
	};

	BaseIter& operator++();
	BaseIter operator++(int);

	iter_type& operator*() const;
	iter_type* operator->() const;

	bool operator==(const BaseIter& other) const;
	bool operator!=(const BaseIter& other) const;
};

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::template BaseIter<iter_type>& 
	UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter<iter_type>::operator++() {
	++list_iter;
	return *this;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::template BaseIter<iter_type>
UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter<iter_type>::operator++(int) {
	BaseIter copy = *this;
	++(*this);
	return copy;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
iter_type& UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter<iter_type>::operator*() const {
	return *(list_iter.node->value);
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
iter_type* UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter<iter_type>::operator->() const {
	return *list_iter;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
bool UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter<iter_type>::operator==(const BaseIter<iter_type>& other) const{
	return list_iter == other.list_iter;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
template<typename iter_type>
bool UnorderedMap<Key, Value, Hash, Equal, Alloc>::BaseIter<iter_type>::operator!=(const BaseIter<iter_type>& other) const{
	return list_iter != other.list_iter;
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::begin() {
	return Iterator(nodes.begin());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::Iterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::end() {
	return Iterator(nodes.end());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::ConstIterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::begin() const {
	return ConstIterator(nodes.begin());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::ConstIterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::end() const{
	return ConstIterator(nodes.end());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::ConstIterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::cbegin() const{
	return ConstIterator(nodes.begin());
}

template <typename Key, typename Value, typename Hash, typename Equal, typename Alloc>
typename UnorderedMap<Key, Value, Hash, Equal, Alloc>::ConstIterator UnorderedMap<Key, Value, Hash, Equal, Alloc>::cend() const{
	return ConstIterator(nodes.end());
}