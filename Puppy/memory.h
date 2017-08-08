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

	template<typename T, typename Deleter>
	class unique_ptr;

	//default_deleter
	template<typename T>
	class default_deleter {
	public:
		void operator()(const T* ptr) {
			delete ptr;
		}
	};

	//shared_ptr<T>
	template<typename T, typename Deleter=default_deleter<T>>
	class shared_ptr {
	public:
		typedef T				element_type;
		typedef weak_ptr<T>		weak_type;

	private:
		T*				__ptr;
		std::size_t*	__use_count;
		Deleter			__deleter;

		//不再管理当前对象
		void no_longer_management() {
			if (--(*__use_count) == 0) {
				__deleter(__ptr);
				delete __use_count;
			}
		}

		//从其他对象获得资源
		template<typename U>
		void copy_from_others(const shared_ptr<U,Deleter>& rhs) {
			__ptr = rhs.__ptr;
			__use_count = rhs.__use_count;
		}
	public:
		//constructor
		shared_ptr()
			:__ptr(nullptr), __use_count(new std::size_t(1)) {}

		shared_ptr(std::nullptr_t) :__ptr(nullptr), __use_count(new std::size_t(1)) {}
		
		template<typename U>
		explicit shared_ptr(U* ptr)
			:__ptr(ptr), __use_count(new std::size_t(1)) {}

		template<typename U>
		shared_ptr(U* ptr, Deleter d)
			: __ptr(ptr), __use_count(new std::size_t(1)), __deleter(d) {}

		shared_ptr(std::nullptr_t ptr, Deleter d)
			: __ptr(nullptr), __use_count(new std::size_t(1)), __deleter(d) {}

		template<typename U>
		shared_ptr(const shared_ptr<U, Deleter>& rhs, element_type* ptr)
			: __ptr(ptr), __use_count(new std::size_t(1)), __deleter(rhs.__deleter) {}

		shared_ptr(const shared_ptr& rhs)
			:__ptr(rhs.__ptr), __use_count(rhs.__use_count), __deleter(rhs.__deleter) {
			++*(__use_count);
		}

		template<typename U>
		shared_ptr(const shared_ptr<U, Deleter>& rhs) 
			: __ptr(ptr), __use_count(rhs.__use_count), __deleter(rhs.__deleter) {}

		shared_ptr(shared_ptr&& rhs)
			:__ptr(rhs.__ptr), __use_count(rhs.__use_count), __deleter(rhs.__deleter) {
			rhs.__ptr = nullptr;
			rhs.__use_count = new std::size_t(1);
		}

		template<typename U>
		shared_ptr(shared_ptr<U, Deleter>&& rhs)
			: __ptr(rhs.__ptr), __use_count(rhs.__use_count), __deleter(rhs.__deleter) {
			rhs.__ptr = nullptr;
			rhs.__use_count = new std::size_t(1);
		}

		template<typename U>
		explicit shared_ptr(const weak_ptr<U>& rhs) {}

		template<typename U>
		shared_ptr(unique_ptr<U, Deleter>&& rhs)
			:__ptr = rhs.release(), __use_count = new std::size_t(1), __deleter = rhs.get_deleter() {}

		//destructor
		~shared_ptr();

		//operator =
		shared_ptr& operator=(const shared_ptr& rhs);

		template<typename U>
		shared_ptr& operator=(const shared_ptr<U, Deleter>& rhs);

		shared_ptr& operator=(shared_ptr&& rhs);

		template<typename U>
		shared_ptr& operator=(shared_ptr<U, Deleter>&& rhs);

		template<typename U>
		shared_ptr& operator=(unique_ptr<U, Deleter>&& rhs);
		
		//reset
		void reset();

		template<typename U>
		void reset(U* ptr);

		template<typename U>
		void reset(U* ptr, Deleter d);
		
		//swap
		void swap(shared_ptr& rhs);

		//get
		element_type* get()const { return __ptr; }

		//operator *
		element_type& operator*()const { return *get(); }

		//operator ->
		element_type* operator->()const { return get(); }

		//operator []
		element_type& operator[](std::ptrdiff_t i) {
			return get()[i];
		}

		//use_count
		std::size_t use_count()const { return *(__use_count); }

		//unique
		bool unique()const { return *(__use_count) == 1; }

		//operator bool
		explicit operator bool()const { return get() != nullptr; }

		//owner_before
		template<typename U>
		bool owner_before(const shared_ptr<U, Deleter>& rhs)const;

		template<typename U>
		bool owner_before(const weak_ptr<U>& rhs)const;

		//get_deleter
		Deleter& get_deleter() { return __deleter; }
		const Deleter& get_deleter()const { return __deleter; }
	};
}

