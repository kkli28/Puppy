#pragma once

#include "stdafx.h"


//================================================================================
// forward_list_node<T> �ඨ��
//================================================================================
namespace kkli {

	template<typename T>
	class forward_list_node {
	public:
		T value;
		forward_list_node* next;

		//constructor
		forward_list_node() = default;
		forward_list_node(const T& val) : value(val), next(nullptr) {}
		forward_list_node(T&& val) :value(val), next(nullptr) {}
		forward_list_node(const forward_list_node& rhs) = default;
		forward_list_node(forward_list_node&& rhs) : value(std::move(rhs.value)), next(rhs.next) {}

		//operator =
		forward_list_node& operator=(const forward_list_node& rhs) = default;
		forward_list_node& operator=(forward_list_node&& rhs) {
			value = std::move(rhs.value);
			next = rhs.next;
			return *this;
		}

		//operator==
		bool operator==(const forward_list_node& rhs) {
			return (value == rhs.value && next == rhs.next);
		}
	};
}

//================================================================================
// forward_list<T> �ඨ��
//================================================================================
namespace kkli {

	//forward_list<T>
	template<typename T>
	class forward_list {
	private:

		//iterator: __iterator
		class __iterator {
		private:
			forward_list_node<T>* iter;

			//�������ⲿʹ��
			__iterator(forward_list_node<T>* ptr) : iter(ptr) {}

		public:
			//constructor
			__iterator() : iter(nullptr) {}
			__iterator(const T& t) : iter(new forward_list_node<T>(t)) {}
			__iterator(const __iterator& it) :iter(it.iter) {}

			//operator=
			__iterator& operator=(const __iterator& it) {
				iter = it.iter;
				return *this;
			}

			//get
			forward_list_node<T>* get()const { return iter; }

			//operator++
			__iterator& operator++() {
				iter = iter->next;
				return *this;
			}

			//operator++(int)
			__iterator operator++(int) {
				__iterator it = iter;
				iter = iter->next;
				return it;
			}

			//operator==
			bool operator==(const __iterator& it)const {
				return iter == it.iter;
			}

			//operator!=
			bool operator!=(const __iterator& it)const {
				return !(*this == it);
			}

			//operator*
			T& operator*() { return iter->value; }
			T operator*()const { return iter->value; }

			//operator->
			forward_list_node<T>* operator->() { return iter; }
			const forward_list_node<T>* operator->()const { return iter; }
		};

	public:

		//typedefs
		typedef T								value_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef forward_list_node<T>*			pointer;
		typedef const forward_list_node<T>*		const_pointer;
		typedef __iterator						iterator;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef std::forward_iterator_tag		iterator_category;

		//************************************************************
		// WRONG! const_iteratorӦ��ʵ��Ϊָ������ָ�룬�����ǳ���ָ��
		//************************************************************
		//typedef const iterator				const_iterator;
		typedef __iterator						const_iterator;

	private:
		//forward_list's __head
		iterator __head;

		//��begΪ�׽ڵ㣬endΪβ�ڵ��������뵽pos��
		void __insert(int pos, const_iterator& beg, const_iterator& end);

	public:

		//constructors
		forward_list() :__head() {}									//��
		forward_list(const forward_list& fl);						//���ƹ���
		forward_list(forward_list&& fl);							//�ƶ�����
		forward_list(int n, const T& elem);							//n����t��ʼ����Ԫ��
		forward_list(int n) :forward_list(n, T()) {}				//n��Ĭ�ϳ�ʼ����Ԫ��
		forward_list(const_iterator& beg, const_iterator& end);		//ͨ����������Χ����
		forward_list(std::initializer_list<T> il);  				//��ʼ�й���

		//destructor
		~forward_list();

		//begin / cbegin
		iterator begin()const { return __head; }
		const_iterator cbegin()const { return __head; }

		//end / cend
		iterator end() const { return iterator(); }
		const_iterator cend()const { return iterator(); }

		//push_front / pop_front
		void push_front(const T& elem);
		void pop_front();

