#pragma once

#include "stdafx.h"
#include "memory.h"
#include "iterator.h"
#include "iterator.h"

//================================================================================
// vector<T> 类定义
//================================================================================

namespace kkli {

	template<typename T, typename Allocator = kkli::allocator<T>>
	class vector {
	public:
		//typedefs
		typedef	T							value_type;
		typedef Allocator					allocator_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type*					iterator;
		typedef const value_type*			const_iterator;
		typedef kkli::reverse_iterator<iterator>		reverse_iterator;
		typedef kkli::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::random_access_iterator_tag			iterator_category;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;

	private:
		iterator __start;			//数据首指针
		iterator __end;				//有效数据尾指针
		iterator __capacity;		//容量尾指针
		Allocator __alloc;			//内存分配器

		//析构元素
		void __deallocate();

		//重置内部迭代器
		void __reset_iterators() { __start = __end = __capacity = iterator(); }

		//重新申请内存，并将原有元素复制到新内存中
		void __reallocate_and_copy(size_type new_cap);

		//构造值
		void __construct_value_by_value(iterator addr, size_type count, value_type value) {
			for (; count > 0; --count, ++addr) __alloc.construct(addr, value);
		}
		template<typename InputIt>
		size_type __construct_value_by_range(iterator addr, InputIt first, InputIt last);

		//设置值
		void __set_value_by_value(iterator addr, size_type count, value_type value) {
			for (; count > 0; --count, ++addr) *addr = value;
		}
		template<typename InputIt>
		size_type __set_value_by_range(iterator addr, InputIt first, InputIt last);

		//获取长度
		template<typename InputIt>
		size_type __get_size(InputIt first, InputIt last) { //通过iterator_traits来提高效率
			return __aux_get_size(first, last, typename kkli::iterator_traits<InputIt>::iterator_category());
		}
		//__aux_get_size（__get_size的辅助函数）
		template<typename RandomIt>
		size_type __aux_get_size(RandomIt firt, RandomIt last,kkli::random_access_iterator_tag){
			return last - first;
		}
		//__aux_get_size（__get_size的辅助函数）
		template<typename InputIt>
		size_type __aux_get_size(InputIt firt, InputIt last, kkli::input_iterator_tag) {
			size_type size = 0;
			for (; first != last; ++first, ++size);
			return size;
		}

	public:
		//constructors
		vector() = default;
		vector(const Allocator& alloc) :__alloc(alloc) {}
		vector(size_type count, const value_type& value, const Allocator& alloc = Allocator());
		vector(size_type count, const Allocator& alloc = Allocator()) :vector(count, value_type(), alloc) {}
		vector(const vector& rhs, const Allocator& alloc);
		vector(const vector& rhs) :vector(rhs, Allocator()) {}
		vector(vector&& rhs, const Allocator& alloc);
		vector(vector&& rhs) :vector(std::move(rhs), Allocator()) {}
		vector(std::initializer_list<value_type> init, const Allocator& alloc = Allocator());

		//需要SFINAE
		//template<typename InputIterator>
		//vector(InputIterator first, InputIterator last)

		//destructor
		~vector();

		//operator =
		vector& operator=(const vector& rhs);
		vector& operator=(vector&& rhs);
		vector& operator=(std::initializer_list<value_type> init);

		//assign
		void assign(size_type count, const value_type& value);
		template<typename InputIt>
		void assign_range(InputIt first, InputIt last);
		void assign(std::initializer_list<value_type> init) {
			return assign_range(init.begin(), init.end());
		}

		//at
		reference at(size_type pos);
		const_reference at(size_type pos)const;

		//operator []
		reference operator[](size_type pos) { return __start[pos]; }
		const_reference operator[](size_type pos)const { return __start[pos]; }

		//front & back
		reference front() { return __start[0]; }
		reference back() { return __end[-1]; }
		const_reference front()const { return __start[0]; }
		const_reference back()const { return __end[-1]; }

		//data
		iterator data() { return __start; }
		const_iterator data()const { return __start; }

		//begin & end
		iterator begin() { return __start; }
		iterator end() { return __end; }
		const_iterator cbegin()const { return __start; }
		const_iterator cend()const { return __end; }

		//rbegin & rend
		reverse_iterator rbegin() { return reverse_iterator(__end); }
		reverse_iterator rend() { return reverse_iterator(__start); }
		const_reverse_iterator crbegin()const { return const_reverse_iterator(__end); }
		const_reverse_iterator crend()const { return const_reverse_iterator(__start); }

