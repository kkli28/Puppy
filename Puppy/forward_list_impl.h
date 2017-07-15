#pragma once

#include "stdafx.h"
#include "forward_list.h"

namespace kkli {

	//���ƹ��캯��
	template<typename T>
	forward_list<T>::forward_list(const forward_list& fl) {
		if (fl.begin()) == fl.end()) return;

		//����head����Ϊ����ͷ�ڵ�
		Iter<T> it = *(fl.begin());
		head = it;

		//��Ӻ���Ԫ��
		for (auto iter = ++fl.begin(); iter != fl.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	//�ƶ����캯��
	template<typename T>
	forward_list<T>::forward_list(forward_list&& fl) {
		head = fl.head;
		fl.head = iterator();
	}

	//��ʼ���б���
	template<typename T>
	forward_list<T>::forward_list(std::initializer_list<T> il) {
		int size = il.size();
		if (size == 0) return;

		//����head
		auto it = *(il.begin());
		head = it;

		//��������ڵ�
		auto iter = il.begin();
		++iter;
		for (; iter != il.end(); ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	//����n��elem
	template<typename T>
	forward_list<T>::forward_list(int n, const T& elem) {
		if (n <= 0) return;

		//����head
		iterator it = elem;
		head = it;

		//��������ڵ�
		for (int i = 1; i < n; ++i) {
			it.get()->next = new Node<T>(elem);
			++it;
		}
	}

	//���ô����캯��
	template<typename T>
	forward_list<T>::forward_list(int n) :forward_list(n, T()) {}

	//ͨ����������Χ����
	template<typename T>
	forward_list<T>::forward_list(const iterator& beg, const iterator& end) {
		if (beg == end) return;

		//����head
		iterator it = *beg;
		head = it;

		//��������ڵ�
		auto iter = beg;
		++iter;
		for (; iter != end; ++iter) {
			it.get()->next = new Node<T>(*iter);
			++it;
		}
	}

	//��������
	template<typename T>
	forward_list<T>::~forward_list() {
		clear();
	}

	//���뵽forward_list�ײ�
	template<typename T>
	void forward_list<T>::push_front(const T& elem) {
		iterator iter = elem;
		iter.get()->next = head.get();
		head = iter;
	}

	//����forward_list�ײ��ڵ�
	template<typename T>
	void forward_list<T>::pop_front() {
		iterator iter = head;
		++head;
		delete iter.get();
	}

	//��begΪ�׽ڵ㣬endΪβ�ڵ��������뵽pos��
	template<typename T>
	void forward_list<T>::__insert(
		int pos, const iterator& beg, const iterator& end) {
		//�ҵ������
		int count = 0;
		auto iter = head;
		while (count != pos) {
			++iter;
			++count;
		}

		//����ʱ�������posλ��
		end.get()->next = iter.get()->next;
		iter.get()->next = beg.get();
		return beg
	}

	//����n��elem����posλ�ú�
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(int pos, int n, const T& elem) {
		if (n <= 0) return;
		iterator temp_beg = elem;					//��ʱ�����׽ڵ������
		iterator temp_end = temp_beg;				//��ʱ����β�ڵ������
		for (int i = 1; i < n; ++i) {
			temp_end.get()->next = new Node(elem);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return temp_beg;
	}

	//����1��elem����posλ�ýڵ�󣬵���insert_after(pos,n,elem)
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(int pos, const T& elem) {
		return insert_after(pos, 1, elem);
	}

	//��[beg,end)�е�Ԫ�ز��뵽posλ�ú�
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(
		int pos, const iterator& beg, const iterator& end) {
		if (beg == end) return;
		iterator temp_beg = *beg;				//��ʱ�����׽ڵ������
		iterator temp_end = temp_beg;			//��ʱ����β�ڵ������

		//ͨ��[beg,end)������ʱ����
		auto begin = beg;
		while (++begin != end) {
			temp_end.get()->next() = new Node<T>(*begin);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return it;
	}

	//��initializer_list�е�Ԫ�ز��뵽posλ�ú�
	template<typename T>
	forward_list<T>::iterator forward_list<T>::insert_after(
		int pos, std::initializer_list<T> elems) {
		int size = elems.size();
		if (size == 0) return;

		//�ȹ�����ʱ������Ԫ��
		iterator temp_beg = *(elems.begin());
		auto temp_end = temp_beg;

		//����ʣ��Ԫ��
		auto il_beg = elems.begin();
		auto il_end = elems.end();
		for (auto iter = ++il_beg; iter != il_end; ++iter) {
			temp_end.get()->next = new Node<T>(*iter);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return temp_beg;
	}

	//�Ƴ�posλ�ú�Ľڵ�
	template<typename T>
	void forward_list<T>::erase_after(int pos) {

		//�ҵ�posλ�õĽڵ�
		auto iter = head;
		int count = 0;
		while (count < pos) {
			++iter;
			++count;
		}

		//ɾ��posλ�õĽڵ�֮��Ľڵ�
		auto del = iter;
		++del;
		iter.get()->next = del.get()->next;
		delete del.get();
	}

	//�Ƴ�[beg,end)��ʶ��Χ�Ľڵ�
	template<typename T>
	void forward_list<T>::erase_after(const iterator& beg, const iterator& end) {
		if (head == beg) {
			head.get() = end.get();
		}
		else {
			auto iter = head;				//beg��ָ�ڵ��ǰһ���ڵ�
			auto next_iter = head;			//beg��ָ�ڵ�
			++next_iter;
			while (next_iter != beg) {
				++next_iter;
				++iter;
			}

			//��������[beg,end)��������
			iter.get()->next = end.get();
		}

		//ɾ��[beg,end)��ʶ�Ľڵ�
		auto iter = beg;
		while (iter != end) {
			auto del = iter;
			++iter;
			delete del.get();
		}
	}

	//�Ƴ�����������Ԫ��
	template<typename T>
	void forward_list<T>::remove_if(bool(*op)(const T& elem)) {
		if (head == end()) return;

		//ɾ���ײ��������������Ľڵ�
		auto end = end();
		while (head != end && op(*head)) {
			auto del = head;
			++head;
			delete del.get();
		}

		auto prev_iter = head;				//ѭ����������ǰһ��������
		auto iter = head;					//ѭ��������
		++iter;
		while (iter != end) {

			//�ҵ����������Ľڵ�
			if (op(*iter)) {
				auto del = iter;
				prev_iter.get()->next = iter.get()->next;
				++iter;						//������prev_iter
				delete del.get();
			}
			else {
				//��������������
				++iter;
				++prev_iter;
			}
		}
	}

	//�Ƴ�����ֵΪelem�Ľڵ�
	template<typename T>
	void forward_list<T>::remove(const T& elem) {
		remove_if(
			[&elem](const T& e) -> bool {return elem == e; }
		);
	}

	//���ô�С
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
		bool less_n = true;				//Ԫ�ظ���С��n
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

		//Ԫ�ظ���С��n������Ҫ���䵽n��
		if (less_n) {
			while (count < n) {
				prev_iter.get()->next = new Node<T>(elem);
				++prev_iter;
				++count;
			}
		}

		//Ԫ�ظ������ڵ���n����ֻ����ǰn��
		else {
			if (iter == end()) return;		//Ԫ�ظ����պ�Ϊn��

			//Ԫ�ظ�������n��
			else {
				while (iter != end) {
					auto del = iter;
					++iter;
					delete del.get();
				}
			}
		}
	}

	//���ô�С
	template<typename T>
	void forward_list<T>::resize(int n) {
		resize(n, T());
	}

	//�������
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

	//�����ã����������Ϣ
	template<typename T>
	void forward_list<T>::print()const {
		auto end = end();
		for (auto iter = head; iter != end; ++iter) {
			cout << *iter << " ";
		}
		cout << endl;
	}
}
