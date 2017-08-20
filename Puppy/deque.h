#pragma once

#include "stdafx.h"
#include "memory.h"
#include "iterator.h"

//================================================================================
// __deque_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename T, typename Ref, typename Ptr, std::size_t BufSize>
	class __deque_iterator {
	public:
		typedef T				value_type;
		typedef Ptr				pointer;
		typedef Ref				reference;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef kkli::random_access_iterator_tag	iterator_category;

	public:
		typedef T** map_pointer;
		typedef __deque_iterator<T, T&, T*, BufSize> iterator;
		typedef __deque_iterator<T, const T&, const T*, BufSize> const_iterator;
		typedef __deque_iterator self;
		pointer first;
		pointer curr;
		pointer last;
		map_pointer node;
		static std::size_t buffer_size() { return BufSize > 8 ? BufSize : 8; } //至少为8

	private:
		//set_node
		void set_node(map_pointer new_node) { //跳缓冲区
			node = new_node;
			first = *node;
			last = first + difference_type(buffer_size());
		}

		//constructor
		__deque_iterator() :first(nullptr), curr(nullptr), last(nullptr), node(nullptr) {}
		__deque_iterator(pointer ptr, map_pointer mp) 
			:first(*mp), curr(ptr), last(first + difference_type(buffer_size())), node(mp) {}
		__deque_iterator(const iterator& rhs)
			:first(rhs.first), curr(rhs.curr), last(rhs.last), node(rhs.node) {}

		reference operator*()const { return *curr; }
		pointer operator->()const { return &(operator*()); }
		difference_type operator-(const self& rhs) {
			return difference_type(buffer_size())*(node - rhs.node - 1) +
				(curr - first) + (rhs.last - rhs.curr);
		}
		self& operator++() {
			++curr;
			if (curr == last) {
				set_node(node + 1);
				curr = first;
			}
			return *this;
		}
		self operator++(int) {
			self temp = *this;
			++*this;
			return temp;
		}
		self& operator--() {
			if (curr == first) {
				set_node(node - 1);
				curr = last;
			}
			--curr;
			return *this;
		}
		self operator--(int) {
			self temp = *this;
			--*this;
			return temp;
		}
		self& operator+=(difference_type n) {
			//TODO: 
		}
		self operator+(difference_type n)const {
			self temp = *this;
			return temp += n;
		}
		self& operator-=(difference_type n) {
			return *this += -n;
		}
		self operator-(difference_type n)const {
			self temp = *this;
			return temp -= n;
		}

		reference operator[](difference_type n)const {
			return *(*this + n);
		}
		bool operator==(const self& rhs)const {
			return curr == x.curr;
		}
		bool operator!=(const self& rhs)const {
			return !(*this == rhs);
		}
		bool operator<(const self& rhs)const {
			return (node == rhs.node) ? (curr < rhs.curr) : (node < rhs.node);
		}
	};
}
