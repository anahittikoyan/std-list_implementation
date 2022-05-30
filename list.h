#ifndef LIST_H
#define LIST_H

#include<iostream>
#include <iterator>
#include<type_traits>

namespace nstd {
	template<typename T, typename Allocator = std::allocator<T>>
	class list {
		using allocator_type = Allocator;
		using value_type = T;
		using size_type = size_t;
		using reference_type = T&;
		using const_reference_type = const T&;
	private:
		struct Node {
		public:
			Node() {}
			Node(Node* p, Node* n, T val = 0) :prev{ p }, next{ n }, value{ val }{}
		public:
			Node* next = nullptr;
			Node* prev = nullptr;
			T value{};
		};
		Node* head = nullptr;
		Node* tail = nullptr;
		size_t _size = 0;

	public:
		class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			iterator() {}
			iterator(const iterator& o) :it{ o.it } {}
			iterator(Node* ptr) :it{ ptr } {}
			~iterator() {}
			friend bool operator==(const iterator& ob1, const iterator& ob2) {
				return ob1.it == ob2.it;
			}
			friend bool operator!=(const iterator& ob1, const iterator& ob2) {
				return !(ob1.it == ob2.it);
			}
			T& operator*() const {
				return it->value;
			}
			T* operator->() const {
				return &it->value;
			}
			iterator operator++() {
				it = it->next;
				return *this;
			}
			iterator operator++(int) {
				iterator temp = it;
				++* this;
				return temp;
			}
			iterator operator--() {
				it = it->prev;
				return *this;
			}
			iterator operator--(int) {
				iterator temp = it;
				--* this;
				return temp;
			}

		public:
			Node* it{};
		};
		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T> {
		public:
			const_iterator() {}
			const_iterator(const const_iterator& o) :it{ o.it } {}
			const_iterator(const Node* ptr) :it{ ptr } {}
			~const_iterator() {}
			friend bool operator==(const const_iterator& ob1, const const_iterator& ob2) {
				return ob1.it == ob2.it;
			}
			friend bool operator!=(const_iterator& ob1, const_iterator& ob2) {
				return !(ob1.it == ob2.it);
			}
			T& operator*() const {
				return it->value;
			}
			T* operator->() const {
				return &it->value;
			}
			const_iterator& operator++() {
				it = it->next;
				return *this;
			}
			const_iterator& operator++(int) {
				iterator temp = it;
				++* this;
				return temp;
			}
			const_iterator& operator--() {
				it = it->prev;
				return *this;
			}
			const_iterator operator--(int) {
				iterator temp = it;
				--* this;
				return temp;
			}

		public:
			const Node* it{};
		};
		class reverse_iterator :public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			reverse_iterator() {}
			reverse_iterator(const reverse_iterator& o) :it{ o.it } {}
			reverse_iterator(Node* ptr) :it{ ptr } {}
			~reverse_iterator() {}
			friend bool operator==(const reverse_iterator& ob1, const reverse_iterator& ob2) {
				return ob1.it == ob2.it;
			}
			friend bool operator!=(const reverse_iterator& ob1, const reverse_iterator& ob2) {
				return !(ob1.it == ob2.it);
			}
			T& operator*() const {
				return it->value;
			}
			T* operator->() const {
				return &it->value;
			}
			reverse_iterator operator++() {
				it = it->prev;
				return *this;
			}
			reverse_iterator operator++(int) {
				iterator temp = it;
				++* this;
				return temp;
			}
			reverse_iterator operator--() {
				it = it->next;
				return *this;
			}
			reverse_iterator operator--(int) {
				iterator temp = it;
				--* this;
				return temp;
			}

