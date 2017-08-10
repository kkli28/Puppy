#pragma once

#include "stdafx.h"
#include "vector.h"
#include "algorithm.h"

//================================================================================
// list_node<T> �ඨ��
//================================================================================
namespace kkli {
	
	template<typename T>
	class list_node {
	public:
		T value;
		list_node* next;
		list_node* prev;

		//constructor
		list_node() :value(T()), next(nullptr), prev(nullptr) {}
		list_node(const T& val) :value(val), next(nullptr), prev(nullptr) {}
		list_node(T&& val) :value(val), next(nullptr), prev(nullptr) {}
		list_node(const list_node& rhs) :value(rhs.value), next(rhs.next), prev(rhs.prev) {}
		list_node(list_node&& rhs) :value(std::move(rhs.value)), next(rhs.next), prev(rhs.prev) {}
		
		//operator =
		list_node& operator=(const list_node& rhs) = default;
		list_node& operator=(list_node&& rhs) {
			value = std::move(rhs.value);
			next = rhs.next;
			prev = rhs.prev;
			return *this;
		}

		//operator ==
		bool operator==(const list_node<T>& rhs) {
			return (value == rhs.value && next == rhs.next && prev == rhs.prev);
		}
	};
}

//================================================================================
// list<T> �ඨ��
//================================================================================
namespace kkli {

	template<typename T>
	class list {
	private:

		//iterator: __iterator
		class __iterator {
		public:
			//typedef
			typedef T				value_type;
			typedef T&				reference;
			typedef T*				pointer;
			typedef std::ptrdiff_t	difference_type;
			typedef kkli::bidirectional_iterator_tag iterator_category;

		private:
			list_node<T>* iter;

			//�������ⲿʹ��
			__iterator(list_node<T>* ptr) :iter(ptr) {}
		public:
			//constructor
			__iterator() = default;
			__iterator(const T& t) :iter(new list_node<T>(t)) {}
			__iterator(const __iterator& it) :iter(it.iter) {}

			//operator =
			__iterator& operator=(const __iterator& it) = default;

			//get
			list_node<T>* get()const { return iter; }

			//operator ++
			__iterator& operator++() {
				iter = iter->next;
				return *this;
			}

			//operator ++(int)
			__iterator operator++(int) {
				__iterator it(iter);
				iter = iter->next;
				return it;
			}

			//operator --
			__iterator& operator--() {
				iter = iter->prev;
				return *this;
			}

			//operator --(int)
			__iterator operator--(int) {
				__iterator it(iter);
				iter = iter->prev;
				return it;
			}

			//operator ==
			bool operator==(const __iterator& rhs)const {
				return iter == rhs.iter;
			}

			//operator !=
			bool operator!=(const __iterator& rhs)const {
				return !(*this == rhs);
			}

			//operator *
			T&  operator*() { return iter->value; }
			T operator*()const { return iter->value; }

			//operator ->
			list_node<T>* operator->() { return iter; }
			const list_node<T>* operator->()const { return iter; }
		};

	public:
		//typedefs
		typedef	T							value_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef __iterator					iterator;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef std::forward_iterator_tag	iterator_category;

		//************************************************************
		// WRONG! const_iteratorӦ��ʵ��Ϊָ������ָ�룬�����ǳ���ָ��
		//************************************************************
		//typedef const iterator				const_iterator;
		typedef __iterator						const_iterator;

	private:
		iterator __head;		//ͷ�ڵ�ָ��
		size_type __size;		//������Ч����

		//����ͷ�ڵ㣬����__sizeΪ0�������ú�__head��next��prev
		void create_head_node();

		//��ȡ[first, last)ָʾ��Χ�ĳ���
		static size_type get_size(iterator first, iterator last);

		//��������͵ȡ
		void cheat_from_rhs(list&& rhs);
	public:
		//constructor
		list() { create_head_node(); }
		list(size_type count, const value_type& value);
		list(size_type count) :list(count, value_type()) {}
		list(const list& rhs);
		list(list&& rhs);
		list(std::initializer_list<T> il);

		/*
		//��ҪSFINAE����ʱ���ᣬ��û��ʵ�ָù��캯��
		template< class InputIt >
		list(InputIt first, InputIt last);
		*/

		//destructor
		~list();

