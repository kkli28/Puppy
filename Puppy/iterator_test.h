#pragma once

#include "stdafx.h"
#include "string.h"
#include "list.h"
#include "forward_list.h"
#include "char_traits.h"
#include "memory.h"
#include "iterator.h"
#include "test_utility.h"
#include "algorithm.h"

namespace test {
	namespace iterator_test {

		using std::cin;
		using std::cout;
		using std::endl;
		using kkli::forward_list;
		using kkli::list;
		using kkli::string;
		using reverse_iterator = kkli::reverse_iterator<string::iterator>;

		//Ç°ÖÃÉùÃ÷
		void test_reverse_iterator();
		void test_move_iterator();
		void test_back_insert_iterator();
		void test_front_insert_iterator();
		void test_insert_iterator();
		void test_istream_iterator();		//buggy
		void test_ostream_iterator();		//buggy
		void test_make_reverse_iterator();
		void test_make_move_iterator();
		void test_front_inserter();
		void test_back_inserter();
		void test_inserter();
		void test_advance();
		void test_distance();
		void test_next();
		void test_prev();
		void test_begin();
		void test_end();

		//ÕûÌå²âÊÔ
		void test() {
			cout << "\n========================================" << endl;
			cout << "            iterator.h " << endl;
			cout << "========================================" << endl;

			test_reverse_iterator();
			test_move_iterator();
			test_back_insert_iterator();
			test_front_insert_iterator();
			test_insert_iterator();

			test_make_reverse_iterator();
			test_make_move_iterator();
			test_front_inserter();
			test_back_inserter();
			test_inserter();
			test_advance();
			test_distance();
			test_next();
			test_prev();
			test_begin();
			test_end();

			//test_istream_iterator();	//buggy
			//test_ostream_iterator();	//buggy
		}

		//²âÊÔ reverse_iterator
		void test_reverse_iterator() {
			cout << "test: reverse_iterator" << endl;

			string str1("abcd");
			auto rbeg = reverse_iterator(str1.end());
			auto rend = reverse_iterator(str1.begin());
			EXPECT_EQ_VAL(*rbeg, 'd');
			EXPECT_EQ_VAL(*(rbeg + 1), 'c');
			EXPECT_EQ_VAL(*(rbeg + 2), 'b');
			EXPECT_EQ_VAL(*(rbeg + 3), 'a');

			string str2(rbeg, rend);
			EXPECT_EQ_ARR(str2.c_str(), "dcba", 4);
		}

		//²âÊÔ move_iterator
		void test_move_iterator() {
			cout << "test: move_iterator" << endl;

			string sarr1[4] = { "abcd","efgh","hijk","lmno" };
			string str1("abcd");
			string sarr2[4] = {};
			string comp1[4] = { "abcd","efgh","hijk","lmno" };
			kkli::move_iterator<string*> move_iter(kkli::begin(sarr1));
			auto iter1 = kkli::begin(sarr1);
			auto iter2 = kkli::begin(sarr2);
			auto end = kkli::end(sarr1);
			for (; iter1 != end; ++iter1) {
				*iter2 = *move_iter;
				++move_iter;
				++iter2;
			}
			EXPECT_EQ_ARR(sarr2, comp1, 4);
			EXPECT_EQ_VAL(sarr1[1].begin(), sarr1[1].end());
		}

		//²âÊÔ back_insert_iterator
		void test_back_insert_iterator() {
			cout << "test: back_insert_iterator" << endl;

			string str1;
			string str2("abcd");
			auto lmd = [](kkli::back_insert_iterator<string>& bii) {
				for (int i = 'a'; i < 'e'; ++i) *bii = i;
			};
			lmd(kkli::back_inserter(str1));
			lmd(kkli::back_inserter(str2));

			EXPECT_EQ_ARR(str1.c_str(), "abcd", 4);
			EXPECT_EQ_ARR(str2.c_str(), "abcdabcd", 8);
		}

