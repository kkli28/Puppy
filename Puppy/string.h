#pragma once

#include "stdafx.h"
#include "memory.h"
#include "char_traits.h"
#include "iterator.h"

//================================================================================
// basic_string<T> �ඨ��
//================================================================================

namespace kkli {

	//typedef string
	template<
		typename CharType = char,
		typename Traits = kkli::char_traits<char>,
		typename Allocator = kkli::allocator<CharType>
	>
		class basic_string;
	typedef basic_string<char, char_traits<char>, allocator<char>> string;
	
	//basic_string
	template<
		typename CharType,
		typename Traits,
		typename Allocator
	>
		class basic_string {

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

			iterator __start;			//�ڴ濪ʼ��ַ
			iterator __end;				//[__start,__end)����Ч�ַ��ռ�
			iterator __capacity;		//[__start,__capacity)�������ַ��ռ�
			Allocator __alloc;

			//�����ڲ�������
			void __reset_iterators() { __start = __end = __capacity = iterator(); }

			//�����ڴ沢������Ӧֵ
			template<typename InputIterator>
			void __allocate(size_type mem_size, InputIterator first, InputIterator last);

			//�����ڴ沢������Ӧֵ
			void __allocate(size_type mem_size, size_type count, value_type value);

			//�����ڴ�
			iterator __allocate(size_type mem_size) { return __alloc.allocate(mem_size + 1); }

			//�ͷ�ԭ���ڴ�
			void __deallocate() {
				__alloc.deallocate(__start, (__capacity - __start) + 1);		//ĩβ��һ��Ԥ���Ŀռ䣬���� +1
			}

			//��[first, last)���ַ���ӵ�*this��
			template<typename InputIterator>
			void __append(size_type size, InputIterator first, InputIterator last);

			//��*this��ֵΪ[first,last)��ָ�ַ�
			template<typename InputIterator>
			void __assign(size_type size, InputIterator first, InputIterator last) {
				__deallocate();
				__allocate(size, first, last);
			}

			//��[first, last)��ʾ���ַ����Ƶ�ָ���ڴ��ַ�У����ع�����ַ�����
			template<typename InputIteratorA, typename InputIteratorB>
			size_type __set_value_by_range(iterator addr, InputIteratorA first, InputIteratorB last);

			//��count��valueд��ָ���ڴ��ַ��
			void __set_value_by_value(iterator addr, size_type count, value_type value);

			//��[first1, last1)��[first2, last2)���бȽ�
			template<typename InputIteratorA, typename InputIteratorB>
			int __compare(size_type size1, InputIteratorA first1, InputIteratorA last1,
				size_type size2, InputIteratorB first2, InputIteratorB last2) const;

			//��[first1, last1)�滻Ϊ[first2, last2)
			template<typename InputIterator>
			void __replace(const_iterator first, const_iterator last, size_type size,
				InputIterator first2, InputIterator last2);

		public:
			//��ȡdata����Ч�ַ�����
			static size_type get_size(const_pointer data);

			//��ȡ[first, last)���ַ�����
			template<typename InputIteratorA,typename InputIteratorB>
			static size_type get_size(InputIteratorA first, InputIteratorB last) {
				size_type size = 0;
				for (auto iter = first; iter != last; ++size, ++iter);
				return size;
			}

		public:

			//constructor
			basic_string(const Allocator& alloc = Allocator());
			basic_string(size_type count, value_type value, const Allocator& alloc = Allocator());
			basic_string(const basic_string& rhs, size_type pos, size_type count = npos,
				const Allocator& alloc = Allocator());
			basic_string(const_pointer data, size_type count = npos,
				const Allocator& alloc = Allocator());
			basic_string(size_type count, const Allocator& alloc = Allocator());

			template<typename InputIterator>
			basic_string(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());
			basic_string(const basic_string& rhs);
			basic_string(basic_string&& rhs);
			basic_string(std::initializer_list<value_type> init, const Allocator& alloc = Allocator());

			//destructor
			~basic_string();

			//get_allocator
			allocator_type get_allocator()const { return __alloc; }

			//operator =
			basic_string& operator=(const basic_string& rhs) {
				if (this == &rhs) return *this;
				__deallocate();
				__allocate(rhs.size(), rhs.cbegin(), rhs.cend());
				return *this;
			}
			basic_string& operator=(basic_string&& rhs);
			basic_string& operator=(const_pointer data) {
				if (__start == data) return *this;
				size_type size = get_size(data);
				__allocate(size, data, data + size);
				return *this;
			}
			basic_string& operator=(std::initializer_list<value_type> init) {
				__deallocate();
				__allocate(init.size(), init.begin(), init.end());
				return *this;
			}

