#pragma once

#include "stdafx.h"
#include "memory.h"
#include "iterator.h"
#include "algorithm.h"
#include "string.h"

//================================================================================
// __deque_iterator<T> 类定义
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
		self& operator=(const iterator& rhs) {
			first = rhs.first;
			curr = rhs.curr;
			last = rhs.last;
			node = rhs.node;
			return *this;
		}

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
			//目标位置在当前node
			if (offset >= 0 && offset < difference_type(buffer_size())) {
				curr += n;
			}
			//目标位置在其他node
			else {
				/*
				若offset为正，则可直接处buffer_size获得新node相对于当前node的偏移
				若offset为负，node_offset则自带一个偏移（因向前，故最前方有负号），故最后需要+1。
				因offset与buffer_size正好相等时刚好落在first上，此时node_offset不需+1，故
				需要对-offset进行-1来避免
				*/
				difference_type node_offset = offset > 0 ?
					offset / difference_type(buffer_size())
					: -(difference_type(-offset - 1) / difference_type(buffer_size()) + 1);
				set_node(node + node_offset);

				//设置curr在新node中的位置。注意！offset=(curr-first)+n，即从first开始算起而非curr
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
		
		bool operator==(const self& rhs)const { return curr == rhs.curr; }
		bool operator!=(const self& rhs)const { return !(*this == rhs); }
		bool operator<(const self& rhs)const {
			return (node == rhs.node) ? (curr < rhs.curr) : (node < rhs.node);
		}
	};
}

