#pragma once

#include "stdafx.h"

//================================================================================
// list_node<T> 类定义
//================================================================================
namespace kkli {
	
	template<typename T>
	class list_node {
	public:
		T value;
		T* next;
		T* prev;

		//constructor
		list_node() :value(T()), next(nullptr), prev(nullptr) {}
		list_node(const T& val) :value(val), next(nullptr), prev(nullptr) {}
		list_node(T&& val) :value(val), next(nullptr), prev(nullptr) {}
		list_node(const list_node& rhs) :value(rhs.value), next(rhs.next), prev(rhs.prev) {}
		list_node(list_node&& rhs) :value(std::move(rhs.value)), next(rhs.next), prev(rhs.prev) {}
		
		//operator =
		list_node& operator=(const list_node& rhs) = default;
		list_node& operator=(list_node&& rhs) {
			value = std::move(rhs.value);
			next = rhs.next;
			prev = rhs.prev;
			return *this;
		}

		//operator ==
		bool operator==(const forward_list& rhs) {
			return (value == rhs.value && next == rhs.next && prev == rhs.prev);
		}
	};
}

//================================================================================
// list<T> 类定义
//================================================================================
namespace kkli {

	template<typename T>
	class list {
	private:

		//iterator: __iterator
		class __iterator {
		private:
			list_node<T>* iter;

			//不允许外部使用
			__iterator(list_node<T>* ptr) :iter(ptr) {}
		public:
			//constructor
			__iterator() = default;
			__iterator(const T& t) :iter(new list_node<T>(t)) {}
			__iterator(const __iterator& it) :iter(it.iter) {}

			//operator =
			__iterator& operator=(const __iterator& it) = default;

			//get
			list_node<T>* get()const { return iter; }

			//operator ++
			__iterator& operator++() {
				iter = iter->next;
				return *this;
			}

			//operator ++(int)
			__iterator operator++(int) {
				__iterator it(iter);
				iter = iter->next;
				return it;
			}

			//operator ==
			bool operator==(const __iterator& rhs)const {
				return iter == it.iter;
			}

			//operator !=
			bool operator!=(const __iterator& rhs)const {
				return !(*this == it);
			}

			//operator *
			T&  operator*() { return iter->value; }
			T operator*()const { return iter->value; }

			//operator ->
			list_node<T>* operator->() { return iter; }
			const list_node<T>* operator->()const { return iter; }
		};

	public:
		//typedefs
		typedef	T							value_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef __iterator					iterator;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef std::forward_iterator_tag	iterator_category;

		//************************************************************
		// WRONG! const_iterator应该实现为指向常量的指针，而不是常量指针
		//************************************************************
		//typedef const iterator				const_iterator;
		typedef __iterator						const_iterator;

	private:
		iterator __head;		//头节点指针
		size_type __size;		//链表有效长度

		//创建头节点，设置__size为0，并设置好__head的next与prev
		void create_head_node();
	public:
		//constructor
		list() { create_head_node(); }
		list(size_type count, const value_type& value);
		list(size_type count) :list(count, value_type()) {}
		list(const list& rhs);
		list(list&& rhs);
		list(std::initializer_list<T> il);

		/*
		//需要SFINAE，暂时不会，故没有实现该构造函数
		template< class InputIt >
		list(InputIt first, InputIt last, const Allocator& alloc = Allocator());
		*/

		//destructor
		~list();

		//operator =
		list& operator=(const list& rhs);
		list& operator=(list&& rhs);

		//其他成员函数
		std::allocator<T> get_allocator()const { return std::allocator<T>(); }
		void assign(size_type count, const value_type& value);
		void assign(std::initializer_list<T> il);
		reference front() { return __head->next->value; }
		const_reference front()const { return __head->next->value; }
		reference back() { return __head->prev->value; }
		const_reference back()const { return __head->prev->value; }
		iterator begin() { return ++iterator(__head); }
		const_iterator cbegin()const { return ++iterator(__head); }
		iterator end() { return __head; }
		const_iterator cend()const { return __head; }
		bool empty()const { return __head->next == __head->prev; }
		size_type size()const { return __size; }
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }
		void clear();
		iterator insert(iterator pos, value_type&& value);
		iterator insert(iterator pos, size_type count, const value_type& value);
		iterator insert(iterator pos, const value_type& value) {
			return insert(pos, 1, value);
		}
		iterator insert(iterator pos, std::initializer_list<value_type> il);