			//operator []
			reference operator[](size_type pos) { return __start[pos]; }
			const_reference operator[](size_type pos)const { return __start[pos]; }

			//operator +=
			basic_string& operator+=(const basic_string& rhs) {
				__append(rhs.size(), rhs.cbegin(), rhs.cend());
				return *this;
			}
			basic_string& operator+=(value_type value) {
				this->push_back(value);
				return *this;
			}
			basic_string& operator+=(const_pointer data) {
				size_type size = get_size(data);
				__append(size, data, data + size);
				return *this;
			}
			basic_string& operator+=(std::initializer_list<value_type> init) {
				__append(init.size(), init.begin(), init.end());
				return *this;
			}

			//assign
			void assign(size_type count, value_type value) {
				__deallocate();
				__allocate(count, count, value);
			}
			void assign(const basic_string& rhs) {
				if (this == &rhs) return;
				__assign(rhs.size(), rhs.cbegin(), rhs.cend());
			}
			void assign(basic_string&& rhs) { operator=(std::move(rhs)); }
			void assign(const basic_string& rhs, size_type pos, size_type count = npos) {
				if (count == npos) count = rhs.size() - pos;
				__assign(count, rhs.cbegin() + pos, rhs.cbegin() + pos + count);
			}
			void assign(const_pointer data, size_type count = npos) {
				if (count == npos) count = get_size(data);
				__assign(count, data, data + count);
			}

			template<typename InputIterator>
			void assign(InputIterator first, InputIterator last) {
				size_type size = get_size(first, last);
				__assign(size, first, last);
			}
			void assign(std::initializer_list<value_type> init) {
				__assign(init.size(), init.begin(), init.end());
			}

			//insert
			template<typename InputIterator>
			void insert(const_iterator pos, InputIterator first, InputIterator last);
			iterator insert(const_iterator pos, size_type count, value_type value);
			void insert(size_type index, const basic_string& rhs, size_type index_rhs, size_type count = npos) {
				if (count == npos) count = rhs.size() - index_rhs;
				insert(__start + index, rhs.cbegin() + index_rhs, rhs.cbegin() + index_rhs + count);
			}
			void insert(size_type index, const_pointer data, size_type count = npos) {
				if (count == npos) count = get_size(data);
				insert(__start + index, data, data + count);
			}

			void insert(size_type index, const basic_string& rhs) { return insert(__start + index, rhs.cbegin(), rhs.cend()); }
			void insert(size_type index, size_type count, value_type value) { insert(__start + index, count, value); }
			iterator insert(const_iterator pos, value_type value) { return insert(pos, 1, value); }
			void insert(const_iterator pos, std::initializer_list<value_type> init) { return insert(pos, init.begin(), init.end()); }

			//erase
			iterator erase(const_iterator first, const_iterator last) {
				auto iter = __start + (first - __start);
				__set_value_by_range(iter, last, __end);			//��[last, __end)Ԫ���ƶ���[first, ~)��
				__end -= last - first;
				return iter;
			}
			iterator erase(size_type index = 0, size_type count = npos) {
				if (count == npos) return erase(__start + index, __end);
				else return erase(__start + index, __start + index + count);
			}
			iterator erase(const_iterator pos) { return erase(pos, pos + 1); }

			//append
			void append(const basic_string& rhs, size_type pos = 0, size_type count = npos) {
				if (count == npos) count = rhs.size() - pos;
				__append(count, rhs.cbegin() + pos, rhs.cbegin() + pos + count);
			}
			void append(const_pointer data, size_type count = npos) {
				if (count == npos) count = get_size(data);
				__append(count, data, data + count);
			}
			void append(size_type count, value_type value) { insert(__end, count, value); }

			template<typename InputIterator>
			void append(InputIterator first, InputIterator last) {
				size_type size = get_size(first, last);
				__append(size, first, last);
			}
			void append(std::initializer_list<value_type> init) { __append(init.size(), init.begin(), init.end()); }

			//compare
			int compare(const basic_string& rhs)const {
				return __compare(this->size(), __start, __end, rhs.size(), rhs.cbegin(), rhs.cend());
			}
			int compare(size_type pos1, size_type count1,
				const basic_string& rhs, size_type pos2 = 0, size_type count2 = npos)const {
				if (count2 == npos) count2 = rhs.size() - pos2;
				return __compare(count1, __start + pos1, __start + pos1 + count1, count2,
					rhs.cbegin() + pos2, rhs.cbegin() + pos2 + count2);
			}
			int compare(const_pointer data)const {
				size_type size = get_size(data);
				return __compare(this->size(), __start, __end, size, data, data + size);
			}
			int compare(size_type pos1, size_type count1,
				const_pointer data, size_type count2 = npos)const {
				if (count2 == npos) count2 = get_size(data);
				return __compare(count1, __start + pos1, __start + pos1 + count1,
					count2, data, data + count2);
			}