//成员函数定义
namespace kkli{

	//~shared_ptr
	template<typename T, typename Deleter>
	shared_ptr<T, Deleter>::~shared_ptr() {
		no_longer_management();
	}

	//operator =(rhs)
	template<typename T, typename Deleter>
	shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(const shared_ptr& rhs) {
		no_longer_management();
		++(*(rhs.__use_count));		//获得资源+1
		copy_from_others(rhs);
		return *this;
	}

	//operator =(rhs<U>)
	template<typename T,typename Deleter>
	template<typename U>
	shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(const shared_ptr<U, Deleter>& rhs) {
		no_longer_management();
		++(*(rhs.__use_count));		//获得资源+1
		copy_from_others(rhs);
		return *this;
	}

	//operator =(&&rhs)
	template<typename T, typename Deleter>
	shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(shared_ptr&& rhs) {
		no_longer_management();
		copy_from_others(rhs);
		rhs.__ptr = nullptr;
		rhs.__use_count = new std::size_t(1);
		return *this;
	}

	//operator =(&&rhs<U>)
	template<typename T, typename Deleter>
	template<typename U>
	shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(shared_ptr<U, Deleter>&& rhs) {
		no_longer_management();
		copy_from_others(rhs);
		rhs.__ptr = nullptr;
		rhs.__use_count = new std::size_t(1);
		return *this;
	}

	//reset()
	template<typename T, typename Deleter>
	void shared_ptr<T, Deleter>::reset() {
		no_longer_management();
		__ptr = nullptr;
		__use_count = new std::size_t(1);
	}

	//reset(ptr)
	template<typename T, typename Deleter>
	template<typename U>
	void shared_ptr<T, Deleter>::reset(U* ptr) {
		no_longer_management();

		__ptr = ptr;
		__use_count = new std::size_t(1);
	}

	//reset(ptr, d)
	template<typename T, typename Deleter>
	template<typename U>
	void shared_ptr<T,Deleter>::reset(U* ptr, Deleter d) {
		no_longer_management();
		__ptr = ptr;
		__use_count = new std::size_t(1);
		__deleter = &d;
	}

	//swap(rhs)
	template<typename T, typename Deleter>
	void shared_ptr<T, Deleter>::swap(shared_ptr<T, Deleter>& rhs) {
		auto temp1 = __ptr;
		__ptr = rhs.__ptr;
		rhs.__ptr = temp1;

		auto temp2 = __use_count;
		__use_count = rhs.__use_count;
		rhs.__use_count = temp2;
	}
}

//非成员函数定义
namespace kkli {

	//make_shared
	template<typename T, class... Args>
	shared_ptr<T> make_shared(Args&&... args) {
		return shared_ptr<T>(new T(args...));
	}

	//allocate_shared
	template<typename T, typename Alloc, typename... Args>
	shared_ptr<T> allocate_shared(const Alloc& alloc, Args&&... args);

	//static_pointer_cast
	template<typename T, typename U, typename Deleter>
	shared_ptr<T, Deleter> static_pointer_cast(const shared_ptr<U, Deleter>& rhs) {
		return shared_ptr<T, Deleter>(static_cast<T*>(rhs.get()));
	}

	//dynamic_pointer_cast
	template<typename T, typename U, typename Deleter>
	shared_ptr<T, Deleter> dynamic_pointer_cast(const shared_ptr<U, Deleter>& rhs) {
		return shared_ptr<T, Deleter>(dynamic_cast<T*>(rhs.get()));
	}

	//const_pointer_cast
	template<typename T, typename U, typename Deleter>
	shared_ptr<T, Deleter> const_pointer_cast(const shared_ptr<U, Deleter>& rhs) {
		return shared_ptr<T, Deleter>(const_cast<T*>(rhs.get()));
	}

	//reinterpret_pointer_cast
	template<typename T, typename U, typename Deleter>
	shared_ptr<T, Deleter> reinterpret_pointer_cast(const shared_ptr<U, Deleter>& rhs) {
		return shared_ptr<T, Deleter>(reinterpret_cast<T*>(rhs.get()));
	}

	//get_deleter
	template<typename T, typename Deleter>
	Deleter* get_deleter(const shared_ptr<T, Deleter>& sp) {
		return static_cast<Deleter*>(sp.get_deleter());
	}

	//operator ==
	template<typename T, typename U, typename Deleter>
	inline bool operator==(const shared_ptr<T, Deleter>& lhs, const shared_ptr<U, Deleter>& rhs) {
		return lhs.get() == rhs.get();
	}