		//operator =
		list& operator=(const list& rhs);
		list& operator=(list&& rhs);

		//������Ա����
		std::allocator<T> get_allocator()const { return std::allocator<T>(); }
		void assign(size_type count, const value_type& value);
		void assign(std::initializer_list<T> il);
		reference front() {
			if (__size == 0) throw std::runtime_error("list is empty!");
			return __head->next->value;
		}
		const_reference front()const {
			if (__size == 0) throw std::runtime_error("list is empty!");
			return __head->next->value;
		}
		reference back() {
			if (__size == 0) throw std::runtime_error("list is empty!");
			return __head->prev->value;
		}
		const_reference back()const {
			if (__size == 0) throw std::runtime_error("list is empty!");
			return __head->prev->value;
		}
		iterator begin() { return ++iterator(__head); }
		const_iterator cbegin()const { return ++iterator(__head); }
		iterator end() { return __head; }
		const_iterator cend()const { return __head; }
		bool empty()const { return __size == 0; }
		size_type size()const { return __size; }
		constexpr static size_type max_size() { return std::numeric_limits<size_type>::max(); }
		void clear();
		iterator insert(iterator pos, value_type&& value);
		iterator insert(iterator pos, size_type count, const value_type& value);
		iterator insert(iterator pos, const value_type& value) {
			return insert(pos, 1, value);
		}
		iterator insert(iterator pos, std::initializer_list<value_type> il);

		/*
		//����дemplace��غ���
		template<typename... Args>
		iterator emplace(const_iterator pos, Args&&... args);

		template<typename... Args>
		void emplace_back(Args&&... args);

		template<typename... Args>
		void emplace_front(Args&&... args);
		*/

		iterator erase(iterator first, iterator last);
		iterator erase(iterator pos) {
			iterator iter = pos;
			++iter;
			return erase(pos, iter);
		}
		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back();
		void push_front(const value_type& value);
		void push_front(value_type&& value);
		void pop_front();
		void resize(size_type count, const value_type& value);
		void resize(size_type count) { resize(count, value_type()); }
		void swap(list& rhs);

		template<typename Compare>
		void merge(list&& rhs, Compare comp);
		void merge(list&& rhs) { merge(std::move(rhs), std::less<T>()); }

		void splice(iterator pos, list& rhs, iterator first, iterator last);
		void splice(iterator pos, list& rhs, iterator it) {
			iterator iter(it);
			++iter;
			splice(pos, rhs, it, iter);
		}
		void splice(iterator pos, list& rhs) { splice(pos, rhs, begin(), end()); }

		template<typename UnaryPredicate>
		void remove_if(UnaryPredicate pred);
		void remove(const value_type& value) {
			remove_if([&value](const value_type& val) ->bool {return val == value; });
		}

		void reverse();
		
		template<typename BinaryPredicate>
		void unique(BinaryPredicate pred);
		void unique() {
			unique([](const T& t1, const T& t2)->bool {return t1 == t2; });
		}

		template<typename Compare>
		void sort(Compare comp = std::less<T>());
		void sort() { sort(std::less<T>()); }

		void print(const std::string& obj_name = "")const;
	};
}

//================================================================================
// list<T> ��Ա��������
//================================================================================
namespace kkli {
	
	//create_head_node()
	template<typename T>
	void list<T>::create_head_node() {
		__head = iterator(value_type());	//ͷ�ڵ�
		__head->next = __head.get();
		__head->prev = __head.get();
		__size = 0;
	}

	//get_size(first, last)
	template<typename T>
	typename list<T>::size_type list<T>::get_size(iterator first, iterator last) {
		size_type size = 0;
		for (auto iter = first; iter != last; ++iter)
			++size;
		return size;
	}

	//cheat_from_rhs(&&rhs)
	template<typename T>
	void list<T>::cheat_from_rhs(list&& rhs) {
		__head->next = rhs.__head->next;
		__head->next->prev = __head.get();
		__head->prev = rhs.__head->prev;
		__head->prev->next = __head.get();
		__size = rhs.__size;
		rhs.__head->next = rhs.__head.get();
		rhs.__head->prev = rhs.__head.get();
		rhs.__size = 0;
	}

