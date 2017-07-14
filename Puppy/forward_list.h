#pragma once
#include "stdafx.h"

namespace kkli {

	//Node<T>
	template<typename T>
	struct Node {
		T info;
		Node* next;
		Node() :T(), next(nullptr) {}
		Node(T&& i) :info(i), next(nullptr) {}
		bool operator==(const Node& node) {
			return (info == node.info && next == node.next);
		}
	};

	//forward_list<T>
	template<typename T>
	class forward_list {
	private:

		//iterator
		class Iter {
		private:
			Node<T>* iter;
		public:

			//Iter
			Iter() :iter(nullptr) {}
			Iter(Node<T>* ptr) :iter(ptr) {}
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
				iterator it = iter;
				iter = iter->next;
				return it;
			}

			//operator ==
			bool operator==(const Iter& it) { return iter == it.iter; }

			//operator !=
			bool operator!=(const Iter& it) { return !(*this == it); }

			//operator *
			T& operator*() { return (*iter).info; }

			//operator *, for const iterator
			T operator*() const { return (*iter).info; }
		};

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

		typedef Iter				iterator;
		typedef const iterator		const_iterator;

	private:

		//head iterator
		const_iterator head;

	public:
		forward_list() :head() {}
		forward_list(const forward_list& fl);
		forward_list(std::initializer_list<T> il);

		//begin
		Iter begin() { return head; }

		//end
		Iter end() { return Iter(); }

		//TEST: print
		void print()const {
			for (auto iter = head; iter != Iter(); ++iter) {
				cout << iter->info << " ";
			}
			cout << endl;
		}
	};
}

template<typename T>
forward_list<T>::forward_list(const forward_list& fl) {
	if (fl.begin() == fl.end()) return;
	head = new Node<T>(*(fl.begin()));
	auto it = head;
	//TODO: 如何让forward_list支持范围for语句？
	for (auto iter = ++fl.begin(); iter != fl.end(); ++iter) {
		*it = new Node<T>(*iter);
		++it;
	}
}

template<typename T>
forward_list<T>::forward_list(std::initializer_list<T> il) {
	int size = il.size();
	if (size == 0) return;
	head = new Node<T>(*(il.begin()));
	auto it = head;
	for (auto iter = ++il.begin(); iter != il.end(); ++iter) {
		*it = new Node<T>(*iter);
		++it;
	}
}