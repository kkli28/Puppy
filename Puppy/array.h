#pragma once

#include "stdafx.h"

namespace kkli {
	//================================================================================
	// array<T,N>
	//================================================================================
	template<typename T,std::size_t N>
	class array{
	public:

		//typedefs
		typedef T						value_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type*				iterator;
		typedef const value_type*		const_iterator;
		typedef std::random_access_iterator_tag		iterator_category;

		value_type __data[N];

		//constructors
		array() {}
		array(std::initializer_list<T> il);

		//member funciton
		reference at(size_t index)const;
		reference front()const;
		reference back()const;
		pointer data()const { return __data; }
		iterator begin()const { return __data; }
		iterator end()const { return __data+N; }
		const_iterator cbegin() { return  __data; }
		const_iterator cend() { return __data + N; }
		bool empty()const { return N == 0; }
		size_type size()const { return N; }
		size_type max_size()const { return std::numeric_limits<size_type>::max(); }
		void fill(const value_type& T);
		void swap(const array& rhs);
		array& operator=(const array& rhs);
		reference operator[](size_type index) { return __data[index]; }
	};

	//================================================================================
	// member function
	//================================================================================

	//array(initializer_list)
	template<typename T>
	array<T>::array(std::initializer_list<T> il) {
		if (il.size() > N) throw std::runtime_error("初始化列表中元素个数太多!");
		auto beg = il.begin();
		auto end = il.end();
		int index = 0;
		while (beg != end) {
			__data[index] = *beg;
			++index;
			++beg;
		}
	}

	//at
	template<typename T,size_t N>
	typename array<T,N>::reference array<T,N>::at(size_t index)const {
		if (index < 0 || index >= N) throw runtime_error("下标越界!");
		return __data[index];
	}

	//front
	template<typename T, size_t N>
	typename array<T, N>::reference array<T, N>::front()const {
		if (empty()) throw runtime_error("array为空!");
		return __data[0];
	}

	//back
	template<typename T, size_t N>
	typename array<T, N>::reference array<T, N>::back()const {
		if (empty()) throw runtime_error("array为空!");
		return __data[N - 1];
	}

	//fill
	template<typename T,size_t N>
	void array<T, N>::fill(const value_type& elem) {
		for (size_t i = 0; i < N; ++i)
			__data[i] = elem;
	}

	//swap
	template<typename T,size_t N>
	void array<T, N>::swap(const array<T,N>& rhs) {
		for (size_t i = 0; i < N; ++i) {
			value_type val = __data[i];
			__data[i] = rhs[i];
			rhs[i] = __val;
		}
	}

	//operator =
	template<typename T,size_t N>
	array<T, N>& operator=(const array<T,N>& rhs) {
		for (size_t i = 0; i < N; ++i)
			__data[i] = rhs[i];
	}

	//================================================================================
	// non-member function
	//================================================================================

	//operator ==
	template<typename T, size_t N>
	bool operator==(const array<T, N>& lhs, const array<T, N>& rhs) {
		for (size_t i = 0; i < N; ++i)
			if (lhs[i] != rhs[i]) return false;
		return true;
	}

	//operator !=
	template<typename T,size_t N>
	inline bool operator!=(const array<T, N>& lhs, const array<T, N>& rhs) {
		return !operator==(lhs, rhs);
	}

	//operator <
	template<typename T,size_t N>
	bool operator<(const array<T, N>& lhs, const array<T, N>& rhs) {
		for (size_t i = 0; i < N; ++i)
			if (lhs[i] >= rhs[i]) return false;
		return true;
	}

	//operator >
	template<typename T,size_t N>
	bool operator>(const array<T, N>& lhs, const array<T, N>& rhs) {
		for (size_t i = 0; i < N; ++i)
			if (lhs[i] <= rhs[i]) return false;
		return true;
	}

	//operator <=
	template<typename T,size_t N>
	inline bool operator<=(const array<T, N>& lhs, const array<T, N>& rhs) {
		return !operator>(lhs, rhs);
	}

	//operator >=
	template<typename T,size_t N>
	bool operator>=(const array<T, N>& lhs, const array<T, N>& rhs) {
		return !operator<(lhs, rhs);
	}

	//get
	template<size_t INDEX, typename T,size_t N>
	inline typename array<T,N>::reference get(const array<T, N>& arr) {
		return arr[INDEX];
	}

	//swap
	template<typename T,size_t N>
	void swap(const array<T, N>& lhs, const array<T, N>& rhs) {
		lhs.swap(rhs);
	}

	//tuple_size
	template<typename T,size_t N>
	class tuple_size<const array<T, N>& arr> {
	public:
		constexpr static size_t value = N;
	};

	//tuple_elem
	template<size_t INDEX, typename T,size_t N>
	class tuple_element<INDEX, array<T, N>> {
		typedef T type;
	};
}