		//insert
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		iterator insert(const_iterator pos, const value_type& value) { return insert(pos, 1, value); }
		iterator insert(const_iterator pos, value_type&& value);
		template<typename InputIt>
		iterator insert_range(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<value_type> init) {
			return insert_range(pos, init.begin(), init.end());
		}

		//erase
		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator pos) { return erase(pos, pos + 1); }

		//push_back
		void push_back(const value_type& value) { insert(__end, value); }
		void push_back(value_type&& value) { insert(__end, std::move(value)); }
		
		//pop_back
		void pop_back() { erase(__end - 1); }

		//resize
		void resize(size_type count, const value_type& value);
		void resize(size_type count) { resize(count, value_type()); }

		//others
		allocator_type get_allocator()const { return __alloc; }
		bool empty()const { return __start == __end; }
		size_type size()const { return __end - __start; }
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }

		void reserve(size_type new_cap);
		size_type capacity()const { return __capacity - __start; }
		void shrink_to_fit() {} //没有任何效果
		void clear();
		void swap(vector& rhs);

		//print
		void print(const std::string& prefix = "")const;
	};
}

//================================================================================
// vector<T> 成员函数定义
//================================================================================

namespace kkli {

	//__deallocate
	template<typename T, typename Allocator>
	void vector<T, Allocator>::__deallocate() {
		if (this->empty()) return;
		for (auto iter = __start; iter != __end; ++iter) __alloc.destroy(iter);
		__alloc.deallocate(__start, __capacity - __start);
	}

	//__reallocate_and_copy
	template<typename T, typename Allocator>
	void vector<T, Allocator>::__reallocate_and_copy(size_type new_cap) {
		auto start = __start;			//原容器的__start
		__start = __alloc.allocate(new_cap); //申请空间

											 //复制原容器元素到新容器
		size_type size = __construct_value_by_range(__start, start, __end);

		__alloc.deallocate(start, __capacity - start); //释放原有内存
		__end = __start + size;
		__capacity = __start + new_cap;
	}

	//__construct_value_by_range
	template<typename T, typename Allocator>
	template<typename InputIt>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::__construct_value_by_range(
		iterator addr, InputIt first, InputIt last) {
		size_type size = 0;
		for (; first != last; ++first, ++addr, ++size) __alloc.construct(addr, *first);
		return size;
	}

	//__set_value_by_range
	template<typename T, typename Allocator>
	template<typename InputIt>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::__set_value_by_range(
		iterator addr, InputIt first, InputIt last) {
		size_type size = 0;
		for (; first != last; ++first, ++addr, ++size) *addr = *first;
		return size;
	}

