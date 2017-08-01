#pragma once

#include "stdafx.h"
#include "allocator.h"
#include "char_traits.h"

//================================================================================
// string<T> 类定义
//================================================================================

namespace kkli {

	template<
		typename CharType, 
		typename Traits=kkli::char_traits<char>,
		typename Allocator = kkli::allocator<CharType>
	>
	class string {
	public:

		//typedefs
		typedef CharType				value_type;
		typedef Traits					traits_type;
		typedef Allocator				allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type*				iterator;
		typedef const value_type*		const_iterator;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;

		//npos
		constexpr static size_type npos = -1;

	private:

		iterator __start;
		iterator __end;
		iterator __capacity;
		Allocator __alloc;

		//重置内部迭代器
		void __reset_iterators() { __start = __end = __capacity = iterator(); }

		//设置末尾字符为结束字符
		void __set_end_char(size_type pos) {
			*(__start + pos) = kkli::char_traits<value_type>::eof();
		}

		//申请内存并设置相应值
		template<typename InputIterator>
		void __allocate(size_type mem_size, InputIterator first, InputIterator last);

		//申请内存并设置相应值
		void __allocate(size_type mem_size, size_type count, value_type value);

		//释放原有内存
		void __deallocate() { __alloc.deallocate(__start, __capacity - __start); }

		//将[first, last)的字符添加到*this后
		template<typename InputIterator>
		void __append(size_type size, InputIterator first, InputIterator last);

		//将*this赋值为[first,last)所指字符
		template<typename InputIterator>
		void __assign(size_type size, InputIterator first, InputIterator last) {
			__deallocate();
			__allocate(size, first, last);
		}

		//将[first, last)插入pos之后
		template<typename InputIterator>
		void __insert(const_iterator pos, InputIterator first, InputIterator last);

		//将count个value插入pos之后
		void __insert(const_iterator pos, size_type count, value_type value);

	public:

		//获取data的有效字符个数
		static size_type __get_size(const_pointer data);

		//获取[first, last)的字符个数
		template<typename InputIterator>
		static size_type __get_size(InputIterator first, InputIterator last) {
			size_type size = 0;
			for (auto iter = first; iter != last; ++size, ++iter);
			return size;
		}

		//将[first, last)标示的字符复制到指定内存地址中，返回构造的字符个数
		template<typename InputIterator>
		static size_type __set_value(iterator addr, InputIterator first, InputIterator last);

		//将count个value写入指定内存地址中
		static void __set_value(iterator addr, size_type count, value_type value);

		//将[first1, last1)与[first2, last2)进行比较
		template<typename InputIterator>
		static int __compare(size_type size1, InputIterator first1, InputIterator last1,
			size_type size2, InputIterator first2, InputIterator last2);

	public:
		//constructor
		string(const Allocator& alloc = Allocator());
		string(size_type count, value_type value, const Allocator& alloc = Allocator());
		string(const string& rhs, size_type pos, size_type count = npos,
			const Allocator& alloc = Allocator());
		string(const_pointer data, size_type count=npos,
			const Allocator& alloc = Allocator());
		string(size_type count, const Allocator& alloc = Allocator());
		
		template<typename InputIterator>
		string(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());
		string(const string& rhs);
		string(string&& rhs);
		string(std::initializer_list<value_type> init, const Allocator& alloc = Allocator());

		//destructor
		~string();

		//get_allocator
		allocator_type get_allocator()const { return __alloc; }

		//operator =
		string& operator=(const string& rhs){
			if (this == &rhs) return *this;
			__deallocate();
			__allocate(rhs.size() + 1, rhs.begin(), rhs.end());
		}
		string& operator=(string&& rhs);
		string& operator=(const_pointer data){
			if (__start == data) return *this;
			size_type size = __get_size(data);
			__allocate(size + 1, data, data + size);
		}
		string& operator=(std::initializer_list<value_type> init){
			__deallocate();
			__allocate(init.size() + 1, init.begin(), init.end());
		}

		//operator []
		reference operator[](size_type pos) { return __start[pos]; }
		const_reference operator[](size_type pos)const { return __start[pos]; }

