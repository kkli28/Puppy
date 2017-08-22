#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "algorithm.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;

		//«∞÷√…˘√˜
		void test_iota();
		void test_accumulate();
		void test_inner_product();
		void test_adjacent_difference();
		void test_partial_sum();

		//≤ø∑÷≤‚ ‘ part9
		void test_part9() {
			test_iota();
			test_accumulate();
			test_inner_product();
			test_adjacent_difference();
			test_partial_sum();
		}

		//≤‚ ‘ iota
		void test_iota() {
			cout << "test: iota()" << endl;

			int dest1[4] = { 0,0,0,0 };
			kkli::iota(dest1, dest1, 1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 0,0,0,0 });
			kkli::iota(dest1, dest1 + 4, 1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 1,2,3,4 });
		}

		//≤‚ ‘ accumulate
		void test_accumulate() {
			cout << "test: accumulate()" << endl;

			int arr1[4] = { 1,2,3,4 };
			
			int val1 = kkli::accumulate(arr1, arr1, 1);
			EXPECT_EQ_VAL(val1, 1);
			val1 = kkli::accumulate(arr1, arr1 + 4, 1);
			EXPECT_EQ_VAL(val1, 11);

			auto lmd1 = [](int i, int j)->int {return i*j; };
			val1 = kkli::accumulate(arr1, arr1 + 4, 1, lmd1);
			EXPECT_EQ_VAL(val1, 24);
		}

		//≤‚ ‘ inner_product
		void test_inner_product() {
			cout << "test: inner_product()" << endl;

			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,5,7 };

			int val1 = kkli::inner_product(arr1, arr1, arr2, arr2, 1);
			EXPECT_EQ_VAL(val1, 1);
			
			val1 = kkli::inner_product(arr1, arr1 + 4, arr2, arr2 + 4, 1);
			EXPECT_EQ_VAL(val1, 51);
			
			auto lmd1 = [](int i, int j)->int {return i + j; };
			val1 = kkli::inner_product(arr1, arr1 + 4, arr2, arr2 + 4, 1, lmd1, lmd1);
			EXPECT_EQ_VAL(val1, 27);
		}

		//≤‚ ‘ adjacent_difference
		void test_adjacent_difference() {
			cout << "test: adjacent_difference()" << endl;

			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,5,7 };
			int dest1[4] = { 0,0,0,0 };
			
			auto iter1 = kkli::adjacent_difference(arr1, arr1 + 4, dest1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 1,1,1,1 });
			EXPECT_EQ_VAL(iter1, dest1 + 4);

			iter1 = kkli::adjacent_difference(arr2, arr2 + 4, dest1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 1,2,2,2 });
			EXPECT_EQ_VAL(iter1, dest1 + 4);

			auto lmd1 = [](int i, int j)->int {return i + j; };
			iter1 = kkli::adjacent_difference(arr2, arr2 + 4, dest1, lmd1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 1,4,8,12 });
		}

		//≤‚ ‘ partial_sum
		void test_partial_sum() {
			cout << "test: partial_sum()" << endl;

			int arr1[4] = { 1,2,3,4 };
			int dest1[4] = { 0,0,0,0 };

			auto iter1 = kkli::partial_sum(arr1, arr1, dest1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 0,0,0,0 });
			EXPECT_EQ_VAL(iter1, dest1);

			iter1 = kkli::partial_sum(arr1, arr1 + 4, dest1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 1, 3, 6, 10 });

			auto lmd1 = [](int i, int j)->int {return i*j; };
			iter1 = kkli::partial_sum(arr1, arr1 + 4, dest1, lmd1);
			EXPECT_EQ_ARRLIST(dest1, 4, { 1,2,6,24 });
		}
	}
}