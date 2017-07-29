#pragma once

#include "stdafx.h"
#include "allocator.h"

//================================================================================
// string 类定义
//================================================================================

namespace kkli {

	template<typename CharType, typename Allocator = kkli::allocator<CharType>>
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
		constexpr static size_type npos = std::numeric_limits<size_type>::max();

	private:
		value_type* __data;
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

		string& erase(size_type index = 0, size_type count = npos);
		iterator erase(const_iterator pos);
		iterator(const_iterator first, const_iterator last);

		//TODO: push_back
	};
}