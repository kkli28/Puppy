#pragma once

#include "stdafx.h"

//================================================================================
// iterator_traits<T> ¿‡∂®“Â
//================================================================================

namespace kkli {

	//defined in iterator.h
	class random_access_iterator_tag;

	//iterator_traits<Iterator>
	template<typename Iterator>
	class iterator_traits {
	public:
		//typedefs
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	//iterator_traits<T*>
	template<typename T>
	class iterator_traits<T*> {
	public:
		//typedefs
		typedef T				value_type;
		typedef T&				reference;
		typedef T*				pointer;
		typedef std::ptrdiff_t	difference_type;
		typedef typename kkli::random_access_iterator_tag	iterator_category;
	};

	//iterator_traits<const T*>
	template<typename T>
	class iterator_traits<const T*> {
	public:
		//typedefs
		typedef T				value_type;
		typedef const T&		reference;
		typedef const T*		pointer;
		typedef std::ptrdiff_t	difference_type;
		typedef typename kkli::random_access_iterator_tag	iterator_category;
	};
}
