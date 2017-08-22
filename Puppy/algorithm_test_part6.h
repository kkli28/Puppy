#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "algorithm.h"
#include "iterator.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;

		//«∞÷√…˘√˜
		void test_merge();
		void test_inplace_merge();	//…–Œ¥ µœ÷
		void test_include();		//…–Œ¥ µœ÷
		void test_set_difference();
		void test_set_intersection();
		void test_set_symmetric_difference();
		void test_set_union();

		//≤ø∑÷≤‚ ‘ part6
		void test_part6() {
			test_merge();
			//test_inplace_merge();	//…–Œ¥ µœ÷
			//test_include();		//…–Œ¥ µœ÷
			test_set_difference();
			test_set_intersection();
			test_set_symmetric_difference();
			test_set_union();
		}

		//≤‚ ‘ merge
		void test_merge() {
			cout << "test: merge()" << endl;

			int arr1[4] = { 1,3,5,7 };
			int arr2[4] = { 2,4,6,8 };
			int dest1[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int comp1[10] = { 1,3,5,7,1,1,1,1,1,1 };
			int comp2[10] = { 1,2,3,4,5,6,7,8,1,1 };
			int comp3[10] = { 8,7,6,5,4,3,2,1,1,1 };
			auto iter1 = kkli::merge(arr1, arr1, arr1, arr1 + 4, dest1);
			EXPECT_EQ_ARR(dest1, comp1, 10);
			EXPECT_EQ_VAL(*iter1, 1);
			EXPECT_EQ_VAL(*(iter1 - 1), 7);

			iter1 = kkli::merge(arr1, arr1 + 4, arr2, arr2 + 4, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 10);
			EXPECT_EQ_VAL(*iter1, 1);
			EXPECT_EQ_VAL(*(iter1 - 1), 8);

			//∑¥œÚƒÊ–Úmerge
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			iter1 = kkli::merge(
				kkli::make_reverse_iterator(arr1 + 4),
				kkli::make_reverse_iterator(arr1),
				kkli::make_reverse_iterator(arr2 + 4),
				kkli::make_reverse_iterator(arr2),
				dest1, lmd1);
			EXPECT_EQ_ARR(dest1, comp3, 10);
			EXPECT_EQ_VAL(*iter1, 1);
			EXPECT_EQ_VAL(*(iter1 - 2), 2);
		}

		//≤‚ ‘ set_difference
		void test_set_difference() {
			cout << "test: set_difference()" << endl;

			int arr1[8] = { 1,1,2,3,3,4,5,5 };
			int arr2[8] = { 1,2,2,3,4,4,5,6 };
			int dest1[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int comp1[10] = { 1,1,2,3,3,4,5,5,1,1 };
			int comp2[10] = { 1,3,5,3,3,4,5,5,1,1 };
			int comp3[10] = { 2,4,6,3,3,4,5,5,1,1 };

			auto iter1 = kkli::set_difference(arr1, arr1+8, arr1, arr1, dest1);
			EXPECT_EQ_ARR(dest1, comp1, 10);
			EXPECT_EQ_VAL(*(iter1 - 1), 5);
			EXPECT_EQ_VAL(iter1, dest1 + 8);

			iter1 = kkli::set_difference(arr1, arr1 + 8, arr2, arr2 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 10);
			EXPECT_EQ_VAL(*(iter1 - 1), 5);

			iter1 = kkli::set_difference(arr2, arr2 + 8, arr1, arr1 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp3, 10);
			EXPECT_EQ_VAL(*(iter1 - 1), 6);

			//set_difference(first1,last1,first2,last2,dest,comp);
		}

		//≤‚ ‘ set_intersection
		void test_set_intersection() {
			cout << "test: set_intersection()" << endl;

			int arr1[8] = { 1,1,2,3,3,4,5,5 };
			int arr2[8] = { 1,2,2,3,4,4,5,6 };
			int dest1[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int comp1[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int comp2[10] = { 1,2,3,4,5,1,1,1,1,1 };

			auto iter1 = kkli::set_intersection(arr1, arr1 + 8, arr1, arr1, dest1);
			EXPECT_EQ_ARR(dest1, comp1, 10);
			EXPECT_EQ_VAL(iter1, dest1);

			iter1 = kkli::set_intersection(arr1, arr1 + 8, arr2, arr2 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 10);
			EXPECT_EQ_VAL(iter1, dest1 + 5);

			iter1 = kkli::set_intersection(arr2, arr2 + 8, arr1, arr1 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 10);
			EXPECT_EQ_VAL(iter1, dest1 + 5);

			//set_intersection(first1,last1,first2,last2,dest,comp);
		}

		//≤‚ ‘ set_symmetric_difference
		void test_set_symmetric_difference() {
			cout << "test: set_symmetric_difference()" << endl;

			int arr1[8] = { 1,1,2,4,5,7,7,9 };
			int arr2[8] = { 1,2,2,3,4,4,7,8 };
			int dest1[10] = { 1,1,1,1,1,1,1,1,1,1 };
			int comp1[10] = { 1,1,2,4,5,7,7,9,1,1 };
			int comp2[10] = { 1,2,3,4,5,7,8,9,1,1 };

			auto iter1 = kkli::set_symmetric_difference(arr1, arr1 + 8, arr1, arr1, dest1);
			EXPECT_EQ_ARR(dest1, comp1, 10);
			EXPECT_EQ_VAL(iter1, dest1 + 8);

			iter1 = kkli::set_symmetric_difference(arr1, arr1 + 8, arr2, arr2 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 10);
			EXPECT_EQ_VAL(iter1, dest1 + 8);

			iter1 = kkli::set_symmetric_difference(arr2, arr2 + 8, arr1, arr1 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 10);
			EXPECT_EQ_VAL(iter1, dest1 + 8);
		}

		//≤‚ ‘ set_union
		void test_set_union() {
			cout << "test: set_union()" << endl;

			int arr1[8] = { 1,1,2,4,5,7,7,9 };
			int arr2[8] = { 1,2,2,3,4,4,7,8 };
			int dest1[12] = { 1,1,1,1,1,1,1,1,1,1,1,1 };

			int comp1[12] = { 1,1,2,4,5,7,7,9,1,1,1,1 };
			int comp2[12] = { 1,1,2,2,3,4,4,5,7,7,8,9 };

			auto iter1 = kkli::set_union(arr1, arr1 + 8, arr1, arr1, dest1);
			EXPECT_EQ_ARR(dest1, comp1, 12);
			EXPECT_EQ_VAL(iter1, dest1 + 8);

			iter1 = kkli::set_union(arr1, arr1 + 8, arr2, arr2 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 12);
			EXPECT_EQ_VAL(iter1, dest1 + 12);

			iter1 = kkli::set_union(arr2, arr2 + 8, arr1, arr1 + 8, dest1);
			EXPECT_EQ_ARR(dest1, comp2, 12);
			EXPECT_EQ_VAL(iter1, dest1 + 12);
		}
	}
}
