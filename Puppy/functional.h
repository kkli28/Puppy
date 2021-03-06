#pragma once

#include "stdafx.h"

//STL functional.h 的简化版


//================================================================================
// function<T> 类定义
//================================================================================

namespace kkli {

	template<typename T>
	class function;

	template<typename R, typename... Args>
	class function<R(Args...)>;
}

//Function Objects
namespace kkli {

	//less<T>
	template<typename T>
	class less {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
		constexpr result_type operator()(const first_argument_type& first,
			const second_argument_type& second) const {
			return first < second;
		}
	};

	//equal_to
	template<typename T>
	class equal_to {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
		constexpr result_type operator()(const first_argument_type& first,
			const second_argument_type& second) const {
			return first == second;
		}
	};

	//plus
	template<typename T>
	class plus {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
		constexpr result_type operator()(const first_argument_type& first,
			const second_argument_type& second) const {
			return first + second;
		}
	};

	//minus
	template<typename T>
	class minus {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
		constexpr result_type operator()(const first_argument_type& first,
			const second_argument_type& second) const {
			return first - second;
		}
	};

	//multiplies
	template<typename T>
	class multiplies {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
		constexpr result_type operator()(const first_argument_type& first,
			const second_argument_type& second) const {
			return first * second;
		}
	};

	//divides
	template<typename T>
	class divides {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
		constexpr result_type operator()(const first_argument_type& first,
			const second_argument_type& second) const {
			return first / second;
		}
	};
}