		//²âÊÔ front_insert_iterator
		void test_front_insert_iterator() {
			cout << "test: front_insert_iterator" << endl;

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
		}

		//²âÊÔ insert_iterator
		void test_insert_iterator() {
			cout << "test: insert_iterator" << endl;

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
		}

		//²âÊÔ make_reverse_iterator
		void test_make_reverse_iterator() {
			cout << "test: make_reverse_iterator()" << endl;

			string str1("abcd");
			string str2("aaaa");
			auto rbeg1 = kkli::make_reverse_iterator(str1.end());
			auto rend1 = kkli::make_reverse_iterator(str1.begin());
			auto iter1 = str2.begin();
			for (; rbeg1 != rend1; ++rbeg1)
				*(iter1++) = *rbeg1;
			EXPECT_EQ_VAL(str2, "dcba");
		}

		//²âÊÔ make_move_iterator
		void test_make_move_iterator() {
			cout << "test: make_move_iterator()" << endl;

			string sarr1[4] = { "abcd","efgh","hijk","lmno" };
			string sarr2[4] = {};
			string comp1[4] = { "abcd","efgh","hijk","lmno" };
			auto mbeg1 = kkli::make_move_iterator(kkli::begin(sarr1));
			auto mend1 = kkli::make_move_iterator(kkli::end(sarr1));
			auto iter1 = sarr2;
			for (; mbeg1 != mend1; ++mbeg1)
				*(iter1++) = *mbeg1;
			EXPECT_EQ_ARR(sarr2, comp1, 4);
			EXPECT_EQ_VAL(sarr1[1].begin(), sarr1[1].end());
		}

		//²âÊÔ front_inserter
		void test_front_inserter() {
			cout << "test: front_inserter()" << endl;

			list<int> lst1;
			auto fiter1 = kkli::front_inserter(lst1);
			for (int i = 0; i < 4; ++i)
				*fiter1 = 1;
			auto iter1 = lst1.begin();
			for (int i = 0; i < 4; ++i) {
				EXPECT_EQ_VAL(*iter1, 1);
				++iter1;
			}
		}

		//²âÊÔ back_inserter
		void test_back_inserter() {
			cout << "test: back_inserter()" << endl;

			string str1;
			auto biter1 = kkli::back_inserter(str1);
			*(biter1++) = 'a';
			*(biter1++) = 'b';
			EXPECT_EQ_VAL(str1, "ab");
		}

		//²âÊÔ inserter
		void test_inserter() {
			cout << "test: inserter()" << endl;

			string str1("ab");
			auto iter1 = kkli::inserter(str1, str1.begin());
			*(iter1++) = 'a';
			*(iter1++) = 'b';
			EXPECT_EQ_VAL(str1, "abab");
		}

		//²âÊÔ advance
		void test_advance() {
			cout << "test: advance()" << endl;

			forward_list<int> flst1 = { 1,2,3,4 };
			list<int> lst1 = { 1,2,3,4 };
			string str1 = "abcd";
			auto iter1 = flst1.begin();
			auto iter2 = lst1.begin();
			auto iter3 = str1.begin();
			kkli::advance(iter1, 1);
			kkli::advance(iter2, 2);
			kkli::advance(iter3, 3);
			EXPECT_EQ_VAL(*iter1, 2);
			EXPECT_EQ_VAL(*iter2, 3);
			EXPECT_EQ_VAL(*iter3, 'd');
		}

		//²âÊÔ distance
		void test_distance() {
			cout << "test: distance()" << endl;

			forward_list<int> flst1 = { 1,2,3,4 };
			list<int> lst1 = { 1,2,3,4 };
			string str1("abcd");
			EXPECT_EQ_VAL(kkli::distance(flst1.begin(), flst1.end()), 4);
			EXPECT_EQ_VAL(kkli::distance(lst1.begin(), lst1.end()), 4);
			EXPECT_EQ_VAL(kkli::distance(str1.begin(), str1.end()), 4);
		}

