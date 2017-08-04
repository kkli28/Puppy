#pragma once

#include "stdafx.h"
#include "string.h"
#include "char_traits.h"
#include "allocator.h"
#include "iterator.h"

namespace test {
	namespace iterator_test {

		using std::cin;
		using std::cout;
		using std::endl;
		using string = kkli::string<char, kkli::char_traits<char>, kkli::allocator<char>>;
		using reverse_iterator = kkli::reverse_iterator<string::iterator>;

		//前置声明
		void test_reverse_iterator();
		void test_back_insert_iterator();
		void test_front_insert_iterator();
		void test_insert_iterator();
		void test_istream_iterator();
		void test_ostream_iterator();

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: iterator " << endl;
			cout << "========================================" << endl;

			test_reverse_iterator();
			//test_back_insert_iterator();
			//test_front_insert_iterator();
			//test_insert_iterator();
			//test_istream_iterator();
			//test_ostream_iterator();
		}

		//测试 reverse_iterator
		void test_reverse_iterator() {
			cout << "\ntest_reverse_iterator()" << endl;

			string str1("abcd");
			string str2(reverse_iterator(str1.end()), reverse_iterator(str1.begin()));
			str2.print("str2");
		}

	}
}