		//insert_after
		iterator insert_after(int pos, int n, const T& elem);
		iterator insert_after(int pos, const T& elem) { return insert_after(pos, 1, T()); }
		iterator insert_after(int pos, const_iterator& beg, const_iterator& end);
		iterator insert_after(int pos, std::initializer_list<T> elems);

		//erase_after
		void erase_after(int pos);
		void erase_after(const_iterator& beg, const_iterator& end);

		//remove
		void remove(const T& elem);

		//remove_if
		template<typename E=std::equal<T>>
		void remove_if(const E& e);

		//resize
		void resize(int n);
		void resize(int n, const T& elem);

		//clear
		void clear();

		//empty
		bool empty()const { return __head.get() == nullptr; }

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
		void swap(forward_list<T>& fl);

		//TEST: print all elements
		void print()const;
	};

	//swap���ǳ�Ա����
	template<typename T>
	void swap(forward_list<T>& lhs, forward_list<T>& rhs);

}

//================================================================================
// forward_list<T> ��������
//================================================================================
namespace kkli{

	//���ƹ��캯��
	template<typename T>
	forward_list<T>::forward_list(const forward_list& fl) {
		if (fl.begin() == fl.end()) return;

		//����__head����Ϊ����ͷ�ڵ�
		__iterator it = *(fl.begin());
		__head = it;

		//��Ӻ���Ԫ��
		for (auto iter = ++fl.begin(); iter != fl.end(); ++iter) {
			it->next = new forward_list_node<T>(*iter);
			++it;
		}
	}

	//�ƶ����캯��
	template<typename T>
	forward_list<T>::forward_list(forward_list&& fl) {
		__head = fl.__head;
		fl.__head = iterator();
	}

	//����n��elem
	template<typename T>
	forward_list<T>::forward_list(int n, const T& elem) {
		if (n <= 0) return;

		//����__head
		iterator it = elem;
		__head = it;

		//��������ڵ�
		for (int i = 1; i < n; ++i) {
			it->next = new forward_list_node<T>(elem);
			++it;
		}
	}

	//ͨ����������Χ����
	template<typename T>
	forward_list<T>::forward_list(const_iterator& beg, const_iterator& end) {
		if (beg == end) return;

		//����__head
		iterator it = *beg;
		__head = it;

		//��������ڵ�
		auto iter = beg;
		++iter;
		for (; iter != end; ++iter) {
			it->next = new forward_list_node<T>(*iter);
			++it;
		}
	}

