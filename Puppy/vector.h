#pragma once

#include "stdafx.h"

//================================================================================
// vector<T> �ඨ��
//================================================================================
namespace kkli {

	template<typename T,typename Allocator=std::allocator<T>>
	class vector {
	public:
		//typedefs
		typedef	T							value_type;
		typedef Allocator					allocator_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type*					iterator;
		typedef const value_type*			const_iterator;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::random_access_iterator_tag			iterator_category;

	private:
		iterator __start;			//������ָ��
		iterator __end;				//��Ч����βָ��
		iterator __capacity;		//����βָ��
		Allocator __alloc;			//�ڴ������

		//�ͷ�ԭ���ڴ�
		void deallocate() { __alloc.deallocate(__start, __capacity - __start); }

		//�����ڲ�������
		void reset_iterators() { __start = __end = __capacity = iterator(); }

		//���������ڴ棬����ԭ��Ԫ�ظ��Ƶ����ڴ���
		void reallocate_and_copy(size_type new_cap);
	public:

		//constructors
		vector() :__start(nullptr), __end(nullptr), __capacity(nullptr) {}
		vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());

		template<typename InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& rhs) :vector(rhs.begin(), rhs.end()) {}
		vector(vector&& rhs);
		vector(std::initializer_list<T> il) :vector(il.begin(), il.end()) {}

		//destructor
		~vector();

		//operator =
		vector& operator=(const vector& rhs);
		vector& operator=(std::initializer_list<T> il);
		vector& operator=(vector&& rhs);

		//assign
		void assign(size_type count, const T& value);
		void assign(std::initializer_list<T> il) { this->operator=(il); }
		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last);

		//at
		reference at(size_type pos);
		const_reference at(size_type pos)const;

		//operator []
		reference operator[](size_type pos) { return __start[pos]; }
		const_reference operator[](size_type pos)const { return __start[pos]; }

		//other member functions
		allocator_type get_allocator()const { return __alloc; }

		iterator begin() { return __start; }
		iterator end() { return __end; }
		const_iterator cbegin()const { return __start; }
		const_iterator cend()const { return __end; }

		reference front() { return __start[0]; }
		reference back() { return __end[-1]; }
		const_reference front()const { return __start[0]; }
		const_reference back()const { return __end[-1]; }

		iterator data() { return __start; }
		const_iterator data()const { return __start; }

		bool empty()const { return __start == iterator(); }
		size_type size()const { return __end - __start; }
		constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }

		void reserve(size_type new_cap);
		size_type capacity()const { return __capacity - __start; }
		void shrink_to_fit();
		void clear();

		iterator insert(const_iterator pos, std::initializer_list<T> il);
		iterator insert(const_iterator pos, size_type count, const value_type& value) {
			//�����������ʧ�ܣ���ͨ������vector��Ȼ���ٹ���initializer_list��ʵ��n��value���б�
			return insert(pos, std::initializer_list<T>(count, value));
		}
		iterator insert(const_iterator pos, const value_type& value) { return insert(pos, { value }); }
		template<typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
			return insert(pos, std::initializer_list<T>(first, last));
		}

		//emplaceû��ʵ��
		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator pos) { return erase(pos, pos + 1); }

		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back() { __alloc.destroy(--__end); }

		/*
		void emplace(const value& value);

		template< class... Args >
		void emplace_back(Args&&... args);

		template< class... Args >
		reference emplace_back(Args&&... args);
		*/

		void resize(size_type count, const value_type& value);
		void resize(size_type count) { resize(count, value_type()); }

		void swap(vector& rhs);

		bool operator==(const vector& rhs);
		bool operator!=(const vector& rhs) { return !operator==(rhs); }
		bool operator< (const vector& rhs);
		bool operator> (const vector& rhs);
		bool operator<=(const vector& rhs) { return !operator>(rhs); }
		bool operator>=(const vector& rhs) { return !operator<(rhs); }
	};
}

//================================================================================
// vector<T> ��Ա��������
//================================================================================
namespace kkli {

