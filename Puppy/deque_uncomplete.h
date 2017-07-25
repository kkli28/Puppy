#pragma once

#include "stdafx.h"

//================================================================================
// deque<T> 类定义
//================================================================================
namespace kkli {

	template<typename T,typename Allocator=std::allocator<T>>
	class deque {
	public:
		//typedefs
		typedef	T							value_type;
		typedef Allocator					allocator_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type*					iterator;
		typedef const value_type*			const_iterator;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::random_access_iterator_tag			iterator_category;

		//TODO: 内部实现还没有搞定，研究会儿《STL源码剖析》再写
	};
}