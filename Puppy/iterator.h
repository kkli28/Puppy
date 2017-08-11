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
	class bidirectional_iterator_tag :public forward_iterator_tag {};
	class random_access_iterator_tag :public bidirectional_iterator_tag {};
}

//================================================================================
// iterator_traits<T> 类定义
//================================================================================

namespace kkli {
	template<typename Iterator>
	class iterator_traits {
	public:
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
		typedef T				value_type;
		typedef const T&		reference;
		typedef const T*		pointer;
		typedef std::ptrdiff_t	difference_type;
		typedef typename kkli::random_access_iterator_tag	iterator_category;
	};
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

		typedef Iterator iterator_type;

	private:
		Iterator current;

	public:
		//constructor
		reverse_iterator() {}
		explicit reverse_iterator(Iterator curr) :current(curr) {}

		template<typename U>
		reverse_iterator(const reverse_iterator<U>& rhs) : current(rhs.current) {}

		//base
		Iterator base()const { return current; }

		//operator =
		template<typename U>
		reverse_iterator& operator=(const reverse_iterator<U>& rhs) {
			current = rhs.current;
			return *this;
		}

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
			reverse_iterator temp(current);
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
			reverse_iterator temp(current);
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
	inline bool operator>=(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return !(lhs < rhs);
	}

	//operator +
	template<typename Iterator>
	inline  reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rhs) {
		return reverse_iterator(rhs.base() - n);
	}

	//operator -
	template<typename Iterator1, typename Iterator2>
	inline auto operator>=(const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) -> decltype(lhs.base()-rhs.base()) {
		return lhs.base() - rhs.base();
	}
}

