#pragma once

#include "stdafx.h"
#include "memory.h"
#include "iterator.h"

//================================================================================
// __deque_iterator<T> �ඨ��
//================================================================================

namespace kkli {

	template<typename T,typename Ref, typename Ptr, std::size_t BufSize>
	class __deque_iterator {
	public:
		typedef T	value_type;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef kkli::random_access_iterator_tag iterator_category;
		typedef T** map_pointer;
		
		typedef __deque_iterator self;
		typedef __deque_iterator<T, T&, T*, BufSize> iterator;
		typedef __deque_iterator<T, const T&, const T*, BufSize> const_iterator;

	public:
		T* first;
		T* curr;
		T* last;
		map_pointer node;

		static size_type buffer_size() { return BufSize > 8 ? BufSize : 8; }
		void set_node(map_pointer new_node) {
			node = new_node;
			first = *node;
			last = first + difference_type(buffer_size());
		}
		reference operator*()const { return *curr; }
		pointer operator->()const { return &(operator*()); }
		difference_type operator-(const self& rhs)const {
			return difference_type(buffer_size())*(node - rhs.node - 1)
				+ (curr - first) + (rhs.last - rhs.curr);
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
			difference_type offset = (curr - first) + n;
			//Ŀ��λ���ڵ�ǰ������
			if (offset >= 0 && offset < difference_type(buffer_size())) {
				curr += n;
			}
			//Ŀ��λ��������������
			else {
				/*
				��offsetΪ�������ֱ�Ӵ�buffer_size�����node����ڵ�ǰnode��ƫ��
				��offsetΪ����node_offset���Դ�һ��ƫ�ƣ�����ǰ������ǰ���и��ţ����������Ҫ+1��
				��offset��buffer_size�������ʱ�պ�����first�ϣ���ʱnode_offset����+1����
				��Ҫ��-offset����-1������
				*/
				difference_type node_offset = offset > 0 ?
					offset / difference_type(buffer_size())
					: -(difference_type(-offset - 1) / difference_type(buffer_size()) + 1);
				set_node(node + node_offset);

				//����curr���»������е�λ�á�ע�⣡offset=(curr-first)+n������first��ʼ�������curr
				curr = first + (offset - node_offset*difference_type(buffer_size()));
			}
			return *this;
		}
		self operator+(difference_type n) {
			self temp = *this;
			return temp += n;
		}
		self& operator-=(difference_type n) {
			return *this += -n;
		}
		self operator-(difference_type n) {
			self temp = *this;
			return temp -= n;
		}
		reference operator[](difference_type n)const {
			return *(*this + n);
		}
		
		bool operator==(const self& rhs)const { return curr = rhs.curr; }
		bool operator!=(const self& rhs)const { return !(*this == rhs); }
		bool operator<(const self& rhs)const {
			return (node == rhs.node) ? (curr < rhs.curr) : (node < rhs.node);
		}
	};
}
