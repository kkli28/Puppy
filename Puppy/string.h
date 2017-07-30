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
		void reset_iterators() { __start = __end = __capacity = iterator(); }

		//设置末尾字符为结束字符
		void set_end_char(size_type pos) {
			__alloc.construct(__start + pos, kkli::char_traits<value_type>::eof());
		}

		//申请内存并设置相应属性
		template<typename InputIterator>
		void allocate(size_type mem_size, InputIterator first, InputIterator last);

		//释放原有内存
		void deallocate() { __alloc.deallocate(__start, __capacity - __start); }

	public:

		//constructor
		string(const Allocator& alloc = Allocator());
		string(size_type count, value_type value, const Allocator& alloc = Allocator());
		string(const string& rhs, size_type pos, size_type count = npos,
			const Allocator& alloc = Allocator());
		string(const_pointer data, size_type count=npos,
			const Allocator& alloc = Allocator());
		
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
		string& operator=(const string& rhs);
		string& operator=(string&& rhs);
		string& operator=(const_pointer data);
		string& operator=(std::initializer_list<value_type> init);

		//operator []
		reference operator[](size_type pos) { return __start[pos]; }
		const_reference operator[](size_type pos)const { return __start[pos]; }

		//operator +=
		string& operator+=(const string& rhs);
		string& operator+=(value_type value);
		string& operator+=(const_pointer data);
		string& operator+=(std::initializer_list<value_type> init);

		//assign
		string& assign(size_type count, value_type value);
		string& assign(const string& rhs);
		string& assign(string&& rhs);
		string& assign(const string& rhs, size_type pos, size_type count = npos);
		string& assign(const_pointer data, size_type count);
		string& assign(const_pointer data);

		template<typename InputIterator>
		string& assign(InputIterator first, InputIterator last);
		string& assign(std::initializer_list<value_type> init);

		//insert
		string& insert(size_type index, size_type count, value_type value);
		string& insert(size_type index, const_pointer data);
		string& insert(size_type index, const_pointer data, size_type count);
		string& insert(size_type index, const string& rhs);
		string& insert(size_type index, const string& rhs, size_type index_str, size_type count=npos);
		string& insert(iterator pos, value_type value);
		string& insert(const_iterator pos, value_type value);
		void insert(const_iterator pos, size_type count, value_type value);
		iterator insert(const_iterator pos, std::initializer_list<value_type> init);

		template<typename InputIterator>
		void insert(const_iterator pos, InputIterator first, InputIterator last);
		
		//append
		string& append(size_type count, value_type value);
		string& append(const string& rhs);
		string& append(const string& rhs, size_type pos, size_type count = npos);
		string& append(const_pointer data, size_type count);
		string& append(const_pointer data);

		template<typename InputIterator>
		string& append(InputIterator first, InputIterator last);
		string& append(std::initializer_list<value_type> init);

		//compare
		int compare(const string& rhs)const;
		int compare(size_type pos, size_type count, const string& rhs)const;
		int compare(size_type pos1, size_type count1,
			const string& rhs, size_type pos1, size_type count2 = npos)const;
		int compare(const_pointer data)const;
		int compare(size_type pos, size_type count, const_pointer data);
		int compare(size_type pos1, size_type count1,
			const_pointer data, size_type count2)const;

		//replace
		string& replace(size_type pos, size_type count, const string& rhs);
		string& replace(const_iterator first, const_iterator last, const string& rhs);
		string& replace(size_type pos1, size_type count1,
			const string& rhs, size_type pos2, size_type count2 = npos);

		template<typename InputIterator>
		string& repalce(const_iterator first1, const_iterator last1,
			InputIterator first2, InputIterator last2);
		string& replace(size_type pos, size_type count, const_pointer data, size_type count2);
		string& replace(size_type pos, size_type count, const_pointer data);
		string& replace(const_iterator first, const_iterator last, const_pointer data, size_type count2);
		string& replace(const_iterator first, const_iterator last, const_pointer data);
		string& replace(size_type pos1, size_type count1, size_type count2, value_type value);
		string& replace(const_iterator first, const_iterator last, size_type count2, value_type value);
		string& replace(const_iterator first, const_iterator last, std::initializer_list<value_type> init);

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
		reference			at(size_type pos);
		const_reference		at(size_type pos)const;
		value_type&			front();
		const value_type&	front()const;
		value_type&			back();
		const value_type&	back()const;
		iterator			begin();
		const_iterator		cbegin()const;
		iterator			end();
		const_iterator		cend()const;
		pointer				data();
		const_pointer		data()const;

		const pointer		c_str()const;
		bool				empty()const;
		size_type			size()const;
		size_type			length()const { return size(); }
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }
		void				reserve(size_type new_cap = 0);
		size_type			capacity()const;
		void				shrink_to_fit();		//无效果
		void				clear();
		void				push_back(value_type value);
		void				pop_bck();

		string&				erase(size_type index = 0, size_type count = npos);
		iterator			erase(const_iterator pos);
		iterator			erase(const_iterator first, const_iterator last);

		string				substr(size_type pos = 0, size_type count = npos)const;
		size_type			copy(const_pointer data, size_type count, size_type pos = 0)const;
		void				resize(size_type count);
		void				resize(size_type count, value_type value);
		void				swap(string& rhs);

		
	};
}

