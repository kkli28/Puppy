#pragma once

#include "stdafx.h"
#include "memory.h"
#include "functional.h"
#include "iterator.h"
#include "string.h"

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
		forward_list_node(const T& val) :value(val), next(nullptr) {}
		forward_list_node(T&& val) :value(std::move(val)), next(nullptr) {}
		forward_list_node(const forward_list_node& rhs) = default;
		forward_list_node(forward_list_node&& rhs) : value(std::move(rhs.value)), next(rhs.next) {}

		//operator =
		forward_list_node& operator=(const forward_list_node& rhs) = default;
		forward_list_node& operator=(forward_list_node&& rhs) {
			value = std::move(rhs.value);
			next = rhs.next;
			return *this;
		}

		//operator < / ==
		bool operator<(const forward_list_node<T>& rhs) { return value < rhs.value; }
		bool operator==(const forward_list_node& rhs) { return (value == rhs.value && next == rhs.next); }
	};

	//operator <
	template<typename T>
	bool operator<(const forward_list_node<T>& lhs, const forward_list_node<T>& rhs) {
		return value < rhs.value;
	}

	//operator ==
	template<typename T>
	bool operator==(const forward_list_node<T>& lhs, const forward_list_node<T>& rhs) { return (value == rhs.value && next == rhs.next); }
}

//================================================================================
// forward_list<T> �ඨ��
//================================================================================

namespace kkli {

	template<typename T>
	class forward_list {
	public:
		class __iterator {
		public:
			//typedef
			typedef T				value_type;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef std::ptrdiff_t	difference_type;
			typedef std::size_t		size_type;
			typedef kkli::forward_iterator_tag iterator_category;

		private:
			forward_list_node<T>* iter;

		public:
			__iterator() : iter(nullptr) {}
			__iterator(forward_list_node<T>* ptr) : iter(ptr) {}
			__iterator(const __iterator& it) :iter(it.iter) {}

			__iterator& operator=(const __iterator& it) { iter = it.iter; return *this; }
			forward_list_node<T>* get()const { return iter; }

			__iterator& operator++() { iter = iter->next; return *this; }
			__iterator operator++(int) {
				__iterator it = iter;
				iter = iter->next;
				return it;
			}

			bool operator==(const __iterator& it)const { return iter == it.iter; }
			bool operator!=(const __iterator& it)const { return !(*this == it); }

			reference operator*() { return iter->value; }
			const_reference operator*()const { return iter->value; }
			forward_list_node<T>* operator->() { return iter; }
			const forward_list_node<T>* operator->()const { return iter; }
		};

	public:
		//typedefs
		typedef forward_list_node<T>			node_type;
		typedef T								value_type;
		typedef kkli::allocator<T>				allocator_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef node_type*						pointer;
		typedef const node_type*				const_pointer;
		typedef __iterator						iterator;
		typedef iterator						const_iterator; //��iterator
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef kkli::forward_iterator_tag		iterator_category;

	private:
		iterator __head;

		//��[beg, end)��Χ�Ľڵ���뵽pos��
		void __insert(size_type pos, const_iterator first, const_iterator last);
		
		//��[first, last)����forward_list
		template<typename InputIt>
		void __construct(InputIt first, InputIt last);

		//��������
		void __destroy();

	public:
		//constructors
		forward_list() : __head(new node_type()) {}
		forward_list(size_type count, const value_type& value = value_type());

		forward_list(const forward_list& rhs) :__head(new node_type()) {
			__construct(rhs.cbegin(), rhs.cend());
		}
		forward_list(forward_list&& rhs);
		forward_list(std::initializer_list<value_type> init) :__head(new node_type()) {
			__construct(init.begin(), init.end());
		}

		/* ��ҪSFINAE
		template<typename InputIt>
		forward_list(InputIt first, InputIt last);
		*/

		//destructor
		~forward_list();

		//operator =
		forward_list& operator=(const forward_list& rhs);
		forward_list& operator=(forward_list&& rhs);
		forward_list& operator=(std::initializer_list<value_type> init);

		//assign
		void assign(size_type count, const value_type& value);
		template<typename InputIt>
		void assign(InputIt first, InputIt last);
		void assign(std::initializer_list<value_type> init) {
			return assign(init.begin(), init.end());
		}

		//front
		reference front() { return __head->next->value; }
		const_reference front()const { return __head->next->value; }

		//before_begin
		iterator before_begin() { return __head; }
		const_iterator before_begin()const { return __head; }

		//begin / cbegin
		iterator begin()const { return iterator(__head->next); }
		const_iterator cbegin()const { return const_iterator(__head->next); }

		//end / cend
		iterator end() const { return iterator(); }
		const_iterator cend()const { return const_iterator(); }