		//operator +=
		string& operator+=(const string& rhs) {
			__append(rhs.cbegin(), rhs.cend(), rhs.size());
			return *this;
		}
		string& operator+=(value_type value){
			this->push_back(value);
			return *this;
		}
		string& operator+=(const_pointer data) {
			size_type size = get_size(data);
			__append(data, data + size, size);
			return *this;
		}
		string& operator+=(std::initializer_list<value_type> init){
			__append(init.cbegin(), init.cend(), init.size());
			return *this;
		}

		//assign
		void assign(size_type count, value_type value) {
			__deallocate();
			__allocate(count + 1, count, value);
		}
		void assign(const string& rhs) {
			if (this == &rhs) return;
			__assign(rhs.size() + 1, rhs.cbegin(), rhs.cend());
		}
		void assign(string&& rhs);
		void assign(const string& rhs, size_type pos, size_type count = npos) {
			if (count == npos) count = rhs.size() - pos;
			__assign(count + 1, rhs.cbegin() + pos, rhs.cbegin() + pos + count);
		}
		void assign(const_pointer data, size_type count) {
			if (data == __start && count == this->size()) return;		//自我赋值
			__assign(count + 1, data, data + count);
		}
		void assign(const_pointer data) {
			if (data == __start) return;		//自我赋值
			size_type size = get_size(data);
			__assign(size + 1, data, data + size);
		}

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last) {
			size_type size = __get_size(first, last);
			__assign(size + 1, first, last);

		}
		void assign(std::initializer_list<value_type> init) {
			__assign(init.size() + 1, init.cbegin(), init.cend());
		}

		//insert
		template<typename InputIterator>
		void insert(const_iterator pos, InputIterator first, InputIterator last);
		void insert(const_iterator pos, size_type count, value_type value);
		void insert(size_type index, const string& rhs, size_type index_rhs, size_type count = npos) {
			if (count == npos) count = rhs.size() - index_rhs;
			insert(__start + index, rhs.cbegin() + index_rhs, rhs.cbegin() + index_rhs + count);
		}
		void insert(size_type index, const_pointer data, size_type count = npos) {
			if (count == npos) count = get_size(data);
			__insert(__start + index, data, data + count);
		}

		void insert(size_type index, const string& rhs) { return insert(__start + index, rhs.cbegin(), rhs.cend()); }
		void insert(size_type index, size_type count, value_type value) { insert(__start + index, count, value); }
		void insert(const_iterator pos, value_type value) { insert(pos, 1, value); }
		void insert(const_iterator pos, std::initializer_list<value_type> init) { return insert(pos, init.cbegin(), init.cend()); }

		//erase
		iterator erase(const_iterator first, const_iterator last) {
			__set_value(first, last, __end);			//将[last, __end)元素移动到[first, ~)中
			__end -= last - first;
			return first;
		}
		iterator erase(size_type index = 0, size_type count = npos) {
			if (count == npos) return erase(__start + index, __end);
			else return erase(__start + index, __start + index + count);
		}
		iterator erase(const_iterator pos) { return erase(pos, pos + 1); }

		//append
		void append(const string& rhs, size_type pos, size_type count = npos) {
			if (count == npos) count = rhs.size() - pos;
			__append(count, rhs.cbegin() + pos, rhs.cbegin() + pos + count);
		}
		void append(const string& rhs) { __append(rhs.size(), rhs.cbegin(), rhs.cend()); }
		void append(const_pointer data, size_type count) { __append(count, data, data + count); }
		void append(size_type count, value_type value) { insert(__end, count, value); }
		void append(const_pointer data) {
			size_type size = get_size(data);
			__append(size, data, data + size);
		}

		template<typename InputIterator>
		void append(InputIterator first, InputIterator last) {
			size_type size = get_size(first, last);
			__append(size, first, last);
		}
		void append(std::initializer_list<value_type> init) { __append(init.size(), init.cbegin(), init.cend()); }