//================================================================================
// move_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename Iterator>
	class move_iterator {
	public:
		//typedefs
		typedef typename kkli::iterator_traits<Iterator>::value_type
			value_type;
		typedef typename kkli::iterator_traits<Iterator>::iterator_category
			terator_category;
		typedef typename kkli::iterator_traits<Iterator>::difference_type
			difference_type;
		typedef Iterator			iterator_type;
		typedef Iterator			pointer;
		typedef value_type&&		reference;

	private:
		Iterator current;

	public:
		//constructor
		move_iterator() :current(Iterator()) {}
		explicit move_iterator(Iterator x) :current(x) {}
		
		template<typename U>
		move_iterator(const move_iterator<U>& rhs) 
			: current(rhs.current) {}

		//operator =
		template<typename U>
		move_iterator& operator=(const move_iterator<U>& rhs) {
			current = rhs.current;
			return *this;
		}

		//base
		Iterator base()const { return current; }

		//operator *
		reference operator*() {
			return std::move(*current);
		}

		//operator ->
		pointer operator->() {
			return current;
		}

		//operator []
		value_type operator[](difference_type n)const {
			return std::move(*(current + n));
		}

		//operator ++ / ++(int) / -- / --(int)
		move_iterator& operator++() { ++current; return *this; }
		move_iterator operator++(int) { 
			auto iter = *this;
			++current;
			return iter;
		}
		move_iterator& operator--() { --current; return *this; }
		move_iterator operator--(int) { 
			auto iter = *this;
			--current;
			return iter; 
		}

		//operator + / += / - / -=
		move_iterator operator+(difference_type n)const {
			return move_iterator(base() + n);
		}
		move_iterator operator-(difference_type n)const {
			return move_iterator(base() - n);
		}
		move_iterator& operator+=(difference_type n)const {
			current += n;
			return *this;
		}
		move_iterator& operator-=(difference_type n)const {
			current -= n;
			return *this;
		}
	};

	//operator <
	template<typename Iterator1,typename Iterator2>
	bool operator==(const move_iterator<Iterator1>& lhs,
		const move_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	//operator !=
	template<typename Iterator1, typename Iterator2>
	bool operator!=(const move_iterator<Iterator1>& lhs,
		const move_iterator<Iterator2>& rhs) {
		return !(lhs == rhs);
	}

	//operator <
	template<typename Iterator1, typename Iterator2>
	bool operator<(const move_iterator<Iterator1>& lhs,
		const move_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	//operator >
	template<typename Iterator1, typename Iterator2>
	bool operator>(const move_iterator<Iterator1>& lhs,
		const move_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	//operator <=
	template<typename Iterator1, typename Iterator2>
	bool operator<=(const move_iterator<Iterator1>& lhs,
		const move_iterator<Iterator2>& rhs) {
		return !(lhs > rhs);
	}

	//operator >=
	template<typename Iterator1, typename Iterator2>
	bool operator>=(const move_iterator<Iterator1>& lhs,
		const move_iterator<Iterator2>& rhs) {
		return !(lhs < rhs);
	}

	//operator +
	template<typename Iterator>
	move_iterator<Iterator> operator+(
		typename move_iterator<Iterator>::difference_type n,
		const move_iterator<Iterator>& iter) {
		return iter + n;
	}

	//operator -
	template<typename Iterator1,typename Iterator2>
	auto operator-( const move_iterator<Iterator1>& lhs, 
		const move_iterator<Iterator2>& iter) ->decltype(lhs.base() - rhs.base()) {
		return lhs.base() - rhs.base();
	}
}

//================================================================================
// back_insert_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename Container>
	class back_insert_iterator {
	public:
		//typedefs
		typedef	void			value_type;
		typedef void			reference;
		typedef void			pointer;
		typedef void			difference_type;
		typedef kkli::output_iterator_tag	iterator_category;

		typedef Container		container_type;
	private:
		Container* container;

	public:
		//constructor
		explicit back_insert_iterator(Container& cont) :container(&cont) {}

		//operator =(value)
		back_insert_iterator& operator=(const typename Container::value_type& value) {
			container->push_back(value);
			return *this;
		}

		//operator =(&&value)
		back_insert_iterator& operator=(typename Container::value_type&& value) {
			container->push_back(std::move(value));
			return *this;
		}

		//operator *
		back_insert_iterator& operator*() { return *this; }

		//operator ++
		back_insert_iterator& operator++() { return *this; }

		//operator ++(int)
		back_insert_iterator& operator++(int) { return *this; }
	};
}

//================================================================================
// front_insert_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename Container>
	class front_insert_iterator {
	public:
		//typedefs
		typedef void			value_type;
		typedef void			reference;
		typedef void			pointer;
		typedef void			difference_type;
		typedef kkli::output_iterator_tag	iterator_category;

		typedef Container		container_type;

	private:
		Container* container;

	public:
		//constructor
		explicit front_insert_iterator(Container& cont) :container(&cont) {}

		//operator =(value)
		front_insert_iterator& operator=(const typename Container::value_type& value) {
			container->push_front(value);
			return *this;
		}

		//operatpr =(&&value)
		front_insert_iterator& operator=(typename Container::value_type&& value) {
			container->push_front(std::move(value));
			return *this;
		}

		//operator *
		front_insert_iterator& operator*() { return *this; }
		
		//operator ++
		front_insert_iterator& operator++() { return *this; }

		//operator ++(int)
		front_insert_iterator& operator++(int) { return *this; }
	};
}

//================================================================================
// insert_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename Container>
	class insert_iterator {
	public:
		//typedefs
		typedef void			value_type;
		typedef void			reference;
		typedef void			pointer;
		typedef void			difference_type;
		typedef kkli::output_iterator_tag		iterator_category;

		typedef Container		container_type;

	private:
		Container* container;
		typename Container::iterator iter;

	public:
		//constructor
		insert_iterator(Container& cont, typename Container::iterator it)
			:container(&cont), iter(it) {}

		//operator =(value)
		insert_iterator& operator=(const typename Container::value_type& value) {
			iter = container->insert(iter, value);
			++iter;
			return *this;
		}

		//operator =(&&value)
		insert_iterator& operator=(typename Container::value_type&& value) {
			iter = container->insert(iter, std::move(value));
			++iter;
			return *this;
		}

		//operator *
		insert_iterator<Container>& operator*() { return *this; }

		//operator ++
		insert_iterator<Container>& operator++() { return *this; }

		//operator ++(int)
		insert_iterator<Container>& operator++(int) { return *this; }
	};
}