			//replace
			template<typename InputIterator>
			void replace(const_iterator first, const_iterator last, InputIterator first2, InputIterator last2) {
				__replace(first, last, npos, first2, last2);
			}
			void replace(const_iterator first, const_iterator last, size_type count2, value_type value);
			void replace(const_iterator first, const_iterator last, const basic_string& rhs) {
				__replace(first, last, rhs.size(), rhs.cbegin(), rhs.cend());
			}
			void replace(const_iterator first, const_iterator last, const_pointer data, size_type count2 = npos) {
				if (count2 == npos) count2 = get_size(data);
				__replace(first, last, count2, data, data + count2);
			}
			void replace(const_iterator first, const_iterator last, std::initializer_list<value_type> init) {
				__replace(first, last, init.size(), init.begin(), init.end());
			}
			void replace(size_type pos, size_type count,
				const basic_string& rhs, size_type pos2 = 0, size_type count2 = npos) {
				if (count2 == npos) count2 = rhs.size() - pos2;
				__replace(__start + pos, __start + pos + count, count2, rhs.cbegin() + pos2, rhs.cbegin() + pos2 + count2);
			}
			void replace(size_type pos, size_type count, const_pointer data, size_type count2 = npos) {
				if (count2 == npos) count2 = get_size(data);
				replace(__start + pos, __start + pos + count, count2, data, data + count2);
			}
			void replace(size_type pos1, size_type count1, size_type count2, value_type value) {
				replace(__start + pos1, __start + pos1 + count1, count2, value);
			}

			//find
			size_type find(const basic_string& rhs, size_type pos = 0)const;
			size_type find(const_pointer data, size_type pos = 0, size_type count = npos)const;
			size_type find(value_type value, size_type pos = 0)const;

			//Ҫ��Ҫʵ�� rfind��
			size_type rfind(const basic_string& rhs, size_type pos = npos, size_type count = npos)const;
			size_type rfind(const_pointer data, size_type pos = npos)const;
			size_type rfind(value_type value, size_type pos = npos)const;

			size_type find_first_of(const basic_string& rhs, size_type pos = 0)const;
			size_type find_first_of(const_pointer data, size_type pos = 0, size_type count = npos)const;
			size_type find_first_of(value_type value, size_type pos = 0)const;

			size_type find_first_not_of(const basic_string& rhs, size_type pos = 0)const;
			size_type find_first_not_of(const_pointer data, size_type pos, size_type count)const;
			size_type find_first_not_of(value_type value, size_type pos = 0)const;

			size_type find_last_of(const basic_string& rhs, size_type pos = npos)const;
			size_type find_last_of(const_pointer data, size_type pos = 0, size_type count = npos)const;
			size_type find_last_of(value_type value, size_type pos = npos)const;

			size_type find_last_not_of(const basic_string& rhs, size_type pos = npos)const;
			size_type find_last_not_of(const_pointer data, size_type pos = 0, size_type count = npos)const;
			size_type find_last_not_of(value_type value, size_type pos = npos)const;

			//c_str
			const pointer c_str()const {
				*__end = kkli::char_traits<char>::eof();			//���ý����ַ�
				return __start;
			}


			//other member functions
			reference at(size_type pos) {
				if (pos >= this->size()) throw std::runtime_error("�±�Խ��!");
				return __start[pos];
			}
			const_reference	at(size_type pos)const {
				if (pos >= this->size()) throw std::runtime_error("�±�Խ��!");
				return __start[pos];
			}
			value_type&			front() { return __start[0]; }
			const value_type&	front()const { return __start[0]; }
			value_type&			back() { return __end[-1]; }
			const value_type&	back()const { return __end[-1]; }
			iterator			begin() { return __start; }
			const_iterator		cbegin()const { return __start; }
			iterator			end() { return __end; }
			const_iterator		cend()const { return __end; }
			pointer				data() { return __start; }
			const_pointer		data()const { return __start; }

			kkli::reverse_iterator<iterator> 
				rbegin() { return kkli::reverse_iterator<iterator>(__end); }
			const kkli::reverse_iterator<iterator>
				crbegin()const { return kkli::reverse_iterator<iterator>(__end);}
			kkli::reverse_iterator<iterator>
				rend() { return kkli::reverse_iterator<iterator>(__start); }
			const kkli::reverse_iterator<iterator>
				crend()const { return kkli::reverse_iterator<iterator>(__start);}