	//operator !=
	template<typename T, typename U, typename Deleter>
	inline bool operator!=(const shared_ptr<T, Deleter>& lhs, const shared_ptr<U, Deleter>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T, typename U, typename Deleter>
	bool operator<(const shared_ptr<T, Deleter>& lhs, const shared_ptr<U, Deleter>& rhs) {
		return lhs.get() < rhs.get();
	}

	//operator >
	template<typename T, typename U, typename Deleter>
	bool operator>(const shared_ptr<T, Deleter>& lhs, const shared_ptr<U, Deleter>& rhs) {
		return rhs < lhs;
	}

	//operator <=
	template<typename T, typename U, typename Deleter>
	bool operator<=(const shared_ptr<T, Deleter>& lhs, const shared_ptr<U, Deleter>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T, typename U, typename Deleter>
	bool operator>=(const shared_ptr<T, Deleter>& lhs, const shared_ptr<U, Deleter>& rhs) {
		return !(lhs < rhs);
	}

	//compare a shared_ptr with a null pointer

	//operator ==(lhs, nullptr)
	template<typename T, typename Deleter>
	bool operator==(const shared_ptr<T, Deleter>& lhs, std::nullptr_t rhs) {
		return !lhs;
	}

	//operator ==(nullptr, rhs)
	template<typename T, typename Deleter>
	bool operator==(std::nullptr_t lhs, const shared_ptr<T, Deleter>& rhs) {
		return !rhs;
	}

	//operator !=(lhs, nullptr)
	template<typename T, typename Deleter>
	bool operator!=(const shared_ptr<T, Deleter>& lhs, std::nullptr_t rhs) {
		return bool(lhs);
	}

	//operator !=(nullptr, rhs)
	template<typename T, typename Deleter>
	bool operator!=(std::nullptr_t lhs, const shared_ptr<T, Deleter>& rhs) {
		return bool(rhs);
	}

	//operator <(lhs, nullptr)
	template<typename T, typename Deleter>
	bool operator<(const shared_ptr<T, Deleter>& lhs, std::nullptr_t rhs) {
		return std::less<shared_ptr<T, Deleter>::element_type*>()(lhs.get(), rhs);
	}

	//operator <(nullptr, rhs)
	template<typename T, typename Deleter>
	bool operator<(std::nullptr_t lhs, const shared_ptr<T, Deleter>& rhs) {
		return std::less<shared_ptr<T, Deleter>::element_type*>()(lhs, rhs.get());
	}

	//operator >(lhs, nullptr)
	template<typename T, typename Deleter>
	bool operator>(const shared_ptr<T, Deleter>& lhs, std::nullptr_t rhs) {
		return rhs < lhs;
	}

	//operator >(nullptr, rhs)
	template<typename T, typename Deleter>
	bool operator>(std::nullptr_t lhs, const shared_ptr<T, Deleter>& rhs) {
		return rhs < lhs;
	}

	//operator <=(lhs, nullptr)
	template<typename T, typename Deleter>
	bool operator<=(const shared_ptr<T, Deleter>& lhs, std::nullptr_t rhs) {
		return !(rhs < lhs);
	}

	//operator <=(nullptr, rhs)
	template<typename T, typename Deleter>
	bool operator<=(std::nullptr_t lhs, const shared_ptr<T, Deleter>& rhs) {
		return !(rhs < lhs);
	}

	//operator >=(lhs, nullptr)
	template<typename T, typename Deleter>
	bool operator>=(const shared_ptr<T, Deleter>& lhs, std::nullptr_t rhs) {
		return !(lhs < rhs);
	}

	//operator >=(nullptr, rhs)
	template<typename T, typename Deleter>
	bool operator>=(std::nullptr_t lhs, const shared_ptr<T, Deleter>& rhs) {
		return !(lhs < rhs);
	}

	//operator <<
	template<typename T, typename Deleter>
	std::ostream& operator<<(std::ostream& os, const shared_ptr<T, Deleter>& sp) {
		os << sp.get();
		return os;
	}

	//swap
	template<typename T, typename Deleter>
	void swap(shared_ptr<T, Deleter>& lhs, shared_ptr<T, Deleter>& rhs) {
		return lhs.swap(rhs);
	}
}

//================================================================================
// weak_ptr<T> 类定义
//================================================================================

namespace kkli {
	template<typename T>
	class weak_ptr {
	public:
		typedef T	element_type;

	private:
		const shared_ptr<T>* __sp;

	public:
		//constructor
		constexpr weak_ptr() :__sp(nullptr) {}
		weak_ptr(const weak_ptr& rhs) :__sp(rhs.__sp) {}
		weak_ptr(weak_ptr&& rhs) :__sp(rhs.__sp) { rhs.__sp = nullptr; }

		template<typename U>
		weak_ptr(const weak_ptr<U>& rhs) : __sp(rhs.__sp) {}

		template<typename U>
		weak_ptr(const shared_ptr<U>& rhs) : __sp(&rhs) {}

		template<typename U>
		weak_ptr(weak_ptr<U>&& rhs) : __sp(rhs.__sp) { rhs.__sp = nullptr; }

		//destructor
		~weak_ptr() { __sp = nullptr; }

		//operator =
		weak_ptr& operator=(const weak_ptr& rhs) {
			__sp = rhs.__sp;
			return *this;
		}

		weak_ptr& operator=(weak_ptr&& rhs) {
			__sp = rhs.__sp;
			rhs.__sp = nullptr;
			return *this;
		}

		template<typename U>
		weak_ptr& operator=(const weak_ptr<U>& rhs) {
			__sp = rhs.__sp;
			return *this;
		}

		template<typename U>
		weak_ptr& operator=(const shared_ptr<U>& rhs) {
			__sp = &rhs;
			return *this;
		}

		template<typename U>
		weak_ptr& operator=(weak_ptr<U>&& rhs) {
			__sp = rhs.__sp;
			rhs.__sp = nullptr;
			return *this;
		}

		//reset
		void reset() { __sp = nullptr; }
		
		//swap
		void swap(weak_ptr& rhs) {
			auto temp = __sp;
			__sp = rhs.__sp;
			rhs.__sp = temp;
		}

		std::size_t use_count()const {
			if (__sp != nullptr) {
				return __sp->use_count();
			}
			else return 0;
		}

		//expired
		bool expired()const { return use_count()==0; }

		//lock
		shared_ptr<T> lock()const {
			return expired() ? shared_ptr<T>() : shared_ptr<T>(*__sp);
		}

		//owner_before
		template<typename U>
		bool owner_before(const weak_ptr<U>& rhs)const;

		template<typename U>
		bool owner_before(const shared_ptr<T>& rhs)const;
	};

	//swap
	template<typename T>
	void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) {
		lhs.swap(rhs);
	}
}

//================================================================================
// unique_ptr<T> 类定义
//================================================================================

namespace kkli {