		//compare
		int compare(const string& rhs)const {
			return __compare(this->size(), __start, __end, rhs.size(), rhs.cbegin(), rhs.cend());
		}
		int compare(size_type pos, size_type count, const string& rhs)const {
			return __compare(count, __start + pos, __start + pos + count, rhs.size(), rhs.cbegin(), rhs.cend());
		}
		int compare(size_type pos1, size_type count1,
			const string& rhs, size_type pos2, size_type count2 = npos)const {
			if (count2 == npos) count2 = rhs.size() - pos2;
			return __compare(count1, __start + pos1, __start + pos1 + count1, count2,
				rhs.cbegin() + pos2, rhs.cbegin() + pos2 + count2);
		}
		int compare(const_pointer data)const {
			size_type size = __get_size(data);
			return __compare(this->size(), __start, __end, size, data, data + size);
		}
		int compare(size_type pos, size_type count, const_pointer data) {
			size_type size = __get_size(data);
			return __compare(count, __start + pos, __start + pos + count,
				size, data, data + size);
		}
		int compare(size_type pos1, size_type count1,
			const_pointer data, size_type count2)const {
			return __compare(count1, __start + pos1, __start + pos1 + count1,
				count2, data, data + count2);
		}

		//replace
		
		template<typename InputIterator>
		void repalce(const_iterator first1, const_iterator last1,
			InputIterator first2, InputIterator last2) {
			erase(first1, last1);		//移除[first1, last1)
			insert(first1, first2, last2);
		}

		void replace(const_iterator first, const_iterator last, const string& rhs) {
			replace(first, last, rhs.cbegin(), rhs.cend());
		}
		void replace(size_type pos, size_type count, const string& rhs) {
			replace(__start + pos, __start + pos + count, rhs.cbegin(), rhs.cend());
		}
		void replace(size_type pos1, size_type count1,
			const string& rhs, size_type pos2, size_type count2 = npos) {
			if (count2 == npos) count2 = rhs.size() - pos2;
			replace(__start + pos1, __start + pos1 + count1, rhs.cbegin() + pos2, rhs.cbegin() + pos2 + count2);
		}

