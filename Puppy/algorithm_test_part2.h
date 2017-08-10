#pragma once

#include "stdafx.h"
#include "test.h"
#include "algorithm.h"
#include "string.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;
		using kkli::string;

		//«∞÷√…˘√˜

		//part2: modifying sequence operations
		void test_copy();
		void test_copy_if();
		void test_copy_n();
		void test_copy_backward();
		void test_move();
		void test_move_backward();
		void test_fill();
		void test_fill_n();
		void test_transform();
		void test_generate();
		void test_generate_n();
		void test_remove();
		void test_remove_if();
		void test_remove_copy();
		void test_remove_copy_if();
		void test_replace();
		void test_replace_if();
		void test_replace_copy();
		void test_replace_copy_if();
		void test_swap();
		void test_swap_ranges();
		void test_iter_swap();
		void test_reverse();
		void test_reverse_copy();
		void test_rotate();
		void test_rotate_copy();
		void test_unique();
		void test_unique_copy();

		//≤‚ ‘ part2
		void test_part2() {
			test_copy();
			test_copy_if();
			test_copy_n();
			test_copy_backward();
			test_move();
			test_move_backward();
			test_fill();
			test_fill_n();
			test_transform();
			test_generate();
			test_generate_n();
			test_remove();
			test_remove_if();
			test_remove_copy();
			test_remove_copy_if();
			test_replace();
			test_replace_if();
			test_replace_copy();
			test_replace_copy_if();
			test_swap();
			test_swap_ranges();
			test_iter_swap();
			test_reverse();
			test_reverse_copy();
			test_rotate();
			test_rotate_copy();
			test_unique();
			test_unique_copy();
		}

		//≤‚ ‘ copy
		void test_copy() {
			cout << "test: copy()" << endl;

			string str1;
			string str2("abcd");
			string str3("aaaa");
			string str4("aaaaaa");
			auto iter1 = kkli::copy(str1.begin(), str1.end(), str2.begin());
			auto iter2 = kkli::copy(str2.begin(), str2.end(), str3.begin());
			auto iter3 = kkli::copy(str2.begin(), str2.end(), str4.begin());
			EXPECT_EQ_VAL(str2, "abcd");
			EXPECT_EQ_VAL(str3, "abcd");
			EXPECT_EQ_VAL(str4, "abcdaa");
			EXPECT_EQ_VAL(iter1, str2.begin());
			EXPECT_EQ_VAL(iter2, str3.end());
			EXPECT_EQ_VAL(iter3, str4.begin() + 4);
		}

		//≤‚ ‘ copy_if
		void test_copy_if() {
			cout << "test: copy_if()" << endl;

			string str1;
			string str2("abab");
			string str3("aaaa");
			auto lmd1 = [](char val)->bool {return val == 'b'; };
			auto iter1 = kkli::copy_if(str1.begin(), str1.end(), str2.begin(), lmd1);
			auto iter2 = kkli::copy_if(str2.begin(), str2.end(), str3.begin(), lmd1);
			EXPECT_EQ_VAL(str2, "abab");
			EXPECT_EQ_VAL(str3, "bbaa");
			EXPECT_EQ_VAL(iter1, str2.begin());
			EXPECT_EQ_VAL(iter2, str3.begin() + 2);
		}

		//≤‚ ‘ copy_n
		void test_copy_n() {
			cout << "test: copy_n()" << endl;

			string str1;
			string str2("abcd");
			string str3("aaaa");
			auto iter1 = kkli::copy_n(str1.begin(), 0, str2.begin());
			auto iter2 = kkli::copy_n(str2.begin(), 2, str3.begin());
			EXPECT_EQ_VAL(str2, "abcd");
			EXPECT_EQ_VAL(str3, "abaa");
			EXPECT_EQ_VAL(iter1, str2.begin());
			EXPECT_EQ_VAL(iter2, str3.begin() + 2);

			iter1 = kkli::copy_n(str2.begin(), 4, str3.begin());
			EXPECT_EQ_VAL(str3, "abcd");
			EXPECT_EQ_VAL(iter1, str3.end());
		}

		//≤‚ ‘ copy_backward
		void test_copy_backward() {
			cout << "test: copy_backward()" << endl;

			string str1;
			string str2("abcd");
			string str3("aaaa");
			auto iter1 = kkli::copy_backward(str1.begin(),str1.end(), str2.end());
			auto iter2 = kkli::copy_backward(str2.begin(), str2.end(), str3.end());
			EXPECT_EQ_VAL(str2, "abcd");
			EXPECT_EQ_VAL(str3, "abcd");
			EXPECT_EQ_VAL(iter1, str2.end());
			EXPECT_EQ_VAL(iter2, str3.begin());
		}

		//≤‚ ‘ move
		void test_move() {
			cout << "test: move()" << endl;

			string str1;
			string str2("abcd");
			string str3("aaaa");
			auto iter1 = kkli::move(str1.begin(), str1.end(), str2.begin());
			auto iter2 = kkli::move(str2.begin(), str2.end(), str3.begin());
			EXPECT_EQ_VAL(str2, "abcd");
			EXPECT_EQ_VAL(str3, "abcd");
			EXPECT_EQ_VAL(iter1, str2.begin());
			EXPECT_EQ_VAL(iter2, str3.end());
		}

		//≤‚ ‘ move_backward
		void test_move_backward() {
			cout << "test: move_backward()" << endl;

			string str1;
			string str2("abcd");
			string str3("aaaaaa");
			auto iter1 = kkli::move_backward(str1.begin(), str1.end(), str2.end());
			auto iter2 = kkli::move_backward(str2.begin(), str2.end(), str3.end());
			EXPECT_EQ_VAL(str2, "abcd");
			EXPECT_EQ_VAL(str3, "aaabcd");
			EXPECT_EQ_VAL(iter1, str2.end());
			EXPECT_EQ_VAL(iter2, str3.begin() + 2);
		}

		//≤‚ ‘ fill
		void test_fill() {
			cout << "test: fill()" << endl;

			string str1;
			string str2("abcd");
			kkli::fill(str1.begin(), str1.end(), 'a');
			kkli::fill(str2.begin(), str2.end(), 'b');
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "bbbb");
		}

		//≤‚ ‘ fill_n
		void test_fill_n() {
			cout << "test: fill_n()" << endl;

			string str1("ab");
			string str2("abcd");
			string str3("abcd");
			kkli::fill_n(str1.begin(), 0, 'a');
			kkli::fill_n(str2.begin(), 2, 'c');
			kkli::fill_n(str3.begin(), 4, 'z');
			EXPECT_EQ_VAL(str1, "ab");
			EXPECT_EQ_VAL(str2, "cccd");
			EXPECT_EQ_VAL(str3, "zzzz");
		}

		//≤‚ ‘ transform
		void test_transform() {
			cout << "test: transform()" << endl;

			string str1;
			string str2("abcd");
			auto lmd1 = [](char c)->char { return c + 2; };
			auto iter1 = kkli::transform(str1.begin(), str1.end(), str1.begin(), lmd1);
			auto iter2 = kkli::transform(str2.begin(), str2.end(), str2.begin(), lmd1);
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "cdef");
			EXPECT_EQ_VAL(iter1, str1.begin());
			EXPECT_EQ_VAL(iter2, str2.end());
		}

		//≤‚ ‘ generate
		void test_generate() {
			cout << "test: generate()" << endl;

			auto lmd1 = []()->char {static char c = 'a'; return ++c; };
			string str1;
			string str2("abcd");
			kkli::generate(str1.begin(), str1.end(), lmd1);
			kkli::generate(str2.begin(), str2.end(), lmd1);
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "bcde");
		}

		//≤‚ ‘ generate_n
		void test_generate_n() {
			cout << "test: generate_n()" << endl;

			auto lmd1 = []()->char {static char c = 'a'; return c++; };
			string str1("aa");
			string str2("aaaa");
			string str3("aaaaaa");
			auto iter1 = kkli::generate_n(str1.begin(), 0, lmd1);
			auto iter2 = kkli::generate_n(str2.begin(), 2, lmd1);
			auto iter3 = kkli::generate_n(str3.begin(), 6, lmd1);
			EXPECT_EQ_VAL(str1, "aa");
			EXPECT_EQ_VAL(str2, "abaa");
			EXPECT_EQ_VAL(str3, "cdefgh");
			EXPECT_EQ_VAL(iter1, str1.begin());
			EXPECT_EQ_VAL(iter2, str2.begin() + 2);
			EXPECT_EQ_VAL(iter3, str3.end());
		}

		//≤‚ ‘ remove
		void test_remove() {
			cout << "test: remove()" << endl;

			string str1;
			string str2("aabbccdd");
			auto iter1 = kkli::remove(str1.begin(), str1.end(), 'a');
			auto iter2 = kkli::remove(str2.begin(), str2.end(), 'b');
			auto iter3 = kkli::remove(str2.begin(), str2.end(), 'z');
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "aaccdddd");
			EXPECT_EQ_VAL(iter1, str1.end());
			EXPECT_EQ_VAL(iter2, str2.end() - 2);
			EXPECT_EQ_VAL(iter2, str2.end() - 2);
		}

		//≤‚ ‘ remove_if
		void test_remove_if() {
			cout << "test: remove_if()" << endl;

			string str1;
			string str2("abcdab");
			string str3("abcdab");
			auto lmd1 = [](char c)->bool {return c >= 'c'; };
			auto lmd2 = [](char c)->bool {return c >= 'a'; };
			auto iter1 = kkli::remove_if(str1.begin(), str1.end(), lmd1);
			auto iter2 = kkli::remove_if(str2.begin(), str2.end(), lmd1);
			auto iter3 = kkli::remove_if(str3.begin(), str3.end(), lmd2);
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "ababab");
			EXPECT_EQ_VAL(str3, "abcdab");
			EXPECT_EQ_VAL(iter1, str1.begin());
			EXPECT_EQ_VAL(iter2, str2.end() - 2);
			EXPECT_EQ_VAL(iter3, str3.begin());
		}

		//≤‚ ‘ remove_copy
		void test_remove_copy() {
			cout << "test: remove_copy()" << endl;

			string str1;
			string str2("abcd");
			string str_dest1("aaaa");
			string str_dest2("aaaa");
			string str_dest3("aaaa");
			auto iter1 = kkli::remove_copy(str1.begin(), str1.end(), 
				str_dest1.begin(), 'a');
			auto iter2 = kkli::remove_copy(str2.begin(), str2.end(), 
				str_dest2.begin(), 'b');
			auto iter3 = kkli::remove_copy(str2.begin(), str2.end(), 
				str_dest3.begin(), 'z');
			EXPECT_EQ_VAL(str_dest1, "aaaa");
			EXPECT_EQ_VAL(str_dest2, "acda");
			EXPECT_EQ_VAL(str_dest3, "abcd");
			EXPECT_EQ_VAL(iter1, str_dest1.begin());
			EXPECT_EQ_VAL(iter2, str_dest2.end() - 1);
			EXPECT_EQ_VAL(iter3, str_dest3.end());
		}

		//≤‚ ‘ remove_copy_if
		void test_remove_copy_if() {
			cout << "test: remove_copy_if()" << endl;

			string str1;
			string str2("abcd");
			string str_dest1("aaaa");
			string str_dest2("aaaa");
			string str_dest3("aaaa");
			auto lmd1 = [](char c)->bool {return c >= 'c'; };
			auto lmd2 = [](char c)->bool {return c >= 'z'; };
			auto iter1 = kkli::remove_copy_if(str1.begin(), str1.end(),
				str_dest1.begin(), lmd1);
			auto iter2 = kkli::remove_copy_if(str2.begin(), str2.end(),
				str_dest2.begin(), lmd1);
			auto iter3 = kkli::remove_copy_if(str2.begin(), str2.end(),
				str_dest3.begin(), lmd2);
			EXPECT_EQ_VAL(str_dest1, "aaaa");
			EXPECT_EQ_VAL(str_dest2, "abaa");
			EXPECT_EQ_VAL(str_dest3, "abcd");
			EXPECT_EQ_VAL(iter1, str_dest1.begin());
			EXPECT_EQ_VAL(iter2, str_dest2.begin()+2);
			EXPECT_EQ_VAL(iter3, str_dest3.end());
		}

		//≤‚ ‘ replace
		void test_replace() {
			cout << "test: replace()" << endl;

			string str1;
			string str2("abcd");
			kkli::replace(str1.begin(), str1.end(), 'a', 'b');
			kkli::replace(str2.begin(), str2.end(), 'b', 'c');
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "accd");
		}

		//≤‚ ‘ replace_if
		void test_replace_if() {
			cout << "test: replace_if()" << endl;

			string str1;
			string str2("abcd");
			auto lmd1 = [](char c)->bool {return c >= 'c'; };
			kkli::replace_if(str1.begin(), str1.end(), lmd1, 'z');
			kkli::replace_if(str2.begin(), str2.end(), lmd1, 'z');
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "abzz");
		}
		
		//≤‚ ‘ replace_copy
		void test_replace_copy() {
			cout << "test: replace_copy()" << endl;

			string str1;
			string str2("abcd");
			string str_dest1("aaaa");
			string str_dest2("aaaa");
			auto iter1 = kkli::replace_copy(str1.begin(), str1.end(),
				str_dest1.begin(), 'a', 'b');
			auto iter2 = kkli::replace_copy(str2.begin(), str2.end(),
				str_dest2.begin(), 'b', 'z');
			EXPECT_EQ_VAL(str_dest1, "aaaa");
			EXPECT_EQ_VAL(str_dest2, "azcd");
			EXPECT_EQ_VAL(iter1, str_dest1.begin());
			EXPECT_EQ_VAL(iter2, str_dest2.end());
		}

		//≤‚ ‘ replace_copy_if
		void test_replace_copy_if() {
			cout << "test: replace_copy_if()" << endl;

			string str1;
			string str2("abcd");
			string str_dest1("aaaa");
			string str_dest2("aaaa");
			auto lmd1 = [](char c)->bool {return c >= 'c'; };
			auto iter1 = kkli::replace_copy_if(str1.begin(), str1.end(),
				str_dest1.begin(), lmd1, 'z');
			auto iter2 = kkli::replace_copy_if(str2.begin(), str2.end(),
				str_dest2.begin(), lmd1, 'z');
			EXPECT_EQ_VAL(str_dest1, "aaaa");
			EXPECT_EQ_VAL(str_dest2, "abzz");
			EXPECT_EQ_VAL(iter1, str_dest1.begin());
			EXPECT_EQ_VAL(iter2, str_dest2.end());
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			int i1 = 1;
			int i2 = 2;
			string str1("abcd");
			string str2("qwer");
			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 5,6,7,8 };
			int arr_comp1[4] = { 1,2,3,4 };
			int arr_comp2[4] = { 5,6,7,8 };
			kkli::swap(i1, i2);
			kkli::swap(*(str1.begin()), *(str2.begin()));
			kkli::swap(arr1, arr2);
			EXPECT_EQ_VAL(i1, i2 + 1);
			EXPECT_EQ_VAL(str1, "qbcd");
			EXPECT_EQ_VAL(str2, "awer");
			EXPECT_EQ_ARR(arr1, arr_comp2, 4);
			EXPECT_EQ_ARR(arr2, arr_comp1, 4);
		}

		//≤‚ ‘ swap_ranges
		void test_swap_ranges() {
			cout << "test: swap_ranges()" << endl;

			string str1("aaaa");
			string str2("abcd");
			auto iter1 = kkli::swap_ranges(str1.begin(), str1.end(), str2.begin());
			EXPECT_EQ_VAL(str1, "abcd");
			EXPECT_EQ_VAL(str2, "aaaa");
		}

		//≤‚ ‘ iter_swap
		void test_iter_swap() {
			cout << "test: iter_swap()" << endl;

			string str1("ab");
			kkli::iter_swap(str1.begin(), str1.begin() + 1);
			EXPECT_EQ_VAL(str1, "ba");
		}

		//≤‚ ‘ reverse
		void test_reverse() {
			cout << "test: reverse()" << endl;

			string str1("abcd");
			kkli::reverse(str1.begin(), str1.begin());
			EXPECT_EQ_VAL(str1, "abcd");

			kkli::reverse(str1.begin(), str1.end());
			EXPECT_EQ_VAL(str1, "dcba");
		}

		//≤‚ ‘ reverse_copy
		void test_reverse_copy() {
			cout << "test: reverse_copy()" << endl;

			string str1("abcd");
			string str2("qwer");
			auto iter1 = kkli::reverse_copy(str1.begin(), str1.begin(), str2.begin());
			EXPECT_EQ_VAL(str2, "qwer");
			EXPECT_EQ_VAL(iter1, str2.begin());
			
			iter1 = kkli::reverse_copy(str1.begin(), str1.end(), str2.begin());
			EXPECT_EQ_VAL(str2, "dcba");
			EXPECT_EQ_VAL(iter1, str2.end());
		}

		//≤‚ ‘ rotate
		void test_rotate() {
			cout << "test: rotate()" << endl;

			string str1("abcdefgh");
			kkli::rotate(str1.begin(), str1.begin() + 2, str1.end());
			EXPECT_EQ_VAL(str1, "cdefghab");
			kkli::rotate(str1.begin(), str1.begin(), str1.end());
			EXPECT_EQ_VAL(str1, "cdefghab");
			kkli::rotate(str1.begin(), str1.end(), str1.end());
			EXPECT_EQ_VAL(str1, "cdefghab");
		}

		//≤‚ ‘ rotate_copy
		void test_rotate_copy() {
			cout << "test: rotate_copy()" << endl;

			string str1("abcd");
			string str2("aaaa");
			auto iter1 = kkli::rotate_copy(str1.begin(), str1.begin() + 1,
				str1.end(), str2.begin());
			EXPECT_EQ_VAL(str2, "bcda");
			EXPECT_EQ_VAL(iter1, str2.end());
			iter1 = kkli::rotate_copy(str1.begin(), str1.begin() + 2,
				str1.end(), str2.begin());
			EXPECT_EQ_VAL(str2, "cdab");
			EXPECT_EQ_VAL(iter1, str2.end());
		}

		//≤‚ ‘ unique
		void test_unique() {
			cout << "test: unique()" << endl;

			string str1;
			string str2("aabbccdd");
			auto iter1 = kkli::unique(str1.begin(), str1.end());
			auto iter2 = kkli::unique(str2.begin(), str2.end());
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "abcdccdd");
			EXPECT_EQ_VAL(iter1, str1.begin());
			EXPECT_EQ_VAL(iter2, str2.begin() + 4);
		}

		//≤‚ ‘ unique_copy
		void test_unique_copy() {
			cout << "test: unique_copy()" << endl;

			string str1;
			string str2("aabbccdd");
			string dest("aaaaaaaa");
			auto lmd1 = [](char c1, char c2)->bool { return c1 >= 'c'; };
			auto iter1 = kkli::unique_copy(str1.begin(), str1.end(), dest.begin());
			EXPECT_EQ_VAL(dest, "aaaaaaaa");
			EXPECT_EQ_VAL(iter1, dest.begin());
			iter1 = kkli::unique_copy(str2.begin(), str2.end(), dest.begin());
			EXPECT_EQ_VAL(dest, "abcdaaaa");
			EXPECT_EQ_VAL(iter1, dest.begin() + 4);
			iter1 = kkli::unique_copy(str2.begin(), str2.end(), dest.begin(), lmd1);
			EXPECT_EQ_VAL(dest, "aabbaaaa");
			EXPECT_EQ_VAL(iter1, dest.begin() + 4);
		}
	}
}