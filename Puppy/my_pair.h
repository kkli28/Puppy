#pragma once

#pragma once

#include "stdafx.h"

namespace kkli {

	//class my_pair
	template<typename T1, typename T2>
	class my_pair {
	public:
		T1 first;
		T2 second;

		typedef T1 first_type;
		typedef T2 second_type;

		// my_pair
		my_pair() {
			std::cout << "my_pair()" << std::endl;
		}

		template<typename K1, typename K2>
		my_pair(const K1& f, const K2& s) :first(f), second(s) {
			std::cout << "my_pair(const K1&, const K2&)" << std::endl;
		}

		template<typename K1, typename K2>
		my_pair(K1&& f, K2&& s) : first(std::move(f)), second(std::move(s)) {
			std::cout << "my_pair(K1&&, K2&&)" << std::endl;
		}

		template<typename K1, typename K2>
		my_pair(const my_pair<K1, K2>& mp) : first(mp.first), second(mp.second) {
			std::cout << "my_pair(const my_pair<K1, K2>&)" << std::endl;
		}

		template<typename K1, typename K2>
		my_pair(my_pair<K1, K2>&& mp) : first(std::move(mp.first)), second(std::move(mp.second)) {
			std::cout << "my_pair(my_pair<K1, K2>&&)" << std::endl;
		}

		// operator =
		template<typename K1, typename K2>
		my_pair& operator=(const my_pair<K1, K2>& mp) {
			std::cout << "operator=(const my_pair<K1,K2>&)" << endl;

			first = mp.first;
			second = mp.second;
			return *this;
		}

		template<typename K1, typename K2>
		my_pair& operator=(my_pair<K1,K2>&& mp) {
			std::cout << "operator=(my_pair<K1,K2>&&)" << endl;

			first = std::move(mp.first);
			second = std::move(mp.second);
			return *this;
		}

		// swap
		template<typename K1, typename K2>
		void swap(my_pair<K1, K2>& mp) {
			std::cout << "swap(my_pair<K1,K2>&)" << endl;

			std::swap(first, mp.first);
			std::swap(second, mp.second);
		}
	};

	// ********** non-member functions **********

	// make_pair
	template<typename T1, typename T2>
	my_pair<T1, T2> make_pair(const T1& f, const T2& s) {
		std::cout << "make_pair(const T1&, const T2&)" << endl;
		return my_pair(f, s);
	}

	template<typename T1, typename T2>
	my_pair<T1, T2> make_pair(T1&& f, T2&& s) {
		std::cout << "make_pair(T1&&, T2&&)" << endl;
		return my_pair(f, s);
	}

	// operator ==
	template<typename T1, typename T2>
	bool operator==(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	// operator !=
	template<typename T1, typename T2>
	bool operator!=(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	// operator <
	template<typename T1, typename T2>
	bool operator<(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		return (lhs.first < rhs.first)
			|| ((lhs.first == rhs.first) && (lhs.second < rhs.second));
	}

	// operator >
	template<typename T1, typename T2>
	bool operator>(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		return (lhs.first > rhs.first)
			|| ((lhs.first == rhs.first) && (lhs.second > rhs.second));
	}

	// operator <=
	template<typename T1, typename T2>
	bool operator<=(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		return !(lhs > rhs);
	}

	// operator >=
	template<typename T1, typename T2>
	bool operator>=(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}

	// swap
	template<typename T1, typename T2>
	void swap(const my_pair<T1, T2>& lhs, const my_pair<T1, T2>& rhs) {
		lhs.swap(rhs);
	}
}

namespace kkli{

	//tuple_element<N,my_pair<T1,T2>>
	template<size_t N, typename T>
	class tuple_element;

	//模板偏特化
	template<typename T1, typename T2>
	class tuple_element<0, my_pair<T1, T2>> {
	public:
		typedef typename my_pair<T1, T2>::first_type type;
	};

	//模板偏特化
	template<typename T1, typename T2>
	class tuple_element<1, my_pair<T1, T2>> {
	public:
		typedef typename my_pair<T1, T2>::second_type type;
	};

	// get
	template<size_t N,typename T1,typename T2>
	typename tuple_element<N,my_pair<T1,T2>>::type& get(my_pair<T1,T2>& mp) {
		return get(mp, typename tuple_element<N, my_pair<T1, T2>>::type());
	}

	template<typename T1,typename T2>
	typename my_pair<T1, T2>::first_type& get(my_pair<T1, T2>& mp, 
		typename tuple_element<0, my_pair<T1, T2>>::type) {
		return mp.first;
	}

	template<typename T1,typename T2>
	typename my_pair<T1,T2>::second_type& get(my_pair<T1, T2>& mp, 
		typename tuple_element<1, my_pair<T1, T2>>::type) {
		return mp.second;
	}

	//OVER
}