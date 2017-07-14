#pragma once

#include "stdafx.h"
#include "forward_list.h"

namespace kkli {

	template<typename T>
	forward_list<T>::forward_list(const forward_list& fl) {
		if (fl.begin()) == fl.end()) return;

		//设置head，因为不带头节点
		Iter<T> it = *(fl.begin());
		head = it;

		//添加后续元素
		for (auto iter = ++fl.begin(); iter != fl.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	template<typename T>
	forward_list<T>::forward_list(forward_list&& fl) {
		head = fl.head;
		fl.head = iterator();
	}

	template<typename T>
	forward_list<T>::forward_list(std::initializer_list<T> il) {
		int size = il.size();
		if (size == 0) return;
		auto it = *(il.begin());
		head = it;

		auto iter = il.begin();
		++iter;
		for (; iter != il.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	template<typename T>
	forward_list<T>::forward_list(int n, const T& elem) {
		if (n <= 0) return;
		iterator it = elem;
		head = it;

		for (int i = 1; i < n; ++i) {
			it.get()->next = new Node<T>(elem);
			++it;
		}
	}

	template<typename T>
	forward_list<T>::forward_list(int n) :forward_list(n, T()) {}

	template<typename T>
	forward_list<T>::forward_list(const iterator& beg, const iterator& end) {
		if (beg == end) return;
		iterator it = *beg;
		head = it;
		
		auto iter = beg;
		++iter;
		for (; iter != end; ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	template<typename T>
	forward_list<T>::~forward_list() {
		auto end = end();
		while (head != end) {
			auto iter = head;
			++head;
			delete iter.get();
		}
	}

	template<typename T>
	void forward_list<T>::push_front(const T& elem) {
		iterator iter = elem;
		iter.get()->next = head.get();
		head = iter;
	}

	template<typename T>
	void forward_list<T>::pop_front() {
		iterator iter = head;
		++head;
		delete iter.get();
	}

	/////////////////////////////////////////////////
	// TODO: insert_after
	/////////////////////////////////////////////////

	template<typename T>
	void forward_list<T>::print()const {
		auto end = end();
		for (auto iter = head; iter != end; ++iter) {
			cout << *iter << " ";
		}
		cout << endl;
	}
}