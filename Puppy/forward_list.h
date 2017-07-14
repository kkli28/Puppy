#pragma once
#include "stdafx.h"

namespace kkli {

	//Node<T>
	template<typename T>
	struct Node {
		T info;
		Node* next;
		Node() :T(), next(nullptr) {}
		Node(const T& i) :info(i), next(nullptr) {}
		Node(T&& i) :info(i), next(nullptr) {}
		bool operator==(const Node& node) {
			return (info == node.info && next == node.next);
		}
	};

	//iterator
	template<typename T>
	class Iter {
	private:
		Node<T>* iter;
		Iter(Node<T>* ptr) :iter(ptr) {}
	public:
		/*
		暂时不能与STL兼容
		typedef std::forward_iterator_tag	iterator_category;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef const reference		const_refernece;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		*/

		//Iter
		Iter() :iter(nullptr) {}
		Iter(const T& t) :iter(new Node<T>(t)) {}
		Iter(const Iter& it) :iter(it.iter) {}

		//operator =
		Iter& operator=(const Iter& it) {
			iter = it.iter;
			return *this;
		}

		//operator ++
		Iter& operator++() {
			iter = iter->next;
			return *this;
		}

		//operator ++(int)
		Iter operator++(int) {
			Iter it = iter;
			iter = iter->next;
			return it;
		}

		Node<T>* get()const { return iter; }

		//operator ==
		bool operator==(const Iter& it) { return iter == it.iter; }

		//operator !=
		bool operator!=(const Iter& it) { return !(*this == it); }

		//operator *
		T& operator*() { return (*iter).info; }

		//operator *, for const iterator
		T operator*() const { return (*iter).info; }
	};

	//forward_list<T>
	template<typename T>
	class forward_list {
	public:

		//typedefs
		typedef T					value_type;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;

		//TODO: pointer? const_pointer?
		typedef Node<T>*			pointer;
		typedef const Node<T>*		const_pointer;

		typedef Iter<T>				iterator;
		typedef const iterator		const_iterator;

	private:

		//head iterator
		iterator head;

	public:
		forward_list() : head() {}
		forward_list(const forward_list& fl);
		forward_list(std::initializer_list<T> il);

		//begin
		Iter<T> begin() const { return head; }

		//end
		Iter<T> end() const { return Iter<T>(); }

		//TEST: print
		void print()const;
	};

	//constructor
	template<typename T>
	forward_list<T>::forward_list(const forward_list& fl) {
		if (fl.begin() == fl.end()) return;
		Iter<T> it = *(fl.begin());
		head = it;
		Iter<T> iter = ++fl.begin();
		//TODO: 如何让forward_list支持范围for语句？
		for (; iter != fl.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	template<typename T>
	forward_list<T>::forward_list(std::initializer_list<T> il) {
		int size = il.size();
		if (size == 0) return;
		Iter<T> it = *(il.begin());
		head = it;

		auto iter = il.begin();
		++iter;
		for (; iter != il.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	//print
	template<typename T>
	void forward_list<T>::print()const {
		for (Iter<T> iter = head; iter != Iter<T>(); ++iter) {
			cout << *iter << " ";
		}
		cout << endl;
	}
}
