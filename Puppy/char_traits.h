#pragma once

#include "stdafx.h"

//================================================================================
// char_traits<T> 类定义
//================================================================================

namespace kkli {

	template<typename CharType>
	class char_traits {};

	// CharType = char 的偏特化
	template<>
	class char_traits<char> {
	public:
		//typedefs
		typedef char			char_type;
		typedef int				int_type;
		typedef std::streamoff	off_type;
		typedef std::streampos	pos_type;
		typedef std::mbstate_t	state_type;

		//eof
		static constexpr int_type eof() { return 0; }

		//not_eof
		static int_type not_eof(int_type e) {
			if (e == char_traits<char>::eof()) return e + 1;
			return e;
		}

		//assign
		static constexpr void assign(char_type& r, const char_type& a) {
			r = a;
		}
		static char_type* assign(char_type* p, std::size_t count, char_type a) {
			for (std::size_t i = 0; i < count; ++i)
				p[i] = a;
			return p;
		}

		//eq
		static bool eq(char_type a, char_type b) {
			return a == b;
		}

		//lt
		static bool lt(char_type a, char_type b) {
			return a < b;
		}

		//length
		static std::size_t length(const char_type* s) {
			if (s == NULL) return 0;
			for (std::size_t i = 0;; ++i)
				if (s[i] == char_traits<char>::eof()) return i;
		}

		//move
		static char_type* move(char_type* dest, const char_type* src, std::size_t count) {
			for (std::size_t i = 0; i < count; ++i)
				dest[i] = src[i];
			return dest;
		}

		//copy
		static char_type* copy(char_type* dest, const char_type* src, std::size_t count) {
			for (std::size_t i = 0; i < count; ++i)
				dest[i] = src[i];
			return dest;
		}

		//compare
		static int compare(const char_type* s1, const char_type* s2, std::size_t count) {
			for (std::size_t i = 0; i < count; ++i) {
				if (s1[i] == char_traits<char>::eof() && s2[i] == char_traits<char>::eof()) return 0;
				if (s1[i] == char_traits<char>::eof()) return -1;
				if (s2[i] == char_traits<char>::eof()) return 1;
				if (s1[i] < s2[i]) return -1;
				if (s1[i] > s2[i]) return 1;
			}
			return 0;
		}

		//find
		static const char_type* find(const char_type* p, std::size_t count, const char_type& ch) {
			std::size_t i = 0;
			for (; i < count; ++i) {
				if (p[i] == char_traits<char>::eof()) return NULL;
				if (p[i] == ch) return &p[i];
			}
			return NULL;
		}

		//to_char_type
		static char_type to_char_type(int_type c) { return c; }

		//to_int_type
		static int_type to_int_type(char_type c) { return c; }

		//eq_int_type
		static bool eq_int_type(int_type c1, int_type c2) {
			return c1 == c2;
		}
	};

	// CharType = wchar_t  的偏特化
	// CharType = char16_t 的偏特化
	// CharType = char32_t 的偏特化
}