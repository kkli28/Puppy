#pragma once

#include "stdafx.h"

//================================================================================
// set<T> 类定义
//================================================================================

namespace kkli {

	template<typename T,typename Compare>
	class set {
	private:

		//iterator: __iterator
		class __iterator {
		private:
			kkli::avl_node<T>* __ptr;
		public:
			//TODO: 如何写呢？？？
		};
	public:
		//typedefs
		typedef T					key_type;
		typedef T					value_type;
		typedef T&					reference;
		typedef const T&			const_reference;
		typedef T*					pointer;
		typedef const T*			const_pointer;
		typedef __iterator			iterator;
		typedef __iterator			const_iterator;
		typedef kkli::avl_node<T>	node_type;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;

	private:
		kkli::avl_tree<T> __tree;

		set(Compare comp=std::equal<T>());
		
		template<typename InputIterator>
		set(InputIterator first, InputIerator last,const Compare& comp=std::equal<T>());
		set(const set& rhs);
		set(set&& rhs);
		set(std::initializer_list<value_type> init, const Compare& comp = std::equal<T>());
	};
}

//================================================================================
// set<T> 成员函数定义
//================================================================================

namespace kkli {
	//TODO: 
}