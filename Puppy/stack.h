#pragma once

#include "stdafx.h"
#include "deque.h"

//================================================================================
// stack<T> 类定义
//================================================================================

namespace kkli {

	template<typename T,typename Container=kkli::deque<T>>
	class stack {
	public:
		typedef Container	container_type;
		typedef T			value_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::size_type		size_type;

	private:
		container_type cont; //内部容器

	public: 
		//constructor
		explicit stack(const container_type& c) :cont(c) {}
		explicit stack(container_type&& c = container_type()) :cont(c) { }
		stack(stack&& rhs) :cont(std::move(rhs.cont)) {}

		//operator =
		stack& operator=(const stack& rhs) {
			cont = rhs.cont;
			return *this;
		}
		stack& operator=(stack&& rhs) {
			cont = std::move(rhs.cont);
			return *this;
		}

		const container_type& get_container()const { return cont; }
		reference top() { return cont.back(); }
		const_reference top()const { return cont.back(); }
		bool empty()const { return cont.empty(); }
		size_type size()const { return cont.size(); }
		void push(const value_type& value) { cont.push_back(value); }
		void push(value_type&& value) { cont.push_back(std::move(value)); }
		void pop() { cont.pop_back(); }
		void swap(stack& rhs) {
			kkli::swap(cont, rhs.cont);
		}
	};
}

//================================================================================
// 非成员函数定义
//================================================================================

namespace kkli {

	//operator ==
	template<typename T, typename Container>
	bool operator==( stack<T, Container>& lhs,  stack<T, Container>& rhs) {
		return lhs.get_container() == rhs.get_container();
	}
	
	//operator !=
	template<typename T, typename Container>
	bool operator!=( stack<T, Container>& lhs,  stack<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename T, typename Container>
	bool operator<( stack<T, Container>& lhs,  stack<T, Container>& rhs) {
		return lhs.get_container() < rhs.get_container();
	}

	//operator >
	template<typename T, typename Container>
	bool operator>( stack<T, Container>& lhs,  stack<T, Container>& rhs) {
		return rhs < lhs;
	}

	//operator <=
	template<typename T, typename Container>
	bool operator<=( stack<T, Container>& lhs,  stack<T, Container>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename T, typename Container>
	bool operator>=( stack<T, Container>& lhs,  stack<T, Container>& rhs) {
		return !(lhs < rhs);
	}

	//swap
	template<typename T, typename Container>
	void swap(stack<T,Container>& lhs, stack<T, Container>& rhs) {
		return lhs.swap(rhs);
	}
}