	template<typename T, typename Deleter = default_deleter<T>>
	class unique_ptr {
	public:
		typedef T		element_type;
		typedef T*		pointer;
		typedef Deleter deleter_type;

	private:
		pointer __ptr;
		Deleter __deleter;

	public:
		//constructor
		constexpr unique_ptr() :__ptr(nullptr) {}
		constexpr unique_ptr(std::nullptr_t ptr) : __ptr(ptr) {}
		explicit unique_ptr(pointer ptr) :__ptr(ptr) {}
		unique_ptr(pointer ptr, Deleter d) :__ptr(ptr), __deleter(d) {}
		unique_ptr(unique_ptr&& rhs)
			:__ptr(rhs.__ptr) {
			rhs.__ptr = nullptr;
		}

		template<typename U, typename D>
		unique_ptr(unique_ptr<U, D>&& rhs)
			: __ptr(rhs.__ptr), __deleter(rhs.__deleter) {}

		//destructor
		~unique_ptr() { __deleter(__ptr); }

		//operator =
		unique_ptr& operator=(unique_ptr&& rhs) {
			__deleter(__ptr);
			__ptr = rhs.__ptr;
			rhs.__ptr = nullptr;
			return *this;
		}
		unique_ptr& operator=(std::nullptr_t ptr) {
			__deleter(__ptr);
			__ptr = ptr;
			return *this;
		}

		template<typename U, typename D>
		unique_ptr& operator= (unique_ptr<U, D>&& rhs) {
			__ptr = rhs.__ptr;
			__deleter = rhs.__deleter;
			rhs.__ptr = nullptr;
			return *this;
		}

		//release
		pointer release() {
			pointer ptr = __ptr;
			__ptr = nullptr;
			return ptr;
		}

		//reset
		void reset(pointer ptr = pointer()) {
			__deleter(__ptr);
			__ptr = ptr;
		}

		//swap
		void swap(unique_ptr& rhs) {
			auto ptr = __ptr;
			__ptr = rhs.__ptr;
			rhs.__ptr = ptr;

			auto deleter = __deleter;
			__deleter = rhs.__deleter;
			rhs.__deleter = deleter;
		}

		//get
		pointer get()const { return __ptr; }

		//get_deleter
		Deleter& get_deleter() { return __deleter; }
		const Deleter& get_deleter()const { return __deleter; }

