#pragma once

#include "stdafx.h"
#include "deque.h"

//================================================================================
// queue<T> 类定义
//================================================================================

namespace kkli {

	template<typename T,typename Container=kkli::deque<T>>
	class queue {
	public:
		typedef Container	container_type;
		typedef T			value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference const_reference;

	private:
		container_type cont; //内部容器

	public:
		//constructor
		explicit queue(const container_type& c) :cont(c) {}
		explicit queue(container_type&& c = container_type()) :cont(std::move(c)) {}
		queue(const queue& rhs) :cont(rhs.cont) {}
		queue(queue&& rhs) :cont(std::move(rhs.cont)) {}

		//operator =
		queue& operator=(const queue& rhs) {
			cont = rhs.cont;
			return *this;
		}
		queue& operator=(queue&& rhs) {
			cont = std::move(rhs.cont);
			return *this;
		}

		const container_type& get_container()const { return cont; }
		reference front() { return cont.front(); }
		const_reference front()const { return cont.front(); }
		reference back() { return cont.back(); }
		const_reference back()const { return cont.back(); }
		bool empty()const { return cont.empty(); }
		size_type size()const { return cont.size(); }
		void push(const value_type& value) { cont.push_back(value); }
		void push(value_type&& value) { cont.push_back(std::move(value)); }
		void pop() { cont.pop_front(); }
		void swap(deque& rhs) {
			kkli::swap(cont, rhs.cont);
		}
	};
}

//================================================================================
// 非成员函数定义
//================================================================================

namespace kkli {

	//operator ==
	template<typename T,typename Container>
	bool operator==(const deque<T, Container>& lhs, const deque<T, Container>& rhs) {
		return lhs.get_container() == rhs.get_container();
	}

	//operator !=
	template<typename T, typename Container>
	bool operator!=(const deque<T, Container>& lhs, const deque<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T, typename Container>
	bool operator<(const deque<T, Container>& lhs, const deque<T, Container>& rhs) {
		return lhs.get_container() < rhs.get_container();
	}

	//operator >
	template<typename T, typename Container>
	bool operator>(const deque<T, Container>& lhs, const deque<T, Container>& rhs) {
		return rhs < lhs;
	}

	//operator <=
	template<typename T, typename Container>
	bool operator<=(const deque<T, Container>& lhs, const deque<T, Container>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T, typename Container>
	bool operator>=(const deque<T, Container>& lhs, const deque<T, Container>& rhs) {
		return !(lhs < rhs);
	}
}