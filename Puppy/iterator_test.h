#pragma once

#include "stdafx.h"
#include "string.h"
#include "list.h"
#include "char_traits.h"
#include "memory.h"
#include "iterator.h"
#include "test.h"

namespace test {
	namespace iterator_test {

		using std::cin;
		using std::cout;
		using std::endl;
		using kkli::string;
		using kkli::list;
		using reverse_iterator = kkli::reverse_iterator<string::iterator>;

		//Ç°ÖÃÉùÃ÷
		void test_reverse_iterator();
		void test_back_insert_iterator();
		void test_front_insert_iterator();
		void test_insert_iterator();
		void test_istream_iterator();		//buggy
		void test_ostream_iterator();		//buggy

		//ÕûÌå²âÊÔ
		void test() {
			test_reverse_iterator();
			test_back_insert_iterator();
			test_front_insert_iterator();
			test_insert_iterator();
			//test_istream_iterator();
			//test_ostream_iterator();
		}

		//²âÊÔ reverse_iterator
		void test_reverse_iterator() {
			cout << "test: reverse_iterator";

			string str1("abcd");
			auto rbeg = reverse_iterator(str1.end());
			auto rend = reverse_iterator(str1.begin());
			EXPECT_EQ_VAL(*rbeg, 'd');
			EXPECT_EQ_VAL(*(rbeg + 1), 'c');
			EXPECT_EQ_VAL(*(rbeg + 2), 'b');
			EXPECT_EQ_VAL(*(rbeg + 3), 'a');

			string str2(rbeg, rend);
			EXPECT_EQ_ARR(str2.c_str(), "dcba", 4);

			cout << " ---- succeed!" << endl;
		}

		//²âÊÔ back_insert_iterator
		void test_back_insert_iterator() {
			cout << "test: back_insert_iterator";

			string str1;
			string str2("abcd");
			auto lmd = [](kkli::back_insert_iterator<string>& bii) {
				for (int i = 'a'; i < 'e'; ++i) *bii = i;
			};
			lmd(kkli::back_inserter(str1));
			lmd(kkli::back_inserter(str2));

			EXPECT_EQ_ARR(str1.c_str(), "abcd", 4);
			EXPECT_EQ_ARR(str2.c_str(), "abcdabcd", 8);

			cout << " ---- succeed!" << endl;
		}

		//²âÊÔ front_insert_iterator
		void test_front_insert_iterator() {
			cout << "test: front_insert_iterator";

			list<char> lst1;
			list<char> lst2{ 'a','b','c','d' };
			list<char> comp1{ 'd','c','b','a' };
			list<char> comp2{ 'd','c','b','a','a','b','c','d' };

			auto lmd = [](kkli::front_insert_iterator<list<char>>& bii) {
				for (int i = 'a'; i < 'e'; ++i) *bii = i;
			};
			lmd(kkli::front_inserter(lst1));
			lmd(kkli::front_inserter(lst2));
			EXPECT_EQ_ITER(lst1.begin(), lst1.end(), comp1.begin(), comp1.end());
			EXPECT_EQ_ITER(lst2.begin(), lst2.end(), comp2.begin(), comp2.end());
			
			cout << " ---- succeed!" << endl;
		}

		//²âÊÔ insert_iterator
		void test_insert_iterator() {
			cout << "test: insert_iterator";

			string str1;
			string str2("abcd");
			string comp1("abcd");
			string comp2("abcdabcd");

			auto lmd = [](kkli::insert_iterator<string>& bii) {
				for (int i = 'a'; i < 'e'; ++i) *bii = i;
			};
			lmd(kkli::inserter(str1,str1.begin()));
			lmd(kkli::inserter(str2,str2.begin()));
			EXPECT_EQ_ITER(str1.begin(), str1.end(), comp1.begin(), comp1.end());
			EXPECT_EQ_ITER(str2.begin(), str2.end(), comp2.begin(), comp2.end());

			cout << " ---- succeed!" << endl;
		}

		//²âÊÔ istream_iterator
		/*
		void test_istream_iterator() {
			cout << "\ntest_istream_iterator()" << endl;

			string str1((kkli::istream_iterator<char>(cin)), kkli::istream_iterator<char>());
			//str1.print("str1");
		}
		*/
		
		//²âÊÔ ostream_iterator
		/*
		void test_ostream_iterator() {
			cout << "\ntest_ostream_iterator()" << endl;

			string str1("abcd");
			auto iter = str1.begin();
			kkli::ostream_iterator<char> oi(cout, " ");
			while (iter!= str1.end()) {
				*oi = *iter;
				++iter;
			}
		}
		*/
	}
}
