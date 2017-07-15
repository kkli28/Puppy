#pragma once

#include "stdafx.h"

//Node<T>
namespace kkli {

	//Node<T>
	template<typename T>
	class Node {
	public:

		//data
		T info;
		Node* next;

		//constructors
		Node() : T(), next(nullptr) {}
		Node(const T& i) : info(i), next(nullptr) {}
		Node(const Node& node) : info(node.info), next(node.next) {}
		Node(Node&& node) : info(node.info), next(node.next) {}

		//operator==
		bool operator==(const Node& node) {
			return (info == node.info && next == node.next);
		}
	};
}

//Iter<T>
namespace kkli{

	//Iter<T>
	template<typename T>
	class Iter {
	private:
		Node<T>* iter;

		//不允许误用，故为private
		Iter(Node<T>* ptr) : iter(ptr) {}

	public:
		//constructors
		Iter() : iter(nullptr) {}
		Iter(const T& t) : iter(new Node<T>(t)) {}
		Iter(const Iter& it) :iter(it.iter) {}

		//get
		Node<T>* get()const { return iter; }

		//operator=
		Iter& operator=(const Iter& it) {
			iter = it.iter;
			return *this;
		}

		//operator++
		Iter& operator++() {
			iter = iter->next;
			return *this;
		}

		//operator++(int)
		Iter operator++(int) {
			Iter it = iter;
			iter = iter->next;
			return it;
		}

		//operator==
		bool operator==(const Iter& it) {
			return iter == it.iter;
		}

		//operator!=
		bool operator!=(const Iter& it) {
			return !(*this == it);
		}

		//operator*
		T& operator*() { return iter->info; }
		T operator*()const { return iter->info; }
	};
}

//forward_list<T>
namespace kkli {

	//forward_list<T>
	template<typename T>
	class forward_list {
	public:

		//typedefs
		typedef T						value_type;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef Node<T>*				pointer;
		typedef const Node<T>*			const_pointer;
		typedef Iter<T>					iterator;
		typedef const iterator			const_iterator;
		typedef std::forward_iterator_tag	iterator_category;

	private:
		//forward_list's head
		iterator head;

		//将beg为首节点，end为尾节点的链表插入到pos后
		void __insert(int pos, const_iterator& beg, const_iterator& end);
	public:

		//constructors
		forward_list() :head() {}									//空
		forward_list(const forward_list& fl);						//复制构造
		forward_list(forward_list&& fl);							//移动构造
		forward_list(std::initializer_list<T> il);					//初始列构造
		forward_list(int n);										//n个默认初始化的元素
		forward_list(int n, const T& elem);							//n个用t初始化的元素
		forward_list(const_iterator& beg, const_iterator& end);		//通过迭代器范围构造
		~forward_list();											//析构

		//begin / cbegin
		iterator begin()const { return head; }
		const_iterator cbegin()const { return head; }

		//end / cend
		iterator end() const { return iterator(); }
		const_iterator cend()const { return iterator(); }

		//push_front / pop_front
		void push_front(const T& elem);
		void pop_front();

		
		//insert_after
		iterator insert_after(int pos, const T& elem);
		iterator insert_after(int pos, int n, const T& elem);
		iterator insert_after(int pos, const_iterator& beg, const_iterator& end);
		iterator insert_after(int pos, std::initializer_list<T> elems);

		//erase_after
		void erase_after(int pos);
		void erase_after(const_iterator& beg, const_iterator& end);

		//remove
		void remove(const T& elem);

		//remove_if
		void remove_if(bool(*op)(const T& elem));

		//resize
		void resize(int n);
		void resize(int n, const T& elem);

		//clear
		void clear();

		//empty
		bool empty()const { return head.get()->next == nullptr; }

		//operators
		bool operator==	(const forward_list<T>& fl)const;
		bool operator!=	(const forward_list<T>& fl)const;
		bool operator<	(const forward_list<T>& fl)const;
		bool operator>	(const forward_list<T>& fl)const;
		bool operator<=	(const forward_list<T>& fl)const;
		bool operator>=	(const forward_list<T>& fl)const;

		//assign
		void assign(int n, const T& elem);
		void assign(const_iterator& beg, const_iterator& end);

		//swap
		void swap(const forward_list<T>& fl);

		//TEST: print all elements
		void print()const;
	};

	//swap，非成员函数
	template<typename T>
	void swap(const forward_list<T>& lhs, const forward_list<T>& rhs);

	//forward_list 的实现文件
#include "forward_list_impl.h"

}