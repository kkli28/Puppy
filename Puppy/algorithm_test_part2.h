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
			//test_move();
			//test_move_backward();
			//test_fill();
			//test_fill_n();
			//test_transform();
			//test_generate();
			//test_generate_n();
			//test_remove();
			//test_remove_if();
			//test_remove_copy();
			//test_remove_copy_if();
			//test_replace();
			//test_replace_if();
			//test_replace_copy();
			//test_replace_copy_if();
			//test_swap();
			//test_swap_ranges();
			//test_iter_swap();
			//test_reverse();
			//test_reverse_copy();
			//test_rotate();
			//test_rotate_copy();
			//test_unique();
			//test_unique_copy();
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
			auto iter1 = kkli::copy_backward(str1.end(), str1.begin(), str2.end());
			cout << str2 << endl;
			auto iter2 = kkli::copy_backward(str2.end(), str2.begin(), str3.end());
			EXPECT_EQ_VAL(str2, "abcd");
			EXPECT_EQ_VAL(str3, "abcd");
			EXPECT_EQ_VAL(iter1, str2.end());
			EXPECT_EQ_VAL(iter2, str3.begin());
		}
	}
}