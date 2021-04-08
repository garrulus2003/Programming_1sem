#include <stdexcept>

size_t mod = 1000;

template <typename T>
class Deque {
	size_t start = 0;
	size_t sz = 0;
	size_t cap = 0;
	T** arr = nullptr;

	void resize();

	template <typename iter_type>
	class BaseIter;

public:
	Deque() = default;
	Deque(int n, const T& element = T());
	Deque(const Deque& other);

	Deque<T>& operator=(const Deque<T>& other);
	~Deque();

	T& operator[](size_t i);
	T& at(size_t i);

	const T& operator[](size_t i) const;
	const T& at(size_t i) const;
	
	size_t size() const;

	void push_back(const T& element);
	void pop_back();
	void push_front(const T& element);
	void pop_front();

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

	void insert(iterator iter, const T& element);
	void erase(iterator iter);
};

template<typename T>
template<typename iter_type>
class Deque<T>::BaseIter{
protected:
	size_t index;
	Deque<T>* deque;

public:

	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = iter_type;
	using difference_type = std::ptrdiff_t;
	using pointer = iter_type*;
	using reference = iter_type&;

	size_t array_ind() const;
	size_t bucket_ind() const;

	BaseIter(Deque<T>* deque, int index);
	BaseIter(const Deque<T>* deque, int index);

	BaseIter& operator++();
	BaseIter operator++(int);
	BaseIter& operator--();
	BaseIter operator--(int);

	bool operator<(const BaseIter& other) const;
	bool operator>(const BaseIter& other) const;
	bool operator<=(const BaseIter& other) const;
	bool operator>=(const BaseIter& other) const;
	bool operator==(const BaseIter& other) const;
	bool operator!=(const BaseIter& other) const;

	BaseIter operator+(int n) const;
	BaseIter operator-(int n) const;

	int operator-(const BaseIter& other) const;

	iter_type& operator*() const;
	iter_type* operator->() const;
};


template <typename T>
Deque<T>::Deque(int n, const T& element) : start(mod), sz(n), cap(n / mod + 3) {
	arr = new T*[cap];
	size_t j = start;
	try {
		for (size_t i = 0; i < cap; ++i) {
			arr[i] = reinterpret_cast<T*>(new int8_t[mod * sizeof(T)]);
		}

		for (; j < sz + mod; ++j) {
			new(arr[j / mod] + j % mod) T(element);
		}
	}
	catch (...) {
		for (; j >= start; --j) {
			(arr[j / mod] + (j % mod))->~T();
		}

		for (size_t i = 0; i < cap; ++i) {
			delete[] reinterpret_cast<int8_t*>(arr[i]);
		}
		delete[] arr;
		throw;
	}
};

template <typename T>
Deque<T>::Deque(const Deque& other) : start(other.start), sz(other.sz), cap(other.cap) {
	arr = new T * [cap];
	size_t j = start;
	try {
		for (size_t i = 0; i < cap; ++i) {
			arr[i] = reinterpret_cast<T*>(new int8_t[mod * sizeof(T)]);
		}

		for (; j < sz + start; ++j) {
			new(arr[j / mod] + j % mod) T(other.arr[j / mod][j % mod]);
		}
	}
	catch (...) {
		for (; j >= start; --j) {
			(arr[j / mod] + (j % mod))->~T();
		}

		for (size_t i = 0; i < cap; ++i) {
			delete[] reinterpret_cast<int8_t*>(arr[i]);
		}
		delete[] arr;
		throw;
	}
};

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other) {
	Deque<T> copy(other);
	std::swap(arr, copy.arr);
	std::swap(start, copy.start);
	std::swap(sz, copy.sz);
	std::swap(cap, copy.cap);
	return *this;
}

template <typename T>
Deque<T>::~Deque() {
	size_t j = start + sz;
	for (; j + 1 >= start + 1; --j) {
		(arr[j / mod] + (j % mod))->~T();
	}

	for (size_t i = 0; i < cap; ++i) {
		delete[] reinterpret_cast<int8_t*>(arr[i]);
	}
	delete[] arr;
}