		/*
		//不想写emplace相关函数
		template<typename... Args>
		iterator emplace(const_iterator pos, Args&&... args);

		template<typename... Args>
		void emplace_back(Args&&... args);

		template<typename... Args>
		void emplace_front(Args&&... args);
		*/

		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back();
		void push_front(const value_type& value);
		void push_front(value_type&& value);
		void pop_front();
		void resize(size_type count, const value_type& value);
		void resize(size_type count) { resize(count, value_type()); }
		void swap(list& rhs);

		void merge(list&& rhs);

		template<typename Compare>
		void merge(list&& rhs, Compare comp);

		void splice(const_iterator pos, list&& rhs);
		void splice(const_iterator pos, list&& rhs, const_iterator it);
		void splice(const_iterator pos, list&& rhs, const_iterator first, const_iterator last);

		template<typename UnaryPredicate>
		void remove_if(UnaryPredicate pred);
		void remove(const value_type& value) {
			remove_if([&value](const value_type& val) -> {return val == value; });
		}

		void reverse();
		
		template<typename BinaryPredicate>
		void unique(BinaryPredicate pred);
		void unique() { unique(std::equal<T>()); }

		template<class Compare>
		void sort(Compare comp);
		void sort() { sort(std::less<T>()); }
	};
}

//================================================================================
// list<T> 成员函数定义
//================================================================================
namespace kkli {
	
	//create_head_node()
	template<typename T>
	void list<T>::create_head_node() {
		__head = iterator(value_type());	//头节点
		__head->next = __head.get();
		__head->prev = __head.get();
		__size = 0;
	}

	// list(count, value)
	template<typename T>
	list<T>::list(size_type count, const value_type& value) {
		if (count == 0) return;
		create_head_node();			//创建头节点，不算入有效节点
		for (size_type i = 0; i < count; ++i)
			push_back(value);
	}

	//list(rhs)
	template<typename T>
	list<T>::list(const list& rhs) {
		create_head_node();
		for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
			push_back(*iter);
	}

	//list(&&rhs)
	template<typename T>
	list<T>::list(list&& rhs) {
		__head = rhs.__head;
		__size = rhs.__size;
		rhs.__head = iterator();
	}

	//list(il)
	template<typename T>
	list<T>::list(std::initializer_list<T> il) {
		create_head_node();
		for (auto iter = il.begin(); iter != il.end(); ++iter)
			push_back(*iter);
	}

	//~list()
	template<typename T>
	list<T>::~list() {
		clear();				//清空有效节点
		delete __head.get();	//删除头节点
	}

	//operator =
	template<typename T>
	list<T>& list<T>::operator=(const list& rhs) {
		if (this == &rhs) return *this;				//避免自我赋值
		clear();									//清空原有节点（保留头节点）
		for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
			push_back(*iter);
	}

	template<typename T>
	list<T>& list<T>::operator=(list&& rhs) {
		if (this == &rhs) return *this;				//避免自我赋值
		clear();									//清空原有节点（保留头节点）
		__head = rhs.__head;			//窃取

		rhs.__head = iterator();		//无奈，大哭
		rhs.__size = 0;
	}

	//assgin(count, value)
	template<typename T>
	void list<T>::assign(size_type count, const value_type& value) {
		clear();
		for (size_type i = 0; i < count; ++i)
			push_back(value);
	}

	template<typename T>
	void list<T>::assign(std::initializer_list<value_type> il) {
		clear();
		for (auto iter = il.begin(); iter != il.end(); ++iter)
			push_back(*iter);
	}

