#pragma once

#include "stdafx.h"
#include "memory.h"
#include "functional.h"
#include "iterator.h"
#include "string.h"
#include "vector.h"
#include "algorithm.h"

//================================================================================
// forward_list_node<T> 类定义
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
// forward_list<T> 类定义
//================================================================================

namespace kkli {

	template<typename T>
	class forward_list {
	public:

		//迭代器
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
		typedef iterator						const_iterator; //即iterator
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef kkli::forward_iterator_tag		iterator_category;

	private:
		iterator __head;

		//将[beg, end)范围的节点插入到pos后
		void __insert(size_type pos, const_iterator first, const_iterator last);
		
		//用[first, last)建立forward_list
		template<typename InputIt>
		void __construct(InputIt first, InputIt last);

		//销毁链表
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

		/* 需要SFINAE
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
		template<typename Compare>
		void merge(forward_list& rhs, Compare comp);
		void merge(forward_list& rhs) {
			merge(rhs, kkli::less<value_type>());
		}

		//splice_after
		void splice_after(const_iterator pos, forward_list& rhs,
			const_iterator first, const_iterator last);
		void splice_after(const_iterator pos, forward_list& rhs) {
			return splice_after(pos, rhs, rhs.begin(), rhs.end());
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
		void sort(Compare comp);
		void sort() {
			sort(kkli::less<value_type>());
		}
		
		void print(const kkli::string& prefix)const;
	};
}

//================================================================================
// forward_list<T> 成员函数定义
//================================================================================

namespace kkli {

	//__insert
	template<typename T>
	void forward_list<T>::__insert(size_type pos, const_iterator first, const_iterator last) {
		//找到插入点
		auto iter = __head;
		size_type count = 0;
		for (; count != pos; ++count, ++iter);

		//将临时链表插入pos位置
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
		auto del_iter = __head;
		auto end = this->end();
		while (__head != end) {
			del_iter = __head;
			++__head;
			delete del_iter.get();
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
		if (__head == rhs.__head) return;
		this->clear();
		auto end = rhs.cend();
		auto iter = __head;
		for (auto i = rhs.cbegin(); i != end; ++i,++iter)
			iter->next = new node_type(*i);
	}

	//operator =(&&rhs)
	template<typename T>
	forward_list<T>& forward_list<T>::operator=(forward_list&& rhs) {
		if (__head == rhs.__head) return;
		__destroy();
		__head = rhs.__head;
		(rhs.__head).get() = nullptr;
	}

	//operator =(init)
	template<typename T>
	forward_list<T>& forward_list<T>::operator=(std::initializer_list<value_type> init) {
		if (__head == rhs.__head) return;
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
		//构建由count个value组合成的链
		auto first = new node_type(value);
		auto iter = first;
		while (--count > 0) {
			iter->next = new node_type(value);
			++iter;
		}

		//拼接
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
		
		//构建由[first, last)元素组成的链
		auto beg = new node_type(*first);
		auto end = beg;
		++first;
		while (first != last) {
			end->next = new node_type(*first);
			++first;
			++end;
		}
		end->next = pos->next; //拼接
		pos->next = beg.get();
	}

	//erase_after
	template<typename T>
	typename forward_list<T>::iterator forward_list<T>::erase_after(
		const_iterator first, const_iterator last) {
		if (first == last) return last;
		auto iter = kkli::next(first);
		auto del_iter = iter;
		while (iter != last) {
			del_iter = iter;
			++iter;
			delete del_iter.get();
		}
		first->next = last.get(); //重新连接
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
		//计算元素个数
		size_type size = 0;
		auto iter = __head;
		auto end = this->end();
		while (++iter != end) ++size;

		if (!(size < count)) return;
		count = count - size;
		end = __head;
		while (end->next != nullptr) ++end;
		while (count > 0) {
			end->next = new node_type(value);
			++end;
			--count;
		}
	}

	//merge(rhs, comp)
	template<typename T>
	template<typename Compare>
	void forward_list<T>::merge(forward_list& rhs, Compare comp) {
		auto iter1 = kkli::next(__head);     //this链
		auto iter2 = kkli::next(rhs.__head); //rhs链
		(rhs.__head).get() = nullptr;

		auto head = __head; //添加位置
		auto end = iterator();
		while ((iter1 != end) && (iter2 != end)) {
			if (!comp(*iter2, *iter1)) {
				head->next = iter1.get();
				++iter1;
			}
			else {
				head->next = iter2.get();
				++iter2;
			}
			++head;
		}
		if (iter1 != end) head->next = iter1.get();
		if (iter2 != end) head->next = iter2.get();
	}

	//splice_after
	template<typename T>
	void forward_list<T>::splice_after(const_iterator pos, forward_list& rhs,
		const_iterator first, const_iterator last) {
		if (first == last) return;
		auto iter = kkli::next(first); //(first, last)链首
		first->next = last.get();
		auto i = iter;
		auto before_last = iter;
		while (++i != last) ++before_last;
		before_last->next = pos->next;
		pos->next = iter.get();
	}

	//remove_if
	template<typename T>
	template<typename UnaryPredicate>
	void forward_list<T>::remove_if(UnaryPredicate pred) {
		auto before = __head;
		auto iter = kkli::next(__head);
		auto end = this->end();
		auto del_iter = iter;
		while (iter != end) {
			if (pred(*iter)) {
				before->next = iter->next;
				del_iter = iter;
				++iter;
				delete del_iter.get();
			}
			else {
				++iter;
				++before;
			}
		}
	}
	
	//reverse
	template<typename T>
	void forward_list<T>::reverse() {
		kkli::vector<iterator> vec; //存放指向每一个元素的迭代器
		auto iter = __head;
		auto end = this->end();
		while (++iter != end) vec.push_back(iter);
		auto size = vec.size();

		//重新连接
		for (auto i = size - 1; i > 0; --i)
			vec[i]->next = vec[i - 1].get();
		vec[0]->next = nullptr;
		__head = vec[size - 1].get();
	}
	
	//unique
	template<typename T>
	template<typename BinaryPredicate>
	void forward_list<T>::unique(BinaryPredicate pred) {
		if (this->empty())) return;
		forward_list<T> fl; //用于暂存多余的重复元素
		auto fl_iter = fl.__head;

		//将多余的重复元素移到fl中
		auto before_iter = kkli::next(__head);
		auto iter = before_iter;
		auto end = this->end();
		while (++iter != end) {
			if (!pred(*before_iter, *iter)) {
				before_iter->next = iter->next;
				fl_iter->next = iter.get();
				++fl_iter;
				fl_iter->next = nullptr;
			}
			else before_iter = iter;
		}

		//fl析构时自动删除多余元素
	}

	//sort
	template<typename T>
	template<typename Compare>
	void forward_list<T>::sort(Compare comp) {
		kkli::vector<iterator> vec;
		auto iter = __head;
		auto end = this->end();
		while (++iter != end) vec.push_back(iter);
		kkli::sort(vec.begin(), vec.end(), 
			[](iterator iter1, iterator iter2)->bool {return iter1->value < iter2->value; });
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

//================================================================================
// forward_list<T> 非成员函数定义
//================================================================================

namespace kkli {

	//swap
	template<typename T>
	void swap(forward_list<T>& lhs, forward_list<T>& rhs) {
		lhs.swap(rhs);
	}

	//operator ==
	template<typename T>
	bool operator==(const forward_list<T>& lhs, const foward_list<T>& rhs) {
		auto iter1 = lhs.begin();
		auto iter2 = rhs.begin();
		auto end1 = lhs.end();
		auto end2 = rhs.end();
		while (iter1 != end1 && iter2 != end2)
			if ((*iter1) != (*iter2)) return false;
		if (iter1 != end1) return false;
		if (iter2 != end2) return false;
		return true;
	}

	//operator <
	template<typename T>
	bool operator<(const forward_list<T>& lhs, const foward_list<T>& rhs) {
		auto iter1 = lhs.begin();
		auto iter2 = rhs.begin();
		auto end1 = lhs.end();
		auto end2 = rhs.end();
		while (iter1 != end1 && iter2 != end2)
			if ((*iter1) < (*iter2)) return true;
		return false;
	}

	//operator >
	template<typename T>
	bool operator>(const forward_list<T>& lhs, const foward_list<T>& rhs) {
		auto iter1 = lhs.begin();
		auto iter2 = rhs.begin();
		auto end1 = lhs.end();
		auto end2 = rhs.end();
		while (iter1 != end1 && iter2 != end2)
			if ((*iter2) < (*iter1)) return true;
		return false;
	}

	//operator !=
	template<typename T>
	bool operator!=(const forward_list<T>& lhs, const foward_list<T>& rhs) {
		return !(lhs == rhs);
	}

	//operator <=
	template<typename T>
	bool operator<=(const forward_list<T>& lhs, const foward_list<T>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T>
	bool operator>=(const forward_list<T>& lhs, const foward_list<T>& rhs) {
		return !(lhs < rhs);
	}
}