		void replace(size_type pos, size_type count, const_pointer data, size_type count2) {
			replace(__start + pos, __start + pos + count, data, data + count2);
		}
		void replace(size_type pos, size_type count, const_pointer data) {
			size_type size = __get_size(data);
			replace(__start + pos, __start + pos + count, data, data + size);
		}
		void replace(const_iterator first, const_iterator last, const_pointer data, size_type count2) {
			replace(first, last, data, data + count2);
		}
		void replace(const_iterator first, const_iterator last, const_pointer data) {
			size_type size = __get_size(data);
			replace(first, last, data, data + size);
		}
		void replace(size_type pos1, size_type count1, size_type count2, value_type value) {
			erase(__start + pos1, __start + pos1 + count1);
			insert(__start + pos1, count2, value);
		}
		void replace(const_iterator first, const_iterator last, size_type count2, value_type value) {
			erase(first, last);
			insert(first, count2, value);
		}
		void replace(const_iterator first, const_iterator last, std::initializer_list<value_type> init) {
			replace(first, last), init.cbegin(), init.cend());
		}


		//find
		size_type find(const string& rhs, size_type pos = 0)const;
		size_type find(const_pointer data, size_type pos, size_type count)const;
		size_type find(const_pointer data, size_type pos = 0)const;
		size_type find(value_type value, size_type pos = 0)const;
		size_type rfind(const string& rhs, size_type pos = npos)const;
		size_type rfind(const_pointer data, size_type pos, size_type count)const;
		size_type rfind(const_pointer data, size_type pos = npos)const;
		size_type rfind(value_type value, size_type pos = npos)const;
		size_type find_first_of(const string& rhs, size_type pos = 0)const;
		size_type find_first_of(const_pointer data, size_type pos, size_type count)const;
		size_type find_first_of(const_pointer data, size_type pos = 0)const;
		size_type find_first_of(value_type value, size_type pos = 0)const;
		size_type find_first_not_of(const string& rhs, size_type pos = 0)const;
		size_type find_first_not_of(const_pointer data, size_type pos, size_type count)const;
		size_type find_first_not_of(const_pointer data, size_type pos = 0)const;
		size_type find_first_not_of(value_type value, size_type pos = 0)const;
		size_type find_last_of(const string& rhs, size_type pos = npos)const;
		size_type find_last_of(const_pointer data, size_type pos, size_type count)const;
		size_type find_last_of(const_pointer data, size_type pos = npos)const;
		size_type find_last_of(value_type value, size_type pos = npos)const;
		size_type find_last_not_of(const string& rhs, size_type pos = npos)const;
		size_type find_last_not_of(const_pointer data, size_type pos, size_type count)const;
		size_type find_last_not_of(const_pointer data, size_type pos = npos)const;
		size_type find_last_not_of(value_type value, size_type pos = npos)const;


		//other member functions
		reference			at(size_type pos) {
			if (pos >= this->size()) throw std::runtime_error("下标越界!");
			return __start[pos];
		}
		const_reference		at(size_type pos)const {
			if (pos >= this->size()) throw std::runtime_error("下标越界!");
			return __start[pos];
		}
		value_type&			front() { return __start[0]; }
		const value_type&	front()const { return __start[0]; }
		value_type&			back() { return __end[-1]; }
		const value_type&	back()const { return __end[-1]; }
		iterator			begin() { return __start; }
		const_iterator		cbegin()const { return __start; }
		iterator			end() { return __end; }
		const_iterator		cend()const { return __end; }
		pointer				data() { return __start; }
		const_pointer		data()const { return __start; }

		const pointer		c_str()const { return __start; }
		bool				empty()const { return __start==__end; }
		size_type			size()const { return __end - __start; }
		size_type			length()const { return size(); }
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }
		void				reserve(size_type new_cap = 0);
		size_type			capacity()const { return __capacity - __start; }
		void				shrink_to_fit() {}		//无效果
		void				clear() { __deallocate(); }
		void				push_back(value_type value) { insert(__end, 1, value); }
		void				pop_bck() { __alloc.destroy(--__end); }

		string				substr(size_type pos = 0, size_type count = npos)const;
		size_type			copy(const_pointer data, size_type count, size_type pos = 0)const;
		void				resize(size_type count, value_type value);
		void				resize(size_type count) { resize(count, value_type()); }
		void				swap(string& rhs);
	};
}

//================================================================================
// string<T> 成员函数定义
//================================================================================

namespace kkli {

