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

		//创建头节点，并设置好next与prev
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
		iterator insert(const_iterator pos, const value_type& value);
		iterator insert(const_iterator pos, value_type&& value);
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		iterator insert(const_iterator pos, std::initializer_list<value_Type> il);

		/*
		//不想写emplace相关函数
		template<typename... Args>
		iterator emplace(const_iterator pos, Args&&... args);

		template<typename... Args>
		void emplace_back(Args&&... args);

		template<typename... Args>
		void emplace_front(Args&&... args);
		*/

		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);
		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back();
		void push_front(const value_type& value);
		void push_front(value_type&& value);
		void pop_front();
		void resize(size_type count, const value_type& value);
		void resize(size_type count) { resize(count, value_type()); }
		void swap(list& rhs);			//别忘了非成员函数 swap
	};
}

//================================================================================
// list<T> 成员函数定义
//================================================================================
namespace kkli {
	
	//create_head_node
	template<typename T>
	void list<T>::create_head_node() {
		__head = iterator(value_type());	//头节点
		__head->next = __head.get();
		__head->prev = __head.get();
	}

	// list(count, value)
	template<typename T>
	list<T>::list(size_type count, const value_type& value) {
		if (count == 0) return;
		create_head_node();
		for (size_type i = 1; i < count; ++i)
			this->
	}
}