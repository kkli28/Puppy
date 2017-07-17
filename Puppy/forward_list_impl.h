#pragma once

#include "stdafx.h"
#include "forward_list.h"

namespace kkli {

	template<typename T>
	class forward_list {
	public:
		//���ƹ��캯��
		forward_list(const forward_list& fl) {
			if (fl.begin() == fl.end()) return;

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
		forward_list(forward_list&& fl) {
			head = fl.head;
			fl.head = iterator();
		}

		//��ʼ���б���
		forward_list(std::initializer_list<T> il) {
			auto size = il.size();
			if (size == 0) return;

			//����head
			iterator it = *(il.begin());
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
		forward_list(int n, const T& elem) {
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
		forward_list(int n) :forward_list(n, T()) {}

		//ͨ����������Χ����
		forward_list(const_iterator& beg, const_iterator& end) {
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
			int pos, const_iterator& beg, const_iterator& end) {
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
		}

		//����n��elem����posλ�ú�
		template<typename T>
		typename forward_list<T>::iterator forward_list<T>::insert_after(int pos, int n, const T& elem) {
			if (n <= 0) return iterator();
			iterator temp_beg = elem;					//��ʱ�����׽ڵ������
			iterator temp_end = temp_beg;				//��ʱ����β�ڵ������
			for (int i = 1; i < n; ++i) {
				temp_end.get()->next = new Node<T>(elem);
				++temp_end;
			}

			__insert(pos, temp_beg, temp_end);
			return temp_beg;
		}

		//����1��elem����posλ�ýڵ�󣬵���insert_after(pos,n,elem)
		template<typename T>
		typename forward_list<T>::iterator forward_list<T>::insert_after(int pos, const T& elem) {
			return insert_after(pos, 1, elem);
		}

		//��[beg,end)�е�Ԫ�ز��뵽posλ�ú�
		template<typename T>
		typename forward_list<T>::iterator forward_list<T>::insert_after(
			int pos, const_iterator& beg, const_iterator& end) {
			if (beg == end) return beg;
			iterator temp_beg = *beg;				//��ʱ�����׽ڵ������
			iterator temp_end = temp_beg;			//��ʱ����β�ڵ������

													//ͨ��[beg,end)������ʱ����
			auto begin = beg;
			while (++begin != end) {
				temp_end.get()->next = new Node<T>(*begin);
				++temp_end;
			}

			__insert(pos, temp_beg, temp_end);
			return temp_beg;
		}

		//��initializer_list�е�Ԫ�ز��뵽posλ�ú�
		template<typename T>
		typename forward_list<T>::iterator forward_list<T>::insert_after(
			int pos, std::initializer_list<T> elems) {
			auto size = elems.size();
			if (size == 0) return iterator();

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
		void forward_list<T>::erase_after(const_iterator& beg, const_iterator& end) {
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
		void forward_list<T>::remove_if(bool(*op)(const T& e)) {
			if (head == iterator()) return;

			//ɾ���ײ��������������Ľڵ�
			auto end = iterator();
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
			if (head == iterator()) return;

			//ɾ���ײ��������������Ľڵ�
			auto end = iterator();
			while (head != end && *head == elem) {
				auto del = head;
				++head;
				delete del.get();
			}

			auto prev_iter = head;				//ѭ����������ǰһ��������
			auto iter = head;					//ѭ��������
			++iter;
			while (iter != end) {

				//�ҵ����������Ľڵ�
				if (*iter == elem) {
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

		//���ô�С
		template<typename T>
		void forward_list<T>::resize(int n, const T& elem) {
			auto end = iterator();
			if (n == 0) {
				clear();
				return;
			}

			//ԭ��Ϊ��ʱ����Ҫ����head
			if (head == iterator()) {
				head = iterator(elem);
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
				if (iter == iterator()) return;		//Ԫ�ظ����պ�Ϊn��

													//Ԫ�ظ�������n��
				else {
					//ɾ�������Ľڵ�
					auto it = iter;
					++it;						//����������Чĩβ�ڵ�
					while (it != end) {
						auto del = it;
						++it;
						delete del.get();
					}
					//�������ڵ��next��
					iter.get()->next = nullptr;
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
			auto end = iterator();;

			auto iter = head;
			head = end;
			while (iter != end) {
				auto del = iter;
				++iter;
				delete del.get();
			}
		}

		//operator==
		template<typename T>
		bool forward_list<T>::operator==(const forward_list<T>& fl)const {
			auto beg = head;
			auto end = iterator();
			auto fl_beg = fl.head;

			//��������Ϊ��
			while (beg != end && fl_beg != end) {
				if (*beg != *fl_beg) return false;
				++beg;
				++fl_beg;
			}

			if (beg == end && fl_beg == end) return true;
			else return false;
		}

		//operator!=
		template<typename T>
		bool forward_list<T>::operator!=(const forward_list<T>& fl)const {
			return !operator==(fl);
		}

		//operator<
		template<typename T>
		bool forward_list<T>::operator<(const forward_list<T>& fl)const {
			auto beg = head;
			auto end = iterator();
			auto fl_beg = fl.head;

			while (beg != end && fl_beg != end) {
				if (*beg >= *fl_beg) return false;
				++beg;
				++fl_beg;
			}

			if (beg == end) return true;
			else return false;
		}

		//operator>
		template<typename T>
		bool forward_list<T>::operator>(const forward_list<T>& fl)const {
			auto beg = head;
			auto end = iterator();
			auto fl_beg = fl.head;

			while (beg != end && fl_beg != end) {
				if (*beg <= *fl_beg) return false;
				++beg;
				++fl_beg;
			}

			if (fl_beg == end) return true;
			else return false;
		}

		//operator<=
		template<typename T>
		bool forward_list<T>::operator<=(const forward_list<T>& fl)const {
			return !(operator>(fl));
		}

		//operator>=
		template<typename T>
		bool forward_list<T>::operator>=(const forward_list<T>& fl)const {
			return !(operator<(fl));
		}

		//assign
		template<typename T>
		void forward_list<T>::assign(int n, const T& elem) {
			clear();
			if (n <= 0) return;
			iterator iter = elem;
			head = iter;

			int count = 1;
			while (count < n) {
				iter.get()->next = new Node<T>(elem);
				++iter;
				++count;
			}
		}

		//assign
		template<typename T>
		void forward_list<T>::assign(const_iterator& beg, const_iterator& end) {
			if (beg == end) return;
			iterator iter = *beg;
			head = iter;

			auto it = beg;
			++it;
			while (it != end) {
				iter.get()->next = new Node<T>(*it);
				++iter;
				++it;
			}
		}

		//swap
		template<typename T>
		void forward_list<T>::swap(forward_list<T>& fl) {
			auto iter = head;
			head = fl.head;
			fl.head = iter;
		}

		//�����ã����������Ϣ
		template<typename T>
		void forward_list<T>::print()const {
			auto end = iterator();
			for (auto iter = head; iter != end; ++iter) {
				cout << *iter << " ";
			}
			cout << endl;
		}

		//swap���ǳ�Ա����
		template<typename T>
		void swap(forward_list<T>& lhs, forward_list<T>& rhs) {
			lhs.swap(rhs);
		}
	};
}