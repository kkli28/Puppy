#pragma once

#include "stdafx.h"

//================================================================================
// allocator ¿‡∂®“Â
//================================================================================
namespace kkli {

	template<typename T>
	class allocator {
	public:
		typedef T value_type;

		//constructor
		allocator() {}
		
		template<typename U>
		allocator(const allocator<U>&) {}

		//allocate
		value_type* allocate(std::size_t num) {
			return static_cast<value_type*>(::operator new(num * sizeof(value_type)));
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
			delete ptr;
		}
	};

	//TODO:
	//uninitialized_fill / uninitialized_fill_n / uninitialized_copy / uninitialized_copy_n
}