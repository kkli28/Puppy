#pragma once

#include "stdafx.h"
#include "memory.h"
#include "iterator.h"
#include "algorithm.h"

//__deque_buf_size

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

		static size_type buffer_size() { return BufSize > 8 ? BufSize : 8; }
	public:
		T* first;
		T* curr;
		T* last;
		map_pointer node;

		__deque_iterator()
			:first(nullptr), curr(nullptr), last(nullptr), node(nullptr) {}
		__deque_iterator(T* ptr, map_pointer mp)
			:first(*mp), curr(ptr), last(*mp + buffer_size()), node(mp) {}
		__deque_iterator(const iterator& rhs)
			:first(rhs.first), curr(rhs.curr), last(rhs.last), node(rhs.node) {}

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

//================================================================================
// deque<T> �ඨ��
//================================================================================

namespace kkli {

	template<typename T, typename Allocator=kkli::allocator<T>>
	class deque {
	public:
		typedef Allocator				allocator_type;
		typedef T						value_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;

		typedef __deque_iterator<T, reference, pointer, 8>				iterator;
		typedef __deque_iterator<T, const_reference, const_pointer, 8>	const_iterator;
		typedef kkli::reverse_iterator<iterator>		reverse_iterator;
		typedef kkli::reverse_iterator<const_iterator>	const_reverse_iterator;

	public:
		typedef pointer* map_pointer;
		typedef kkli::allocator<value_type> data_allocator;
		typedef kkli::allocator<pointer> map_allocator;

	private:
		iterator start;
		iterator finish;
		map_pointer map;
		size_type map_size;
		
		constexpr static size_type buffer_size = 8;		//����������
		constexpr static size_type init_map_size = 8;	//��Сmap_size
		pointer allocate_node(size_type elems) { return data_allocator.allocate(buffer_size); }; //���仺����
		void create_map_and_nodes(size_type num_size);	//����map����������
		void destroy_map_and_nodes(); //����map�Ͷ�Ӧ�Ļ�����
		void fill_initialize(size_type count, const value_type& value); //����deque
		void reset_data_members(); //�������ݳ�Ա

	public:
		//constructor
		explicit deque(const allocator_type& alloc)
			:start(), finish(), map(nullptr), map_size(0) {
			create_map_and_nodes(0);
		}
		deque() :deque(allocator_type()) {}
		deque(size_type count, const_reference value, const Allocator& alloc = allocator_type()) {
			fill_initialize(count, value);
		}
		explicit deque(size_type count) :deque(count, value_type(), allocator_type()) {}
		deque(const deque& rhs, const allocator_type& alloc) {
			create_map_and_nodes(rhs.size());
			kkli::uninitialized_copy(rhs.begin(), rhs.end(), start);
		}
		deque(const deque& rhs) :deque(rhs, allocator_type()) {}
		deque(deque&& rhs, const allocator_type& alloc)
			:start(std::move(rhs.start)), finish(std::move(rhs.finish)), map(rhs.map), map_size(rhs.map_size) {
			rhs.reset_data_members();
		}
		deque(deque&& rhs) :deque(std::move(rhs), allocator_type()) {}
		deque(std::initializer_list<value_type> init, const allocator_type& alloc) {
			create_map_and_nodes(init.size());
			kkli::uninitialized_copy(init.begin(), init.end(), start);
		}

		~deque() {
			kkli::destroy(start, finish);
			destroy_map_and_nodes();
		}
	};
}

//deque<T> �ǳ�Ա��������
namespace kkli {

	//create_map_and_nodes
	template<typename T,typename Allocator>
	void deque<T, Allocator>::create_map_and_nodes(size_type num_size) {
		sizse_type num_nodes = num_size / buffer_size + 1; //������Ҫ��node����
		map_size = kkli::max(init_map_size, num_nodes);
		map = map_allocator.allocate(map_size); //�����ܿ�map

		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;
		map_pointer curr;
		for (curr = nstart; curr != nfinish; ++curr)
			*curr = allocate_node(); //���仺����

		start.set_node(nstart);
		finish.set_node(nfinish);
		start.curr = start.first;
		finish.curr = finish.first + num_size%buffer_size;
	}

	//create_map_and_nodes
	template<typename T, typename Allocator>
	void deque<T, Allocator>::destroy_map_and_nodes() {
		for (map_pointer curr = start.node; curr != finish.node; ++curr)
			data_allocator.deallocate(*curr, buffer_size); //�ͷŻ������ڴ�
		map_allocator.deallocate(map, map_size); //�ͷ�map�ܿ��ڴ�
	}

	//reset_data_members
	template<typename T, typename Allocator>
	void deque<T, Allocator>::reset_data_members() {
		start = iterator();
		finish = iterator();
		map = nullptr;
		map_size = 0;
	}

	//fill_initialize
	template<typename T, typename Allocator>
	void deque<T, Allocator>::fill_initialize(size_type count, const value_type& value) {
		create_map_and_nodes(count);
		map_pointer curr;
		for (curr = start.node; curr != finish.node; ++curr) //��ǰ��������������ֵ
			kkli::uninitialized_fill(*curr, *curr + buff_size, value);
		kkli::uninitailized_fill(finish.first, finish.curr, value); //�����һ������������Ч���ָ�ֵ
	}
}