			bool				empty()const { return __start == __end; }
			size_type			size()const { return __end - __start; }
			size_type			length()const { return size(); }
			constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }
			void				reserve(size_type new_cap = 0);
			size_type			capacity()const { return __capacity - __start; }
			void				shrink_to_fit() {}		//��Ч��
			void				clear() { __end = __start; }
			void				push_back(value_type value) { insert(__end, 1, value); }
			void				pop_back() { --__end; }

			void				resize(size_type count, value_type value = value_type());
			basic_string				substr(size_type pos = 0, size_type count = npos)const;
			size_type			copy(const_pointer data, size_type pos = 0, size_type count = npos);
			void				swap(basic_string& rhs);
			void				reverse();

			void print(const basic_string& prefix) const {
				this->c_str();
				std::cout << prefix << ": ";
				size_type size = this->size();
				for (size_type i = 0; i < size; ++i)
					std::cout << __start[i];
				std::cout << std::endl;
				std::cout << "size: " << this->size() << std::endl;
				std::cout << "capacity: " << this->capacity() << std::endl << std::endl;
			}
	};
}

//================================================================================
// basic_string<T> ��Ա��������
//================================================================================

namespace kkli {

	//__allocate(mem_size, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void basic_string<CharType, Traits, Allocator>::__allocate(size_type mem_size, InputIterator first, InputIterator last) {
		__start = __alloc.allocate(mem_size + 1);
		size_type index = __set_value_by_range(__start, first, last);
		__end = __start + index;
		__capacity = __start + mem_size;
	}

	//__allocate(mem_size, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::__allocate(size_type mem_size, size_type count, value_type value) {
		__start = __alloc.allocate(mem_size + 1);
		__set_value_by_value(__start, count, value);
		__end = __start + count;
		__capacity = __start + mem_size;
	}

	//get_size(data)
	template<typename CharType, typename Traits, typename Allocator>
	typename basic_string<CharType, Traits, Allocator>::size_type basic_string<CharType, Traits, Allocator>::get_size(const_pointer data) {
		size_type size = 0;
		if (data != NULL) {
			for (;; ++size)
				if (data[size] == kkli::char_traits<char>::eof()) break;
		}
		return size;
	}

	//__set_value_by_range(addr, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIteratorA, typename InputIteratorB>
	typename basic_string<CharType, Traits, Allocator>::size_type basic_string<CharType, Traits, Allocator>::__set_value_by_range(
		iterator addr, InputIteratorA first, InputIteratorB last) {
		size_type index = 0;
		for (; first != last; ++first) {
			*(addr + index) = *first;
			++index;
		}
		return index;
	}

	//__set_value_by_value(addr, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::__set_value_by_value(iterator addr, size_type count, value_type value) {
		for (size_type i = 0; i < count; ++i) {
			*(addr + i) = value;
		}
	}

	//__append(size, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void basic_string<CharType, Traits, Allocator>::__append(size_type size, InputIterator first, InputIterator last) {
		//ʣ��ռ��㹻��ֱ�ӽ�rhs��������䵽����
		if (__capacity - __end >= size) {
			__end += __set_value_by_range(__end, first, last);
			//__capacity����
		}

		//ʣ��ռ䲻��
		else {
			//����[fist, last)ָ���������򣬹ʲ���ֱ���ͷ�ԭ���ڴ�
			size_type capacity = (this->size() + size) * 2;					//Ԥ��һ��ռ�
			iterator new_addr = __allocate(capacity);
			size_type index = __set_value_by_range(new_addr, __start, __end);		//��[__start,__end)�е��ַ�д��
			index += __set_value_by_range(new_addr + index, first, last);			//��[first, last)�е��ַ�д��
			__deallocate();			//�ͷ�ԭ���ڴ�
			__start = new_addr;
			__end = __start + index;
			__capacity = __start + capacity;
		}
	}

	//__compare(count1, first1, last1, count2, first2, last2)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIteratorA, typename InputIteratorB>
	int basic_string<CharType, Traits, Allocator>::__compare(size_type count1, InputIteratorA first1, InputIteratorA last1,
		size_type count2, InputIteratorB first2, InputIteratorB last2) const {
		auto iter1 = first1;
		auto iter2 = first2;
		while (iter1 != last1 && iter2 != last2) {
			if (*iter1 < *iter2) return -1;
			if (*iter1 > *iter2) return 1;
			++iter1;
			++iter2;
		}
		if (count1 < count2) return -1;
		if (count1 > count2) return 1;
		return 0;				//��Ӧֵ��ȣ���һ����
	}

	//__replace(first1, last1, size2, first2, last2)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void basic_string<CharType, Traits, Allocator>::__replace(const_iterator first1, const_iterator last1, size_type size2,
		InputIterator first2, InputIterator last2) {
		size_type size1 = last1 - first1;
		if (size2 == npos) size2 = get_size(first2, last2);

		//[first1, last1)��Χ�㹻����[first2, last2)
		if (size1 >= size2) {
			auto first = __start + (first1 - __start);
			__set_value_by_range(first, first2, last2);				//��[first2, last2)����[first1, last1)ǰ����
			__set_value_by_range(first + size2, last1, __end);		//[last1, __end)ǰ��
			__end = __end - size1 + size2;
		}

		//[first1, last1)��Χ��������[first2, last2)
		else {
			if (size2 - size1 <= __capacity - __end) {		//���������ڴ�
				size_type offset = size2 - size1;

				//[last, __end)�ַ�����offset��λ��
				auto iter = __end - 1 + offset;
				auto prev_iter = __end - 1;
				while (prev_iter >= last1) {
					*iter = *prev_iter;
					--iter;
					--prev_iter;
				}

				auto first = __start + (first1 - __start);
				__set_value_by_range(first, first2, last2);			//д��[first2, last2)
				__end += offset;
			}
			else {
				size_type offset = size2 - size1;
				size_type capacity = (this->size() + offset) * 2;
				auto addr = __allocate(capacity);
				size_type index = __set_value_by_range(addr, __start, first1);		//��ǰ��д��
				__set_value_by_range(addr + index, first2, last2);					//����[first2, last2)
				index += size2;
				index += __set_value_by_range(addr + index, last2, __end);							//����д��
				__deallocate();					//�ͷ�ԭ���ڴ�
				__start = addr;
				__end = addr + index;
				__capacity = __start + capacity;
			}
		}
	}

	//basic_string(alloc)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(0, 0, value_type());
	}

	//basic_string(count, value)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(size_type count, value_type value,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(count, count, value);
	}

	//basic_string(rhs, pos, count)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(const basic_string& rhs, size_type pos,
		size_type count = npos, const Allocator& alloc = Allocator())
		:__alloc(alloc) {

		//����Ӧ������ڴ��С
		if (count == npos) count = rhs.size();
		__allocate(count, rhs.cbegin() + pos, rhs.cbegin() + pos + count);
	}

	//basic_string(data, count)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(const_pointer data, size_type count = npos,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		if (count == npos) count = get_size(data);
		__allocate(count, data, data + count);
	}

	//basic_string(first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	basic_string<CharType, Traits, Allocator>::basic_string(InputIterator first, InputIterator last,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(get_size(first, last), first, last);
	}

	//basic_string(count)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(size_type count, const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(count, 0, value_type());
	}

	//basic_string(rhs)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(const basic_string& rhs) {
		__allocate(rhs.size(), rhs.cbegin(), rhs.cend());
	}

	//basic_string(&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(basic_string&& rhs) {
		__start = rhs.__start;
		__end = rhs.__end;
		__capacity = rhs.__capacity;
		rhs.__reset_iterators();
	}

	//basic_string(init)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::basic_string(std::initializer_list<value_type> init,
		const Allocator& alloc = Allocator())
		:__alloc(alloc) {
		__allocate(init.size(), init.begin(), init.end());
	}

	//~basic_string
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>::~basic_string() {
		__deallocate();
		__reset_iterators();
	}

	//operator =(&&rhs)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator>& basic_string<CharType, Traits, Allocator>::operator=(basic_string&& rhs) {
		if (this == &rhs) return *this;
		__deallocate();
		__start = rhs.__start;
		__end = rhs.__end;
		__alloc = rhs.__alloc;
		__capacity = rhs.__capacity;
		rhs.__reset_iterators();
		return *this;
	}

	//insert(pos, first, last)
	template<typename CharType, typename Traits, typename Allocator>
	template<typename InputIterator>
	void basic_string<CharType, Traits, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last) {
		if (first == last) return;
		size_type count = get_size(first, last);

		//ʣ��ռ��㹻
		if (__capacity - __end >= count) {

			//��[pos,__end)�����ַ�����count��λ��
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			while (src_iter >= pos) {
				*dst_iter = *src_iter;
				--src_iter;
				--dst_iter;
			}

			//��[first, last)���뵽posλ��
			auto iter = __start + (pos - __start);
			__set_value_by_range(iter, first, last);
			__end += count;
		}

		//ʣ��ռ䲻��
		else {
			//rhs���ܾ���*this����˲���ֱ�ӽ�ԭ�ڴ��ͷ�
			size_type new_cap = (this->size() + count) * 2;			//Ԥ��һ��ռ�
			auto new_addr = __allocate(new_cap);

			//��this��[0,pos)���ݹ��쵽���ڴ���
			size_type i = __set_value_by_range(new_addr, __start, pos);

			__set_value_by_range(new_addr + i, first, last);			//������ֵд��
			i += count;
			i += __set_value_by_range(new_addr + i, pos, __end);		//������ֵд��

			__deallocate();			//�ͷ�ԭ���ڴ�
			__start = new_addr;
			__end = new_addr + i;
			__capacity = __start + new_cap;
		}
	}

	//insert(pos, count, value)
	template<typename CharType, typename Traits, typename Allocator>
	typename basic_string<CharType, Traits, Allocator>::iterator  basic_string<CharType, Traits, Allocator>::insert(
		const_iterator pos, size_type count, value_type value) {

		//ʣ��ռ��㹻
		if (__capacity - __end >= count) {

			//��[pos,__end)�����ַ�����count��λ��
			auto src_iter = __end - 1;
			auto dst_iter = src_iter + count;
			while (src_iter >= pos) {
				*dst_iter = *src_iter;
				--src_iter;
				--dst_iter;
			}
			
			//��ֵд�뵽posλ��
			auto iter = __start + (pos - __start);
			__set_value_by_value(iter, count, value);
			__end += count;
			return __start + (pos - __start);
		}

		//ʣ��ռ䲻��
		else {
			size_type size = this->size();
			size_type capacity = (size + count) * 2;				//Ԥ��һ��ռ�
			auto addr = __allocate(capacity);
			size_type index = 0;
			index = __set_value_by_range(addr, __start, pos);			//��[0, pos)��ʾ�ַ�д��
			auto ret = addr + index;
			__set_value_by_value(addr + index, count, value);				//�������ַ�д��
			index += count;
			index += __set_value_by_range(addr + index, pos, __end);			//�������ַ�д��
			__deallocate();				//�ͷ�ԭ���ڴ�
			__start = addr;
			__end = __start + index;
			__capacity = __start + capacity;
			return ret;
		}
	}

	//replace(first, last, count2, value)
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::replace(const_iterator first1, const_iterator last1,
		size_type count2, value_type value) {
		size_type count1 = last1 - first1;

		//[first1, last1)��Χ�㹻����count���ַ�
		if (count1 >= count2) {
			auto first = __start + (first1 - __start);				//���first1�ķ�const�汾
			auto last = __start + (last1 - __start);				//���last1�ķ�const�汾
			__set_value_by_value(first, count2, value);				//����[first1, last1)ǰ����
			__set_value_by_range(first + count2, last, __end);		//[last1, __end)ǰ��
			__end -= count2;
		}

		//[first1, last1)��Χ��������count���ַ�
		else {
			if (count2 - count1 <= __capacity - __end) {		//���������ڴ�
				size_type offset = count2 - count1;

				//[last, __end)�ַ�����offset��λ��
				auto iter = __end - 1 + offset;
				auto prev_iter = __end - 1;
				while (prev_iter >= last1) {
					*iter = *prev_iter;
					--iter;
					--prev_iter;
				}

				auto first = __start + (first1 - __start);
				__set_value_by_value(first, count2, value);			//д��[first2, last2)
				__end += offset;
			}
			else {
				size_type offset = count2 - count1;
				size_type capacity = (this->size() + offset) * 2;
				auto addr = __allocate(capacity);
				size_type index = __set_value_by_range(addr, __start, first1);		//��ǰ��д��
				__set_value_by_value(addr + index, count2, value);					//����[first2, last2)
				index += count2;
				index += __set_value_by_range(addr + index, last1, __end);							//����д��
				__deallocate();					//�ͷ�ԭ���ڴ�
				__start = addr;
				__end = addr + index;
				__capacity = __start + capacity;
			}
		}
	}

	//reserve(new_cap)
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::reserve(size_type new_cap = 0) {
		if (__capacity - __start >= new_cap) return;
		size_type size = this->size();
		auto addr = __allocate(new_cap);
		__set_value_by_range(addr, __start, __end);
		__deallocate();
		__start = addr;
		__end = __start + size;
		__capacity = __start + new_cap;
	}

	//resize(count, value)
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::resize(size_type count, value_type value = value_type()) {
		size_type size = this->size();
		if (count < size) return;
		reserve(count);
		__set_value_by_value(__end, count - size, value);
		__end += (count - size);
	}

	//substr(pos, count)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator> basic_string<CharType, Traits, Allocator>::substr(size_type pos = 0, size_type count = npos)const {
		if (count == npos) count = this->size() - pos;
		return basic_string(*this, pos, count);
	}

	//copy(data, pos, count)
	template<typename CharType, typename Traits, typename Allocator>
	typename basic_string<CharType, Traits, Allocator>::size_type basic_string<CharType, Traits, Allocator>::copy(
		const_pointer data, size_type pos = 0, size_type count = npos) {
		if (count == npos) count = get_size(data) - pos;
		__assign(count, data + pos, data + pos + count);
		return count;
	}

	//swap
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::swap(basic_string& rhs) {
		auto temp = __start;
		__start = rhs.__start;
		rhs.__start = temp;

		temp = __end;
		__end = rhs.__end;
		rhs.__end = temp;

		temp = __capacity;
		__capacity = rhs.__capacity;
		rhs.__capacity = temp;

		auto alloc = __alloc;
		__alloc = rhs.__alloc;
		rhs.__alloc = alloc;
	}

	//reverse
	template<typename CharType, typename Traits, typename Allocator>
	void basic_string<CharType, Traits, Allocator>::reverse() {
		size_type size = this->size();
		size_type mid_size = size / 2;
		for (size_type i = 0; i < mid_size; ++i) {
			value_type temp = __start[i];
			__start[i] = __start[size - i - 1];
			__start[size - i - 1] = temp;
		}
	}
}