		//empty
		bool empty()const { return __head->next == nullptr; }

		//max_size
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }

		//clear
		void clear();

		//insert_after
		iterator insert_after(const_iterator pos, size_type count, const value_type& value);
		iterator insert_after(const_iterator pos, const value_type& value) {
			return insert_after(pos, 1, value);
		}
		iterator insert_after(const_iterator pos, value_type&& value);
		template<typename InputIt>
		iterator insert_after(const_iterator pos, InputIt first, InputIt last);
		iterator insert_after(const_iterator pos, std::initializer_list<value_type> init) {
			return insert_after(pos, init.begin(), init.end());
		}

		//erase_after
		iterator erase_after(const_iterator first, const_iterator last);
		iterator erase_after(const_iterator pos) {
			return erase_after(pos, kkli::next(pos));
		}

		//push_front / pop_front
		void push_front(const value_type& value);
		void push_front(value_type&& value);
		void pop_front();

		//resize
		void resize(size_type count, const value_type& value);
		void resize(size_type count) {
			return resize(count, value_type());
		}

		//swap
		void swap(forward_list& rhs) { kkli::swap(__head, rhs.__head); }

		//merge
		void merge(forward_list& rhs);
		void merge(forward_list&& rhs);
		template<typename Compare>
		void merge(forward_list& rhs, Compare comp);
		template<typename Compare>
		void merge(forward_list&& rhs, Compare comp);

		//splice_after
		void splice_after(const_iterator pos, forward_list& rhs,
			const_iterator first, const_iterator last);
		void splice_after(const_iterator pos, forward_list&& rhs,
			const_iterator first, const_iterator last);
		void splice_after(const_iterator pos, forward_list& rhs) {
			return splice_after(pos, rhs, rhs.begin(), rhs.end());
		}
		void splice_after(const_iterator pos, forward_list&& rhs) {
			return splice_after(pos, std::move(rhs), rhs.begin(), rhs.end());
		}
		void splice_after(const_iterator pos, forward_list& rhs, const_iterator it) {
			return splice_after(pos, rhs, it, rhs.end());
		}

		//remove
		template<typename UnaryPredicate>
		void remove_if(UnaryPredicate pred);
		void remove(const value_type& value) {
			remove_if([=](const value_type& val)->bool {return val == value; });
		}

		//reverse
		void reverse();

		//unique
		template<typename BinaryPredicate>
		void unique(BinaryPredicate pred);
		void unique() {
			unique(kkli::equal_to<value_type>());
		}

		//sort
		template<typename Compare>
		void sort(Compare comp); //�Ƚ�iterator����vector��Ȼ�������������������next����
		void sort() {
			sort(kkli::less<value_type>());
		}
		
		void print(const kkli::string& prefix)const;
	};

	//non-member functions
}

//================================================================================
// forward_list<T> ��Ա��������
//================================================================================

namespace kkli {

	//__insert
	template<typename T>
	void forward_list<T>::__insert(size_type pos, const_iterator first, const_iterator last) {
		//�ҵ������
		auto iter = __head;
		size_type count = 0;
		for (; count != pos; ++count, ++iter);

		//����ʱ�������posλ��
		last->next = iter->next;
		iter->next = first.get();
	}

	//__construct
	template<typename T>
	template<typename InputIt>
	void forward_list<T>::__construct(InputIt first, InputIt last) {
		auto iter = __head;
		for (auto i = first; i != last; ++i, ++iter)
			iter->next = new node_type(*i);
	}

	//__destroy
	template<typename T>
	void forward_list<T>::__destroy() {
		auto iter = __head;
		while (__head != this->end()) {
			iter = __head;
			++__head;
			delete iter.get();
		}
	}

	//forward_list(count, value)
	template<typename T>
	forward_list<T>::forward_list(size_type count, const value_type& value) :__head(new node_type()) {
		auto iter = __head;
		for (size_type i = 0; i < count; ++i, ++iter)
			iter->next = new node_type(value);
	}

	//forward_list(&&rhs)
	template<typename T>
	forward_list<T>::forward_list(forward_list&& rhs) {
		__head = rhs.__head;
		rhs.__head = iterator();
	}

	//destructor
	template<typename T>
	forward_list<T>::~forward_list() {
		__destroy();
	}

	//operator =(rhs)
	template<typename T>
	forward_list<T>& forward_list<T>::operator=(const forward_list& rhs) {
		this->clear();
		auto end = rhs.cend();
		auto iter = __head;
		for (auto i = rhs.cbegin(); i != end; ++i,++iter)
			iter->next = new node_type(*i);
	}

	//operator =(&&rhs)
	template<typename T>
	forward_list<T>& forward_list<T>::operator=(forward_list&& rhs) {
		__destroy();
		__head = rhs.__head;
		(rhs.__head).get() = nullptr;
	}