	//insert(pos, &&value)
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, value_type&& value) {
		list_node<T>* node=new list_node<T>(std::move(value));			//加std::move()是否多余？
		node->next = pos->next;
		node->prev = pos.get();
		pos->next = node;
		node->next->prev = node;
		++__size;	//差点忘了
	}

	//insert(pos, count, value)
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, size_type count, const value_type& value) {
		list_node<T>* head_node = new list_node<T>();

		//创建由count个值为value的节点链
		list_node<T>* ptr = head_node;
		size_type size = 0;
		for (size_type i = 0; i < count; ++i) {
			ptr->next = new list_node<T>(value);
			ptr->next->prev = ptr;
			ptr = ptr->next;
			head_node->prev = ptr;			//head_node->prev时刻指向末尾节点
			++size;
		}

		//将节点链插入到pos位置
		head_node->next->prev = pos;
		head_node->prev->next = pos->next;
		pos->next->prev = head_node->prev;
		pos->next = head_node->next;
		delete head_node;
		__size += size;		//差点忘了

		return pos;
	}

	//insert(pos, il)
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, std::initializer_list<value_type> il) {
		list_node<T>* head_node = new list_node<T>();

		//创建由count个值为value的节点链
		list_node<T>* ptr = head_node;
		size_type size = 0;
		for (auto iter = il.begin(); iter != il.end(); ++iter) {
			ptr->next = new list_node<T>(*iter);
			ptr->next->prev = ptr;
			ptr = ptr->next;
			head_node->prev = ptr;
			++size;
		}

		//将节点链插入到pos位置
		head_node->next->prev = pos;
		head_node->prev->next = pos->next;
		pos->next->prev = head_node->prev;
		pos->next = head_node->next;
		delete head_node;
		__size += size;			//差点忘了

		return pos;
	}

	//erase(pos)
	template<typename T>
	typename list<T>::iterator list<T>::erase(iterator pos) {
		auto iter = pos;
		pos->next = pos->next->next;
		pos->next->prev = pos;
		delete iter;
		--__size;

		return pos;
	}

	//erase(first, last)
	template<typename T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
		for (auto iter = first; iter != last; ++iter) {
			erase(iter);
			--__size;
		}
		return first;
	}

	//push_back(value)
	template<typename T>
	void list<T>::push_back(const value_type& value) {
		list_node<T>* node = new list_node<T>(value);
		node->next = __head;
		node->prev = __head->prev;
		__head->prev->next = node;
		__head->prev = node;
		++__size;
	}

	//push_back(&&value)
	template<typename T>
	void list<T>::push_back(value_type&& value) {
		list_node<T>* node = new list_node<T>(std::move(value));
		node->next = __head;
		node->prev = __head->prev;
		__head->prev->next = node;
		__head->prev = node;
		++__size;
	}

	//pop_back()
	template<typename T>
	void list<T>::pop_back() {
		list_node<T>* del_ptr = __head->prev;
		__head->prev = __head->prev->prev;
		__head->prev->next = __head.get();
		--__size;
		delete del_ptr;
	}

	//push_front(value)
	template<typename T>
	void list<T>::push_front(const value_type& value) {
		list_node<T>* node = new list_node(value);
		node->next = __head->next;
		node->prev = __head.get();
		__head->next->prev = node;
		__head->next = node;
		++__size;
	}

	//push_front(&&value)
	template<typename T>
	void list<T>::push_front(value_type&& value) {
		list_node<T>* node = new list_node(std::move(value));
		node->next = __head->next;
		node->prev = __head.get();
		__head->next->prev = node;
		__head->next = node;
		++__size;
	}

	//pop_front()
	template<typename T>
	void list<T>::pop_front() {
		list_node<T>* del_ptr = __head->next;
		__head->next = __head->next->next;
		__head->next->prev = __head.get();
		--__size;
		delete del_ptr;
	}

	//resize(count, value)
	template<typename T>
	void list<T>::resize(size_type count, const value_type& value) {
		//TODO: 
	}

	//clear()
	template<typename T>
	void list<T>::clear() {
		__head->prev->next = nullptr;			//末尾节点的next置空，作为循环结束条件

		//删除非__head的所有节点
		auto ptr = __head->next;
		while (ptr != nullptr) {
			auto del_ptr = ptr;
			ptr = ptr->next;
			delete del_ptr;
		}

		//__head的next和prev都指向自身
		__head->next = __head.get();
		__head->prev = __head->next;
		__size = 0;
	}
}

//================================================================================
// list<T> 非成员函数定义
//================================================================================
namespace kkli {

	//operator ==
	template<typename T>
	bool operator==(const list<T>& lhs, const list<T>& rhs) {
		//TODO: 
	}

	//operator !=
	template<typename T>
	bool operator!=(const list<T>& lhs, const list<T>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T>
	bool operator< (const list<T>& lhs, const list<T>& rhs) {
		//TODO: 
	}

	//operator >
	template<typename T>
	bool operator> (const list<T>& lhs, const list<T>& rhs) {
		//TODO: 
	}

	//operator <=
	template<typename T>
	bool operator<=(const list<T>& lhs, const list<T>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T>
	bool operator>=(const list<T>& lhs, const list<T>& rhs) {
		return !(lhs < rhs);
	}

	//非成员版本 swap
	template<typename T>
	void swap(list<T>& lhs, list<T>& rhs) { lhs.swap(rhs); }
}