template <typename T>
size_t Deque<T>::size() const{
	return sz;
}

template <typename T>
T& Deque<T>::operator[](size_t i) {
	return arr[(start + i) / mod][(start + i) % mod];
}

template <typename T>
T& Deque<T>::at(size_t i) {
	if (i >= sz) throw std::out_of_range("");
	return arr[(start + i) / mod][(start + i) % mod];
}

template <typename T>
const T& Deque<T>::operator[](size_t i) const {
	return arr[(start + i) / mod][(start + i) % mod];
}

template <typename T>
const T& Deque<T>::at(size_t i) const {
	if (i >= sz) throw std::out_of_range("");
	return arr[(start + i) / mod][(start + i) % mod];
}

template <typename T>
void Deque<T>::pop_back() {
	(arr[(start + sz - 1) / mod] + ((start + sz - 1) % mod))->~T();
	--sz;
}


template <typename T>
void Deque<T>::pop_front() {
	(arr[start / mod] + (start % mod))->~T();
	++start;
	--sz;
}

template <typename T>
void Deque<T>::push_back(const T& element) {
	if (start + sz + 1 > mod * cap) resize();
	try {
		new(arr[(start + sz) / mod] + (start + sz) % mod) T(element);
		++sz;
	}
	catch (...) {
		throw;
	}
}

template <typename T>
void Deque<T>::push_front(const T& element) {
	if (start == 0) resize();
	try {
		new(arr[(start - 1) / mod] + (start - 1) % mod) T(element);
		--start;
		++sz;
	}
	catch (...) {
		throw;
	}
}

template <typename T>
void Deque<T>::resize() {
	if (cap != 0) {
		size_t new_cap = 3 * cap;
		T** newarr = new T * [new_cap];
		for (size_t i = 0; i < cap; ++i) {
			newarr[i] = reinterpret_cast<T*>(new int8_t[mod * sizeof(T)]);
		}
		for (size_t i = 0; i < cap; ++i) {
			newarr[2 * cap + i] = reinterpret_cast<T*>(new int8_t[mod * sizeof(T)]);
		}
		for (size_t i = 0; i < cap; ++i) {
			newarr[cap + i] = arr[i];
		}
		delete[] arr;
		arr = newarr;
		start += cap * mod;
		cap *= 3;
		return;
	}
	cap = 1;
	arr = new T * [cap];
	start = mod / 3;
	arr[0] = reinterpret_cast<T*>(new int8_t[mod * sizeof(T)]);
}

template<typename T>
template<typename iter_type>
size_t Deque<T>::BaseIter<iter_type>::array_ind() const {
	return (index) / mod;
}

template<typename T>
template<typename iter_type>
size_t Deque<T>::BaseIter<iter_type>::bucket_ind() const {
	return (index) % mod;
}

template<typename T>
template<typename iter_type>
Deque<T>::BaseIter<iter_type>::BaseIter(Deque<T>* new_deque, int index) : index(index), deque(new_deque) {}

template<typename T>
template<typename iter_type>
Deque<T>::BaseIter<iter_type>::BaseIter(const Deque<T>* new_deque, int index) : 
	index(index), deque(const_cast<Deque<T>*>(new_deque)) {}

template<typename T>
template<typename iter_type>
typename Deque<T>::template BaseIter<iter_type>& Deque<T>::BaseIter<iter_type>::operator++() {
	++index;
	return *this;
}

template<typename T>
template<typename iter_type>
typename Deque<T>::template BaseIter<iter_type> Deque<T>::BaseIter<iter_type>::operator++(int) {
	Deque<T>::BaseIter<iter_type> copy = *this;
	++(*this);
	return copy;
}

template<typename T>
template<typename iter_type>
typename Deque<T>::template BaseIter<iter_type>& Deque<T>::BaseIter<iter_type>::operator--() {
	--index;
	return *this;
}

