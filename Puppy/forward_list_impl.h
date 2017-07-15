#pragma once

#include "stdafx.h"
#include "forward_list.h"

namespace kkli {

	//复制构造函数
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

	//移动构造函数
	template<typename T>
	forward_list<T>::forward_list(forward_list&& fl) {
		head = fl.head;
		fl.head = iterator();
	}

	//初始化列表构造
	template<typename T>
	forward_list<T>::forward_list(std::initializer_list<T> il) {
		int size = il.size();
		if (size == 0) return;

		//构造head
		auto it = *(il.begin());
		head = it;

		//构造后续节点
		auto iter = il.begin();
		++iter;
		for (; iter != il.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	//构造n个elem
	template<typename T>
	forward_list<T>::forward_list(int n, const T& elem) {
		if (n <= 0) return;

		//构造head
		iterator it = elem;
		head = it;

		//构造后续节点
		for (int i = 1; i < n; ++i) {
			it.get()->next = new Node<T>(elem);
			++it;
		}
	}

	//调用代理构造函数
	template<typename T>
	forward_list<T>::forward_list(int n) :forward_list(n, T()) {}

	//通过迭代器范围构造
	template<typename T>
	forward_list<T>::forward_list(const iterator& beg, const iterator& end) {
		if (beg == end) return;

		//构造head
		iterator it = *beg;
		head = it;

		//构造后续节点
		auto iter = beg;
		++iter;
		for (; iter != end; ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	//析构函数
	template<typename T>
	forward_list<T>::~forward_list() {
		clear();
	}

	//插入到forward_list首部
	template<typename T>
	void forward_list<T>::push_front(const T& elem) {
		iterator iter = elem;
		iter.get()->next = head.get();
		head = iter;
	}

	//弹出forward_list首部节点
	template<typename T>
	void forward_list<T>::pop_front() {
		iterator iter = head;
		++head;
		delete iter.get();
	}

	//将beg为首节点，end为尾节点的链表插入到pos后
	template<typename T>
	void forward_list<T>::__insert(
		int pos, const iterator& beg, const iterator& end) {
		//找到插入点
		int count = 0;
		auto iter = head;
		while (count != pos) {
			++iter;
			++count;
		}

		//将临时链表插入pos位置
		end.get()->next = iter.get()->next;
		iter.get()->next = beg.get();
		return beg
	}

	//插入n个elem到第pos位置后
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(int pos, int n, const T& elem) {
		if (n <= 0) return;
		iterator temp_beg = elem;					//临时链表首节点迭代器
		iterator temp_end = temp_beg;				//临时链表尾节点迭代器
		for (int i = 1; i < n; ++i) {
			temp_end.get()->next = new Node(elem);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return temp_beg;
	}

	//插入1个elem到第pos位置节点后，调用insert_after(pos,n,elem)
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(int pos, const T& elem) {
		return insert_after(pos, 1, elem);
	}

	//将[beg,end)中的元素插入到pos位置后
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(
		int pos, const iterator& beg, const iterator& end) {
		if (beg == end) return;
		iterator temp_beg = *beg;				//临时链表首节点迭代器
		iterator temp_end = temp_beg;			//临时链表尾节点迭代器

		//通过[beg,end)构造临时链表
		auto begin = beg;
		while (++begin != end) {
			temp_end.get()->next() = new Node<T>(*begin);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return it;
	}

	//将initializer_list中的元素插入到pos位置后
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(
		int pos, std::initializer_list<T> elems) {
		int size = elems.size();
		if (size == 0) return;

		//先构造临时链表首元素
		iterator temp_beg = *(elems.begin());
		auto temp_end = temp_beg;

		//构造剩余元素
		auto il_beg = elems.begin();
		auto il_end = elems.end();
		for (auto iter = ++il_beg; iter != il_end; ++iter) {
			temp_end.get()->next = new Node<T>(*iter);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return temp_beg;
	}

	//移除pos位置后的节点
	template<typename T>
	void forward_list<T>::erase_after(int pos) {

		//找到pos位置的节点
		auto iter = head;
		int count = 0;
		while (count < pos) {
			++iter;
			++count;
		}

		//删除pos位置的节点之后的节点
		auto del = iter;
		++del;
		iter.get()->next = del.get()->next;
		delete del.get();
	}

	//移除[beg,end)标识范围的节点
	template<typename T>
	void forward_list<T>::erase_after(const iterator& beg, const iterator& end) {
		if (head == beg) {
			head.get() = end.get();
		}
		else {
			auto iter = head;				//beg所指节点的前一个节点
			auto next_iter = head;			//beg所指节点
			++next_iter;
			while (next_iter != beg) {
				++next_iter;
				++iter;
			}

			//链表跳过[beg,end)重新连接
			iter.get()->next = end.get();
		}

		//删除[beg,end)标识的节点
		auto iter = beg;
		while (iter != end) {
			auto del = iter;
			++iter;
			delete del.get();
		}
	}

	//移除满足条件的元素
	template<typename T>
	void forward_list<T>::remove_if(bool(*op)(const T& elem)) {
		if (head == end()) return;

		//删除首部所有满足条件的节点
		auto end = end();
		while (head != end && op(*head)) {
			auto del = head;
			++head;
			delete del.get();
		}

		auto prev_iter = head;				//循环迭代器的前一个迭代器
		auto iter = head;					//循环迭代器
		++iter;
		while (iter != end) {

			//找到满足条件的节点
			if (op(*iter)) {
				auto del = iter;
				prev_iter.get()->next = iter.get()->next;
				++iter;						//不递增prev_iter
				delete del.get();
			}
			else {
				//递增两个迭代器
				++iter;
				++prev_iter;
			}
		}
	}

	//移除所有值为elem的节点
	template<typename T>
	void forward_list<T>::remove(const T& elem) {
		remove_if(
			[&elem](const T& e) -> bool {return elem == e; }
		);
	}

	//重置大小
	template<typename T>
	void forward_list<T>::resize(int n, const T& elem) {
		auto end = end();
		if (n == 0) {
			clear();
			return;
		}

		int count = 0;
		auto iter = head;
		auto prev_iter = iter;

		++iter;
		++count;
		bool less_n = true;				//元素个数小于n
		if (count != n) {
			while (iter != end) {
				++iter;
				++prev_iter;
				++count;
				if (count == n) {
					less_n = false;
					break;
				}
			}
		}

		//元素个数小于n个，需要补充到n个
		if (less_n) {
			while (count < n) {
				prev_iter.get()->next = new Node<T>(elem);
				++prev_iter;
				++count;
			}
		}

		//元素个数大于等于n个，只保留前n个
		else {
			if (iter == end()) return;		//元素个数刚好为n个

			//元素个数大于n个
			else {
				while (iter != end) {
					auto del = iter;
					++iter;
					delete del.get();
				}
			}
		}
	}

	//重置大小
	template<typename T>
	void forward_list<T>::resize(int n) {
		resize(n, T());
	}

	//清空链表
	template<typename T>
	void forward_list<T>::clear() {
		auto end = end();

		auto iter = head;
		head = end;
		while (iter != end) {
			auto del = iter;
			++iter;
			delete del.get();
		}
	}

	//测试用：输出链表信息
	template<typename T>
	void forward_list<T>::print()const {
		auto end = end();
		for (auto iter = head; iter != end; ++iter) {
			cout << *iter << " ";
		}
		cout << endl;
	}
}
