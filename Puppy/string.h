#pragma once

#include "stdafx.h"
#include "allocator.h"

//================================================================================
// string 类定义
//================================================================================

namespace kkli {

	template<
		typename CharType, 
		typename Traits=kkli::char_traits, 
		typename Allocator = kkli::allocator<CharType>
	>
	class string {
	public:

		//typedefs
		typedef CharType				value_type;
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
		reference operator[](size_type pos);
		const_reference operator[](size_type pos)const;

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
// string 非成员函数定义
//================================================================================

namespace kkli {

	//============================== [operator +] ==============================

	//operator +(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator +(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		throw 1;
	}
	
	//operator +(lhs, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		CharType value) {
		throw 1;
	}

	//operator +(lhs, &&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(const string<CharType, Traits, Allocator>& lhs,
		string<CharType, Traits, Allocator>&& rhs) {
		throw 1;
	}

	//operator +(&&lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator +(&&lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
		const CharType* data) {
		throw 1;
	}

	//operator +(&&lhs, value)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(string<CharType, Traits, Allocator>&& lhs,
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
	string<CharType, Allocator> operator+(const CharType* data, 
		const string<CharType, Traits, Allocator>& rhs) {
		throw 1;
	}

	//operator +(data,&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	string<CharType, Allocator> operator+(const CharType* data, 
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
	string<CharType, Allocator> operator+(CharType value, 
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

	//TODO: stoi / stol / stoll
}