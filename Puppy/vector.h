#pragma once

#include "stdafx.h"
#include "allocator.h"
#include "iterator.h"
#include "iterator_traits.h"

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
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef std::random_access_iterator_tag			iterator_category;

	private:
		iterator __start;			//数据首指针
		iterator __end;				//有效数据尾指针
		iterator __capacity;		//容量尾指针
		Allocator __alloc;			//内存分配器

		//释放原有内存
		void deallocate() { __alloc.deallocate(__start, __capacity - __start); }

		//重置内部迭代器
		void reset_iterators() { __start = __end = __capacity = iterator(); }

		//重新申请内存，并将原有元素复制到新内存中
		void reallocate_and_copy(size_type new_cap);
	public:

		//constructors
		vector() :__start(nullptr), __end(nullptr), __capacity(nullptr) {}
		vector(size_type count, const value_type& value = value_type(), const Allocator& alloc = Allocator());

		//解决本函数覆盖上方函数vector(size_type,const value_type&,const Allocator&)，需要使用SFINAE，然而我不会，so不定义这个函数
		//以后升级了再来，先刷刷小怪
		//template<typename InputIterator>
		//vector(InputIterator first, InputIterator last,
		//	typename kkli::input_iterator_tag = typename kkli::iterator_traits<InputIterator>::iterator_category);

		vector(const vector& rhs);
		vector(vector&& rhs);
		vector(std::initializer_list<value_type> il);

		//destructor
		~vector();

		//operator =
		vector& operator=(const vector& rhs);
		vector& operator=(std::initializer_list<value_type> il);
		vector& operator=(vector&& rhs);

		//assign
		void assign(size_type count, const value_type& value);
		void assign(std::initializer_list<value_type> il) { this->operator=(il); }

		//template<typename InputIterator>	-- 不会！！！
		//void assign(InputIterator first, InputIterator last);

		//at
		reference at(size_type pos);
		const_reference at(size_type pos)const;

		//operator []
		reference operator[](size_type pos) { return __start[pos]; }
		const_reference operator[](size_type pos)const { return __start[pos]; }

		//other member functions
		allocator_type get_allocator()const { return __alloc; }

		iterator begin() { return __start; }
		iterator end() { return __end; }
		const_iterator cbegin()const { return __start; }
		const_iterator cend()const { return __end; }

		reference front() { return __start[0]; }
		reference back() { return __end[-1]; }
		const_reference front()const { return __start[0]; }
		const_reference back()const { return __end[-1]; }

		iterator data() { return __start; }
		const_iterator data()const { return __start; }

		bool empty()const { return __start == __end; }
		size_type size()const { return __end - __start; }
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }

		void reserve(size_type new_cap);
		size_type capacity()const { return __capacity - __start; }
		void shrink_to_fit();
		void clear();

		iterator insert(const_iterator pos, std::initializer_list<value_type> il);
		iterator insert(const_iterator pos, size_type count, const value_type& value) {
			std::vector<value_type> vec(count, value);
			std::initializer_list<value_type> il(vec.data(), vec.data() + vec.size());
			return insert(pos, il);
		}
		iterator insert(const_iterator pos, const value_type& value) { return insert(pos, { value }); }

		//template<typename InputIterator>
		//iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
		//    return insert(pos, std::initializer_list<T>(first, last));
		//}

		//emplace没有实现
		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator pos) { return erase(pos, pos + 1); }
		 
		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back() { erase(__end - 1); }

		/*
		void emplace(const value& value);

		template< class... Args >
		void emplace_back(Args&&... args);

		template< class... Args >
		reference emplace_back(Args&&... args);
		*/

		void resize(size_type count, const value_type& value);
		void resize(size_type count) { resize(count, value_type()); }

		void swap(vector& rhs);

		bool operator==(const vector& rhs);
		bool operator!=(const vector& rhs) { return !operator==(rhs); }
		bool operator< (const vector& rhs);
		bool operator> (const vector& rhs);
		bool operator<=(const vector& rhs) { return !operator>(rhs); }
		bool operator>=(const vector& rhs) { return !operator<(rhs); }

		void print(const std::string& prefix = "")const;
	};
}

//================================================================================
// vector<T> 成员函数定义
//================================================================================
namespace kkli {