//================================================================================
// istream_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename T, typename Distance = std::ptrdiff_t>
	class istream_iterator {
	public:
		//typedefs
		typedef T				value_type;
		typedef const T&		reference;
		typedef const T*		pointer;
		typedef Distance		difference_type;
		typedef kkli::input_iterator_tag	iterator_category;

	private:
		std::istream* stream;
		value_type value;

		void read() {
			if (*stream) {
				*stream >> value;
			}
			if ((*stream).fail()) {
				(*stream).clear();
				(*stream).ignore(std::numeric_limits<std::streampos>::max());
				stream = nullptr;
			}
		}

	public:
		//constructor
		istream_iterator() :stream(nullptr) {}
		istream_iterator(std::istream& is) :stream(&is) {
			read();
		}
		istream_iterator(const istream_iterator& rhs) {
			stream = rhs.stream;
			value = rhs.value;
		}

		//operator *
		reference operator*()const {
			return value; 
		}

		//operator ->
		pointer operator->()const {
			return &value; 
		}

		//operator ++
		istream_iterator& operator++() {
			read();
			return *this;
		}

		//operator ++(int)
		istream_iterator& operator++(int) {
			istream_iterator temp(*this);
			read();
			return temp;
		}

		//operator ==
		bool operator==(const istream_iterator<T, Distance>& rhs) {
			return stream == rhs.stream;
		}

		//opertor !=
		bool operator!=(const istream_iterator<T, Distance>& rhs) {
			return stream != rhs.stream;
		}
	};
}

//================================================================================
// ostream_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename T>
	class ostream_iterator {
	public:
		//typedefs
		typedef void			value_type;
		typedef void			reference;
		typedef void			pointer;
		typedef void			difference_type;
		typedef kkli::output_iterator_tag	iterator_category;

	private:
		std::ostream* stream;
		const char* str;

	public:
		//constructor
		ostream_iterator(std::ostream& os) :stream(&os) {}
		ostream_iterator(std::ostream& os, const char* c) :stream(&os), str(c) {}

		//operator =
		ostream_iterator& operator=(const T& value) {
			*stream << value;
			if (str) *stream << str;
			return *this;
		}

		//operator *
		ostream_iterator& operator*() { return *this; }

		//operator ++
		ostream_iterator& operator++() { return *this; }

		//operator ++(int)
		ostream_iterator& operator++(int) { return *this; }
	};
}

//================================================================================
// 工具函数定义
//================================================================================

namespace kkli {

	//make_reverse_iterator
	template<typename Iterator>
	inline kkli::reverse_iterator<Iterator> make_reverse_iterator(Iterator iter) {
		return kkli::reverse_iterator<Iterator>(iter);
	}

	//make_move_iterator
	template<typename Iterator>
	inline kkli::move_iterator<Iterator> make_move_iterator(Iterator iter) {
		return kkli::move_iterator<Iterator>(iter);
	}

	//front_inserter
	template<typename Container>
	inline kkli::front_insert_iterator<Container> front_inserter(Container& cont) {
		return kkli::front_insert_iterator<Container>(cont);
	}

	//back_inserter
	template<typename Container>
	inline kkli::back_insert_iterator<Container> back_inserter(Container& cont) {
		return kkli::back_insert_iterator<Container>(cont);
	}

	//inserter
	template<typename Container>
	inline kkli::insert_iterator<Container> inserter(Container& cont,
		typename Container::iterator it) {
		return kkli::insert_iterator<Container>(cont, it);
	}