	//ͨ����ʼ�б���
	template<typename T>
	forward_list<T>::forward_list(std::initializer_list<T> il) {
		auto beg = il.begin();
		auto end = il.end();
		if (beg == end) return;

		//����__head
		iterator it = *beg;
		__head = it;

		//��������ڵ�
		++beg;
		for (; beg != end; ++beg) {
			it->next = new forward_list_node<T>(*beg);
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
		iter->next = __head.get();
		__head = iter;
	}

	//����forward_list�ײ��ڵ�
	template<typename T>
	void forward_list<T>::pop_front() {
		iterator iter = __head;
		++__head;
		delete iter.get();
	}

	//��begΪ�׽ڵ㣬endΪβ�ڵ��������뵽pos��
	template<typename T>
	void forward_list<T>::__insert(
		int pos, const_iterator& beg, const_iterator& end) {
		//�ҵ������
		int count = 0;
		auto iter = __head;
		while (count != pos) {
			++iter;
			++count;
		}

		//����ʱ�������posλ��
		end->next = iter->next;
		iter->next = beg.get();
	}

	//����n��elem����posλ�ú�
	template<typename T>
	typename forward_list<T>::iterator forward_list<T>::insert_after(int pos, int n, const T& elem) {
		if (n <= 0) return iterator();
		iterator temp_beg = elem;					//��ʱ�����׽ڵ������
		iterator temp_end = temp_beg;				//��ʱ����β�ڵ������
		for (int i = 1; i < n; ++i) {
			temp_end->next = new forward_list_node<T>(elem);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return temp_beg;
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
			temp_end->next = new forward_list_node<T>(*begin);
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
			temp_end->next = new forward_list_node<T>(*iter);
			++temp_end;
		}

		__insert(pos, temp_beg, temp_end);
		return temp_beg;
	}

	//�Ƴ�posλ�ú�Ľڵ�
	template<typename T>
	void forward_list<T>::erase_after(int pos) {

		//�ҵ�posλ�õĽڵ�
		auto iter = __head;
		int count = 0;
		while (count < pos) {
			++iter;
			++count;
		}

		//ɾ��posλ�õĽڵ�֮��Ľڵ�
		auto del = iter;
		++del;
		iter->next = del->next;
		delete del.get();
	}

	//�Ƴ�[beg,end)��ʶ��Χ�Ľڵ�
	template<typename T>
	void forward_list<T>::erase_after(const_iterator& beg, const_iterator& end) {
		if (__head == beg) {
			__head = end;
		}
		else {
			auto iter = __head;				//beg��ָ�ڵ��ǰһ���ڵ�
			auto next_iter = __head;			//beg��ָ�ڵ�
			++next_iter;
			while (next_iter != beg) {
				++next_iter;
				++iter;
			}

			//��������[beg,end)��������
			iter->next = end.get();
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
	template<typename E=std::equal<T>>
	void forward_list<T>::remove_if(const E& op) {
		if (__head == iterator()) return;

		//ɾ���ײ��������������Ľڵ�
		auto end = iterator();
		while (__head != end && op(*__head)) {
			auto del = __head;
			++__head;
			delete del.get();
		}

		auto prev_iter = __head;				//ѭ����������ǰһ��������
		auto iter = __head;					//ѭ��������
		++iter;
		while (iter != end) {

			//�ҵ����������Ľڵ�
			if (op(*iter)) {
				auto del = iter;
				prev_iter->next = iter->next;
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

		//log
		cout << "call remove(" << elem << ")" << endl;

		return remove_if([=](const T& e) -> bool {return e == elem; });

		if (__head == iterator()) return;

		//ɾ���ײ��������������Ľڵ�
		auto end = iterator();
		while (__head != end && *__head == elem) {
			auto del = __head;
			++__head;
			delete del.get();
		}

		auto prev_iter = __head;				//ѭ����������ǰһ��������
		auto iter = __head;					//ѭ��������
		++iter;
		while (iter != end) {

			//�ҵ����������Ľڵ�
			if (*iter == elem) {
				auto del = iter;
				prev_iter->next = iter->next;
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

		//ԭ��Ϊ��ʱ����Ҫ����__head
		if (__head == iterator()) {
			__head = iterator(elem);
		}

		int count = 0;
		auto iter = __head;
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
				prev_iter->next = new forward_list_node<T>(elem);
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
				iter->next = nullptr;
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

		auto iter = __head;
		__head = end;
		while (iter != end) {
			auto del = iter;
			++iter;
			delete del.get();
		}
	}

	//operator==
	template<typename T>
	bool forward_list<T>::operator==(const forward_list<T>& fl)const {
		auto beg = __head;
		auto end = iterator();
		auto fl_beg = fl.__head;

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
		auto beg = __head;
		auto end = iterator();
		auto fl_beg = fl.__head;

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
		auto beg = __head;
		auto end = iterator();
		auto fl_beg = fl.__head;

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
		__head = iter;

		int count = 1;
		while (count < n) {
			iter->next = new forward_list_node<T>(elem);
			++iter;
			++count;
		}
	}

	//assign
	template<typename T>
	void forward_list<T>::assign(const_iterator& beg, const_iterator& end) {
		if (beg == end) return;
		iterator iter = *beg;
		__head = iter;

		auto it = beg;
		++it;
		while (it != end) {
			iter->next = new forward_list_node<T>(*it);
			++iter;
			++it;
		}
	}

	//swap
	template<typename T>
	void forward_list<T>::swap(forward_list<T>& fl) {
		auto iter = __head;
		__head = fl.__head;
		fl.__head = iter;
	}

	//�����ã����������Ϣ
	template<typename T>
	void forward_list<T>::print()const {
		auto end = iterator();
		for (auto iter = __head; iter != end; ++iter) {
			cout << *iter << " ";
		}
		cout << endl;
	}

	//swap���ǳ�Ա����
	template<typename T>
	void swap(forward_list<T>& lhs, forward_list<T>& rhs) {
		lhs.swap(rhs);
	}
}