		public:
			Node* it{};
		};
		class const_reverse_iterator :public std::iterator<std::bidirectional_iterator_tag, const T> {
		public:
			const_reverse_iterator() {}
			const_reverse_iterator(const const_reverse_iterator& o) :it{ o.it } {}
			const_reverse_iterator(const Node* ptr) :it{ ptr } {}
			~const_reverse_iterator() {}
			friend bool operator==(const reverse_iterator& ob1, const reverse_iterator& ob2) {
				return ob1.it == ob2.it;
			}
			friend bool operator!=(const reverse_iterator& ob1, const reverse_iterator& ob2) {
				return !(ob1.it == ob2.it);
			}
			T& operator*() const {
				return it->value;
			}
			T* operator->() const {
				return &it->value;
			}
			const_reverse_iterator operator++() {
				it = it->prev;
				return *this;
			}
			const_reverse_iterator operator++(int) {
				const_reverse_iterator temp = it;
				++* this;
				return temp;
			}
			const_reverse_iterator operator--() {
				it = it->next;
				return *this;
			}
			const_reverse_iterator operator--(int) {
				const_reverse_iterator temp = it;
				--* this;
				return temp;
			}

		public:
			Node* it{};
		};

	public:
		list() = default;
		list(size_t);
		list(size_t, const T&);
		list(const list&);
		list(list&&)noexcept;
		list(std::initializer_list<T>);
		list(iterator, iterator);
		list(reverse_iterator, reverse_iterator);
		~list();

	public:
		list& operator=(const list&);
		list& operator=(list&&)noexcept;
		bool operator==(const list&)const;
		bool operator!=(const list&)const;
		bool operator<(const list&)const;
		bool operator>(const list&)const;
		bool operator>=(const list&)const;
		bool operator<=(const list&)const;
		friend std::ostream& operator<<(std::ostream& os, const list& ls)
		{
			size_t size = ls._size;
			if (size) {
				auto it = ls.begin();
				while (it != ls.end()) {
					os << *it << " ";
					++it;
				}
				return os;
			}
			else return os;
		}


	public:
		bool empty()const;
		size_t size()const;
		auto max_size()const;

	public:
		void assign(size_t, T);
		void assign(iterator, iterator);
		friend void swap(list& ls1, list& ls2) {
			Node* temp = ls1.head;
			ls1.head = ls2.head;
			ls2.head = temp;
			temp = ls1.tail;
			ls1.tail = ls2.tail;
			ls2.tail = temp;
			int t = ls1._size;
			ls1._size = ls2._size;
			ls2._size = t;
		}

	public:
		T& front()const;
		T& back()const;

	public:
		iterator begin()const;
		iterator end()const;
		const_iterator cbegin()const;
		const_iterator cend()const;
		reverse_iterator rbegin()const;
		reverse_iterator rend()const;
		const_reverse_iterator crbegin()const;
		const_reverse_iterator crend()const;

	public:
		void push_back(const T&);
		void push_front(const T&);
		void pop_back();
		void pop_front();
		iterator insert(iterator, const T&);
		void insert(iterator, size_t, const T&);
		void insert(iterator, iterator, iterator);
		iterator emplace(iterator, T&&...);
		void emplace_back(T&&...);
		void emplace_front(T&&...);
		void erase(iterator);
		void remove(const T&);
		void clear();

	public:
		void unique();
		void merge(const list&);
		void sort();
		void reverse();
		void splice(iterator, const list&);
		void splice(iterator, const list&, iterator);
		void splice(iterator, iterator, iterator);
		void resize(size_t);
		void resize(size_t, const T&);

	public:
		template<typename Predicat>
		void remove_if(Predicat);
		template<typename Predicat>
		void sort(Predicat);
	};

	template<typename T, typename Allocator>
	list<T, Allocator>::list(size_t size) {
		if (size) {
			_size = size;
			head = new Node(nullptr, nullptr);
			head->prev = new Node(nullptr, head);//rend
			Node* temp = head;
			--size;
			while (size) {
				temp->next = new Node(temp, nullptr);
				temp = temp->next;
				--size;
			}
			tail = temp;
			tail->next = new Node(tail, nullptr);//end
		}
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::list(size_t size, const T& value) {
		if (size) {
			_size = size;
			head = new Node(nullptr, nullptr, value);
			head->prev = new Node(nullptr, head);
			Node* temp = head;
			--size;
			while (size) {
				temp->next = new Node(temp, nullptr, value);
				temp = temp->next;
				--size;
			}
			tail = temp;
			tail->next = new Node(tail, nullptr);//end
		}
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::list(const list<T, Allocator>& ls) {
		if (ls._size) {
			_size = ls._size;
			head = new Node(nullptr, nullptr, ls.head->value);
			head->prev = new Node(nullptr, head);
			Node* temp1 = head;
			Node* temp2 = ls.head->next;
			while (temp2) {
				temp1->next = new Node(temp1, nullptr, temp2->value);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			tail = temp1->prev;
			tail->next = temp1;//end
		}
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::list(list<T, Allocator>&& ls)noexcept {
		head = ls.head;
		tail = ls.tail;
		_size = ls._size;
		ls._size = 0;
		ls.head = ls.tail = nullptr;
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::list(std::initializer_list<T> ls) {
		if (ls.size()) {
			_size = ls.size();
			auto it = ls.begin();//in place of range based for
			head = new Node(nullptr, nullptr, *it);
			head->prev = new Node(nullptr, head);
			Node* temp = head;
			for (int i = 1; i < ls.size(); ++i) {
				++it;
				temp->next = new Node(temp, nullptr, *it);
				temp = temp->next;
			}
			tail = temp;
			tail->next = new Node(tail, nullptr);
		}
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::list(list<T, Allocator>::iterator it1, list<T, Allocator>::iterator it2) {
		if (it1 == it2) {
			head = new Node(nullptr, nullptr, *it1);
			head->prev = new Node(nullptr, head);
			head->next = new Node(head, nullptr);
			tail = head;
			++_size;
		}
		else {
			head = new Node(nullptr, nullptr, *it1);
			head->prev = new Node(nullptr, head);
			Node* temp = head;
			++it1;
			++_size;
			while (it1 != it2)
			{
				temp->next = new Node(temp, nullptr, *it1);
				temp = temp->next;
				++it1;
				++_size;
			}
			tail = temp;
			tail->next = new Node(tail, nullptr);
		}
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::list(typename list<T, Allocator>::reverse_iterator it1, typename list<T, Allocator>::reverse_iterator it2) {
		if (it1 == it2) {
			head = new Node(nullptr, nullptr, *it1);
			head->prev = new Node(nullptr, head);
			head->next = new Node(head, nullptr);
			tail = head;
			++_size;
		}
		else if (it1 != it2) {
			head = new Node(new Node(nullptr, head), nullptr, *it1);
			Node* temp = head;
			++it1;
			++_size;
			while (it1 != it2)
			{
				temp->next = new Node(temp, nullptr, *it1);
				temp = temp->next;
				++it1;
				++_size;
			}
			tail = temp;
			tail->next = new Node(tail, nullptr);
		}
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::~list() {
		clear();
	}

	template<typename T, typename Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(const list<T, Allocator>& ls) {
		list<T, Allocator> list(ls.begin(), ls.end());
		swap(*this, list);
		return *this;
	}

	template<typename T, typename Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(list<T, Allocator>&& ls)noexcept {
		head = ls.head;
		tail = ls.tail;
		_size = ls._size;
		ls.head = nullptr;
		ls.tail = nullptr;
		ls._size = 0;
		return *this;
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::operator==(const list<T, Allocator>& ls)const {
		if (head == ls.head)return true;
		if (_size != ls.size())return false;
		list<T, Allocator>::iterator temp = begin();
		list<T, Allocator>::iterator temp2 = ls.begin();
		while (temp != end()) {
			if (*temp == *temp2) {
				++temp;
				++temp2;
				continue;
			}
			return false;
		}
		return true;
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::operator!=(const list<T, Allocator>& ls)const {
		return !(*this == ls);
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::operator>(const list<T, Allocator>& ls)const {
		return _size > ls.size();
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::operator<(const list<T, Allocator>& ls)const {
		return _size < ls.size();
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::operator>=(const list<T, Allocator>& ls)const {
		return (*this > ls || *this == ls);
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::operator<=(const list<T, Allocator>& ls)const {
		return (*this < ls || *this == ls);
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::empty()const {
		return !_size;
	}

	template<typename T, typename Allocator>
	auto list<T, Allocator>::max_size()const {
		Allocator A;
		return A.max_size();
	}

	template<typename T, typename Allocator>
	size_t list<T, Allocator>::size()const {
		return _size;
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::assign(size_t count, T elem) {
		list<T> ls(count, elem);
		this->clear();
		*this = std::move(ls);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::assign(list<T, Allocator>::iterator it1, list<T, Allocator>::iterator it2) {
		list<T>ls(it1, it2);
		this->clear();
		*this = std::move(ls);
	}

	template<typename T, typename Allocator>
	T& list<T, Allocator>::front()const {
		return head->value;
	}

	template<typename T, typename Allocator>
	T& list<T, Allocator>::back()const {
		return tail->value;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::begin()const {
		if (head) {
			typename list<T>::iterator it = head;
			return it;
		}
		return nullptr;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::end()const {
		if (head) {
			typename list<T>::iterator it = tail->next;
			return it;
		}
		return nullptr;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::const_iterator list<T, Allocator>::cbegin()const {
		if (head) {
			typename list<T>::const_iterator it = head;
			return it;
		}
		return nullptr;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::const_iterator list<T, Allocator>::cend()const {
		if (head) {
			typename list<T>::const_iterator it = tail->next;
			return it;
		}
		return nullptr;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rbegin()const {
		typename list<T>::reverse_iterator it = tail;
		return it;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rend()const {
		typename list<T>::reverse_iterator it = head->prev;
		return it;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::crbegin()const {
		list<T, Allocator>::const_iterator it = cend();
		return it;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::crend()const {
		list<T, Allocator>::const_iterator it = head->prev;
		return it;
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::push_back(const T& elem) {
		if (_size) {
			tail = tail->next;
			tail->value = elem;
			tail->next = new Node(tail, nullptr);
			++_size;
			return;
		}
		head = new Node(new Node(nullptr, head), new Node(head, nullptr), elem);
		tail = head;
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::push_front(const T& elem) {
		if (_size) {
			head = head->prev;
			head->value = elem;
			head->prev = new Node(nullptr, head);
			++_size;
			return;
		}
		head = new Node(new Node(nullptr, head), new Node(head, nullptr), elem);
		tail = head;
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::pop_back() {
		if (_size) {
			delete tail->next;
			tail->next = nullptr;
			tail = tail->prev;
			--_size;
		}
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::pop_front() {
		if (_size) {
			delete head->prev;
			head->prev = nullptr;
			head = head->next;
			--_size;
		}
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(typename list<T, Allocator>::iterator it1, const T& elem) {
		auto it = begin();
		Node* temp = nullptr;
		if (it1 == it) {
			head = head->prev;
			head->value = elem;
			head->prev = new Node(nullptr, head);
			++_size;
			return it;
		}
		else if (it1 == end()) {
			tail = tail->next;
			tail->value = elem;
			tail->next = new Node(tail, nullptr);
			++_size;
			return --end();
		}
		else {
			Node* h = it1.it;
			Node* temp = new Node(h->prev, h, elem);
			h->prev->next = temp;
			h->prev = temp;
			++_size;
			return it1;
		}
	}


	template<typename T, typename Allocator>
	void  list<T, Allocator>::insert(typename list<T, Allocator>::iterator it1, size_t size, const T& elem) {
		auto it = begin();
		list<T>temp(size, elem);
		if (it1 == it) {
			delete temp.head->prev;
			temp.head->prev = nullptr;
			Node* t = head->prev;
			head->prev = temp.tail;
			temp.tail->next = head;
			head = temp.head;
			head->prev = t;
			_size += temp._size;
		}
		else if (it1 == end()) {
			delete temp.head->prev;
			temp.head->prev = nullptr;
			Node* t = tail->next;
			tail->next = temp.head;
			temp.head->prev = tail;
			tail = temp.tail;
			tail->next = t;
			_size += temp._size;
		}
		else {
			if (size > 1) {
				delete temp.head->prev;
				temp.head->prev = nullptr;
				delete temp.head->prev;
				temp.head->prev = nullptr;
				Node* h = it1.it;
				h->prev->next = temp.head;
				temp.head->prev = h->prev;
				h->prev = temp.tail;
				temp.tail->next = h;
				_size += temp._size;
			}
			else insert(it1, elem);
		}
		temp.head = nullptr;
		temp.tail = nullptr;
	}

	template<typename T, typename Allocator>
	void  list<T, Allocator>::insert(typename list<T, Allocator>::iterator it, typename list<T, Allocator>::iterator it1, typename list<T, Allocator>::iterator it2) {
		auto _it = begin();
		list<T>temp(it1, it2);
		if (it == _it) {
			delete temp.tail->next;
			temp.tail->next = nullptr;
			Node* t = head->prev;
			head->prev = temp.tail;
			temp.tail->next = head;
			head = temp.head;
			head->prev = t;
			_size += temp._size;
		}
		else if (it == end()) {
			delete temp.head->prev;
			temp.head->prev = nullptr;
			Node* t = tail->next;
			tail->next = temp.head;
			temp.head->prev = tail;
			tail = temp.tail;
			tail->next = t;
			_size += temp._size;
		}
		else {
			delete temp.tail->next;
			temp.tail->next = nullptr;
			delete temp.head->prev;
			temp.head->prev = nullptr;
			Node* h = it.it;
			h->prev->next = temp.head;
			temp.head->prev = h->prev;
			h->prev = temp.tail;
			temp.tail->next = h;
			_size += temp._size;
		}
			temp.head = nullptr;
			temp.tail = nullptr;
	}

	template<typename T, typename Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::emplace(typename list<T, Allocator>::iterator it1,  T&& elem...) {
		T a(std::move(elem));
		return insert(it1, a);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::emplace_back(T&& elem...) {
		T a(std::move(elem));
		push_back(elem);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::emplace_front(T&& elem...) {
		T a(std::move(elem));
		push_front(elem);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::erase(iterator it1) {
		if (_size) {
			if (it1 == begin()) {
				if (_size == 1) {
					clear();
					return;
				}
				delete head->prev;
				head->prev = nullptr;
				head = head->next;
			}
			else if (it1 == --end()) {
				delete tail->next;
				tail->next = nullptr;
				tail = tail->prev;
			}
			else {
				Node* temp = it1.it;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
			}
			--_size;
		}
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::remove(const T& elem) {
		auto it = begin();
		auto en = end();
		while (it != en) {
			if (*it == elem) {			
				erase(it++);		
			}
			else ++it;
		}
	}

	template<typename T,typename Allocator>
	template<typename Predicat>
	void list<T, Allocator>::remove_if(Predicat p) {
		if (_size) {
			auto it = begin();
			while (it != end()) {
				if (_size) {
					if (p(*it)) {
						erase(it++);
					}
					else ++it;
				}
				else break;
			}
		}
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::clear() {
		if (_size){
			if(head)head = head->prev;
			while (head)
			{
				Node* temp = head;
				head = head->next;
				delete temp;
			}
			_size = 0;
			tail = nullptr;
		}
	}

	template <typename T, typename Allocator>
	void list<T, Allocator>::reverse() {
		auto it = rbegin();
		auto en = rend();
		list<T> ls(it, en);
		swap(*this, ls);
	}

	template <typename T, typename Allocator>
	void list<T, Allocator>::splice(typename list<T, Allocator>::iterator it, const list& ls) {
		if (!ls._size)return;
		if(_size) {
			insert(it, ls.begin(), ls.end());
		}
	}

	template <typename T, typename Allocator>
	void list<T, Allocator>::splice(typename list<T, Allocator>::iterator it, const list& ls, typename list<T, Allocator>::iterator it1) {
		if (!ls._size)return;
		if (_size) {
			insert(it, it1, ls.end());
		}
	}

	template <typename T, typename Allocator>
	void list<T, Allocator>::splice(typename list<T, Allocator>::iterator it,  typename list<T, Allocator>::iterator it1, typename list<T, Allocator>::iterator it2) {
		if (_size) {
			insert(it, it1, it2);
		}
	}

	template <typename T, typename Allocator>
	void list<T, Allocator>::unique() {
		//will be updated
	}

	template <typename T, typename Allocator>
	void list<T, Allocator>::merge(const list<T,Allocator>& ls) {
		//will be updated
	}


	template <typename T, typename Allocator>
	void list<T, Allocator>::sort() {
		//will be updated
	}

	template <typename T, typename Allocator>
	template <typename Predicat>
	void list<T, Allocator>::sort(Predicat p) {
		//will be updated
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::resize(size_t size) {
		if (!_size) {
			head = new Node(nullptr, nullptr);
			head->prev = new Node(nullptr, head);
			Node* temp = head;
			tail = head;
			++ _size;
			--size;
		}
		Node* temp=tail->next;
		while (size ) {
			tail->next = new Node(tail, nullptr);
			tail = tail->next;
			++_size;
			--size;
		}
		tail->next = temp;
		temp->prev = tail;
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::resize(size_t size,const T& value) {
		if (!_size) {
			head = new Node(nullptr, nullptr,value);
			head->prev = new Node(nullptr, head);
			Node* temp = head;
			tail = head;
			++_size;
			--size;
		}
		Node* temp = tail->next;
		while (size) {
			tail->next = new Node(tail, nullptr,value);
			tail = tail->next;
			++_size;
			--size;
		}
		tail->next = temp;
		temp->prev = tail;
	}
}
#endif  
