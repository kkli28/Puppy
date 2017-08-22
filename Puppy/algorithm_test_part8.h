#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "algorithm.h"
#include "string.h"
#include "pair.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;
		using kkli::string;

		//«∞÷√…˘√˜
		void test_max_element();
		void test_max();
		void test_min_element();
		void test_min();
		void test_minmax_element();
		void test_minmax();
		void test_lexicographical_compare();

		//≤ø∑÷≤‚ ‘ part8
		void test_part8() {
			test_max_element();
			test_max();
			test_min_element();
			test_min();
			test_minmax_element();
			test_minmax();
			test_lexicographical_compare();
		}

		//≤‚ ‘ max_element
		void test_max_element() {
			cout << "test: max_element()" << endl;

			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,4,2 };
			int arr3[8] = { 1,1,2,2,3,3,4,4 };

			//max_element(first, last)
			auto iter1 = kkli::max_element(arr1, arr1);
			EXPECT_EQ_VAL(iter1, arr1);
			auto iter2 = kkli::max_element(arr1, arr1 + 4);
			EXPECT_EQ_VAL(*iter2, 4);
			auto iter3 = kkli::max_element(arr2, arr2 + 4);
			EXPECT_EQ_VAL(*iter3, 4);
			auto iter4 = kkli::max_element(arr3, arr3 + 8);
			EXPECT_EQ_VAL(*iter4, 4);

			//max_element(first, last, comp)
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			iter1 = kkli::max_element(arr1, arr1 + 4, lmd1);
			EXPECT_EQ_VAL(*iter1, 1);
			iter2 = kkli::max_element(arr2, arr2 + 4, lmd1);
			EXPECT_EQ_VAL(*iter2, 1);
			iter3 = kkli::max_element(arr3, arr3 + 8, lmd1);
			EXPECT_EQ_VAL(*iter3, 1);
		}

		//≤‚ ‘ max
		void test_max() {
			cout << "test: max()" << endl;

			int i1 = 0;
			int i2 = 1;

			int re1 = kkli::max(i1, i2);
			EXPECT_EQ_VAL(re1, 1);
			
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			re1 = kkli::max(i1, i2, lmd1);
			EXPECT_EQ_VAL(re1, 0);

			int re2 = kkli::max({ 1,2,3,4 });
			EXPECT_EQ_VAL(re2, 4);

			re2 = kkli::max({ 1,2,3,4 }, lmd1);
			EXPECT_EQ_VAL(re2, 1);
		}

		//≤‚ ‘ min_element
		void test_min_element() {
			cout << "test: min_element()" << endl;

			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,4,2 };
			int arr3[8] = { 1,1,2,2,3,3,4,4 };

			//min_element(first, last)
			auto iter1 = kkli::min_element(arr1, arr1);
			EXPECT_EQ_VAL(iter1, arr1);
			auto iter2 = kkli::min_element(arr1, arr1 + 4);
			EXPECT_EQ_VAL(*iter2, 1);
			auto iter3 = kkli::min_element(arr2, arr2 + 4);
			EXPECT_EQ_VAL(*iter3, 1);
			auto iter4 = kkli::min_element(arr3, arr3 + 8);
			EXPECT_EQ_VAL(*iter4, 1);

			//min_element(first, last, comp)
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			iter1 = kkli::min_element(arr1, arr1 + 4, lmd1);
			EXPECT_EQ_VAL(*iter1, 4);
			iter2 = kkli::min_element(arr2, arr2 + 4, lmd1);
			EXPECT_EQ_VAL(*iter2, 4);
			iter3 = kkli::min_element(arr3, arr3 + 8, lmd1);
			EXPECT_EQ_VAL(*iter3, 4);
		}

		//≤‚ ‘ min
		void test_min() {
			cout << "test: min()" << endl;

			int i1 = 0;
			int i2 = 1;

			int re1 = kkli::min(i1, i2);
			EXPECT_EQ_VAL(re1, 0);

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			re1 = kkli::min(i1, i2, lmd1);
			EXPECT_EQ_VAL(re1, 1);

			int re2 = kkli::min({ 1,2,3,4 });
			EXPECT_EQ_VAL(re2, 1);

			re2 = kkli::min({ 1,2,3,4 }, lmd1);
			EXPECT_EQ_VAL(re2, 4);
		}

		//≤‚ ‘ minmax_element
		void test_minmax_element() {
			cout << "test: minmax_element()" << endl;

			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,4,2 };
			int arr3[8] = { 1,1,2,2,3,3,4,4 };

			//minmax_element(first, last)
			auto p1 = kkli::minmax_element(arr1, arr1);
			EXPECT_EQ_VAL(p1.first, arr1);
			EXPECT_EQ_VAL(p1.second, arr1);

			auto p2 = kkli::minmax_element(arr1, arr1 + 4);
			EXPECT_EQ_VAL(*(p2.first), 1);
			EXPECT_EQ_VAL(*(p2.second), 4);

			auto p3 = kkli::minmax_element(arr2, arr2 + 4);
			EXPECT_EQ_VAL(*(p3.first), 1);
			EXPECT_EQ_VAL(*(p3.second), 4);

			auto p4 = kkli::minmax_element(arr3, arr3 + 8);
			EXPECT_EQ_VAL(*(p4.first), 1);
			EXPECT_EQ_VAL(*(p4.second), 4);

			//minmax_element(first, last, comp)
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			p1 = kkli::minmax_element(arr1, arr1, lmd1);
			EXPECT_EQ_VAL(p1.first, arr1);
			EXPECT_EQ_VAL(p1.second, arr1);

			p2 = kkli::minmax_element(arr1, arr1 + 4, lmd1);
			EXPECT_EQ_VAL(*(p2.first), 4);
			EXPECT_EQ_VAL(*(p2.second), 1);

			p3 = kkli::minmax_element(arr2, arr2 + 4, lmd1);
			EXPECT_EQ_VAL(*(p3.first), 4);
			EXPECT_EQ_VAL(*(p3.second), 1);

			p4 = kkli::minmax_element(arr3, arr3 + 8, lmd1);
			EXPECT_EQ_VAL(*(p4.first), 4);
			EXPECT_EQ_VAL(*(p4.second), 1);
		}

		//≤‚ ‘ minmax
		void test_minmax() {
			cout << "test: minmax()" << endl;

			int i1 = 0;
			int i2 = 1;

			kkli::pair<const int&,const int&> p1 = kkli::minmax(i1, i2);
			EXPECT_EQ_VAL(p1.first, 0);
			EXPECT_EQ_VAL(p1.second, 1);

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			kkli::pair<const int&, const int&> p2 = kkli::minmax(i1, i2, lmd1);
			EXPECT_EQ_VAL(p2.first, 1);
			EXPECT_EQ_VAL(p2.second, 0);

			kkli::pair<int, int> p3 = kkli::minmax({ 1,2,3,4 });
			EXPECT_EQ_VAL(p3.first, 1);
			EXPECT_EQ_VAL(p3.second, 4);
			p3 = kkli::minmax({ 1,1,2,2 });
			EXPECT_EQ_VAL(p3.first, 1);
			EXPECT_EQ_VAL(p3.second, 2);
			
			p3 = kkli::minmax({ 1,2,3,4 }, lmd1);
			EXPECT_EQ_VAL(p3.first, 4);
			EXPECT_EQ_VAL(p3.second, 1);
			p3 = kkli::minmax({ 1,1,2,2 }, lmd1);
			EXPECT_EQ_VAL(p3.first, 2);
			EXPECT_EQ_VAL(p3.second, 1);
		}

		//≤‚ ‘ lexicographical_compare
		void test_lexicographical_compare() {
			cout << "test: lexicographical_compare()" << endl;

			string str1("abc");
			string str2("abcd");
			string str3("abef");
			string str4("abcde");

			//lexicographical_compare(first1, last1, first2, last2)
			bool b1=kkli::lexicographical_compare(str1.begin(),str1.end(),
				str1.begin(), str1.end());
			EXPECT_EQ_VAL(b1, false);

			bool b2 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str2.begin(), str2.end());
			EXPECT_EQ_VAL(b2, true);
			b2 = kkli::lexicographical_compare(str2.begin(), str2.end(),
				str1.begin(), str1.end());
			EXPECT_EQ_VAL(b2, false);

			bool b3 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str3.begin(), str3.end());
			EXPECT_EQ_VAL(b3, true);
			b3 = kkli::lexicographical_compare(str3.begin(), str3.end(),
				str1.begin(), str1.end());
			EXPECT_EQ_VAL(b3, false);

			bool b4 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str4.begin(), str4.end());
			EXPECT_EQ_VAL(b4, true);
			b4 = kkli::lexicographical_compare(str4.begin(), str4.end(),
				str1.begin(), str1.end());
			EXPECT_EQ_VAL(b4, false);

			//lexicographical_compare(first1, last1, first2, last2, comp)
			auto lmd1 = [](char c1, char c2)->bool {return c1 > c2; };
			bool b5 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str1.begin(), str1.end(), lmd1);
			EXPECT_EQ_VAL(b5, false);

			bool b6 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str2.begin(), str2.end(), lmd1);
			EXPECT_EQ_VAL(b6, true);
			b6 = kkli::lexicographical_compare(str2.begin(), str2.end(),
				str1.begin(), str1.end(), lmd1);
			EXPECT_EQ_VAL(b6, false);

			bool b7 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str3.begin(), str3.end(), lmd1);
			EXPECT_EQ_VAL(b7, false);
			b7 = kkli::lexicographical_compare(str3.begin(), str3.end(),
				str1.begin(), str1.end(), lmd1);
			EXPECT_EQ_VAL(b7, true);

			bool b8 = kkli::lexicographical_compare(str1.begin(), str1.end(),
				str4.begin(), str4.end(), lmd1);
			EXPECT_EQ_VAL(b8, true);
			b8 = kkli::lexicographical_compare(str4.begin(), str4.end(),
				str1.begin(), str1.end(), lmd1);
			EXPECT_EQ_VAL(b8, false);
		}
	}
}