//================================================================================
// deque<T> 类定义
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

	private:
		//数据成员
		iterator start;
		iterator finish;
		map_pointer map;
		size_type map_size;
		kkli::allocator<value_type>	data_allocator; //产生node和value
		kkli::allocator<pointer>	map_allocator;	//产生map

		//辅助函数
		constexpr static size_type buffer_size = 8;		//node容量
		constexpr static size_type init_map_size = 8;	//最小map_size
		pointer allocate_node() { return data_allocator.allocate(buffer_size); } //分配node
		void deallocate_node(pointer ptr) { data_allocator.deallocate(ptr,buffer_size); } //销毁node
		void create_map_and_nodes(size_type num_size);	//分配map并设置完善
		void destroy_map_and_nodes(); //销毁map和对应的node
		void fill_initialize(size_type count, const value_type& value); //构建deque
		void reset_data_members(); //重置数据成员
		void reallocate_map(size_type nodes_to_add, bool add_at_front); //重新分配map
		void reserve_map_at_front(size_type nodes_to_add = 1) { //map的前方扩容
			if (nodes_to_add > start.node - map) reallocate_map(nodes_to_add, true);
		}
		void reserve_map_at_back(size_type nodes_to_add = 1) { //map的后方扩容
			if (nodes_to_add + 1 > map_size - (finish.node - map)) reallocate_map(nodes_to_add, false);
		}
		void push_front_aux(const value_type& value); //当前node前方已满，需要在前新建node
		void push_back_aux(const value_type& value); //当前node只有一个剩余空间，需要在后新建node
		void pop_front_aux(); //需要释放node
		void pop_back_aux(); //需要释放node
		void destroy(pointer first, pointer last); //销毁[first, last)内的元素
		iterator insert_aux(const_iterator pos, size_type count, const value_type& value);
		template<typename InputIt>
		iterator insert_range_aux(const_iterator pos, InputIt first, InputIt last);

		template<typename InputIt> //get_size
		size_type get_size(InputIt first, InputIt last) {
			return get_size(first, last, typename kkli::iterator_traits<InputIt>::iterator_category());
		}
		template<typename InputIt> //get_size对input iterator的重载
		size_type get_size(InputIt first, InputIt last, kkli::input_iterator_tag) {
			size_type size = 0;
			for (; first != last; ++first, ++size);
			return size;
		}
		template<typename RandomIt> //get_size对random access iterator的重载
		size_type get_size(RandomIt first, RandomIt last, kkli::random_access_iterator_tag) {
			return last - first;
		}
		
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
			kkli::uninitialized_copy(rhs.cbegin(), rhs.cend(), start);
		}
		deque(const deque& rhs) :deque(rhs, allocator_type()) {}
		deque(deque&& rhs, const allocator_type& alloc)
			:start(std::move(rhs.start)), finish(std::move(rhs.finish)), map(rhs.map), map_size(rhs.map_size) {
			rhs.reset_data_members();
		}
		deque(deque&& rhs) :deque(std::move(rhs), allocator_type()) {}
		deque(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type()) {
			create_map_and_nodes(init.size());
			kkli::uninitialized_copy(init.begin(), init.end(), start);
		}

		//destructor
		~deque() {
			kkli::destroy(start, finish);
			destroy_map_and_nodes();
		}

		//operator =
		deque& operator=(const deque& rhs);
		deque& operator=(deque&& rhs);
		deque& operator=(std::initializer_list<value_type> init) {
			assign_range(init.begin(), init.end());
		}

		//assign
		void assign(size_type count, const value_type& value);
		template<typename InputIt>
		void assign_range(InputIt first, InputIt last);
		void assign(std::initializer_list<value_type> init) {
			assign_range(init.begin(), init.end());
		}

		//at
		reference at(size_type pos) {
			if (pos >= this->size()) throw std::out_of_range("");
			return *(start + pos);
		}
		const_reference at(size_type pos)const {
			if (pos >= this->size()) throw std::out_of_range("");
			return *(start + pos);
		}

		//operator []
		reference operator[](size_type pos) { return *(start + pos); }
		const_reference operator[](size_type pos)const { return *(start + pos); }

		//front & back
		reference front() { return *start; }
		reference back() { return *(finish - 1); }
		const_reference front()const { return *start; }
		const_reference back()const { return *(finish - 1); }

		//begin & end
		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator cbegin()const { return start; }
		const_iterator cend()const { return finish; }

		//rbegin & rend
		reverse_iterator rbegin() { return reverse_iterator(finish); }
		reverse_iterator rend() { return reverse_iterator(start); }
		const_reverse_iterator crbegin()const { return const_reverse_iterator(finish); }
		const_reverse_iterator crend()const { return const_reverse_iterator(start); }

		//insert
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		iterator insert(const_iterator pos, const value_type& value) {
			return insert(pos, 1, value);
		}
		template<typename InputIt>
		iterator insert_range(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<value_type> init) {
			return insert_range(pos, init.begin(), init.end());
		}

		//erase
		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator pos) {
			return erase(pos, kkli::next(pos));
		}

		//resize
		void resize(size_type count, value_type value) {
			if (count <= this->size()) return;
			insert(finish, count - this->size(), value);
		}
		void resize(size_type count) { resize(count, value_type()); }
		
		//others
		allocator_type get_allocator()const { return allocator_type(); }
		bool empty()const { return start == finish; }
		size_type size()const { return finish - start; }
		constexpr size_type max_size() { return std::numeric_limits<size_type>::max(); }
		void clear();
		void push_front(const value_type& value);
		void push_back(const value_type& value);
		void pop_front();
		void pop_back();
		void swap(deque& rhs);

		void print(const kkli::string& prefix)const {
			std::cout << prefix << ": ";
			for (iterator iter = start; iter != finish; ++iter)
				std::cout << *iter << " ";
			std::cout << std::endl << "size: " << this->size() << std::endl;
		}
	};
}

//================================================================================
// deque<T> 成员函数定义
//================================================================================

namespace kkli {

	//create_map_and_nodes
	template<typename T, typename Allocator>
	void deque<T, Allocator>::create_map_and_nodes(size_type num_size) {
		size_type num_nodes = num_size / buffer_size + 1; //计算需要的node个数
		map_size = kkli::max(init_map_size, num_nodes + 2);
		map = map_allocator.allocate(map_size); //分配总控map

		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;
		map_pointer curr;
		for (curr = nstart; curr <= nfinish; ++curr)
			*curr = allocate_node(); //只分配必要的node

		start.set_node(nstart);
		finish.set_node(nfinish);
		start.curr = start.first;
		finish.curr = finish.first + num_size%buffer_size;
	}