		//²âÊÔ next
		void test_next() {
			cout << "test: next()" << endl;

			string str1("abcd");
			auto iter1 = str1.begin();
			iter1 = kkli::next(iter1);
			EXPECT_EQ_VAL(*iter1, 'b');
			iter1 = kkli::next(iter1, 2);
			EXPECT_EQ_VAL(*iter1, 'd');
		}

		//²âÊÔ prev
		void test_prev() {
			cout << "test: prev()" << endl;

			list<int> lst1 = { 1,2,3,4 };
			auto iter1 = lst1.end();
			iter1 = kkli::prev(iter1);
			EXPECT_EQ_VAL(*iter1, 4);
			iter1 = kkli::prev(iter1, 2);
			EXPECT_EQ_VAL(*iter1, 2);
		}

		//²âÊÔ begin
		void test_begin() {
			cout << "test: begin()" << endl;

			//begin
			string str1("abcd");
			int arr1[4] = { 1,2,3,4 };
			auto iter11 = kkli::begin(str1);
			auto iter12 = kkli::begin(arr1);
			EXPECT_EQ_VAL(*iter11, 'a');
			EXPECT_EQ_VAL(*iter12, 1);

			//cbegin
			const string str2("abcd");
			const int arr2[4] = { 1,2,3,4 };
			auto iter21 = kkli::cbegin(str2);
			auto iter22 = kkli::cbegin(arr2);
			EXPECT_EQ_VAL(*iter21, 'a');
			EXPECT_EQ_VAL(*iter22, 1);

			//rbegin
			string str3("abcd");
			int arr3[4] = { 1,2,3,4 };
			auto iter31 = kkli::rbegin(str3);
			auto iter32 = kkli::rbegin(arr3);
			EXPECT_EQ_VAL(*iter31, 'd');
			EXPECT_EQ_VAL(*iter32, 4);

			//crbegin
			const string str4("abcd");
			const int arr4[4] = { 1,2,3,4 };
			auto iter41 = kkli::crbegin(str4);
			auto iter42 = kkli::crbegin(arr4);
			EXPECT_EQ_VAL(*iter41, 'd');
			EXPECT_EQ_VAL(*iter42, 4);
		}

		//²âÊÔ end
		void test_end() {
			cout << "test: end()" << endl;

			//end
			string str1("abcd");
			int arr1[4] = { 1,2,3,4 };
			auto iter11 = kkli::end(str1);
			auto iter12 = kkli::end(arr1);
			EXPECT_EQ_VAL(*(--iter11), 'd');
			EXPECT_EQ_VAL(*(--iter12), 4);

			//cend
			const string str2("abcd");
			const int arr2[4] = { 1,2,3,4 };
			auto iter21 = kkli::cend(str2);
			auto iter22 = kkli::cend(arr2);
			EXPECT_EQ_VAL(*(--iter21), 'd');
			EXPECT_EQ_VAL(*(--iter22), 4);

			//rend
			string str3("abcd");
			int arr3[4] = { 1,2,3,4 };
			auto iter31 = kkli::rend(str3);
			auto iter32 = kkli::rend(arr3);
			EXPECT_EQ_VAL(*(--iter31), 'a');
			EXPECT_EQ_VAL(*(--iter32), 1);

			//crend
			const string str4("abcd");
			const int arr4[4] = { 1,2,3,4 };
			auto iter41 = kkli::crend(str4);
			auto iter42 = kkli::crend(arr4);
			EXPECT_EQ_VAL(*(--iter41), 'a');
			EXPECT_EQ_VAL(*(--iter42), 1);
		}

		/*
		//²âÊÔ istream_iterator
		void test_istream_iterator() {
			cout << "\ntest_istream_iterator()" << endl;

			string str1((kkli::istream_iterator<char>(cin)), kkli::istream_iterator<char>());
			//str1.print("str1");
		}
		
		//²âÊÔ ostream_iterator
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
