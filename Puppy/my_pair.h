#pragma once

#pragma once

#include "stdafx.h"
#include "tuple_element.h"

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
			cout << "my_pair()" << endl;
		}

		template<typename K1, typename K2>
		my_pair(const K1& f, const K2& s) :first(f), second(s) {
			cout << "my_pair(const K1&, const K2&)" << endl;
		}

		template<typename K1, typename K2>
		my_pair(K1&& f, K2&& s) : first(std::move(f)), second(std::move(s)) {
			cout << "my_pair(K1&&, K2&&)" << endl;
		}

		template<typename K1, typename K2>
		my_pair(const my_pair<K1, K2>& mp) : first(mp.first), second(mp.second) {
			cout << "my_pair(const my_pair<K1, K2>&)" << endl;
		}

		template<typename K1, typename K2>
		my_pair(my_pair<K1, K2>&& mp) : first(std::move(mp.first)), second(std::move(mp.second)) {
			cout << "my_pair(my_pair<K1, K2>&&)" << endl;
		}

		// operator =
		template<typename K1, typename K2>
		my_pair& operator=(const my_pair<K1, K2>& mp) {
			first = mp.first;
			second = mp.second;
			return *this;
		}

		template<typename K1, typename K2>
		my_pair& operator=(my_pair&& mp) {
			first = std::move(mp.first);
			second = std::move(mp.second);
			return *this;
		}

		// swap
		template<typename K1, typename K2>
		void swap(my_pair<K1, K2>& mp) {
			std::swap(first, mp.first);
			std::swap(second, mp.second);
		}
	};

	// ********** non-member functions **********

	// make_pair
	template<typename T1, typename T2>
	my_pair<T1, T2> make_pair(const T1& f, const T2& s) {
		return my_pair(f, s);
	}

	template<typename T1, typename T2>
	my_pair<T1, T2> make_pair(T1&& f, T2&& s) {
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
	template<size_t N, typename T1, typename T2>
	class tuple_element {};

	//ģ��ƫ�ػ�
	template<typename T1, typename T2>
	class tuple_element<0, my_pair<T1, T2>> {
	public:
		typedef typename my_pair<T1, T2>::first_type type;
	};

	//ģ��ƫ�ػ�
	template<typename T1, typename T2>
	class tuple_element<1, my_pair<T1, T2>> {
	public:
		typedef typename my_pair<T1, T2>::second_type type;
	};

	// get
	template<size_t N,typename T1,typename T2>
	typename tuple_element<N,my_pair<T1,T2>>::type& get(const my_pair<T1,T2>& mp) {
		return get(mp, typename tuple_element<N, my_pair<T1, T2>>::type());
	}

	template<size_t N,typename T1,typename T2>
	typename my_pair<T1,T2>::first_type& get(const my_pair<T1, T2>& mp,typename tuple_element<0,my_pair<T1,T2>>::type()) {
		return first;
	}

	template<size_t N,typename T1,typename T2>
	typename my_pair<T1,T2>::second_type& get<1>(const my_pair<T1, T2>& mp, typename tuple_element<1, my_pair<T1, T2>>::type()) {
		return second;
	}

	//OVER
}