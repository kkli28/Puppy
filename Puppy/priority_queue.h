#pragma once

#include "stdafx.h"
#include "functional.h"
#include "algorithm.h"
#include "vector.h"

//================================================================================
// priority_queue<T> 类定义
//================================================================================

namespace kkli {

	template<typename T,
		typename Container=kkli::vector<T>,
		class Compare=kkli::less<typename Container::value_type>>
		class priority_queue {
		public:
			typedef Container	container_type;
			typedef Compare		value_compare;
			typedef typename Container::value_type		value_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::size_type		size_type;

		private:
			container_type cont;
			value_compare comp;

		public:
			//constructor
			priority_queue() :cont(), comp() {}
			explicit priority_queue(const value_compare& cmp, const container_type& c) :cont(c), comp(cmp) {
				kkli::make_heap(cont.begin(), cont.end(), comp);
			}
			explicit priority_queue(const value_compare& cmp) :cont(), comp(cmp) {}
			explicit priority_queue(const container_type& c) :cont(c), comp() {
				kkli::make_heap(cont.begin(), cont.end());
			}
			priority_queue(const priority_queue& rhs) :cont(rhs.cont), comp(rhs.comp) {}
			priority_queue(priority_queue&& rhs) :cont(std::move(rhs.cont)), comp(std::move(rhs.comp)) {}

			//operator =
			priority_queue& operator=(const priority_queue& rhs) {
				cont = rhs.cont;
				comp = rhs.comp;
				return *this;
			}
			priority_queue& operator=(priority_queue&& rhs) {
				cont = std::move(rhs.cont);
				comp = std::move(rhs.comp);
				return *this;
			}

			const container_type& get_container()const { return cont; }
			value_compare get_compare()const { return comp; }
			const_reference top()const { return cont.front(); }
			bool empty()const { return cont.empty(); }
			size_type size()const { return cont.size(); }
			void push(const value_type& value) {
				cont.push_back(value);
				kkli::make_heap(cont.begin(), cont.end(), comp); //建立堆
			}
			void push(value_type&& value) {
				cont.push_back(std::move(value));
				kkli::make_heap(cont.begin(), cont.end(), comp); //建立堆
			}
			void pop() {
				kkli::pop_heap(cont.begin(), cont.end(), comp); //去掉堆顶元素
				cont.pop_back();
			}
			void swap(priority_queue& rhs) {
				kkli::swap(cont, rhs.cont);
			}
	};

	//swap
	template<typename T,typename Container,typename Compare>
	void swap(priority_queue<T, Container, Compare>& lhs, priority_queue<T, Container, Compare>& rhs) {
		return lhs.swap(rhs);
	}
}
