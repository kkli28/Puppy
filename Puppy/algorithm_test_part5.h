#pragma once

#include "stdafx.h"
#include "test.h"
#include "algorithm.h"
#include "pair.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;
		using kkli::pair;

		//«∞÷√…˘√˜
		void test_lower_bound();
		void test_upper_bound();
		void test_binary_search();
		void test_equal_range();

		//≤‚ ‘ part5
		void test_part5() {
			test_lower_bound();
			test_upper_bound();
			test_binary_search();
			test_equal_range();
		}

		//≤‚ ‘ lower_bound
		void test_lower_bound() {
			cout << "test: lower_bound()" << endl;

			int arr1[8] = { 1,2,3,4,4,5,6,7 };
			auto iter1 = kkli::lower_bound(arr1, arr1 + 8, 4);
			EXPECT_EQ_VAL(*iter1, 4);
			auto iter2 = kkli::lower_bound(arr1, arr1 + 8, 9);
			EXPECT_EQ_VAL(iter2, arr1 + 8);
			auto iter3 = kkli::lower_bound(arr1, arr1 + 8, 0);
			EXPECT_EQ_VAL(iter3, arr1);

			//lower_bound(first, last, value, comp)
		}

		//≤‚ ‘ upper_bound
		void test_upper_bound() {
			cout << "test: upper_bound()" << endl;

			int arr1[8] = { 1,2,3,4,4,5,6,7 };
			auto iter1 = kkli::upper_bound(arr1, arr1 + 8, 4);
			EXPECT_EQ_VAL(*iter1, 5);
			auto iter2 = kkli::upper_bound(arr1, arr1 + 8, 9);
			EXPECT_EQ_VAL(iter2, arr1 + 8);
			auto iter3 = kkli::upper_bound(arr1, arr1 + 8, 0);
			EXPECT_EQ_VAL(iter3, arr1);

			//upper_bound(first, last, value, comp)
		}

		//≤‚ ‘ binary_search
		void test_binary_search() {
			cout << "test: binary_search()" << endl;

			int arr1[8] = { 1,2,3,4,6,7,8,9 };
			bool b1 = kkli::binary_search(arr1, arr1, 4);
			bool b2 = kkli::binary_search(arr1, arr1 + 8, 4);
			bool b3 = kkli::binary_search(arr1, arr1 + 8, 5);
			EXPECT_EQ_VAL(b1, false);
			EXPECT_EQ_VAL(b2, true);
			EXPECT_EQ_VAL(b3, false);

			//binary_search(first, last, value, comp)
		}

		//≤‚ ‘ equal_range
		void test_equal_range() {
			cout << "test: equal_range()" << endl;

			int arr1[8] = { 1,2,3,4,4,4,5,6 };
			pair<int*, int*> p1 = kkli::equal_range(arr1, arr1 + 8, 4);
			pair<int*, int*> p2 = kkli::equal_range(arr1, arr1 + 8, 5);
			pair<int*, int*> p3 = kkli::equal_range(arr1, arr1 + 8, 8);
			EXPECT_EQ_VAL(*(p1.first), 4);
			EXPECT_EQ_VAL(*(p1.second), 5);
			EXPECT_EQ_VAL(*(p2.first), 5);
			EXPECT_EQ_VAL(*(p2.second), 6);
			EXPECT_EQ_VAL(p3.first, p3.second);

			//equal_range(first, last, value, comp)
		}
	}
}