//================================================================================
// basic_string<T> �ǳ�Ա��������
//================================================================================

namespace kkli {

	//============================== [operator +] ==============================

	//operator +(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator> operator+(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		kkli::basic_string<CharType, Traits, Allocator> str(lhs.size() + rhs.size());
		str += lhs;
		str += rhs;
		return str;
	}

	//operator +(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator> operator+(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		auto data_size = basic_string<CharType, Traits, Allocator>::__get_size(data);
		kkli::basic_string<CharType, Traits, Allocator> str(lhs.size() + data_size);
		str += lhs;
		str += data;
		return str;
	}

	//operator +(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator> operator+(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		auto data_size = basic_string<CharType, Traits, Allocator>::__get_size(data);
		kkli::basic_string<CharType, Traits, Allocator> str(lhs.size() + data_size);
		str += data;
		str += lhs;
		return str;
	}

	//operator +(lhs, value)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Traits, Allocator> operator+(const basic_string<CharType, Traits, Allocator>& lhs,
		CharType value) {
		kkli::basic_string<CharType, Traits, Allocator> str(lhs.size());
		str += lhs;
		str.push_back(value);
		return str;
	}

	//operator +(value, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	basic_string<CharType, Allocator> operator+(CharType value,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		kkli::basic_string<CharType, Traits, Allocator> str(rhs.size());
		str.push_back(value);
		str += rhs;
		return str;
	}

	//==================== [operator ==, !=, <, <=, >, >=] ====================

	//operator ==(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return lhs.compare(rhs) == 0;
	}

	//operator ==(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return lhs.compare(data) == 0;
	}

	//operator ==(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator==(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return rhs.compare(data) == 0;
	}

	//operator !=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return !(lhs == rhs);
	}

	//operator !=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return !(lhs == data);
	}

	//operator !=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator!=(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return !(data == rhs);
	}

	//operator <(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return lhs.compare(rhs) == -1;
	}

	//operator <(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return lhs.compare(data) == -1;
	}

	//operator <(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return rhs.compare(data) == 1;		//data<rhs����rhs>data
	}

	//operator >(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return lhs.compare(rhs) == 1;
	}

	//operator >(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return lhs.compare(data) == 1;
	}

	//operator >(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return rhs.compare(data) == -1;			//data>rhs����rhs<data
	}

	//operator <=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return !(lhs > rhs);
	}

	//operator <=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return !(lhs > data);
	}

	//operator <=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator<=(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return !(data > rhs);
	}

	//operator >=(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const basic_string<CharType, Traits, Allocator>& lhs,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return !(lhs < rhs);
	}

	//operator >=(lhs, data)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const basic_string<CharType, Traits, Allocator>& lhs,
		const CharType* data) {
		return !(lhs < data);
	}

	//operator >=(data, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	bool operator>=(const CharType* data,
		const basic_string<CharType, Traits, Allocator>& rhs) {
		return !(data < rhs);
	}


	//============================== [swap] ==============================

	//swap(lhs, rhs)
	template<typename CharType, typename Traits, typename Allocator>
	void swap(basic_string<CharType, Traits, Allocator>& lhs,
		basic_string<CharType, Traits, Allocator>& rhs) {
		lhs.swap(rhs);
	}


	//============================== [getline] ==============================

	//getline(is, str, delim)
	template<typename CharType, typename Traits, typename Allocator>
	std::istream& getline(
		std::istream& is,
		basic_string<CharType, Traits, Allocator>& str, CharType delim = '\n') {
		str = "";
		is >> std::noskipws;
		char c;
		is >> c;
		while (is) {
			if (c == delim) break;
			str.push_back(c);
			is >> c;
		}
		is.ignore(std::numeric_limits<std::streampos>::max());
		is.clear();
		return is;
	}


	//==================== [operator <<, >>] ====================

	//operator <<
	template<typename CharType, typename Traits, typename Allocator>
	std::ostream& operator<<(std::ostream& os,
		const basic_string<CharType, Traits, Allocator>& str) {
		os << str.c_str();
		return os;
	}

	//operator >>
	template<typename CharType, typename Traits, typename Allocator>
	std::istream& operator>>(std::istream& is, basic_string<CharType, Traits,
		Allocator>& str) {
		return getline(is, str);
	}


	//==================== [stox]: ����ʵ�֣����鷳���� ====================

	//basic_string to long long
	template<typename CharType, typename Traits, typename Allocator>
	long long stoll(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10);

	//basic_string to unsigned long long
	template<typename CharType, typename Traits, typename Allocator>
	unsigned long long stoull(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10);

	//basic_string to long double
	template<typename CharType, typename Traits, typename Allocator>
	long double stold(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0);

	//�·���stox��ͨ�������Ϸ���������stoll��stoull��stold ������ʵ�ֵ�

	//basic_string to int
	template<typename CharType, typename Traits, typename Allocator>
	int stoi(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10) {
		return stoll(str, pos, base);		//��ת����long long����խ��ת�ͳ�int
	}

	//basic_string to long
	template<typename CharType, typename Traits, typename Allocator>
	long stol(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10) {
		return stoll(str, pos, base);		//��ת����long long����խ��ת�ͳ�long
	}

	//basic_string to float
	template<typename CharType, typename Traits, typename Allocator>
	float stof(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0) {
		return stoull(str, pos);			//��ת����long double����խ��ת�ͳ�float
	}

	//basic_string to double
	template<typename CharType, typename Traits, typename Allocator>
	double stod(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0) {
		return stold(str, pos);				//��ת����long double����խ��ת�ͳ�double
	}

	//basic_string to unsigned long
	template<typename CharType, typename Traits, typename Allocator>
	unsigned long stoul(const basic_string<CharType, Traits, Allocator>& str,
		std::size_t* pos = 0, int base = 10) {
		return stoull(str, pos, base);		//��ת����unsigned long long����խ��ת�ͳ�unsigned long
	}

	//============================== [to_string] ==============================

	//to_string(unsigned long long)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(unsigned long long value) {
		if (value == 0) return "0";

		basic_string<CharType, Traits, Allocator> result;
		while (value != 0) {
			unsigned long long val = value % 10;
			result.push_back(static_cast<char>(val + 0x30));
			value /= 10;
		}
		result.reverse();		//��ת
		return result;
	}
	
	//to_string(long long)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(long long value) {
		using basic_string = basic_string<CharType, Traits, Allocator>;
		basic_string result;
		if (value < 0) {
			if(value == std::numeric_limits<long long>::min()) return "-9223372036854775808";
			else {
				result.push_back('-');	//����
				value = -value;			//��valueȡ��
			}
		}
		unsigned long long val = value;
		result += to_string(val);		//����to_string(unsigned long long)
		return result;
	}

	//to_string(long double)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(long double value) {
		basic_string<CharType, Traits, Allocator> result;
		if (value < 0) {
			result.push_back('-');
			value = -value;
		}
		unsigned long long integer_part = static_cast<unsigned long long>(value);	//��������
		unsigned long long decimal_part = (value - integer_part)*100000000;			//С�����֣��Ŵ�1ǧ��
		
		result += to_string(integer_part);			//�������֣�����to_string(unsigned long long)
		result.push_back('.');
		result += to_string(decimal_part);			//С�����֣�����to_string(unsigned long long)
		return result;
	}

	//to_string(int)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(int value) {
		return to_string(static_cast<long long>(value));
	}

	//to_sring(long)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(long value) {
		return to_string(static_cast<long long>(value));
	}

	//to_string(unsigned)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(unsigned value) {
		return to_string(static_cast<unsigned long long>(value));
	}

	//to_string(unsigned long)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(unsigned long value) {
		return to_string(static_cast<unsigned long long>(value));
	}

	//to_string(float)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(float value) {
		return to_string(static_cast<long double>(value));
	}

	//to_string(double)
	template<typename CharType = char, typename Traits = kkli::char_traits<CharType>,
		typename Allocator = kkli::allocator<CharType>>
		basic_string<CharType, Traits, Allocator> to_string(double value) {
		return to_string(static_cast<long double>(value));
	}
}