	//vector(count, value, alloc)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type count, const value_type& value, const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__start = __alloc.allocate(count);
		__construct_value_by_value(__start, count, value);
		__end = __start + count;
		__capacity = __end;
	}

	//vector(rhs, alloc)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(const vector& rhs, const Allocator& alloc) :__alloc(alloc) {
		size_type size = rhs.size();
		__start = __alloc.allocate(size);
		__construct_value_by_range(__start, rhs.cbegin(), rhs.cend());
		__end = __start + size;
		__capacity = __end;
	}

	//vector(&&rhs, alloc)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(vector&& rhs, const Allocator& alloc) :__alloc(alloc) {
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		rhs.__reset_iterators();
	}

	//vector(init, alloc)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
		:__alloc(Allocator()) {
		size_type size = init.size();
		__start = __alloc.allocate(size);
		__construct_value_by_range(__start, init.begin(), init.end());
		__end = __start + size;
		__capacity = __end;
	}

	//~vector
	template<typename T, typename Allocator>
	vector<T, Allocator>::~vector() {
		__deallocate();
	}

	//operator =(rhs)
	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& rhs) {
		if (this == &rhs) return *this;
		__deallocate(); //释放原有内存

		__alloc = rhs.__alloc;
		size_type size = rhs.size();
		__start = __alloc.allocate(size);
		__construct_value_by_range(__start, rhs.cbegin(), rhs.cend());
		__end = __start + size;
		__capacity = __end;
		return *this;
	}

	//operator =(&&rhs)
	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& rhs) {
		if (this == &rhs) return *this;			//避免自我赋值
		__alloc = rhs.__alloc;
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;

		rhs.__reset_iterators();
		return *this;
	}

	//operator =(init)
	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<value_type> init) {
		__deallocate();
		size_type size = init.size();
		__start = __alloc.allocate(size);
		__construct_value_by_range(__start, init.begin(), init.end());
		__end = __start + size;
		__capacity = __end;
		return *this;
	}

	//assign(count, value)
	template<typename T, typename Allocator>
	void vector<T, Allocator>::assign(size_type count, const value_type& value) {
		__deallocate();		//释放原有内存

		__start = __alloc.allocate(count);
		__construct_value_by_value(__start, count, value);
		__end = __start + count;
		__capacity = __end;
	}

	//assign_range(first, last)
	template<typename T, typename Allocator>
	template<typename InputIt>
	void vector<T, Allocator>::assign_range(InputIt first, InputIt last) {
		__deallocate();
		size_type new_cap = __get_size(first, last);
		__start = __alloc.allocate(new_cap);
		__construct_value_by_range(__start, first, last);
		__end = __start + new_cap;
		__capacity = __end;
	}

	//at(pos)
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
		if (pos >= size()) throw std::out_of_range("out_of_index!");
		return __start[pos];
	}

	//at(pos) const
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const {
		if (pos >= size()) throw std::out_of_range("out of range!");
		return __start[pos];
	}

	//insert(pos, count, value)
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
		const_iterator pos, size_type count, const value_type& value) {
		if (__capacity - __end >= count) { //剩余空间足够
			//将[pos, __end)的元素后移count个位置
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			for (; src_iter >= pos; --src_iter, --dst_iter) *dst_iter = *src_iter;

			//写入值到pos
			auto iter = __start + (pos - __start);
			__set_value_by_value(iter, count, value);
			__end += count;
			return __start + (pos - __start);
		}
		else { //剩余空间不足
			size_type new_cap = (this->size() + count) * 2;
			auto addr = __alloc.allocate(new_cap);
			size_type index = __set_value_by_range(addr, __start, iterator(pos)); //将[0, pos)写入新内存
			auto ret = addr + index; //保存返回值
			__set_value_by_value(addr, count, value); //写入值
			index += count;
			index += __set_value_by_range(addr + index, iterator(pos), __end); //将[pos, __end)写入新内存
			__deallocate(); //释放原有内存
			__start = addr;
			__end = __start + index;
			__capacity = __start + new_cap;
			return ret;
		}
	}

	//insert(pos, &&value)
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, value_type&& value) {
		const size_type count = 1; //便于和其他insert实现对照，因下方实现代码是insert(pos, count, value)稍作修改的
		if (__capacity - __end >= count) { //剩余空间足够
										   //将[pos, __end)的元素后移count个位置
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			for (; src_iter >= pos; --src_iter, --dst_iter) *dst_iter = *src_iter;

			//写入值到pos
			auto iter = __start + (pos - __strt);
			*iter = std::move(value); //修改处
			__end += count;
			return __start + (pos - __start);
		}
		else { //剩余空间不足
			size_type new_cap = (this->size() + count) * 2;
			auto addr = __alloc.allocate(new_cap);
			size_type index = __set_value_by_range(addr, __start, pos); //将[0, pos)写入新内存
			auto ret = addr + index; //保存返回值
			*ret = std::move(value); //修改处
			index += count;
			index += __set_value_by_range(addr + index, pos, __end); //将[pos, __end)写入新内存
			__deallocate(); //释放原有内存
			__start = addr;
			__end = __start + index;
			__capacity = __start + new_cap;
			return ret;
		}
	}

	//insert_range(pos, first, last)
	template<typename T, typename Allocator>
	template<typename InputIt>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert_range(
		const_iterator pos, InputIt first, InputIt last) {
		if (first == last) return;
		size_type count = __get_size(first, last);
		if (__capacity - __end >= count) { //剩余空间足够
			//将[pos, __end)的元素后移count个位置
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			for (; src_iter >= pos; --src_iter, --dst_iter) *dst_iter = *src_iter;

			//写入值到pos
			auto iter = __start + (pos - __strt);
			__set_value_by_range(iter, first, last);
			__end += count;
			return __start + (pos - __start);
		}
		else { //剩余空间不足
			size_type new_cap = (this->size() + count) * 2;
			auto addr = __alloc.allocate(new_cap);
			size_type index = __set_value_by_range(addr, __start, pos); //将[0, pos)写入新内存
			auto ret = addr + index; //保存返回值
			__set_value_by_range(addr, first, last); //写入值
			index += count;
			index += __set_value_by_range(addr + index, pos, __end); //将[pos, __end)写入新内存
			__deallocate(); //释放原有内存
			__start = addr;
			__end = __start + index;
			__capacity = __start + new_cap;
			return ret;
		}
	}

	//erase
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
		size_type size = last - first;

		//将后续元素往前移，覆盖掉[first,last)
		auto iter = __start + (last - __start);
		for (; iter != __end; ++iter) {
			*(iter - size) = std::move(*iter);
		}

		//需要析构后面的size个元素
		for (size_type i = 0; i < size; ++i) {
			--__end;
			__end->~value_type();	//析构元素
		}

		return __start + (first - __start);
	}

	//resize
	template<typename T, typename Allocator>
	void vector<T, Allocator>::resize(size_type count, const value_type& value) {
		if (count <= this->size()) return; //不可缩减内存

										   //不用申请内存
		if (count <= this->capacity()) {		//将末尾共count-size个未构造内存初始化为value
			size_type index = this->size();
			while (index != count) {
				__alloc.construct(__start + index, value);
				++index;
			}
			__end = __start + count;
		}
		//需要申请内存
		else {
			size_type size = this->size();
			reallocate_and_copy(count);

			//将末尾未构造元素用value构造
			while (size != count) {
				__alloc.construct(__end, value);
				++__end;
				++size;
			}
		}
	}

	//reserve
	template<typename T, typename Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap <= capacity()) return;		//空间大小不变
		__reallocate_and_copy(new_cap);
	}

	//clear
	template<typename T, typename Allocator>
	void vector<T, Allocator>::clear() {
		for (auto iter = __star; iter != __end; ++iter)
			__alloc.destory(iter);
		__end = __start;
	}

	//swap
	template<typename T, typename Allocator>
	void vector<T, Allocator>::swap(vector& rhs) {
		kkli::swap(__start, rhs.__start);
		kkli::swap(__end, rhs.__end);
		kkli::swap(__capacity, rhs.__capacity);
	}

	//print
	template<typename T, typename Allocator>
	void vector<T, Allocator>::print(const std::string& prefix = "")const {
		std::cout << prefix;
		for (auto iter = __start; iter != __end; ++iter)
			std::cout << *iter << " ";
		std::cout << endl << "size: " << size() << std::endl;
		std::cout << "capacity: " << capacity() << std::endl;
	}
}