	// list(count, value)
	template<typename T>
	list<T>::list(size_type count, const value_type& value) {
		if (count == 0) return;
		create_head_node();			//����ͷ�ڵ㣬��������Ч�ڵ�
		for (size_type i = 0; i < count; ++i)
			push_back(value);
	}

	//list(rhs)
	template<typename T>
	list<T>::list(const list& rhs) {
		create_head_node();
		for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter)
			push_back(*iter);
	}

	//list(&&rhs)
	template<typename T>
	list<T>::list(list&& rhs) {
		create_head_node();
		cheat_from_rhs(std::move(rhs));
	}

	//list(il)
	template<typename T>
	list<T>::list(std::initializer_list<T> il) {
		create_head_node();
		for (auto iter = il.begin(); iter != il.end(); ++iter)
			push_back(*iter);
	}

	//~list()
	template<typename T>
	list<T>::~list() {
		clear();				//�����Ч�ڵ�
		__head->next = nullptr;
		__head->prev = nullptr;
		delete __head.get();	//ɾ��ͷ�ڵ�
	}

	//operator =
	template<typename T>
	list<T>& list<T>::operator=(const list& rhs) {
		if (this == &rhs) return *this;				//�������Ҹ�ֵ
		clear();									//���ԭ�нڵ㣨����ͷ�ڵ㣩
		for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter)
			push_back(*iter);
		return *this;
	}

	template<typename T>
	list<T>& list<T>::operator=(list&& rhs) {
		if (this == &rhs) return *this;				//�������Ҹ�ֵ
		clear();									//���ԭ�нڵ㣨�ᱣ��ͷ�ڵ㣩
		cheat_from_rhs(std::move(rhs));
		return *this;
	}

	//assgin(count, value)
	template<typename T>
	void list<T>::assign(size_type count, const value_type& value) {
		clear();
		for (size_type i = 0; i < count; ++i)
			push_back(value);
	}

	template<typename T>
	void list<T>::assign(std::initializer_list<value_type> il) {
		clear();
		for (auto iter = il.begin(); iter != il.end(); ++iter)
			push_back(*iter);
	}

	//clear()
	template<typename T>
	void list<T>::clear() {
		if (__head.get() == nullptr) return;

		__head->prev->next = nullptr;			//ĩβ�ڵ��next�ÿգ���Ϊѭ����������

		auto ptr = __head->next;				//ɾ����__head�����нڵ�
		while (ptr != nullptr) {
			auto del_ptr = ptr;
			ptr = ptr->next;
			delete del_ptr;
		}

		//__head��next��prev��ָ������
		__head->next = __head.get();
		__head->prev = __head->next;
		__size = 0;
	}

	//insert(pos, &&value)
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, value_type&& value) {
		list_node<T>* node=new list_node<T>(std::move(value));			//��std::move()�Ƿ���ࣿ
		node->next = pos->next;
		node->prev = pos.get();
		pos->next = node;
		node->next->prev = node;
		++__size;	//�������
		return pos;
	}

	//insert(pos, count, value)
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, size_type count, const value_type& value) {
		list_node<T>* head_node = new list_node<T>();

		//������count��ֵΪvalue�Ľڵ���
		list_node<T>* ptr = head_node;
		size_type size = 0;
		for (size_type i = 0; i < count; ++i) {
			ptr->next = new list_node<T>(value);
			ptr->next->prev = ptr;
			ptr = ptr->next;
			head_node->prev = ptr;			//head_node->prevʱ��ָ��ĩβ�ڵ�
			++size;
		}

		//���ڵ������뵽posλ��
		head_node->next->prev = pos.get();
		head_node->prev->next = pos->next;
		pos->next->prev = head_node->prev;
		pos->next = head_node->next;
		delete head_node;
		__size += size;		//�������

		return pos;
	}

	//insert(pos, il)
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, std::initializer_list<value_type> il) {
		list_node<T>* head_node = new list_node<T>();

		//������count��ֵΪvalue�Ľڵ���
		list_node<T>* ptr = head_node;
		size_type size = 0;
		for (auto iter = il.begin(); iter != il.end(); ++iter) {
			ptr->next = new list_node<T>(*iter);
			ptr->next->prev = ptr;
			ptr = ptr->next;
			head_node->prev = ptr;
			++size;
		}

		//���ڵ������뵽posλ��
		head_node->next->prev = pos.get();
		head_node->prev->next = pos->next;
		pos->next->prev = head_node->prev;
		pos->next = head_node->next;
		delete head_node;
		__size += size;			//�������

		return pos;
	}

	//erase(first, last)
	template<typename T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
		iterator prev_first = first;		//first��ǰһ���ڵ�
		--prev_first;
		iterator prev_last = last;			//last��ǰһ���ڵ�
		--prev_last;

		//����[first,prev_last]���������ӣ�[first,prev_last]������Ԫ�ض���Ҫɾ��
		prev_first->next = prev_last->next;
		prev_first->next->prev = prev_first.get();

		//ɾ��[first, prev_last]��ָԪ�أ�ע�⣬lastָ���Ԫ����this�ϣ����ڴ�ɾ������
		list_node<T>* ptr = first.get();			//ָ���ɾ���ڵ��ѭ��ָ��
		list_node<T>* end_ptr = prev_last->next;	//��ĩ��ɾ���ڵ��nextָ��
		while (ptr != end_ptr) {
			list_node<T>* del_ptr = ptr;
			ptr = ptr->next;
			delete del_ptr;
			--__size;
		}
		return ++prev_first;
	}

	//push_back(value)
	template<typename T>
	void list<T>::push_back(const value_type& value) {
		list_node<T>* node = new list_node<T>(value);
		node->next = __head.get();
		node->prev = __head->prev;
		__head->prev->next = node;
		__head->prev = node;
		++__size;
	}

	//push_back(&&value)
	template<typename T>
	void list<T>::push_back(value_type&& value) {
		list_node<T>* node = new list_node<T>(std::move(value));
		node->next = __head.get();
		node->prev = __head->prev;
		__head->prev->next = node;
		__head->prev = node;
		++__size;
	}

	//pop_back()
	template<typename T>
	void list<T>::pop_back() {
		if (__size == 0) throw std::runtime_error("list is empty!");
		list_node<T>* del_ptr = __head->prev;
		__head->prev = __head->prev->prev;
		__head->prev->next = __head.get();
		--__size;
		delete del_ptr;
	}

	//push_front(value)
	template<typename T>
	void list<T>::push_front(const value_type& value) {
		list_node<T>* node = new list_node<T>(value);
		node->next = __head->next;
		node->prev = __head.get();
		__head->next->prev = node;
		__head->next = node;
		++__size;
	}

	//push_front(&&value)
	template<typename T>
	void list<T>::push_front(value_type&& value) {
		list_node<T>* node = new list_node<T>(std::move(value));
		node->next = __head->next;
		node->prev = __head.get();
		__head->next->prev = node;
		__head->next = node;
		++__size;
	}

	//pop_front()
	template<typename T>
	void list<T>::pop_front() {
		if (__size == 0) throw std::runtime_error("list is empty!");
		list_node<T>* del_ptr = __head->next;
		__head->next = __head->next->next;
		__head->next->prev = __head.get();
		--__size;
		delete del_ptr;
	}

	//resize(count, value)
	template<typename T>
	void list<T>::resize(size_type count, const value_type& value) {
		if (count <= __size) return;		//���ܼ���Ԫ��
		count -= __size;
		for (size_type i = 0; i < count; ++i)
			push_back(value);
	}

	//merge(&&rhs)
	template<typename T>
	template<typename Compare>
	void list<T>::merge(list&& rhs,Compare comp) {
		iterator lhs_beg = this->begin();
		iterator lhs_end = this->end();
		iterator rhs_beg = rhs.begin();
		iterator rhs_end = rhs.end();

		//��������ڵ���бȽϣ��������������߲��뵽__head��
		iterator iter = __head;
		while (lhs_beg != lhs_end && rhs_beg != rhs_end) {
			if (comp(*lhs_beg, *rhs_beg)) {
				iter->next = lhs_beg.get();
				iter->next->prev = iter.get();
				++lhs_beg;
			}
			else {
				iter->next = rhs_beg.get();
				iter->next->prev = iter.get();
				++rhs_beg;
			}
			++iter;
		}

		//rhs��ĩβ�ڵ��Ƿ���Ϊ����ĩβ�ڵ�
		bool tail_rhs = (rhs_beg != rhs_end ? true : false);

		//��ʣ��ڵ���ӵ�������
		while (lhs_beg != lhs_end) {
			iter->next = lhs_beg.get();
			iter->next->prev = iter.get();
			++lhs_beg;
			++iter;
		}
		while (rhs_beg != rhs_end) {
			iter->next = rhs_beg.get();
			iter->next->prev = iter.get();
			++rhs_beg;
			++iter;
		}

		//���rhs��ĩβ�ڵ���Ϊ����ĩβ�ڵ�
		if (tail_rhs) {
			rhs.__head->prev->next = __head.get();
			__head->prev = rhs.__head->prev;
		}

		//����rhs��__head
		rhs.__head->prev = rhs.__head.get();
		rhs.__head->next = rhs.__head.get();

		//����__size
		__size += rhs.__size;
		rhs.__size = 0;
	}

	//splice(pos, rhs, first, last)
	template<typename T>
	void list<T>::splice(iterator pos, list& rhs, iterator first, iterator last) {
		size_type size = get_size(first, last);			//��ȡ[first, last)�ĳ���

		--last;			//����lastָ��

		//��first��ǰһ���ڵ�����last��һ���ڵ���
		first->prev->next = last->next;
		last->next->prev = first->prev;

		//��[first, last]ָʾ�ڵ���뵽pos��
		last->next = pos->next;
		pos->next->prev = last.get();
		first->prev = pos.get();
		pos->next = first.get();

		__size += size;
		rhs.__size -= size;
	}

	//remove_if(pred)
	template<typename T>
	template<typename UnaryPredicate>
	void list<T>::remove_if(UnaryPredicate pred) {
		iterator iter = this->begin();
		while (iter != end()) {
			if (pred(*iter)) {
				list_node<T>* del_ptr = iter.get();
				--iter;
				iter->next = iter->next->next;
				iter->next->prev = iter.get();
				delete del_ptr;
				--__size;
			}
			++iter;
		}
	}

	//reverse()
	template<typename T>
	void list<T>::reverse() {
		//�ȷ�ת__head��next��prev
		iterator iter = __head;
		iterator end = __head;
		list_node<T>* temp_ptr = iter->next;
		iter->next = iter->prev;
		iter->prev = temp_ptr;

		--iter;				//ע�⣬__head��next��prev������Ҫ�ҵ���һ��Ԫ�أ���Ҫ--
		while (iter != end) {
			temp_ptr = iter->next;
			iter->next = iter->prev;
			iter->prev = temp_ptr;
			--iter;
		}
	}

	//unique(pred)
	template<typename T>
	template<typename BinaryPredicate>
	void list<T>::unique(BinaryPredicate pred) {
		if (__size == 0 || __size == 1) return;

		//Ĭ��list������
		iterator iter = begin();
		++iter;					//������һ��Ԫ��

		//��this���ظ���Ԫ�طŵ�head_node��ָ������
		for (; iter != end(); ++iter) {
			iterator prev_iter = iter;
			--prev_iter;
			if (pred(*iter,*prev_iter)) {
				//iterǰһ��Ԫ������iter��һ��Ԫ��
				prev_iter->next = prev_iter->next->next;
				prev_iter->next->prev = prev_iter.get();

				//ɾ��iter��ָԪ��
				list_node<T>* del_ptr = iter.get();
				delete del_ptr;
				--__size;
				iter = prev_iter;
			}
		}
	}

	//sort(comp)
	template<typename T>
	template<typename Compare>
	void list<T>::sort(Compare comp=std::less<T>()) {
		//�����нڵ����vector����������
		kkli::vector<list_node<T>*> vec(__size);
		int index = 0;
		for (auto iter = this->begin(); iter != this->end(); ++iter)
			vec[index++] = iter.get();
		kkli::sort(vec.begin(), vec.end(), [=](list_node<T>* ptr1, list_node<T>* ptr2)->bool {return comp(ptr1->value, ptr2->value); });
		
		//���½����ڵ�������
		auto head = __head;
		for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
			head->next = *iter;
			(*iter)->prev = head.get();
			++head;
		}
		head->next = __head.get();
		__head->prev = head.get();
	}

	//swap(rhs)
	template<typename T>
	void list<T>::swap(list& rhs) {
		//����ָ���һ�������һ���ڵ�ĵ�����
		iterator temp_beg = this->begin();
		iterator temp_end = this->end();
		--temp_end;

		//thisͷ���nextָ��rhs�ĵ�һ���ڵ�
		__head->next = rhs.__head->next;
		__head->next->prev = __head.get();

		//thisͷ���prevָ��rhs�����һ���ڵ�
		__head->prev = rhs.__head->prev;
		__head->prev->next = __head.get();

		//rhsͷ�ڵ�nextָ��this��һ���ڵ�
		rhs.__head->next = temp_beg.get();
		temp_beg->prev = rhs.__head.get();

		//rhsͷ���prevָ��this���һ���ڵ�
		rhs.__head->prev = temp_end.get();
		temp_end->next = rhs.__head.get();
		 
		//����__size
		size_type temp_size = __size;
		__size = rhs.__size;
		rhs.__size = temp_size;
	}

	//print(prefix)
	template<typename T>
	void list<T>::print(const std::string& obj_name)const {
		std::cout << obj_name << ": ";
		for (auto iter = this->cbegin(); iter != this->cend(); ++iter)
			std::cout << *iter << " ";
		std::cout << std::endl;
		std::cout << "size: " << __size << std::endl;
	}
}

