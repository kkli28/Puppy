#pragma once

#include "stdafx.h"


//================================================================================
// pair<T> 类定义
//================================================================================
namespace kkli {
	template<typename T1, typename T2>
	class pair {
	public:
		T1 first;
		T2 second;

		typedef T1 first_type;
		typedef T2 second_type;

		// pair
		pair() {}

		template<typename K1, typename K2>
		pair(const K1& f, const K2& s) :first(f), second(s) {}

		template<typename K1, typename K2>
		pair(K1&& f, K2&& s) : first(f), second(s) {}

		template<typename K1, typename K2>
		pair(const pair<K1, K2>& mp) : first(mp.first), second(mp.second) {}

		template<typename K1, typename K2>
		pair(pair<K1, K2>&& mp) : first(std::move(mp.first)), second(std::move(mp.second)) {}

		// operator =
		template<typename K1, typename K2>
		pair& operator=(const pair<K1, K2>& mp);

		template<typename K1, typename K2>
		pair& operator=(pair<K1, K2>&& mp);

		// swap
		template<typename K1, typename K2>
		void swap(pair<K1, K2>& mp);
	};

	template<typename T1, typename T2>
	template<typename K1, typename K2>
	pair<T1,T2>& pair<T1, T2>::operator=(const pair<K1, K2>& mp) {
		first = mp.first;
		second = mp.second;
		return *this;
	}

	template<typename T1,typename T2>
	template<typename K1, typename K2>
	pair<T1, T2>& pair<T1, T2>::operator=(pair<K1, K2>&& mp) {
		first = std::move(mp.first);
		second = std::move(mp.second);
		return *this;
	}

	template<typename T1,typename T2>
	template<typename K1, typename K2>
	void pair<T1, T2>::swap(pair<K1, K2>& mp) {
		std::swap(first, mp.first);
		std::swap(second, mp.second);
	}
}

//================================================================================
// non-member functions
//================================================================================
namespace kkli {

	// make_pair
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(const T1& f, const T2& s) {
		return pair(f, s);
	}

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1&& f, T2&& s) {
		return pair<T1, T2>(f, s);
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
	template<size_t N,typename T>
	class tuple_element;

	// class: tuple_element<0>
	template<typename T1,typename T2>
	class tuple_element<0, pair<T1, T2>> {
	public:
		typedef typename pair<T1, T2>::first_type type;
	};

	// class: tuple_element<1>
	template<typename T1,typename T2>
	class tuple_element<1, pair<T1, T2>> {
	public:
		typedef typename pair<T1, T2>::second_type type;
	};
	
	// get
	template<size_t N,typename T1,typename T2>
	typename tuple_element<N,pair<T1,T2>>::type& get(pair<T1, T2>& mp) {
		return get(mp, typename tuple_element<N,pair<T1,T2>>::type());
	}

	// get<0>
	template<typename T1,typename T2>
	typename pair<T1,T2>::first_type& get(pair<T1, T2>& mp, typename tuple_element<0,pair<T1,T2>>::type) {
		return mp.first;
	}

	// get<1>
	template<typename T1,typename T2>
	typename pair<T1,T2>::second_type& get(pair<T1, T2>& mp, typename tuple_element<1,pair<T1,T2>>::type) {
		return mp.second;
	}

	//OVER
}