	//destroy_map_and_nodes
	template<typename T, typename Allocator>
	void deque<T, Allocator>::destroy_map_and_nodes() {
		for (map_pointer curr = start.node; curr != finish.node; ++curr)
			data_allocator.deallocate(*curr, buffer_size); //释放node内存
		map_allocator.deallocate(map, map_size); //释放map总控内存
	}

	//reset_data_members
	template<typename T, typename Allocator>
	void deque<T, Allocator>::reset_data_members() {
		start = iterator();
		finish = iterator();
		map = nullptr;
		map_size = 0;
	}

	//reallocate_map
	template<typename T, typename Allocator>
	void deque<T, Allocator>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
		size_type old_nums = finish.node - start.node + 1;
		size_type new_nums = old_nums + nodes_to_add;

		map_pointer new_nstart;
		if (map_size > 2 * new_nums) { //原本空间足够
			new_nstart = map + (map_size - new_nums) / 2 + (add_at_front ? nodes_to_add : 0);
			//将new_nstart移到正确地位置
			if (new_nstart < start.node) kkli::copy(start.node, finish.node + 1, new_nstart);
			else kkli::copy_backward(start.node, finish.node + 1, new_nstart + old_nums);
		}
		else { //原本空间不够
			size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
			map_pointer new_map = map_allocator.allocate(new_map_size);
			new_nstart = new_map + (new_map_size - new_nums) / 2 + (add_at_front ? nodes_to_add : 0);
			kkli::copy(start.node, finish.node + 1, new_nstart);
			map_allocator.deallocate(map, map_size);
			map = new_map;
			map_size = new_map_size;
		}
		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_nums - 1);
	}

	//fill_initialize
	template<typename T, typename Allocator>
	void deque<T, Allocator>::fill_initialize(size_type count, const value_type& value) {
		create_map_and_nodes(count);
		map_pointer curr;
		for (curr = start.node; curr != finish.node; ++curr) //给前面多个整node赋值
			kkli::uninitialized_fill(*curr, *curr + buffer_size, value);
		kkli::uninitialized_fill(finish.first, finish.curr, value); //给最后一个node的有效部分赋值
	}

	//push_front_aux
	template<typename T, typename Allocator>
	void deque<T, Allocator>::push_front_aux(const value_type& value) {
		reserve_map_at_front();
		*(start.node - 1) = allocate_node();
		start.set_node(start.node - 1);
		start.curr = start.last - 1;
		data_allocator.construct(start.curr, value);
	}

	//push_back_aux
	template<typename T, typename Allocator>
	void deque<T, Allocator>::push_back_aux(const value_type& value) {
		reserve_map_at_back(); //调整map
		*(finish.node + 1) = allocate_node(); //分配一个node
		data_allocator.construct(finish.curr, value);
		finish.set_node(finish.node + 1);
		finish.curr = finish.first;
	}

	//pop_front_aux
	template<typename T,typename Allocator>
	void deque<T, Allocator>::pop_front_aux() {
		data_allocator.destroy(start.curr);
		deallocate_node(start.first);
		start.set_node(start.node + 1);
		start.curr = start.first;
	}

	//pop_back_aux
	template<typename T,typename Allocator>
	void deque<T, Allocator>::pop_back_aux() {
		deallocate_node(finish.first);
		finish.set_node(finish.node - 1);
		finish.curr = finish.last - 1;
		data_allocator.destroy(finish.curr);
	}

	//destroy
	template<typename T, typename Allocator>
	void deque<T, Allocator>::destroy(pointer first, pointer last) {
		for (auto iter = first; iter != last; ++iter)
			data_allocator.destroy(iter);
	}

	//insert_aux
	template<typename T,typename Allocator>
	typename deque<T,Allocator>::iterator deque<T, Allocator>::insert_aux(
		const_iterator pos, size_type count, const value_type& value) {
		auto iter = iterator(pos);
		kkli::move_backward(iter, finish, finish + count); //[pos, finish)后移count个位置
		finish += count;
		auto end = iter + count;
		for (; iter != end; ++iter) //构建[pos, pos+count)的元素
			data_allocator.construct(iter, value);
	}

	//insert_range_aux
	template<typename T,typename Allocator>
	template<typename InputIt>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::insert_range_aux(
		const_iterator pos, InputIt first, InputIt last) {
		auto iter = iterator(pos);
		size_type count = get_size(first, last);
		kkli::move_backward(iter, finish, finish + count); //[pos, finish)后移count个位置
		finish += count;
		auto end = iter + count;
		for (; first != last; ++iter, ++first) //构建[pos, pos+count)的元素
			data_allocator.construct(iter, *first);
	}

	//operator =(rhs)
	template<typename T, typename Allocator>
	deque<T, Allocator>& deque<T, Allocator>::operator=(const deque& rhs) {
		if (this == &rhs) return *this;
		assign_range(rhs.cbegin(), rhs.cend(), rhs.size());
		return *this;
	}

	//operator =(&&rhs)
	template<typename T, typename Allocator>
	deque<T, Allocator>& deque<T, Allocator>::operator=(deque&& rhs) {
		if (this == &rhs) return *this;
		this->destroy(start, finish);
		this->destroy_map_and_nodes();

		start = rhs.start;
		finish = rhs.finish;
		map = rhs.map;
		map_size = rhs.map_size;
		rhs.reset_data_members();
		return *this;
	}

	//assign
	template<typename T, typename Allocator>
	void deque<T, Allocator>::assign(size_type count, const value_type& value) {
		this->clear();
		for (; count > 0; --count) this->push_back(value);
	}

	//assign_range
	template<typename T,typename Allocator>
	template<typename InputIt>
	void deque<T, Allocator>::assign_range(InputIt first, InputIt last) {
		if (first == last) return;
		for (; first != last) this->push_back(*first);
	}

	//clear
	template<typename T, typename Allocator>
	void deque<T, Allocator>::clear() {
		//释放除首尾以外的所有缓冲区（它们一定是满的）
		for (map_pointer node = start.node + 1; node < finish.node; ++node) {
			auto end = *node + buffer_size;
			destroy(*node, *node + buffer_size); //销毁缓冲区中的元素
			data_allocator.deallocate(*node, buffer_size); //释放缓冲区
		}
		if (start.node != finish.node) { //还有两个缓冲区
			destroy(start.curr, start.last);
			destroy(finish.first, finish.curr);
			data_allocator.deallocate(finish.first, buffer_size);
		}
		else { //只有一个缓冲区
			destroy(start.curr, finish.curr);
		}
		finish = start; //调整状态
	}

	//insert
	template<typename T,typename Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(
		const_iterator pos, size_type count, const value_type& value) {
		if (pos.curr == start.curr) { //插入点是deque最前端
			for (; count > 0; --count) this->push_front(value);
			return start;
		}
		else if (pos.curr == finish.curr) { //插入点是deque最尾端
			auto temp = finish;
			for (; count > 0; --count) this->push_back(value);
			return temp;
		}
		else  return insert_aux(pos, count, value); //插入点是deque中间
	}

	//insert_range
	template<typename T,typename Allocator>
	template<typename InputIt>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::insert_range(
		const_iterator pos, InputIt first, InputIt last) {
		if (pos.curr == start.curr) { //插入点是deque最前端
			for (; first != last;++first) this->push_front(*first);
			return start;
		}
		else if (pos.curr == finish.curr) { //插入点是deque最尾端
			auto temp = finish;
			for (; first != last; ++first) this->push_back(*first;);
			return temp;
		}
		else  return insert_range_aux(pos, first, last); //插入点是deque中间
	}

	//erase
	template<typename T,typename Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::erase(
		const_iterator first, const_iterator last) {
		if (first == start && last == finish) { //清除区间为整个deque
			clear();
			return finish;
		}
		
		difference_type len = last - first; //待清除的区间长度
		difference_type before = first - start; //清除点前方的元素个数
		if (before < (this->size() - len) / 2) { //前方元素较少，后移
			move_backward(start, first, last);
			iterator new_start = start + len;
			destroy(start, new_start); //析构冗余元素
			for (auto iter = start.node; iter < new_start.node; ++iter)
				data_allocator.deallocate(*iter, buffer_size);
			start = new_start;
		}
		else { //后方元素较少，前移
			kkli::move(last, finish, first);
			iterator new_finish = finish - len;
			destroy(new_finish, finish);
			for (auto iter = new_finish.node + 1; iter <= finish.node; ++iter)
				data_allocator.deallocate(*iter, buffer_size);
			finish = new_finish;
		}
		return start + before;
	}

	//push_front
	template<typename T, typename Allocator>
	void deque<T, Allocator>::push_front(const value_type& value) {
		if (start.curr != start.first) {
			data_allocator.construct(start.curr - 1, value);
			--start.curr;
		}
		else push_front_aux(value);
	}

	//push_back
	template<typename T,typename Allocator>
	void deque<T, Allocator>::push_back(const value_type& value) {
		if (finish.curr != finish.last - 1) {
			data_allocator.construct(finish.curr, value);
			++finish.curr;
		}
		else push_back_aux(value);
	}
	
	//pop_front
	template<typename T,typename Allocator>
	void deque<T, Allocator>::pop_front() {
		if (start.curr != start.last - 1) {
			data_allocator.destroy(start.curr);
			++start.curr;
		}
		else pop_front_aux();
	}

	//pop_back
	template<typename T,typename Allocator>
	void deque<T, Allocator>::pop_back() {
		if (finish.curr != finish.first) {
			--finish.curr;
			data_allocator.destroy(finish.curr);
		}
		else pop_back_aux();
	}

	//swap
	template<typename T,typename Allocator>
	void deque<T, Allocator>::swap(deque& rhs) {
		kkli::swap(start, rhs.start);
		kkli::swap(finish, rhs.finish);
		kkli::swap(map, rhs.map);
		kkli::swap(map_size, rhs.map_size);
	}
}

