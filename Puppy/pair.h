#pragma once

#include "stdafx.h"
#include "utility.h"

//================================================================================
// pair<T> 类定义
//================================================================================
namespace kkli {
	template<typename T1, typename T2>
	class pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		// pair
		pair() :first(first_type()), second(second_type()) {}
		pair(const T1& f, const T2& s) : first(f), second(s) {}
		//pair(T1&& f, T2&& s) :first(std::move(f)), second(std::move(s)) {}
		pair(const pair& rhs) :first(rhs.first), second(rhs.second) {}
		pair(pair&& rhs) :first(std::move(rhs.first)), second(std::move(rhs.second)) {}

		template<typename U1, typename U2>
		pair(const pair<U1, U2>& rhs) : first(rhs.first), second(rhs.second) {}

		template<typename U1, typename U2>
		pair(pair<U1, U2>&& rhs) : first(std::move(rhs.first)), second(std::move(rhs.second)) {}

		// operator =
		pair& operator=(const pair& rhs) {
			first = rhs.first;
			second = rhs.second;
			return *this;
		}

		pair& operator=(pair&& rhs) {
			first = std::move(rhs.first);
			second = std::move(rhs.second);
			return *this;
		}

		template<typename U1, typename U2>
		pair& operator=(const pair<U1, U2>& rhs) {
			first = rhs.first;
			second = rhs.second;
		}

		template<typename U1, typename U2>
		pair& operator=(pair<U1, U2>&& rhs) {
			first = std::move(rhs.first);
			second = std::move(rhs.second);
		}

		// swap
		void swap(pair& rhs) {
			kkli::swap(first, rhs.first);
			kkli::swap(second, rhs.second);
		}
	};
}

//non-member function
namespace kkli{

	// make_pair
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1&& f, T2&& s) {
		return pair<T1,T2>(std::move(f), std::move(s));
	}

	// operator ==
	template<typename T1, typename T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	// operator !=
	template<typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	// operator <
	template<typename T1, typename T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs.first < rhs.first)
			|| ((lhs.first == rhs.first) && (lhs.second < rhs.second));
	}

	// operator >
	template<typename T1, typename T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs.first > rhs.first)
			|| ((lhs.first == rhs.first) && (lhs.second > rhs.second));
	}

	// operator <=
	template<typename T1, typename T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs > rhs);
	}

	// operator >=
	template<typename T1, typename T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}

	// swap
	template<typename T1, typename T2>
	void swap(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		lhs.swap(rhs);
	}

	//tuple_size
	template<typename T>
	class tuple_size;

	template<typename T1, typename T2>
	class tuple_size<pair<T1, T2>> {
	public:
		typedef std::size_t value_type;
		static constexpr value_type value = 2;
	};

	// get函数模板 与其有关的tuple_element的定义

	// class: tuple_element
	template<std::size_t N, typename T>
	class tuple_element;

	// class: tuple_element<0>
	template<typename T1, typename T2>
	class tuple_element<0, pair<T1, T2>> {
	public:
		typedef typename pair<T1, T2>::first_type type;
	};

	// class: tuple_element<1>
	template<typename T1, typename T2>
	class tuple_element<1, pair<T1, T2>> {
	public:
		typedef typename pair<T1, T2>::second_type type;
	};

	// get
	template<size_t N, typename T1, typename T2>
	typename tuple_element<N, pair<T1, T2>>::type& get(pair<T1, T2>& p) {
		return __aux_get(p, typename tuple_element<N, pair<T1, T2>>::type());
	}

	// get<0>
	template<typename T1, typename T2>
	typename pair<T1, T2>::first_type& __aux_get(pair<T1, T2>& p, typename tuple_element<0, pair<T1, T2>>::type) {
		return p.first;
	}

	// get<1>
	template<typename T1, typename T2>
	typename pair<T1, T2>::second_type& __aux_get(pair<T1, T2>& p, typename tuple_element<1, pair<T1, T2>>::type) {
		return p.second;
	}
}
