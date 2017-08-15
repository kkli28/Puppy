#pragma once

#include "stdafx.h"
#include "iterator.h"
#include "algorithm.h"
#include "string.h"

//================================================================================
// array<T,N> 类定义
//================================================================================

namespace kkli {
	template<typename T, std::size_t N>
	class array{
	public:

		//typedefs
		typedef T						value_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;
		typedef value_type*				iterator;
		typedef const value_type*		const_iterator;
		typedef kkli::reverse_iterator<iterator> reverse_iterator;
		typedef kkli::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::random_access_iterator_tag		iterator_category;

	private:
		pointer __data;

	public:
		//constructors
		array();
		array(std::initializer_list<T> il);

		//复制构造
		array(const array& rhs) : __data(rhs.__data) {}

		//member funciton
		reference at(std::size_t index);
		reference front() { return __data[0]; }
		reference back() { return __data[N - 1]; }
		pointer data() { return __data; }
		const_pointer data()const { return __data; }

		iterator begin() { return __data; }
		iterator end() { return __data + N; }
		const_iterator cbegin()const { return  __data; }
		const_iterator cend()const { return __data + N; }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator crbegin()const { return const_reverse_iterator(cend()); }
		const_reverse_iterator crend()const { return const_reverse_iterator(cbegin()); }

		bool empty()const { return N == 0; }
		size_type size()const { return N; }
		size_type max_size()const { return std::numeric_limits<size_type>::max(); }

		void fill(const value_type& elem);
		void swap(array& rhs) { kkli::swap(__data, rhs.__data); }

		array& operator=(const array& rhs);
		reference operator[](size_type index) { return __data[index]; }
		const_reference operator[](size_type index) const { return __data[index]; }
		void print(const kkli::string& prefix)const;
	};

	//array
	template<typename T, std::size_t N>
	array<T, N>::array() : __data(new value_type[N]) {
		for (size_type i = 0; i < N; ++i) __data[i] = value_type();
	}

	//array(initializer_list)
	template<typename T, std::size_t N>
	array<T, N>::array(std::initializer_list<T> il) {
		__data = new value_type[N];
		auto beg = il.begin();
		for (size_type i = 0; i < N; ++i) __data[i] = *(beg++);
	}

	//at
	template<typename T, std::size_t N>
	typename array<T, N>::reference array<T, N>::at(std::size_t index) {
		if (index < 0 || index >= N) throw runtime_error("下标越界!");
		return __data[index];
	}

	//fill
	template<typename T, std::size_t N>
	void array<T, N>::fill(const value_type& elem) {
		for (size_type i = 0; i < N; ++i)
			__data[i] = elem;
	}

	//operator =
	template<typename T, std::size_t N>
	array<T, N>& array<T, N>::operator=(const array<T, N>& rhs) {
		for (std::size_t i = 0; i < N; ++i)
			__data[i] = rhs[i];
		return *this;
	}

	//print
	template<typename T, std::size_t N>
	void array<T, N>::print(const kkli::string& prefix)const {
		std::cout << prefix << ": ";
		for (std::size_t i = 0; i < N; ++i)
			cout << __data[i] << " ";
		std::cout << std::endl;
	}
}

//================================================================================
// non-member function
//================================================================================

namespace kkli{

	//operator ==
	template<typename T, std::size_t N>
	bool operator==(const array<T, N>& lhs, const array<T, N>& rhs) {
		for (std::size_t i = 0; i < N; ++i)
			if (lhs[i] != rhs[i]) return false;
		return true;
	}

	//operator !=
	template<typename T,std::size_t N>
	inline bool operator!=(const array<T, N>& lhs, const array<T, N>& rhs) {
		return !(lhs==rhs);
	}

	//operator <
	template<typename T,std::size_t N>
	bool operator<(const array<T, N>& lhs, const array<T, N>& rhs) {
		for (std::size_t i = 0; i < N; ++i)
			if (lhs[i] < rhs[i]) return true;
		return false;
	}

	//operator >
	template<typename T,std::size_t N>
	bool operator>(const array<T, N>& lhs, const array<T, N>& rhs) {
		for (std::size_t i = 0; i < N; ++i)
			if (!(lhs[i] < rhs[i]) && !(lhs[i]==rhs[i])) return true;
		return false;
	}

	//operator <=
	template<typename T,std::size_t N>
	inline bool operator<=(const array<T, N>& lhs, const array<T, N>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T,std::size_t N>
	bool operator>=(const array<T, N>& lhs, const array<T, N>& rhs) {
		return !(lhs < rhs);
	}

	//get
	template<std::size_t INDEX, typename T,std::size_t N>
	inline typename array<T,N>::value_type get(const array<T, N>& arr) {
		return arr[INDEX];
	}

	//swap
	template<typename T,std::size_t N>
	void swap(array<T, N>& lhs, array<T, N>& rhs) {
		lhs.swap(rhs);
	}

	//tuple_size
	template<typename T>
	class tuple_size;

	template<typename T,std::size_t N>
	class tuple_size<array<T, N>> {
	public:
		typedef std::size_t value_type;
		constexpr static value_type value = N;
	};

	//tuple_element
	template<std::size_t INDEX, typename T>
	class tuple_element;

	template<std::size_t INDEX, typename T,std::size_t N>
	class tuple_element<INDEX, array<T, N>> {
	public:
		typedef T type;
	};
}