		//operator bool
		explicit operator bool()const { return __ptr != nullptr; }

		//operator *
		T& operator*()const { return *__ptr; }

		//operator ->
		pointer operator->()const { return __ptr; }

		//operator []
		T& operator[](std::size_t idx)const { return get()[idx]; }
	};
}

//非成员函数定义
namespace kkli {
	//make_unique
	template<typename T, typename... Args>
	unique_ptr<T> make_unique(Args&&... args) {
		return unique_ptr<T>(new T(args...));
	}

	//make_unique : only for array types with unknow bound
	/*
	template<typename T>
	unique_ptr<T[]> make_unique(std::size_t size) {
		return unique_ptr<T[]>(new T[size]);
	}
	*/

	//make_unique : only for array types with known bound
	/*
	template<typename T, class... Args>
	// unspecified // make_unique(Args&&... args) = delete;
	*/

	//operator == != < <= > >= (lhs, rhs)
	template<typename T1, typename D1, typename T2, typename D2>
	bool operator==(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return lhs.get() == rhs.get();
	}

	template<typename T1, typename D1, typename T2, typename D2>
	bool operator!=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T1, typename D1, typename T2, typename D2>
	bool operator<(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return lhs.get() < rhs.get();
	}

	template<typename T1, typename D1, typename T2, typename D2>
	bool operator>(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return lhs.get() > rhs.get();
	}

	template<typename T1, typename D1, typename T2, typename D2>
	bool operator<=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return !(lhs > rhs);
	}

	template<typename T1, typename D1, typename T2, typename D2>
	bool operator>=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return !(lhs < rhs);
	}

	//operator == != < <= > >= (lhs, nullptr) / (nullptr, rhs)
	template<typename T, typename D>
	bool operator==(const unique_ptr<T, D>& lhs, std::nullptr_t) {
		return !lhs;
	}

	template<typename T, typename D>
	bool operator==(std::nullptr_t, const unique_ptr<T, D>& rhs) {
		return !rhs;
	}

	template<typename T, typename D>
	bool operator!=(const unique_ptr<T, D>& lhs, std::nullptr_t) {
		return bool(lhs);
	}

	template<typename T, typename D>
	bool operator!=(std::nullptr_t, unique_ptr<T, D>& rhs) {
		return bool(rhs);
	}

	template<typename T, typename D>
	bool operator<(const unique_ptr<T, D>& lhs, std::nullptr_t) {
		return lhs.get() < nullptr;
	}

	template<typename T, typename D>
	bool operator<(std::nullptr_t, const unique_ptr<T, D>& rhs) {
		return nullptr < rhs.get();
	}

	template<typename T, typename D>
	bool operator>(const unique_ptr<T, D>& lhs, std::nullptr_t) {
		return lhs.get() > nullptr;
	}

	template<typename T, typename D>
	bool operator>(std::nullptr_t, const unique_ptr<T, D>& rhs) {
		return nullptr > rhs.get();
	}

	template<typename T, typename D>
	bool operator<=(const unique_ptr<T, D>& lhs, std::nullptr_t) {
		return !(lhs.get() > nullptr);
	}

	template<typename T, typename D>
	bool operator<=(std::nullptr_t, const unique_ptr<T, D>& rhs) {
		return !(nullptr > rhs.get());
	}

	template<typename T, typename D>
	bool operator>=(const unique_ptr<T, D>& lhs, std::nullptr_t) {
		return !(lhs.get() < nullptr);
	}

	template<typename T, typename D>
	bool operator>=(std::nullptr_t, const unique_ptr<T, D>& rhs) {
		return !(nullptr < rhs.get());
	}

	//swap
	template<typename T,typename D>
	void swap(unique_ptr<T, D>& lhs, unique_ptr<T, D>& rhs) {
		lhs.swap(rhs);
	}
}

//如何特化unique_ptr<T[], Deleter>？全部重写一遍？好绝望！

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
				reinterpret_cast<const volatile char&>(val)));
	}

	//uninitialized_copy
	template<typename InputIt, typename ForwardIt>
	ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt dest) {
		for (; first != last; ++first, ++dest) {
			::new (static_cast<void*>(addressof(*dest))) typename iterator_traits<ForwardIt>::value_type(*first);
		}
		return dest;
	}

	//uninitialized_copy_n
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
		for (; count > 0; --count, ++first, ++dest) {
			::new (static_cast<void*>(addressof(*dest))) typename iterator_traits<ForwardIt>::value_type(std::move(*first));
		}
		return make_pair(std::move(first), std::move(dest));
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
