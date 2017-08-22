#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "algorithm.h"
#include "string.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;
		using kkli::string;

		//«∞÷√…˘√˜

		//part3: partitioning operations
		void test_is_partitioned();
		void test_partition();
		void test_partition_copy();
		void test_partition_point();
		void test_statle_partition();		//Œ¥ µœ÷

		//≤ø∑÷≤‚ ‘
		void test_part3() {
			test_is_partitioned();
			test_partition();
			test_partition_copy();
			test_partition_point();
			//test_stable_partition();
		}

		//≤‚ ‘ is_partitioned
		void test_is_partitioned() {
			cout << "test: is_partitioned()" << endl;

			int arr1[8] = { 1,2,3,4,5,6,7,8 };
			int arr2[8] = { 1,3,5,7,2,4,6,8 };
			auto lmd1 = [](int i)->bool {return i <= 4; };
			auto lmd2 = [](int i)->bool {return i % 2; };
			bool b1 = kkli::is_partitioned(kkli::begin(arr1), kkli::end(arr1), lmd1);
			bool b2 = kkli::is_partitioned(kkli::begin(arr2), kkli::end(arr2), lmd1);
			bool b3 = kkli::is_partitioned(kkli::begin(arr1), kkli::end(arr1), lmd2);
			bool b4 = kkli::is_partitioned(kkli::begin(arr2), kkli::end(arr2), lmd2);
			EXPECT_EQ_VAL(b1, true);
			EXPECT_EQ_VAL(b2, false);
			EXPECT_EQ_VAL(b3, false);
			EXPECT_EQ_VAL(b4, true);
		}

		//≤‚ ‘ partition
		void test_partition() {
			cout << "test: partition()" << endl;

			int arr1[8] = { 1,2,5,7,6,3,8,4 };
			int arr2[8] = { 1,2,3,4,5,6,7,8 };
			int comp1[8] = { 1,2,3,4,6,5,8,7 };
			int comp2[8] = { 1,3,5,7,2,6,4,8 };
			auto lmd1 = [](int i)->bool {return i <= 4; };
			auto lmd2 = [](int i)->bool {return i % 2; };
			auto iter1 = kkli::partition(kkli::begin(arr1), kkli::end(arr1), lmd1);
			auto iter2 = kkli::partition(kkli::begin(arr2), kkli::end(arr2), lmd2);
			EXPECT_EQ_ARR(arr1, comp1, 8);
			EXPECT_EQ_ARR(arr2, comp2, 8);
			EXPECT_EQ_VAL(iter1, arr1 + 4);
			EXPECT_EQ_VAL(iter2, arr2 + 4);
		}

		//≤‚ ‘ partition_copy
		void test_partition_copy() {
			cout << "test: partition_copy()" << endl;

			int arr1[8] = { 1,2,3,4,5,6,7,8 };
			int dest1[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int dest2[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int comp1[10] = { 1,2,3,4,1,1,1,1,1,1 };
			int comp2[10] = { 5,6,7,8,1,1,1,1,1,1 };
			auto lmd1 = [](int i)->bool {return i <= 4; };
			kkli::pair<int*, int*> p1 = kkli::partition_copy(
				kkli::begin(arr1), kkli::end(arr1), dest1, dest2, lmd1);
			EXPECT_EQ_ARR(dest1, comp1, 10);
			EXPECT_EQ_ARR(dest2, comp2, 10);
		}

		//≤‚ ‘ partition_point
		void test_partition_point() {
			cout << "test: partition_point()" << endl;

			int arr1[8] = { 1,2,3,4,5,6,7,8 };
			int arr2[8] = { 1,3,5,7,2,4,6,8 };
			auto lmd1 = [](int i)->bool {return i <= 4; };
			auto lmd2 = [](int i)->bool {return i % 2; };
			auto iter1 = kkli::partition_point(kkli::begin(arr1), kkli::end(arr1), lmd1);
			auto iter2 = kkli::partition_point(kkli::begin(arr2), kkli::end(arr2), lmd2);
			EXPECT_EQ_VAL(*iter1, 5);
			EXPECT_EQ_VAL(*iter2, 2);
		}
	}
}