	//__allocate(mem_size, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void string<CharType, Traits, Allocator>::__allocate(size_type mem_size, InputIterator first, InputIterator last) {
		__start = __alloc.allocate(mem_size);
		size_type index = __set_value(__start, first, last);
		__set_end_char(index);
		__end = __start + index;
		__capacity = __end + 1;
	}

	//__allocate(mem_size, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	void string<CharType, Traits, Allocator>::__allocate(size_type mem_size, size_type count, value_type value) {
		__start = __alloc.allocate(mem_size);
		__set_value(__start, count, value);
		__set_end_char(count);
		__end = __start + count;
		__capacity = __end + 1;
	}

	//__get_size(data)
	template<typename CharType, typename Traits, typename Allocator>
	typename string<CharType, Traits, Allocator>::size_type string<CharType, Traits, Allocator>::__get_size(const_pointer data) {
		size_type size = 0;
		if (data != NULL) {
			for (;; ++size)
				if (data[i] == kkli::char_traits<char>::eof()) break;
		}
		return size;
	}

	//__set_value(addr, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void string<CharType, Traits, Allocator>::__set_value(iterator addr, InputIterator first, InputIterator last) {
		size_type index = 0;
		for (auto iter = first; iter != last; ++iter) {
			*(addr + index) = *iter;
			++index;
		}
		return index;
	}

	//__set_value(addr, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	void string<CharType, Traits, Allocator>::__set_value(iterator addr, size_type count, value_type value) {
		for (size_type i = 0; i < count; ++i) {
			*(addr + i) = value;
		}
	}

	//__append(size, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void string<CharType, Traits, Allocator>::__append(size_type size, InputIterator first, InputIterator last) {
		//剩余空间足够，直接将rhs的内容填充到后面
		if (__capacity - __end > size) {
			size_type new_size = __set_value(__end, rhs.cbegin(), rhs.cend());
			new_size += this->size();
			__set_end_char(new_size);
			__end = __start + new_size;
			//__capacity不变
		}

		//剩余空间不够
		else {
			//可能是自己和自己相加，如str=str+str，则不能直接释放原有内存
			iterator new_addr = __alloc.allocate(this->size() + size + 1);			//刚好能装下，且末尾有一个 '\0'
			size_type index = __set_value(new_addr, __start, __end);					//将[__start,__end)中的字符构造在new_addr中
			index + = __set_value(new_addr + index, rhs.cbegin(), rhs.cend());		//将rhs中的字符构造在new_addr中
			__deallocate();			//释放原有内存
			__start = new_addr;
			__end = __start + index;
			__capacity = __end + 1;
			__set_end_char(index);
		}
	}

	//__compare(count1, first1, last1, count2, first2, last2)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	int string<CharType, Traits, Allocator>::__compare(size_type count1, InputIterator first1, InputIterator last1,
		size_type count2, InputIterator first2, InputIterator last2) {
		auto iter1 = first1;
		auto iter2 = first2;
		while (iter1 != last1 && iter2 != last2) {
			if (*iter1 < *iter2) return -1;
			if (*iter1 > *iter2) return 1;
		}
		if (count1 < count2) return -1;
		if (count1 > count2) return 1;
		return 0;				//对应值相等，且一样长
	}

	//string(alloc)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(1, iterator(), iterator());
	}

	//string(count, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(size_type count, value_type value,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(count + 1, count, value);
	}

	//string(rhs, pos, count)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const string& rhs, size_type pos,
		size_type count = npos, const Allocator& alloc = Allocator())
		:__alloc(alloc) {

		//计算应分配的内存大小
		if (count == npos) count = rhs.size();
		__allocate(count + 1, rhs.cbegin() + pos, rhs.cbegin() + pos + count);
	}

	//string(data, count)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const_pointer data, size_type count = npos,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		if (count == npos) count = __get_size(data);
		__allocate(size + 1, data, data + size);
	}

	//string(first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	string<CharType, Traits, Allocator>::string(InputIterator first, InputIterator last,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(__get_size(first, last) + 1, first, last);
	}

	//string(count)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(size_type count, const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__start = __alloc.allocate(count);
		__end = __start;
		__capacity = __start + count;
	}

	//string(rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const string& rhs) {
		__allocate(rhs.size() + 1, rhs.begin(), rhs.end());
	}

	//string(&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(string&& rhs) {
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		__alloc = rhs.__alloc;
		rhs.__reset_iterators();
	}

	//string(init)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(std::initializer_list<value_type> init,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(init.size() + 1, init.begin(), init.end());
	}

	//~string
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::~string() {
		__deallocate();
		__reset_iterators();
	}

	//operator =(&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator=(string&& rhs) {
		if (this == rhs) return *this;
		__deallocate();
		__alloc = rhs.__alloc;
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		rhs.__reset_iterators();
	}

	//assign(&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	void string<CharType, Traits, Allocator>::assign(string<CharType, Traits, Allocator>&& rhs) {
		if (this == &rhs) return *this;
		__deallocate();
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		__alloc = rhs.__alloc;
		rhs.reset_iterators();
	}

	//insert(pos, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void string<CharType, Traits, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last) {
		if (first == last) return;
		size_type count = __get_size(first, last);

		//剩余空间足够
		if (__capacity - __end > count) {

			//将[pos,__end)所有字符后移count个位置
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			while (src_iter >= pos) {
				*dst_iter = *src_iter;
				--src_iter;
				--dst_iter;
			}

			//将[first, last)插入到pos位置
			__set_value(pos, first, last);
			__set_end_char((__end - __start) + count);

			__end += count;
		}

		//剩余空间不足
		else {
			//rhs可能就是*this，因此不能直接将原内存释放
			size_type new_cap = this->size() + count + 1;
			auto new_addr = __alloc.allocate(new_cap);

			//将this的[0,pos)内容构造到新内存中
			size_type i = __set_value(new_addr, __start, pos);

			__set_value(new_addr + i, first, last);			//将插入值写入
			i += count;
			i += __set_value(new_addr + i, pos, __end);		//将后续值写入

			__deallocate();			//释放原有内存
			__start = new_addr;
			__end = new_addr + i;
			__capacity = __start + new_cap;
			__set_end_char()
		}
	}

	//insert(pos, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	void string<CharType, Traits, Allocator>::insert(const_iterator pos, size_type count, value_type value) {

		//剩余空间足够
		if (__capacity - __end > count) {

			//将[pos,__end)所有字符后移count个位置
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			while (src_iter >= pos) {
				*dst_iter = *src_iter;
				--src_iter;
				--dst_iter;
			}

			//将值写入到pos位置
			__set_value(pos, count, value);
			__set_end_char((__end - __start) + count);

			__end += count;
		}

		//剩余空间不足
		else {
			auto size = this->size();
			auto addr = __allocate.allocate(size + count + 1);
			auto index = __set_value(addr, __start, pos);			//将[0, pos)标示字符写入
			__set_value(addr + index, count, value);				//将插入字符写入
			__set_value(addr + index + count, pos, __end);			//将后续字符写入
			__deallocate();				//释放原有内存
			__start = addr;
			__end = __start + size + count;
			__capacity = __end + 1;
			__set_end_char(size + count);
		}
	}

	//compare(rhs)
	template<typename CharType, typename Traits, typename Allocator>
	int string<CharType, Traits, Allocator>::compare(const string& rhs)const {
		if ((*this) > rhs) return 1;
		if ((*this) == rhs) return 0;
		else return -1;
	}

	//find

	//resize
	template<typename CharType, typename Traits, typename Allocator>
	void string<CharType, Traits, Allocator>::resize(size_type count, value_type value) {
		//TODO: 
	}

	//swap
	template<typename CharType, typename Traits, typename Allocator>
	void string<CharType, Traits, Allocator>::swap(string& rhs){
		auto temp = __start;
		__start = rhs.__start;
		rhs.__start = temp;
		
		temp = __end;
		__end = rhs.__end;
		rhs.__end = temp;

		temp = __capacity;
		__capacity = rhs.__capacity;
		rhs.__capacity = temp;

		auto alloc = __alloc;
		__alloc = rhs.__alloc;
		rhs.__alloc = alloc;
	}
}

