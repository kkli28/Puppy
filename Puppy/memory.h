#pragma once

#include "stdafx.h"
#include "iterator_traits.h"
#include "pair.h"

//================================================================================
// shared_ptr<T> 类定义
//================================================================================

namespace kkli {

	//前置声明：weak_ptr<T> 和 unique_ptr<T, Deleter>
	template<typename T>
	class weak_ptr;

	template<typename T,typename Deleter>
	class unique_ptr;

	//shared_ptr<T>
	template<typename T>
	class shared_ptr {
	public:
		typedef T				element_type;
		typedef weak_ptr<T>		weak_type;

	private:
		T* __ptr;
		std::size_t* __use_count;

		//deleter
		using deleter_type = void(*)(T*);
		deleter_type __deleter;

	public:
		//constructor
		shared_ptr() :__ptr(nullptr), __use_count(0), __deleter(nullptr) {}
		
		template<typename U>
		explicit shared_ptr(U* ptr) 
			:__ptr(ptr), __use_count(new std::size_t(1)), __deleter(nullptr) {}

		//__deleter被构造了两次，分别是__deleter(nullptr)和__deleter(&d)，可行吗？
		template<typename U,typename Deleter>
		shared_ptr(U* ptr, Deleter d) : shared_ptr(ptr), __deleter(&d) {}

		template<typename Deleter>
		shared_ptr(Deleter d) : shared_ptr(), __deleter(&d) {}

		template<typename U>
		shared_ptr(const shared_ptr<U>& rhs)
			:__ptr(rhs.__ptr), __use_count(rhs.__use_count), __deleter(rhs.__deleter) {
			++(*__use_count);
		}

		template<typename U>
		shared_ptr(shared_ptr<U>&& rhs)
			: __ptr(rhs.__ptr), __use_count(rhs.__use_count), __deleter(rhs.__deleter) {
			rhs.__ptr = nullptr;
			rhs.__use_count = nullptr;
			rhs.__deleter = nullptr;
		}

		template<typename U>
		explicit shared_ptr(const weak_ptr<U>& wp) {
			//TODO: ?
		}

		template<typename U,typename Deleter>
		shared_ptr(unique_ptr<U, Deleter>&& up) {
			//TODO: ?
		}

		//destructor
		~shared_ptr() {
			--(*__use_count);
			if (*__use_count == 0) {
				if (__deleter == nullptr) delete __ptr;
				else __deleter(__ptr);
				delete __use_count;
			}
		}

		//operator =
		template<typename U>
		shared_ptr& operator=(const shared_ptr<U>& rhs) {
			
			if (--(*__use_count) == 0) {
				if (__deleter == nullptr) delete __ptr;
				else __deleter(__ptr);
				delete __use_count;
			}

			++(*(rhs.__use_count));		//获得资源+1
			__ptr = rhs.__ptr;
			__use_count = rhs.__use_count;
			__deleter = rhs.__deleter;
			return *this;
		}

		//operator =
		//TODO: 
	};
}

//================================================================================
// weak_ptr<T> 类定义
//================================================================================

namespace kkli {
	template<typename T>
	class weak_ptr {
		//TODO: 
	};
}

//================================================================================
// unique_ptr<T> 类定义
//================================================================================


//================================================================================
// allocator<T> 类定义
//================================================================================

namespace kkli {

	template<typename T>
	class allocator {
	public:
		typedef T								value_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;

		//constructor
		allocator() {}

		template<typename U>
		allocator(const allocator<U>&) {}

		//allocate
		pointer allocate(std::size_t num) {
			return static_cast<pointer>(::operator new(num * sizeof(value_type)));
		}

		//deallocate
		void deallocate(value_type* ptr, std::size_t num) {
			::operator delete(ptr);
		}

		//construct
		void construct(value_type* ptr, const value_type& val) {
			new (ptr) value_type(val);
		}

		//destroy
		void destroy(value_type* ptr) {
			ptr->~value_type();
		}
	};

	//non-member function

	//operator ==
	template<typename T1, typename T2>
	bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) { return true; }

	//operator !=
	template<typename T1, typename T2>
	bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) { return false; }
}


//================================================================================
// uninitialized_x / destroy_x 函数定义
//================================================================================

namespace kkli{

	//addressof
	template<typename T>
	T* addressof(T& val) {
		return reinterpret_cast<T*>(
			&const_cast<char&>(
				reinterpret_cast<const volatile char&>(arg)));
	}

	//uninitialized_copy
	template<typename InputIt, typename ForwardIt>
	ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt dest) {
		for (; first != last; ++first, ++dest) {
			::new (static_cast<void*>(addressof(*first))) typename iterator_traits<ForwardIt>::value_type(*first);
		}
		return dest;
	}

	//uninitialized_copy
	template<typename InputIt,typename Size,typename ForwardIt>
	ForwardIt uninitialized_copy_n(InputIt first, Size count, ForwardIt dest) {
		for (; count > 0; --count, ++first, ++dest) {
			::new (static_cast<void*>(addressof(*dest))) typename iterator_traits<ForwardIt>::value_type(*first);
		}
		return dest;
	}

	//uninitialized_fill
	template<typename ForwardIt, typename T>
	void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value) {
		for (; first != last; ++first) {
			::new (static_cast<void*>(addressof(*first))) typename iterator_traits<ForwardIt>::value_type(value);
		}
	}

	//uninitialized_fill_n
	template<typename ForwardIt, typename Size, typename T>
	void uninitialized_fill_n(ForwardIt first, Size count, const T& value) {
		for (; count > 0; --count, ++first) {
			::new (static_cast<void*>(addressof(*first))) typename iterator_traits<ForwardIt>::value_type(value);
		}
	}

	//uninitialized_move
	template<typename InputIt, typename ForwardIt>
	ForwardIt uninitialized_move(InputIt first, InputIt last, ForwardIt dest) {
		for (; first != last; ++first, ++dest) {
			::new (static_cast<void*>(addressof(*dest))) typename iterator_traits<ForwardIt>::value_type(std::move(*first));
		}
		return dest;
	}

	//uninitialized_move_n
	template<typename InputIt, typename Size, typename ForwardIt>
	kkli::pair<InputIt, ForwardIt> uninitialized_move_n(InputIt first, Size count, ForwardIt dest) {
		for (; count > 0; ++first, ++dest) {
			::new (static_cast<void*>(addressof(*dest))) typename iterator_traits<ForwardIt>::value_type(*first);
		}
		return make_pair{ first,dest };
	}

	//uninitialized_default_construct
	template<typename ForwardIt>
	void uninitialized_default_construct(ForwardIt first, ForwardIt last) {
		for (; first != last; ++first) {
			::new (static_cast<void*>(addressof(*first))) typename iterator_traits<ForwardIt>::value_type();
		}
	}

	//uninitialized_default_construct_n
	template<typename ForwardIt,typename Size>
	void uninitialized_default_construct_n(ForwardIt first, Size count) {
		for (; count > 0; --count, ++first) {
			::new (static_cast<void*>(addressof(*first))) typename iterator_traits<ForwardIt>::value_type();
		}
	}

	//destroy_at
	template<typename T>
	void destroy_at(T* ptr) {
		ptr->~T();
	}

	//destroy
	template<typename ForwardIt>
	void destroy(ForwardIt first, ForwardIt last) {
		for (; first != last; ++first)
			destroy_at(addressof(*first));
	}

	//destroy_n
	template<typename ForwardIt, typename Size>
	ForwardIt destroy_n(ForwardIt first, Size count) {
		for (; count > 0; --count, ++first) {
			destroy_at(addressof(*first));
		}
		return first;
	}
}