//================================================================================
// string<T> 成员函数定义
//================================================================================

namespace kkli {

	//allocate(mem_size, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void string<CharType, Traits, Allocator>::allocate(size_type mem_size, InputIterator first, InputIterator last) {
		__start = __alloc.allocate(mem_size);
		size_type index = 0;
		for (auto iter = first; iter != last; ++iter) {
			__alloc.construct(__start + index, *iter);
			++index;
		}
		set_end_char(index);
		__end = __start + index;
		__capacity = __end + 1;
	}

	//string(alloc)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		allocate(1, iterator(), iterator());
	}

	//string(count, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(size_type count, value_type value,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__start = __alloc.allocate(count + 1);
		for (size_type i = 0; i < count; ++i)
			__alloc.construct(__start + i, value);
		set_end_char(count);			//设置结束字符
		__end = __start + count;
		__capacity = __end + 1;
	}

	//string(rhs, pos, count)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const string& rhs, size_type pos,
		size_type count = npos, const Allocator& alloc = Allocator())
		:__alloc(alloc) {

		//计算应分配的内存大小
		size_type size = rhs.size();
		if (count >= size) count = size;

		allocate(count + 1, rhs.begin(), rhs.end());
	}

	//string(data, count)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const_pointer data, size_type count = npos,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {

		//计算data中有效字符个数
		size_type size = 0;
		if (data != NULL) {
			for (;; ++size)
				if (data[i] == kkli::char_traits<value_type>::eof()) break;
		}

		allocate(size + 1, data, data + size);
	}

	//string(first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	string<CharType, Traits, Allocator>::string(InputIterator first, InputIterator last,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {

		//计算[first, last)区间的长度
		size_type size = 0;
		for (auto iter = first; iter != last; ++size, ++iter);

		allocate(size + 1, first, last);
	}

	//string(rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(const string& rhs) {
		allocate(rhs.size() + 1, rhs.begin(), rhs.end());
	}

	//string(&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(string&& rhs) {
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		__alloc = rhs.__alloc;
		rhs.reset_iterators();
	}

	//string(init)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::string(std::initializer_list<value_type> init,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		allocate(init.size() + 1, init.begin(), init.end());
	}

	//~string
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>::~string() {
		deallocate();
		reset_iterators();
	}

	//operator =
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator=(const string& rhs) {
		if (this == &rhs) return *this;
		deallocate();
		allocate(rhs.size() + 1, rhs.begin(), rhs.end());
	}

	//operator =
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator=(string&& rhs) {
		if (this == rhs) return *this;
		deallocate();
		__alloc = rhs.__alloc;
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		rhs.reset_iterators();
	}

	//operator =
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator=(const_pointer data) {
		if (this == &rhs) return *this;
		size_type size = 0;
		if (data != NULL) {
			for (;; ++size)
				if (data[i] == kkli::char_traits<char>::eof()) break;
		}
		allocate(size + 1, data, data + size);
	}

	//operator =
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator=(std::initializer_list<value_type> init) {
		if (this == &rhs) return *this;
		deallocate();
		allocate(init.size() + 1, init.begin(), init.end());
	}

	//operator +=
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator+=(const string& rhs) {
		size_type size = rhs.size();

		//剩余空间足够，直接将rhs的内容填充到后面
		if (__capacity - __end > size) {
			for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter) this->push_back(*iter);
		}

		//剩余空间不够
		else {
			//可能是自己和自己相加，如str=str+str，则不能直接释放原有内存
			iterator new_addr = __alloc.allocate(this->size() + size + 1);		//刚好能装下，且末尾有一个 '\0'
			size_type index = 0;

			//复制this
			for (auto iter = __start; iter != __end; ++iter) {
				__alloc.construct(new_addr + index, *iter);
				++index;
			}

			//复制rhs
			for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter) {
				__alloc.construct(new_addr + index, *iter);
				++index;
			}

			__alloc.construct(new_addr + index, kkli::char_traits<char>::eof());		//末尾添加 '\0'
			deallocate();			//释放原有内存
			__start = new_addr;
			__end = __start + index;
			__capacity = __end + 1;
		}
	}

	//operator +=
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator+=(value_type value) {
		this->push_back(value);
		return *this;
	}

	//operator +=
	template<typename CharType,typename Traits,typename Allocator>
	string<CharType, Traits, Allocator>& string<CharType, Traits, Allocator>::operator+=(const_pointer data) {
		//TODO: 考虑用便捷函数实现在this后添加[first, last)元素
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
		throw 1;
	}

	//operator +(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}
	
	//operator +(lhs, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		CharType value) {
		throw 1;
	}

	//operator +(lhs, &&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		string<CharType, Traits, Allocator>&& rhs) {
		throw 1;
	}

	//operator +(&&lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator +(&&lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator +(&&lhs, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
		CharType value) {
		throw 1;
	}

	//operator +(&&lhs, &&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
		string<CharType, Traits, Allocator>&& rhs) {
		throw 1;
	}

	//operator +(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator +(data,&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(const CharType* data,
		string<CharType, Traits, Allocator>&& rhs) {
		throw 1;
	}

	//operator +(value, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(CharType value, 
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator +(value, &&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Traits, Allocator> operator+(CharType value, 
		string<CharType, Traits, Allocator>&& rhs) {
		throw 1;
	}


	//==================== [operator ==, !=, <, <=, >, >=] ====================

	//operator ==(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator ==(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator ==(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator !=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator !=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator !=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator <(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Allocator>& rhs) {
		throw 1;
	}

	//operator <(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator <(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator <=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator <=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator <=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator >(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator >(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator >(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator >=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator >=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator >=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const CharType* data,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}


	//============================== [swap] ==============================

	//swap(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	void swap(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}


	//==================== [operator <<, >>] ====================

	//operator <<
	template<typename CharType, typename Traits, typename Allocator>
	std::ostream<CharType, Traits, >& operator<<(
		std::ostream<CharType, Traits>& os,
		const string<CharType, Traits, Allocator>& str) {
		throw 1;
	}

	//operator >>
	template<typename CharType, typename Traits, typename Allocator>
	std::istream<CharType, Traits>& operator<<(
		std::istream<CharType, Traits>& is,
		const string<CharType, Traits, Allocator>& str) {
		throw 1;
	}


	//============================== [getline] ==============================

	//getline(is, str, delim
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
		throw 1;
	}


	//============================== [stox] ==============================

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
