#include <vector>
#include <cassert>
#include <string>
#include <iostream>

// Fixed Allocator

template <size_t chunkSize>
class FixedAllocator {

	static FixedAllocator<chunkSize>* instance_;

	size_t size_ = 0;
	size_t capacity_ = 1;
	size_t max_capacity = 1 << 15;
	std::vector<void*> buffer_;
	std::vector<char*> deallocated_;

protected:
	FixedAllocator();

public:
	static FixedAllocator<chunkSize>* Instance();

	void* allocate();
	void deallocate(char* ptr);

	~FixedAllocator();
};

template <size_t chunkSize>
FixedAllocator<chunkSize>* FixedAllocator<chunkSize>::instance_ = nullptr;

template <size_t chunkSize>
FixedAllocator<chunkSize>::FixedAllocator() {
	buffer_.push_back(::operator new(chunkSize));
}

template <size_t chunkSize>
FixedAllocator<chunkSize>* FixedAllocator<chunkSize>::Instance() {
	if (instance_ == nullptr) instance_ = new FixedAllocator<chunkSize>();
	return instance_;
}

template <size_t chunkSize>
void* FixedAllocator<chunkSize>::allocate() {
	if (!deallocated_.empty()) {
		void* allocated = deallocated_[deallocated_.size() - 1];
		deallocated_.pop_back();
		return allocated;
	}
	if (size_ == capacity_) {
		if (capacity_ <= max_capacity) capacity_ *= 2;
		buffer_.push_back(::operator new(capacity_ * chunkSize));
		size_ = 0;
	}
	void* allocated = reinterpret_cast<char*>(buffer_[buffer_.size() - 1]) + size_ * chunkSize;
	++size_;
	return allocated;
}

template <size_t chunkSize>
void FixedAllocator<chunkSize>::deallocate(char* ptr) {
	deallocated_.push_back(ptr);
}

template <size_t chunkSize>
FixedAllocator<chunkSize>::~FixedAllocator() {
	for (size_t pos = 0; pos < buffer_.size(); ++pos) {
		delete buffer_[pos];
	}
}

//Fast Allocator

template <typename T>
class FastAllocator {
	static const bool using_fixed = (sizeof(T) <= 24 ? true : false);
	static FixedAllocator<sizeof(T)>* fixed_allocator;

public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	FastAllocator() = default;
	
	FastAllocator<T>(const FastAllocator<T>&) = default;

	template <typename U>
	FastAllocator<T>(const FastAllocator<U>&) {}

	~FastAllocator() = default;

	T* allocate(size_t sz);
	void deallocate(T* ptr_to_dealloc, size_t sz);

	template <typename U>
	struct rebind {
		using other = FastAllocator<U>;
	};
};

template <typename T>
FixedAllocator<sizeof(T)>* FastAllocator<T>::fixed_allocator = FixedAllocator<sizeof(T)>::Instance();


template <typename T>
T* FastAllocator<T>::allocate(size_t sz) {
	if (using_fixed && sz <= 1) {
		return reinterpret_cast<T*>(fixed_allocator->allocate());
	}
	return reinterpret_cast<T*>(::operator new(sizeof(T) * sz));
}

template <typename T>
void FastAllocator<T>::deallocate(T* ptr_to_dealloc, size_t sz) {
	if (using_fixed && sz <= 1) {
		fixed_allocator->deallocate(static_cast<char*>(static_cast<void*> (ptr_to_dealloc)));
	}
	else {
		::operator delete(ptr_to_dealloc);
	}
}


//List

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
	List& operator=(const List& other);
	~List();

	Allocator get_allocator() const;
	size_t size() const;

	void push_back(const T& element);
	void push_front(const T& element);
	void pop_back();
	void pop_front();

	template <typename iter_type>
	void insert(BaseIter<iter_type> it, const T&);

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