//================================================================================
// 非成员函数定义
//================================================================================

namespace kkli {

	//operator ==
	template<typename T, typename Allocator>
	bool operator==(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		auto beg1 = lhs.begin();
		auto end1 = lhs.end();
		auto beg2 = rhs.begin();
		auto end2 = rhs.end();
		while (beg1 != end1 && beg2 != end2) {
			if (*beg1 != *beg2) return false;
		}
		if (beg1 == end1 && beg2 == end2) return true;
		return false;
	}

	//operator !=
	template<typename T, typename Allocator>
	bool operator!=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T, typename Allocator>
	bool operator<(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		auto beg1 = lhs.begin();
		auto end1 = lhs.end();
		auto beg2 = rhs.begin();
		auto end2 = rhs.end();
		while (beg1 != end1 && beg2 != end2) {
			if (*beg1 < *beg2) return true;
			if (*beg2 < *beg1) return false;
		}
		if (beg1 == end1 && beg2 != end2) return true; //lhs短
		return false;
	}

	//operator >
	template<typename T, typename Allocator>
	bool operator>(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		auto beg1 = lhs.begin();
		auto end1 = lhs.end();
		auto beg2 = rhs.begin();
		auto end2 = rhs.end();
		while (beg1 != end1 && beg2 != end2) {
			if (*beg1 < *beg2) return false
			if (*beg2 < *beg1) return true;
		}
		if (beg1 != end1 && beg2 == end2) return true; //lhs长
		return false;
	}

	//operator <=
	template<typename T, typename Allocator>
	bool operator<=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T, typename Allocator>
	bool operator>=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		return !(lhs < rhs);
	}

	//swap
	template<typename T, typename Allocator>
	void swap(deque<T, Allocator>& lhs, deque<T, Allocator>& rhs) {
		return lhs.swap(rhs);
	}
}