	//advance
	template<typename InputIt, typename Distance>
	void __advance(InputIt& iter, Distance n, kkli::input_iterator_tag) {
		for (; n > 0; --n, ++iter);
	}
	template<typename BidirectIt, typename Distance>
	void __advance(BidirectIt& iter, Distance n, kkli::bidirectional_iterator_tag) {
		if (n > 0) for (; n > 0; --n, ++iter);
		else for (; n < 0; ++n, --iter);
	}
	template<typename RandomAccessIt, typename Distance>
	void __advance(RandomAccessIt& iter, Distance n, kkli::random_access_iterator_tag) {
		iter += n;
	}
	template<typename InputIt, typename Distance>
	void advance(InputIt& iter, Distance n) {
		__advance(iter, n, typename iterator_traits<InputIt>::iterator_category());
	}

	//distance
	template<typename InputIt>
	typename kkli::iterator_traits<InputIt>::difference_type
		__distance(InputIt first, InputIt last, kkli::input_iterator_tag) {
		typename kkli::iterator_traits<InputIt>::difference_type diff = 0;
		for (; first != last; ++first, ++diff);
		return diff;
	}
	template<typename RandomAccessIt>
	typename kkli::iterator_traits<RandomAccessIt>::difference_type
		__distance(RandomAccessIt first, RandomAccessIt last,
			kkli::random_access_iterator_tag) {
		return last - first;
	}
	template<typename InputIt>
	typename kkli::iterator_traits<InputIt>::difference_type
		distance(InputIt first, InputIt last) {
		return __distance(first, last,
			typename kkli::iterator_traits<InputIt>::iterator_category());
	}

	//next
	template<typename InputIt>
	InputIt next(InputIt iter,
		typename kkli::iterator_traits<InputIt>::difference_type n = 1) {
		advance(iter, n);
		return iter;
	}

	//prev
	template<typename BidirectIt>
	BidirectIt prev(BidirectIt iter,
		typename kkli::iterator_traits<BidirectIt>::difference_type n = 1) {
		kkli::advance(iter, -n);
		return iter;
	}

	//begin
	template<typename C>
	auto begin(C& c)->decltype(c.begin()) {
		return c.begin();
	}
	template<typename T, std::size_t N>
	T* begin(T(&a)[N]) {
		return a;
	}

	//cbegin
	template<typename C>
	auto cbegin(const C& c)->decltype(c.cbegin()) {
		return c.cbegin();
	}
	template<typename T,std::size_t N>
	const T* cbegin(const T(&a)[N]) {
		return a;
	}

	//rbegin
	template<typename C>
	auto rbegin(C& c)->decltype(c.rbegin()) {
		return c.rbegin();
	}
	template<typename T, std::size_t N>
	kkli::reverse_iterator<T*> rbegin(T(&a)[N]) {
		return kkli::reverse_iterator<T*>(a + N);
	}

	//crbegin
	template<typename C>
	auto crbegin(const C& c)->decltype(c.crbegin()) {
		return c.crbegin();
	}
	template<typename T, std::size_t N>
	kkli::reverse_iterator<const T*> crbegin(const T(&a)[N]) {
		return kkli::reverse_iterator<const T*>(a + N);
	}

	//end
	template<typename C>
	auto end(C& c)->decltype(c.end()) {
		return c.end();
	}
	template<typename T, std::size_t N>
	T* end(T(&a)[N]) {
		return a + N;
	}

	//cend
	template<typename C>
	auto cend(const C& c)->decltype(c.cend()) {
		return c.cend();
	}
	template<typename T, std::size_t N>
	const T* cend(const T(&a)[N]) {
		return a + N;
	}

	//rend
	template<typename C>
	auto rend(C& c)->decltype(c.rend()) {
		return c.rend();
	}
	template<typename T, std::size_t N>
	kkli::reverse_iterator<T*> rend(T(&a)[N]) {
		return kkli::reverse_iterator<T*>(a);
	}

	//crend
	template<typename C>
	auto crend(const C& c)->decltype(c.crend()) {
		return c.crend();
	}
	template<typename T, std::size_t N>
	kkli::reverse_iterator<const T*> crend(const T(&a)[N]) {
		return kkli::reverse_iterator<const T*>(a);
	}
}