template<typename T>
template<typename iter_type>
typename Deque<T>::template BaseIter<iter_type> Deque<T>::BaseIter<iter_type>::operator--(int) {
	Deque<T>::BaseIter<iter_type> copy = *this;
	--(*this);
	return copy;
}

template<typename T>
template<typename iter_type>
bool Deque<T>::BaseIter<iter_type>::operator<(const BaseIter& other) const {
	return index < other.index;
}

template<typename T>
template<typename iter_type>
bool Deque<T>::BaseIter<iter_type>::operator>(const BaseIter& other) const {
	return index > other.index;
}

template<typename T>
template<typename iter_type>
bool Deque<T>::BaseIter<iter_type>::operator<=(const BaseIter& other) const {
	return index <= other.index;
}

template<typename T>
template<typename iter_type>
bool Deque<T>::BaseIter<iter_type>::operator>=(const BaseIter& other) const {
	return index >= other.index;
}

template<typename T>
template<typename iter_type>
bool Deque<T>::BaseIter<iter_type>::operator==(const BaseIter& other) const {
	return index == other.index;
}

template<typename T>
template<typename iter_type>
bool Deque<T>::BaseIter<iter_type>::operator!=(const BaseIter& other) const {
	return index != other.index;
}

template<typename T>
template<typename iter_type>
typename Deque<T>::template BaseIter<iter_type> Deque<T>::BaseIter<iter_type>::operator+(int n) const {
	return BaseIter(deque, index + n);
}


template<typename T>
template<typename iter_type>
typename Deque<T>::template BaseIter<iter_type> Deque<T>::BaseIter<iter_type>::operator-(int n) const {
	return BaseIter(deque, index - n);
}

template<typename T>
template<typename iter_type>
int Deque<T>::BaseIter<iter_type>::operator-(const BaseIter& other) const {
	return index - other.index;
}

template<typename T>
template<typename iter_type>
iter_type& Deque<T>::BaseIter<iter_type>::operator*() const {
	return (deque->arr)[array_ind()][bucket_ind()];
}

template<typename T>
template<typename iter_type>
iter_type* Deque<T>::BaseIter<iter_type>::operator->() const {
	return &(deque->arr)[array_ind()][bucket_ind()];
}

template<typename T>
typename Deque<T>::iterator Deque<T>::begin() {
	return iterator(this, static_cast<int>(start));
}

template<typename T>
typename Deque<T>::iterator Deque<T>::end() {
	return iterator(this, static_cast<int>(start + sz));
}

template<typename T>
typename Deque<T>::const_iterator Deque<T>::begin() const {
	return cbegin();
}

template<typename T>
typename Deque<T>::const_iterator Deque<T>::end() const {
	return cend();
}

template<typename T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const {
	return const_iterator(this, static_cast<int>(start));
}

template<typename T>
typename Deque<T>::const_iterator Deque<T>::cend() const {
	return const_iterator(this, static_cast<int>(start + sz));
}

template<typename T>
typename Deque<T>::reverse_iterator Deque<T>::rbegin(){
	return reverse_iterator(this, static_cast<int>(start + sz - 1));
}

template<typename T>
typename Deque<T>::reverse_iterator Deque<T>::rend(){
	return reverse_iterator(this, static_cast<int>(start -1));
}


template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::rbegin() const {
	return crbegin();
}

template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::rend() const {
	return crend();
}


template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crbegin() const {
	return const_reverse_iterator(this, static_cast<int>(start + sz - 1));
}

template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crend() const {
	return const_reverse_iterator(this, static_cast<int>(start - 1));
}

template<typename T>
void Deque<T>::insert(iterator iter, const T& element) {
	push_back(element);
	for (auto it = end() - 1; it > iter; --it) {
		std::swap(*it, *(it - 1));
	}
}

template<typename T>
void Deque<T>::erase(iterator iter) {
	for (auto it = iter; it < end(); ++it) {
		std::swap(*it, *(it - 1));
	}
	pop_back();
}