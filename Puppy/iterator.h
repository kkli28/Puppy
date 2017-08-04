#pragma once

#include "stdafx.h"

//================================================================================
// iterator 类定义
//================================================================================

namespace kkli {
	template<typename Category, typename T, typename Distance = std::ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
		class iterator;
}

//================================================================================
// iterator_tags 类定义
//================================================================================

namespace kkli {
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag :public input_iterator_tag, public output_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};
}

//================================================================================
// reverse_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename Iterator>
	class reverse_iterator {

	public:
		//typedefs
		typedef typename kkli::iterator_traits<Iterator>::value_type
			value_type;
		typedef typename kkli::iterator_traits<Iterator>::reference
			reference;
		typedef typename kkli::iterator_traits<Iterator>::pointer
			pointer;
		typedef typename kkli::iterator_traits<Iterator>::difference_type
			difference_type;
		typedef typename kkli::iterator_traits<Iterator>::iterator_category
			iterator_category;

	public:
		typedef Iterator	iterator_type;

	private:
		Iterator current;

	public:
		//constructor
		reverse_iterator();
		explicit reverse_iterator(iterator_type it) :current(it) {}

		template<typename U>
		reverse_iterator(const reverse_iterator<U>& rhs) : current(rhs.current) {}

		//operator =
		template<typename U>
		reverse_iterator& operator=(const reverse_iterator<U>& rhs) {
			current = rhs.current;
		}

		//base
		Iterator base() const { return current; }

		//operator *
		reference operator*()const {
			Iterator temp = current;
			return *(--temp);
		}

		//operator ->
		pointer operator->()const {
			return &(operator*());
		}

		//operator ++
		reverse_iterator& operator++() {
			--current;
			return *this;
		}

		//operator ++(int)
		reverse_iterator operator++(int) {
			reverse_iterator temp = current;
			--current;
			return temp;
		}

		//operator +=
		reverse_iterator& operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		
		//operator +
		reverse_iterator operator+(difference_type n) {
			return reverse_iterator(current - n);
		}

		//operator --
		reverse_iterator& operator--() {
			++current;
			return *this;
		}

		//operator --(int)
		reverse_iterator operator--(int) {
			reverse_iterator temp = current;
			++current;
			return temp;
		}

		//operator -=
		reverse_iterator& operator-=(difference_type n) {
			current += n;
			return *this;
		}

		//operator -
		reverse_iterator operator-(difference_type n) {
			return reverse_iterator(current + n);
		}

		//operator []
		reference operator[](difference_type n) {
			reverse_iterator temp = *this + n;
			return *temp;
		}
	};

	//non-member functions

	//operator ==
	template<typename Iterator1, typename Iterator2>
	inline bool operator==(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}
	
	//operator !=
	template<typename Iterator1, typename Iterator2>
	inline bool operator!=(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename Iterator1, typename Iterator2>
	inline bool operator<(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	//operator >
	template<typename Iterator1, typename Iterator2>
	inline bool operator>(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	//operator <=
	template<typename Iterator1, typename Iterator2>
	inline bool operator<=(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return !(lhs < rhs);
	}

	//operator +
	template<typename Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rhs) {
		return reverse_iterator<Iterator>(rhs.base() - n);
	}

	//operator -
	template<typename Iterator1, typename Iterator2>
	auto operator-(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) -> decltype(lhs.base()-rhs.base()) {
		return lhs.base() - rhs.base();
	}
}