//================================================================================
// string<T> 非成员函数定义
//================================================================================

namespace kkli {

	//============================== [operator +] ==============================

	//operator +(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		kkli::string<CharType, Traits, Allocator> str(lhs.size() + rhs.size() + 1);
		str += lhs;
		str += rhs;
		return str;
	}

	//operator +(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		auto data_size = string<CharType, Traits, Allocator>::__get_size(data);
		kkli::string<CharType, Traits, Allocator> str(lhs.size() + data_size + 1);
		str += lhs;
		str += data;
		return str;
	}

	//operator +(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		auto data_size = string<CharType, Traits, Allocator>::__get_size(data);
		kkli::string<CharType, Traits, Allocator> str(lhs.size() + data_size + 1);
		str += data;
		str += lhs;
		return str;
	}

	//operator +(lhs, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		CharType value) {
		kkli::string<CharType, Traits, Allocator> str(lhs.size() + 1);
		str += lhs;
		str.push_back(value);
		return str;
	}

	//operator +(value, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(CharType value, 
		const string<CharType, Traits, Allocator>& rhs) {
		kkli::string<CharType, Traits, Allocator> str(rhs.size() + 1);
		str.push_back(value);
		str += rhs;
		return str;
	}

	//==================== [operator ==, !=, <, <=, >, >=] ====================

	//operator ==(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		return lhs.compare(rhs) == 0;
	}

	//operator ==(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return lhs.compare(data) == 0;
	}

	//operator ==(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		return rhs.compare(data) == 0;
	}

	//operator !=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		return !(lhs == rhs);
	}

	//operator !=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return !(lhs == data);
	}

	//operator !=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		return !(data == rhs);
	}

	//operator <(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Allocator>& rhs) {
		return lhs.compare(rhs) == -1;
	}

	//operator <(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return lhs.compare(data) == -1;
	}

	//operator <(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		return rhs.compare(data) == 1;		//data<rhs，则rhs>data
	}

	//operator >(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		return lhs.compare(rhs) == 1;
	}

	//operator >(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return lhs.compare(data) == 1;
	}

	//operator >(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		return rhs.compare(data) == -1;			//data>rhs，则rhs<data
	}

	//operator <=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		return !(lhs > rhs);
	}

	//operator <=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return !(lhs > data);
	}

	//operator <=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		return !(data > rhs);
	}

	//operator >=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		return !(lhs < rhs);
	}

	//operator >=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return !(lhs < data);
	}

	//operator >=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		return !(data < rhs);
	}


	//============================== [swap] ==============================

	//swap(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	void swap(string<CharType, Traits, Allocator>& lhs,
		string<CharType, Traits, Allocator>& rhs) {
		lhs.swap(rhs);
	}


	//==================== [operator <<, >>] ====================

	//operator <<
	template<typename CharType, typename Traits, typename Allocator>
	std::ostream<CharType, Traits, >& operator<<(
		std::ostream<CharType, Traits>& os,
		const string<CharType, Traits, Allocator>& str) {
		os << str.data();
		return os;
	}

	//operator >>
	template<typename CharType, typename Traits, typename Allocator>
	std::istream<CharType, Traits>& operator<<(
		std::istream<CharType, Traits>& is,
		const string<CharType, Traits, Allocator>& str) {
		is >> str.data();
	}


	//============================== [getline] ==============================

	//getline(is, str, delim)
	template<typename CharType, typename Traits, typename Allocator>
	std::istream<CharType, Traits>& getline(
		std::istream<CharType, Traits>&& is,
		string<CharType, Traits, Allocator>& str, CharType delim) {
		throw 1;
	}

	//getline(is, str)
	template<typename CharType, typename Traits, typename Allocator>
	std::istream<CharType, Traits>& getline(
		std::istream<CharType, Traits>&& is,
		string<CharType, Traits, Allocator>& str) {
		return getline(is, str, '\n');
	}


	//==================== [stox]: 不想实现，好麻烦！！ ====================

	//stoi
	template<typename CharType,typename Traits,typename Allocator>
	int stoi(const kkli::string<CharType,Traits,Allocator>& str,
		std::size_t* pos = 0, int base = 10);

	//stol
	template<typename CharType, typename Traits, typename Allocator>
	long stol(const kkli::string<CharType, Traits, Allocator>& str, 
		std::size_t* pos = 0, int base = 10);

	//stoll
	template<typename CharType, typename Traits, typename Allocator>
	long long stoll(const kkli::string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10);

	//stoul
	template<typename CharType, typename Traits, typename Allocator>
	unsigned long stoul(const kkli::string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10);

	//stoull
	template<typename CharType, typename Traits, typename Allocator>
	unsigned long long stoull(const std::string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10);

	//stof
	template<typename CharType, typename Traits, typename Allocator>
	float stof(const kkli::string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0);

	//stod
	template<typename CharType, typename Traits, typename Allocator>
	double stof(const kkli::string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0);

	//stold
	template<typename CharType, typename Traits, typename Allocator>
	long double stof(const kkli::string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0);

	//to_string(int)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(int value);

	//to_sring(long)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(long value);

	//to_string(long long)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(long long value);

	//to_string(unsigned)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(unsigned value);

	//to_string(unsigned long)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(unsigned long value);

	//to_string(unsigned long long)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(unsigned long long value);

	//to_string(float)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(float value);

	//to_string(double)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(double value);

	//to_string(long double)
	template<typename CharType, typename Traits, typename Allocator>
	kkli::string<CharType, Traits, Allocator> to_string(long double value);
}