//================================================================================
// list<T> �ǳ�Ա��������
//================================================================================
namespace kkli {

	//operator ==
	template<typename T>
	bool operator==(const list<T>& lhs, const list<T>& rhs) {
		auto lhs_beg = lhs.cbegin();
		auto lhs_end = lhs.cend();
		auto rhs_beg = rhs.cbegin();
		auto rhs_end = rhs.cend();
		while (lhs_beg != lhs_end && rhs_beg != rhs_end) {
			if (*lhs_beg != *rhs_beg) return false;
			++lhs_beg;
			++rhs_beg;
		}
		//���߳��Ȳ�ͬ����false
		if (lhs_beg != lhs_end) return false;
		if (rhs_beg != rhs_end) return false;
		return true;
	}

	//operator !=
	template<typename T>
	bool operator!=(const list<T>& lhs, const list<T>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T>
	bool operator< (const list<T>& lhs, const list<T>& rhs) {
		auto lhs_beg = lhs.cbegin();
		auto lhs_end = lhs.cend();
		auto rhs_beg = rhs.cbegin();
		auto rhs_end = rhs.cend();
		bool smaller = false;
		while (lhs_beg != lhs_end && rhs_beg != rhs_end) {
			if (*lhs_beg > *rhs_beg) return false;
			else if (*lhs_beg < *rhs_beg) smaller = true;
			++lhs_beg;
			++rhs_beg;
		}
		if (lhs_beg != lhs_end) return false;		//lhs������false
		if (rhs_beg != rhs_end) return true;		//rhs������true
		if (smaller) return true;					//���ߵȳ�������Ҫlhs����Ԫ��С��rhs�ж�ӦԪ��
		return false;
	}

	//operator >
	template<typename T>
	bool operator> (const list<T>& lhs, const list<T>& rhs) {
		auto lhs_beg = lhs.cbegin();
		auto lhs_end = lhs.cend();
		auto rhs_beg = rhs.cbegin();
		auto rhs_end = rhs.cend();
		bool greater = false;
		while (lhs_beg != lhs_end && rhs_beg != rhs_end) {
			if (*lhs_beg < *rhs_beg) return false;
			else if (*lhs_beg > *rhs_beg) greater = true;
			++lhs_beg;
			++rhs_beg;
		}
		if (lhs_beg != lhs_end) return true;		//lhs������true
		if (rhs_beg != rhs_end) return false;		//rhs������false
		if (greater) return true;					//���ߵȳ�������Ҫlhs����Ԫ�ش���rhs�ж�ӦԪ��
		return false;
	}

	//operator <=
	template<typename T>
	bool operator<=(const list<T>& lhs, const list<T>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T>
	bool operator>=(const list<T>& lhs, const list<T>& rhs) {
		return !(lhs < rhs);
	}

	//�ǳ�Ա�汾 swap
	template<typename T>
	void swap(list<T>& lhs, list<T>& rhs) { lhs.swap(rhs); }
}