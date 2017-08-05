#pragma once

#include "stdafx.h"
#include "string.h"
#include "char_traits.h"
#include "memory.h"
#include "iterator.h"
#include "list.h"

namespace test {
	namespace iterator_test {

		using std::cin;
		using std::cout;
		using std::endl;
		using kkli::list;
		using string = kkli::string<char, kkli::char_traits<char>, kkli::allocator<char>>;
		using reverse_iterator = kkli::reverse_iterator<string::iterator>;

		//前置声明
		void test_reverse_iterator();
		void test_back_insert_iterator();
		void test_front_insert_iterator();
		void test_insert_iterator();
		void test_istream_iterator();		//buggy
		void test_ostream_iterator();		//buggy

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: iterator " << endl;
			cout << "========================================" << endl;

			test_reverse_iterator();
			test_back_insert_iterator();
			test_front_insert_iterator();
			test_insert_iterator();
			//test_istream_iterator();		//程序不能找到istream_iterator的比较运算符!=
			//test_ostream_iterator();		//同上6
		}

		//测试 reverse_iterator
		void test_reverse_iterator() {
			cout << "\ntest_reverse_iterator()" << endl;

			string str1("abcd");

			auto rbeg = reverse_iterator(str1.end());
			auto rend = reverse_iterator(str1.begin());
			string str2(rbeg, rend);
			str2.print("str2");				//dcba

			//dcba
			for (auto iter = rbeg; iter != rend; ++iter)
				cout << *iter;
			cout << endl;
		}

		//测试 back_insert_iterator
		void test_back_insert_iterator() {
			cout << "\ntest_back_insert_iterator()" << endl;

			string str1;
			string str2("abcd");

			auto lmd = [](kkli::back_insert_iterator<string>& bii) {
				for (int i = 'a'; i < 'e'; ++i) {
					*bii = i;
				}
			};
			lmd(kkli::back_inserter(str1));
			lmd(kkli::back_inserter(str2));

			str1.print("str1");				//abcd
			str2.print("str2");				//abcdabcd
		}

		//测试 front_insert_iterator
		void test_front_insert_iterator() {
			cout << "\ntest_front_insert_iterator()" << endl;

			list<char> lst1;
			list<char> lst2{ 'a','b','c','d' };

			auto lmd = [](kkli::front_insert_iterator<list<char>>& bii) {
				for (int i = 'a'; i < 'e'; ++i) {
					*bii = i;
				}
			};
			lmd(kkli::front_inserter(lst1));
			lmd(kkli::front_inserter(lst2));

			lst1.print("str1");				//dcba
			lst2.print("str2");				//dcbaabcd
		}

		//测试 insert_iterator
		void test_insert_iterator() {
			cout << "\ntest_insert_iterator()" << endl;

			list<char> lst1;
			list<char> lst2{ 'a','b','c','d' };

			auto lmd = [](kkli::insert_iterator<list<char>>& bii) {
				for (int i = 'a'; i < 'e'; ++i) {
					*bii = i;
				}
			};
			lmd(kkli::inserter(lst1,lst1.begin()));
			lmd(kkli::inserter(lst2,lst2.begin()));

			lst1.print("str1");				//abcd
			lst2.print("str2");				//aabcdbcd
		}

		/*
		//测试 istream_iterator
		void test_istream_iterator() {
			cout << "\ntest_istream_iterator()" << endl;

			string str1((kkli::istream_iterator<char>(cin)), kkli::istream_iterator<char>());
			str1.print("str1");
		}
		*/
		
		/*
		//测试 ostream_iterator
		void test_ostream_iterator() {
			cout << "\ntest_ostream_iterator()" << endl;

			string str1("abcd");
			kkli::ostream_iterator<char> os1(cout, " ");
			kkli::ostream_iterator<char> os2();
			auto it = str1.begin();
			for (auto iter = os1; iter != os2; ++iter) {
				*iter = *it;
				++it;
			}
		}
		*/
	}
}