//================================================================================
// vector<T> 非成员函数定义
//================================================================================

namespace kkli{

	//operator ==
	template<typename T, typename Allocator>
	bool operator==(const vector<T,Allocator> lhs, const vector<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		auto iter1 = lhs.cbegin();
		auto iter2 = rhs.cbegin();
		auto end1 = lhs.cend();
		for (; iter1 != end1; ++iter1, ++iter2) if (!(*iter1 == *iter2)) return false;
		return true;
	}

	//operator !=
	template<typename T, typename Allocator>
	bool operator!=(const vector<T, Allocator> lhs, const vector<T, Allocator>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T, typename Allocator>
	bool operator<(const vector<T, Allocator> lhs, const vector<T, Allocator>& rhs) {
		auto iter1 = lhs.cbegin();
		auto iter2 = rhs.cbegin();
		auto end1 = lhs.cend();
		auto end2 = rhs.cend();
		for(;iter1!=end1 && iter2!=end2;++iter1,++iter2){
			if (*iter1 < *iter2) return true;
			if (*iter2 < *iter1) return false;
		}
		if (iter1 == end1 && iter2 != end2) return true; //lhs短
		return false;
	}

	//operator >
	template<typename T, typename Allocator>
	bool operator>(const vector<T, Allocator> lhs, const vector<T, Allocator>& rhs) {
		auto iter1 = lhs.cbegin();
		auto iter2 = rhs.cbegin();
		auto end1 = lhs.cend();
		auto end2 = rhs.cend();
		for (; iter1 != end1 && iter2 != end2; ++iter1, ++iter2) {
			if (*iter2 < *iter1) return true;
			if (*iter1 < *iter2) return false;
		}
		if (iter1 != end1 && iter2 == end2) return true; //lhs长
		return false;
	}

	//operator >=
	template<typename T, typename Allocator>
	bool operator>=(const vector<T, Allocator> lhs, const vector<T, Allocator>& rhs) {
		return !(lhs < rhs);
	}

	//operator <=
	template<typename T, typename Allocator>
	bool operator<=(const vector<T, Allocator> lhs, const vector<T, Allocator>& rhs) {
		return !(lhs > rhs);
	}

	//non-member swap
	template<typename T, typename Allocator>
	void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs) {
		lhs.swap(rhs);
	}
}