	//vector
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type count, const value_type& value = value_type(), const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__start = __alloc.allocate(count);
		for (size_type i = 0; i < count; ++i)
			__alloc.construct(__start + i, value);
		__end = __start + count;
		__capacity = __end;
	}

	//vector(const vecotr&)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(const vector& rhs) :__alloc(rhs.get_allocator()) {
		//只申请足够放已有元素存放的空间(size)，rhs的空余空间不算在内
		size_type cap = rhs.size();
		__start = __alloc.allocate(cap);
		size_type index = 0;
		for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter) {
			__alloc.construct(__start + index, *iter);
			++index;
		}
		__end = __start + cap;
		__capacity = __end;
	}

	//vector(vector&&)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(vector&& rhs) :__alloc(rhs.__alloc) {
		__start = rhs.__start;		//更新内部迭代器
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		rhs.reset_iterators();		//重置rhs的内部迭代器
	}

	//vector(initializer_list)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(std::initializer_list<value_type> il)
		:__alloc(Allocator()) {
		__start = __alloc.allocate(il.end() - il.begin());
		size_type index = 0;
		for (auto iter = il.begin(); iter != il.end(); ++iter) {
			__alloc.construct(__start + index, *iter);
			++index;
		}
		__end = __start + index;
		__capacity = __end;
	}

	//~vector
	template<typename T, typename Allocator>
	vector<T, Allocator>::~vector() {
		deallocate();
		reset_iterators();
	}

	//reallocate
	template<typename T, typename Allocator>
	void vector<T, Allocator>::reallocate_and_copy(size_type new_cap) {
		auto start = __start;						//原容器内存开始位置
		size_type old_cap = capacity();
		__start = __alloc.allocate(new_cap);

		//复制原容器元素到新容器
		size_type index = 0;
		for (auto iter = start; iter != __end; ++iter) {
			__alloc.construct(__start + index, *iter);
			++index;
		}

		__alloc.deallocate(start, old_cap);			//释放原有内存
		__end = __start + index;
		__capacity = __start + new_cap;
	}

	//operator =
	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& rhs) {
		if (this == &rhs) return *this;			//避免自我赋值
		deallocate();		//释放原有内存

		__alloc = rhs.__alloc;
		size_type size = rhs.size();
		__start = __alloc.allocate(size);

		size_type index = 0;
		for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter) {
			__alloc.construct(__start + index, *iter);
			++index;
		}

		__end = __start + size;
		__capacity = __end;
		return *this;
	} 

	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<value_type> il) {
		//原本内存空间足够，直接在上面构造元素
		if (capacity() >= il.size()){
			//将原有元素析构
			size_type size = this->size();
			for (size_type i = 0; i < size; ++i)
				__start[i].~value_type();
			__end = __start;
			//在原有内存空间中构造新元素
			size_type index = 0;
			for (auto iter = il.begin(); iter != il.end(); ++iter) {
				__alloc.construct(__start + index, *iter);
				++index;
			}
			__end += index;
			return *this;
		}
		//原本内存空间不够，需要释放原有内存，并重新申请内存
		else {
			deallocate();			//释放原有内存

			size_type size = il.size();
			__start = __alloc.allocate(size);
			size_type index = 0;
			for (auto iter = il.begin(); iter != il.end(); ++iter) {
				__alloc.construct(__start + index, *iter);
				++index;
			}
			__end = __start + size;
			__capacity = __end;
			return *this;
		}
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& rhs) {
		if (this == &rhs) return *this;			//避免自我赋值
		__alloc = rhs.__alloc;
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;

		rhs.reset_iterators();
		return *this;
	}

	//assign
	template<typename T, typename Allocator>
	void vector<T, Allocator>::assign(size_type count, const value_type& value) {
		deallocate();		//释放原有内存

		__start = __alloc.allocate(count);
		size_type index = 0;
		while (index != count) {
			__alloc.construct(__start + index, value);
			++index;
		}
		__end = __start + count;
		__capacity = __end;
	}

	//at
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
		if (pos >= size()) throw std::runtime_error("下标越界!");
		return __start[pos];
	}

	template<typename T, typename Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const {
		if (pos >= size()) throw std::out_of_range("下标越界!");
		return __start[pos];
	}

	//reserve
	template<typename T, typename Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap <= capacity()) return;		//空间大小不变
		reallocate_and_copy(new_cap);
	}

	//shrink_to_fit
	template<typename T, typename Allocator>
	void vector<T, Allocator>::shrink_to_fit() {
		//暂时没法实现将已分配的部分内存回收，因此该函数没有任何效果
		return;
		/*
		if (__end == __capacity) return;

		//释放__end到__capacity的内存空间，并更新__capacity
		__alloc.deallocate(__end, __capacity - __end);
		__capacity = __end;
		*/
	}

	//clear
	template<typename T, typename Allocator>
	void vector<T, Allocator>::clear() {
		deallocate();
		reset_iterators();
	}

	//TODO: 
	//insert(pos, initializer_list)
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
		const_iterator pos, std::initializer_list<value_type> il) {
		size_type count = il.size();
		//容量空间足够
		if ((__capacity - __end) >= count) {

			//后count个元素需要构造在[__end,__end+count)指向的内存中
			auto iter = __end;
			for (int i = 0; i < count; ++i) {
				__alloc.construct(iter, *(iter - count));
				++iter;
			}

			//将[pos,__end-count)的元素放入[pos+count,__end)中
			//back_iter标示元素放入点，iter表示元素提供点
			auto back_iter = __end - 1;
			iter = back_iter - count;
			for (; iter >= pos; --iter, --back_iter) {
				*back_iter = std::move(*iter);
			}
			__end += count;

			//将initalizer_list中的元素放入[pos,pos+count)中
			iter = __start + (pos - __start);
			for (auto il_iter = il.begin(); il_iter != il.end(); ++iter, ++il_iter) {
				*iter = *il_iter;
			}
			return __start + (pos - __start);
		}

		//容量空间不够
		else {
			auto start = __start;
			size_type size = this->size();					//原容器元素个数
			size_type new_cap = (size + count) * 2;		//容器的新容量
			__start = __alloc.allocate(new_cap);

			//将原内存start到pos的元素构造到新内存中
			size_type index = 0;
			auto iter = start;
			for (; iter < pos; ++iter) {
				__alloc.construct(__start + index, *iter);
				++index;
			}
			auto result = __start + index;			//返回值

			//插入值
			for (auto beg_iter = il.begin(); beg_iter != il.end(); ++beg_iter) {
				__alloc.construct(__start + index, *beg_iter);
				++index;
			}

			//将原内存pos到__end的元素构造到新内存中
			while (iter != __end) {
				__alloc.construct(__start + index, *iter);
				++iter;
				++index;
			}
			__end = __start + index;
			__capacity = __start + new_cap;
			return result;
		}
	}

	//operator ==
	template<typename T, typename Allocator>
	bool vector<T, Allocator>::operator==(const vector& rhs) {
		size_type size = this->size();
		if (size != rhs.size()) return false;
		for (size_type i = 0; i < size; ++i) {
			if (__start[i] != rhs[i]) return false;
		}
		return true;
	}

	//operator <
	template<typename T, typename Allocator>
	bool vector<T, Allocator>::operator<(const vector& rhs) {
		size_type size = this->size();
		if (size > rhs.size()) return false;
		bool smaller = false;		//任一元素小于rhs才行
		for (size_type i = 0; i < size; ++i) {
			if (__start[i] > rhs[i]) return false;
			else if (__start[i] < rhs[i]) smaller = true;
		}

		if (size < rhs.size()) return true;			//比rhs短，则所有元素相等都可以
		if (smaller) return true;					//两者一样长，则至少有一个元素小于rhs才行
		else return false;							//两者一样长，元素也完全相等，则*this不小于rhs
	}

	//operator >
	template<typename T, typename Allocator>
	bool vector<T, Allocator>::operator>(const vector& rhs) {
		size_type size = this->size();
		if (size < rhs.size()) return false;
		bool greater = false;		//任一元素大于rhs才行
		for (size_type i = 0; i < size; ++i) {
			if (__start[i] < rhs[i]) return false;
			else if (__start[i] > rhs[i]) greater = true;
		}

		if (size > rhs.size()) return true;			//比rhs长，则所有元素相等都可以
		if (greater) return true;					//两者一样长，则至少有一个元素大于rhs才行
		else return false;							//两者一样长，元素也完全相等，则*this不大于rhs
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
			__end[i].~value_type();			//析构该元素
		}

		return __start + (first - __start);
	}

	//push_back
	template<typename T, typename Allocator>
	void vector<T, Allocator>::push_back(const value_type& value) {
		//容器未满
		if (__end != __capacity) {
			__alloc.construct(__end, value);
			++__end;
		}
		//容器已满
		else {
			size_type old_cap = capacity();				//原容器容量大小
			size_type new_cap = old_cap * 2;			//容器的新容量大小
			if (new_cap == 0) new_cap = 2;
			reallocate_and_copy(new_cap);				//重新分配内存，并将原有元素移动到新内存中

			//插入元素
			__alloc.construct(__end, value);
			++__end;
		}
	}

	//push_back
	//和push_back(const value_type&)如何区分？代码完全一样
	template<typename T, typename Allocator>
	void vector<T, Allocator>::push_back(value_type&& value) {
		//容器未满
		if (__end != __capacity) {
			__alloc.construct(__end, value);
			++__end;
		}
		//容器已满
		else {
			size_type old_cap = capacity();				//原容器容量大小
			size_type new_cap = old_cap * 2;			//容器的新容量大小
			if (new_cap == 0) new_cap = 2;
			reallocate_and_copy(new_cap);				//重新分配内存，并将原有元素移动到新内存中

														//插入元素
			__alloc.construct(__end, value);
			++__end;
		}
	}

	//resize
	template<typename T, typename Allocator>
	void vector<T, Allocator>::resize(size_type count, const value_type& value) {
		if (count <= size()) return;

		//不用申请内存
		if (count <= capacity()) {		//将末尾共count-size个未构造内存初始化为value
			size_type index = this->size();
			while (index != count) {
				__alloc.construct(__start + index, value);
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

	//swap
	template<typename T, typename Allocator>
	void vector<T, Allocator>::swap(vector& rhs) {
		//swap __start
		auto temp = __start;
		__start = rhs.__start;
		rhs.__start = temp;

		//swap __end
		temp = __end;
		__end = rhs.__end;
		rhs.__end = temp;

		//swap __capacity
		temp = __capacity;
		__capacity = rhs.__capacity;
		rhs.__capacity = temp;

		//swap __alloc: 不需要
	}

	//non-member swap
	template<typename T, typename Allocator>
	void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs) {
		lhs.swap(rhs);
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