	//vector
	//���캯����ֱ�ӷ���պù��õ��ڴ�ռ䣬��׼������Ŀռ�
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__start = __alloc.allocate(count);
		for (size_type i = 0; i < count; ++i)
			__alloc.construct(__start[i], value);
		__end = __start + count;
		__capacity = __end;
	}

	//vector(InputIterator,InputIterator)
	template<typename T, typename Allocator>
	template<typename InputIterator>
	vector<T, Allocator>::vector(InputIterator first, InputIterator last)
		:__alloc(alloc) {
		__start = __alloc.allocate(last-first);
		size_type index = 0;
		for (auto iter = first; iter != last; ++iter) {
			__alloc.construct(__start[index], *iter);
			++index;
		}
		__end = __start + index;
		__capacity = _end;
	}

	//vector(vector&&)
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(vector&& rhs) :__alloc(rhs.__alloc) {
		deallocate();				//�ͷ�ԭ���ڴ�
		__start = rhs.__start;		//�����ڲ�������
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		rhs.reset_iterators();		//����rhs���ڲ�������
	}

	//~vector
	template<typename T, typename Allocator>
	vector<T, Allocator>::~vector() {
		deallocate();
		reset_iterators();
	}

	//reallocate
	template<typename T,typename Allocator>
	void vector<T, Allocator>::reallocate_and_copy(size_type new_cap) {
		auto start = __start;						//ԭ�����ڴ濪ʼλ��
		size_type old_cap = capacity();
		__start = __alloc.allocate(new_cap);

		//����ԭ����Ԫ�ص�������
		size_type index = 0;
		for (auto iter = start; iter != __end; ++iter) {
			__alloc.construct(__start[index], *iter);
			++index;
		}

		__alloc.deallocate(start, old_cap);			//�ͷ�ԭ���ڴ�
		__end = __start + index;
		__capacity = __start + new_cap;
	}

	//operator =
	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& rhs) {
		deallocate();		//�ͷ�ԭ���ڴ�

		__alloc = rhs.__alloc;
		size_type size = rhs.size();
		__size = __alloc.allocate(size);

		size_type index = 0;
		for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
			__alloc.construct(__start[index], *iter);
			++index;
		}

		__end = __start + size;
		__capacity = __end;
		return *this;
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> il) {
		deallocate();			//�ͷ�ԭ���ڴ�

		size_type size = il.size();
		__start = __alloc.allocate(size);
		size_type index = 0;
		for (auto iter = il.begin(); iter != il.end(); ++iter) {
			__alloc.construct(__start[index], *iter);
			++index;
		}
		__end = __start + size;
		__capacity = __end;
		return *this;
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& rhs) {
		deallocate();		//�ͷ�ԭ���ڴ�

		__alloc = rhs.__alloc;
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;

		rhs.reset_iterators();
		return *this;
	}

	//assign
	template<typename T, typename Allocator>
	void vector<T, Allocator>::assign(size_type count, const T& value) {
		deallocate();		//�ͷ�ԭ���ڴ�

		__start = __alloc.allocate(count);
		size_type index = 0;
		while (index != count) {
			__alloc.construct(__start[index], value);
			++index;
		}
		__end = __start + count;
		__capacity = __end;
	}

	template<typename T, typename Allocator>
	template<typename InputIterator>
	void vector<T, Allocator>::assign(InputIterator first, InputIterator last) {
		deallocate();			//�ͷ�ԭ���ڴ�

		size_type size = last - first;
		__start = __alloc.allocate(size);
		size_type index = 0;
		for (auto iter = first; iter != last; ++iter) {
			__alloc.construct(__start[index], *iter);
			++index;
		}

		__end = __start + size;
		__capacity = __end;
	}

	//at
	template<typename T, typename Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
		if (pos >= size()) throw std::runtime_error("�±�Խ��!");
		return __start[pos];
	}

	template<typename T, typename Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) const {
		if (pos >= size()) throw std::out_of_range("�±�Խ��!");
		return __start[pos];
	}

	//reverse
	template<typename T, typename Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap <= capacity()) return;		//�ռ��С����
		reallocate_and_copy(new_cap);
	}

	//shrink_to_fit
	template<typename T, typename Allocator>
	void vector<T, Allocator>::shrink_to_fit() {
		if (__end == __capacity) return;

		//�ͷ�__end��__capacity���ڴ�ռ䣬������__capacity
		__alloc.deallocate(__end, __capacity - __end);
		__capacity = __end;
	}

	//clear
	template<typename T,typename Allocator>
	void vector<T, Allocator>::clear() {
		deallocate();
		reset_iterators();
	}

	//insert(pos, initializer_list)
	template<typename T,typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
		const_iterator pos, std::initializer_list<T> il) {
		size_type count = il.size();
		//�����ռ��㹻
		if (__capacity - __end >= count) {

			//��count��Ԫ����Ҫ������[__end,__end+count)ָ����ڴ���
			auto iter = __end - 1;
			for (int i = 0; i < count; ++i) {
				__alloc.construct(iter + count, *(iter));
				--iter;
			}

			//��[pos,__end-count)��Ԫ�ط���[pos+count,__end)��
			//back_iter��ʾԪ�ط���㣬iter��ʾԪ���ṩ��
			for (auto back_iter = __end - 1; iter >= pos; --iter, --back_iter) {
				*back_iter = std::move(*iter);
			}

			//����ʼ�б��е�Ԫ�ط���[pos,pos+count)��
			auto il_iter = il.begin();
			for (iter = pos; iter != pos + count; ++iter, ++il_iter) {
				*iter = *il_iter;
			}
			return pos;
		}

		//�����ռ䲻��
		else {
			auto start = __start;
			size_type size = size();					//ԭ����Ԫ�ظ���
			size_type new_cap = (size + count) * 2;		//������������
			__start = __alloc.allocate(new_cap);

			//��ԭ�ڴ�start��pos��Ԫ�ع��쵽���ڴ���
			size_type index = 0;
			for (auto iter = start; iter<pos; ++iter) {
				__alloc.construct(__start[index], *iter);
				++index;
			}
			auto result = __start + index;			//����ֵ

			//����ֵ
			for (auto beg_iter = il.begin(); beg_iter != il.end();++beg_iter) {
				__alloc.construct(__start[index], *beg_iter);
				++index;
			}

			//��ԭ�ڴ�pos��__end��Ԫ�ع��쵽���ڴ���
			while (iter != __end) {
				__alloc.construct(__start[index], *iter);
				++iter;
				++index;
			}
			__end = __start + index;
			__capacity = __start + new_cap;
			return result;
		}
	}

	//operator ==
	template<typename T, typename Allocator>
	bool vector<T, Allocator>::operator==(const vector& rhs) {
		size_type size = size();
		if (size != rhs.size()) return false;
		for (size_type i = 0; i < size; ++i) {
			if (__start[i] != rhs[i]) return false;
		}
		return true;
	}

	//operator <
	template<typename T, typename Allocator>
	bool vector<T, Allocator>::operator<(const vector& rhs) {
		size_type size = size();
		if (size > rhs.size()) return false;
		bool smaller = false;		//��һԪ��С��rhs����
		for (size_type i = 0; i < size; ++i) {
			if (__start[i] > rhs[i]) return false;
			else if (__start[i] < rhs[i]) smaller = true;
		}

		if (size < rhs.size()) return true;			//��rhs�̣�������Ԫ����ȶ�����
		if (smaller) return true;					//����һ��������������һ��Ԫ��С��rhs����
		else return false;							//����һ������Ԫ��Ҳ��ȫ��ȣ���*this��С��rhs
	}

	//operator >
	template<typename T, typename Allocator>
	bool vector<T, Allocator>::operator>(const vector& rhs) {
		size_type size = size();
		if (size < rhs.size()) return false;
		bool greater = false;		//��һԪ�ش���rhs����
		for (size_type i = 0; i < size; ++i) {
			if (__start[i] < rhs[i]) return false;
			else if (__start[i] > rhs[i]) greater = true;
		}

		if (size > rhs.size()) return true;			//��rhs����������Ԫ����ȶ�����
		if (greater) return true;					//����һ��������������һ��Ԫ�ش���rhs����
		else return false;							//����һ������Ԫ��Ҳ��ȫ��ȣ���*this������rhs
	}

	//erase
	template<typename T,typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
		size_type size = last - first;
		//������Ԫ����ǰ�ƣ����ǵ�[first,last)
		for (auto iter = last; iter != __end; ++iter) {
			*(iter - size) = *iter;
		}
		//��ĩβsize��Ԫ������
		for (size_type i = 0; i < size; ++i) {
			__alloc.destroy(--__end);
		}
		return pos;
	}

	//push_back
	template<typename T,typename Allocator>
	void vector<T, Allocator>::push_back(const value_type& value) {
		//����δ��
		if (__end != __capacity) {
			__alloc.construct(__end, value);
			++__end;
		}
		//��������
		else {
			size_type old_cap=capacity();				//ԭ����������С
			size_type new_cap = old_cap * 2;			//��������������С
			if (new_cap == 0) new_cap = 2;
			reallocate_and_copy(new_cap);				//���·����ڴ棬����ԭ��Ԫ���ƶ������ڴ���

			//����Ԫ��
			__alloc.construct(++__end, value);
		}
	}

	//push_back
	//��push_back(const value_type&)������֣�������ȫһ��
	template<typename T, typename Allocator>
	void vector<T, Allocator>::push_back(value_type&& value) {
		//����δ��
		if (__end != __capacity) {
			__alloc.construct(__end, value);
			++__end;
		}
		//��������
		else {
			size_type old_cap = capacity();				//ԭ����������С
			size_type new_cap = old_cap * 2;			//��������������С
			if (new_cap == 0) new_cap = 2;
			reallocate_and_copy(new_cap);				//���·����ڴ棬����ԭ��Ԫ���ƶ������ڴ���

														//����Ԫ��
			__alloc.construct(++__end, value);
		}
	}

	//resize
	template<typename T, typename Allocator>
	void vector<T, Allocator>::resize(size_type count, const value_type& value) {
		if (count <= size()) return;

		//���������ڴ�
		if (count <= capacity()) {		//��ĩβ��count-size��δ�����ڴ��ʼ��Ϊvalue
			size_type index = size();
			while (index != count) {
				__alloc.construct(__start[index], value);
			}
			__end = __start + count;
		}
		//��Ҫ�����ڴ�
		else {
			size_type size = size();
			reallocate_and_copy(count);

			//��ĩβδ����Ԫ����value����
			while (size != count) {
				__alloc.construt(++__end, value);
				++size;
			}
		}
	}

	//swap
	template<typename T,typename Allocator>
	void vector<T, Allocator>::swap(vector& rhs) {
		//swap __start
		auto temp = __start;
		__start = rhs.__start;
		rhs.__start = temp;

		//swap __end
		temp = __end;
		__end = rhs.__end;
		rhs.__end = temp;

		//swap __capacity
		temp = __capacity;
		__capacity = rhs.__capacity;
		rhs.__capacity = temp;

		//swap __alloc: ����Ҫ
	}

	//non-member swap
	template<typename T,typename Allocator>
	void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs) {
		lhs.swap(rhs);
	}
}