	//operator =(init)
	template<typename T>
	forward_list<T>& forward_list<T>::operator=(std::initializer_list<value_type> init) {
		__destroy();
		auto end = init.end();
		auto iter = __head;
		for (auto i = init.begin(); i != end; ++i, ++iter)
			iter->next = new node_type(*i);
	}

	//assign(count, value)
	template<typename T>
	void forward_list<T>::assign(size_type count, const value_type& value) {
		this->clear();
		auto iter = __head;
		for (; count > 0; --count, ++iter)
			iter->next = new node_type(value);
	}

	//assign(first, last)
	template<typename T>
	template<typename InputIt>
	void forward_list<T>::assign(InputIt first, InputIt last) {
		this->clear();
		auto iter = __head;
		for (auto i = first; i != last; ++i, ++iter) 
			iter->next = new node_type(*i);
	}

	//clear
	template<typename T>
	void forward_list<T>::clear() {
		auto iter = kkli::next(__head);
		auto end = this->end();
		while (iter != end) {
			auto del_iter = iter;
			++iter;
			delete del_iter.get();
		}
	}

	//insert_after
	template<typename T>
	typename forward_list<T>::iterator forward_list<T>::insert_after(
		const_iterator pos,	size_type count, const value_type& value) {
		//������count��value��ϳɵ���
		auto first = new node_type(value);
		auto iter = first;
		while (--count > 0) {
			iter->next = new node_type(value);
			++iter;
		}

		//ƴ��
		iter->next = pos->next;
		pos->next = first.get();
	}

	//inser_after
	template<typename T>
	typename forward_list<T>::iterator forward_list<T>::insert_after(
		const_iterator pos, value_type&& value) {
		auto iter = new node_type(std::move(value));
		iter->next = pos->next;
		pos->next = iter.get();
	}

	//insert_after
	template<typename T>
	template<typename InputIt>
	typename forward_list<T>::iterator forward_list<T>::insert_after(
		const_iterator pos, InputIt first, InputIt last) {
		if (first == last) return iterator(pos);
		
		//������[first, last)Ԫ����ɵ���
		auto beg = new node_type(*first);
		auto end = beg;
		++first;
		while (first != last) {
			end->next = new node_type(*first);
			++first;
			++end;
		}
		end->next = pos->next; //ƴ��
		pos->next = beg.get();
	}

	//erase_after
	template<typename T>
	typename forward_list<T>::iterator forward_list<T>::erase_after(
		const_iterator first, const_iterator last) {
		if (first == last) return last;

		//�ҵ�firstǰһ��Ԫ�أ�����next��ָ��last��ָ
		auto beg = first;
		auto end = last;
		auto before_first = __head;
		auto iter = __head;
		while (++iter != first) ++before_first;
		before_first->next = last.get();

		//ɾ��[first, last)
		iter = beg;
		while (beg != end) {
			iter = beg;
			++beg;
			delete iter.get();
		}
		return last;
	}

	//push_front(rhs)
	template<typename T>
	void forward_list<T>::push_front(const value_type& value) {
		auto iter = new node_type(value);
		iter->next = __head->next;
		__head->next = iter.get();
	}

	//push_front(&&rhs)
	template<typename T>
	void forward_list<T>::push_front(value_type&& value) {
		auto iter = new node_type(std::move(value));
		iter->next = __head->next;
		__head->next = iter.get();
	}

	//pop_front
	template<typename T>
	void forward_list<T>::pop_front() {
		auto iter = __head->next;
		__head->next = iter->next;
		delete iter.get();
	}

	//resize
	template<typename T>
	void forward_list<T>::resize(size_type count, const value_type& value){
		size_type size = this->size();
		if (!(size < count)) return;
		count = count - size;
		auto end = __head;
		while (end->next != nullptr) ++end;
		while (count > 0) {
			end->next = new node_type(value);
			++end;
			--count;
		}
	}

	//print
	template<typename T>
	void forward_list<T>::print(const kkli::string& prefix)const {
		std::cout << prefix << ": ";
		auto end = iterator();
		for (auto iter = __head; ++iter != end;) std::cout << iter->value << " ";
		std::cout << std::endl;
	}
}
/*
namespace kkli{

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
		__head = new node_type();
		auto iter = __head;
		for (int i = 1; i < n; ++i, ++iter)
			iter->next = new node_type(elem);
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
}

//================================================================================
// forward_list<T> �ǳ�Ա��������
//================================================================================

namespace kkli {
	//swap���ǳ�Ա����
	template<typename T, typename Allocator>
	void swap(forward_list<T, Allocator>& lhs, forward_list<T, Allocator>& rhs) {
		lhs.swap(rhs);
	}
}
*/