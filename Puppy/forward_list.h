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

		//���������ã���Ϊprivate
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
		bool operator==(const Iter& it)const {
			return iter == it.iter;
		}

		//operator!=
		bool operator!=(const Iter& it)const {
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

		//��begΪ�׽ڵ㣬endΪβ�ڵ��������뵽pos��
		void __insert(int pos, const_iterator& beg, const_iterator& end);
	public:

		//constructors
		forward_list() :head() {}									//��
		forward_list(const forward_list& fl);						//���ƹ���
		forward_list(forward_list&& fl);							//�ƶ�����
		forward_list(std::initializer_list<T> il);					//��ʼ�й���
		forward_list(int n);										//n��Ĭ�ϳ�ʼ����Ԫ��
		forward_list(int n, const T& elem);							//n����t��ʼ����Ԫ��
		forward_list(const_iterator& beg, const_iterator& end);		//ͨ����������Χ����
		
		~forward_list();											//����

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
		bool empty()const { return head.get() == nullptr; }

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

	//swap���ǳ�Ա����
	template<typename T>
	void swap(const forward_list<T>& lhs, const forward_list<T>& rhs);

	//���ƹ��캯��
	template<typename T>
	forward_list<T>::forward_list(const forward_list& fl) {
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
	forward_list<T>::forward_list(const_iterator& beg, const_iterator& end) {
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
		return beg;
	}

	//����n��elem����posλ�ú�
	template<typename T>
	Iter<T> forward_list<T>::insert_after(int pos, int n, const T& elem) {
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
	Iter<T> forward_list<T>::insert_after(int pos, const T& elem) {
		return insert_after(pos, 1, elem);
	}

	//��[beg,end)�е�Ԫ�ز��뵽posλ�ú�
	template<typename T>
	Iter<T> forward_list<T>::insert_after(
		int pos, const_iterator& beg, const_iterator& end) {
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
	Iter<T> forward_list<T>::insert_after(
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
	void forward_list<T>::remove_if(bool(*op)(const T& elem)) {
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
		remove_if(
			[&elem](const T& e) -> bool {return elem == e; }
		);
	}

	//���ô�С
	template<typename T>
	void forward_list<T>::resize(int n, const T& elem) {
		auto end = iterator();
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
			if (iter == iterator()) return;		//Ԫ�ظ����պ�Ϊn��

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
		iterator iter = elem;
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
	void forward_list<T>::swap(const forward_list<T>& fl) {
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
	void swap(const forward_list<T>& lhs, const forward_list<T>& rhs) {
		lhs.swap(rhs);
	}
}