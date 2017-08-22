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

		//前置声明

		void test_is_sorted_until();
		void test_is_sorted();
		void test_insertion_sort();
		void test_sort();
		void test_partial_sort();		//尚未实现
		void test_partial_sort_copy();	//尚未实现
		void test_stable_sort();		//尚未实现
		void test_nth_element();		//尚未实现

		//部分测试
		void test_part4() {
			test_is_sorted_until();
			test_is_sorted();
			test_insertion_sort();
			test_sort();
			//test_partial_sort();		//尚未实现
			//test_partial_sort_copy();	//尚未实现
			//test_stable_sort();		//尚未实现
			//test_nth_element();		//尚未实现
		}

		//测试 is_sorted_until
		void test_is_sorted_until() {
			cout << "test: is_sorted_until()" << endl;

			int arr1[8]{ 1,2,3,4,5,6,7,8 };
			int arr2[8]{ 1,2,3,4,7,6,8,5 };
			int arr3[8]{ 8,7,6,5,3,2,4,1 };
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			auto iter1 = kkli::is_sorted_until(arr1, arr1);
			auto iter2 = kkli::is_sorted_until(kkli::begin(arr1), kkli::end(arr1));
			auto iter3 = kkli::is_sorted_until(kkli::begin(arr2), kkli::end(arr2));
			auto iter4 = kkli::is_sorted_until(kkli::begin(arr3), kkli::end(arr3), lmd1);
			EXPECT_EQ_VAL(iter1, arr1);
			EXPECT_EQ_VAL(iter2, arr1 + 8);
			EXPECT_EQ_VAL(*iter3, 6);
			EXPECT_EQ_VAL(*iter4, 4);
		}

		//测试 is_sorted
		void test_is_sorted() {
			cout << "test: is_sorted()" << endl;

			int arr1[4] = { 1,1,1,1 };
			int arr2[4] = { 1,2,3,4 };
			int arr3[4] = { 4,3,2,1 };
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			bool b1 = kkli::is_sorted(arr1, arr1 + 4);
			bool b2 = kkli::is_sorted(arr2, arr2 + 4);
			bool b3 = kkli::is_sorted(arr3, arr3 + 4);
			bool b4 = kkli::is_sorted(arr3, arr3 + 4, lmd1);
			EXPECT_EQ_VAL(b1, true);
			EXPECT_EQ_VAL(b2, true);
			EXPECT_EQ_VAL(b3, false);
			EXPECT_EQ_VAL(b4, true);
		}

		//测试 insertion_sort
		void test_insertion_sort() {
			cout << "test: insertion_sort()" << endl;

			int arr1[8] = { 1,3,6,4,2,5,8,7 };
			int arr2[40] = {
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10
			};
			int comp1[8] = { 1,2,3,4,5,6,7,8 };
			int comp2[8] = { 8,7,6,5,4,3,2,1 };
			int comp3[40] = {
				1,1,1,1,2,2,2,2,
				3,3,3,3,4,4,4,4,
				5,5,5,5,6,6,6,6,
				7,7,7,7,8,8,8,8,
				9,9,9,9,10,10,10,10
			};
			int comp4[40] = {
				10,10,10,10,9,9,9,9,
				8,8,8,8,7,7,7,7,
				6,6,6,6,5,5,5,5,
				4,4,4,4,3,3,3,3,
				2,2,2,2,1,1,1,1
			};
			auto lmd1 = [](int i, int j)->bool {return i > j; };

			kkli::insertion_sort(kkli::begin(arr1), kkli::end(arr1));
			EXPECT_EQ_ARR(arr1, comp1, 8);
			kkli::insertion_sort(kkli::begin(arr1), kkli::end(arr1), lmd1);
			EXPECT_EQ_ARR(arr1, comp2, 8);
			
			kkli::insertion_sort(kkli::begin(arr2), kkli::end(arr2));
			EXPECT_EQ_ARR(arr2, comp3, 40);
			kkli::insertion_sort(kkli::begin(arr2), kkli::end(arr2), lmd1);
			EXPECT_EQ_ARR(arr2, comp4, 40);
		}

		//测试 sort
		void test_sort() {
			cout << "test: sort()" << endl;

			int arr1[8] = { 1,3,6,4,2,5,8,7 };
			int arr2[40] = {
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10,
				1,2,3,4,5,6,7,8,9,10
			};
			int comp1[8] = { 1,2,3,4,5,6,7,8 };
			int comp2[8] = { 8,7,6,5,4,3,2,1 };
			int comp3[40] = {
				1,1,1,1,2,2,2,2,
				3,3,3,3,4,4,4,4,
				5,5,5,5,6,6,6,6,
				7,7,7,7,8,8,8,8,
				9,9,9,9,10,10,10,10
			};
			int comp4[40] = {
				10,10,10,10,9,9,9,9,
				8,8,8,8,7,7,7,7,
				6,6,6,6,5,5,5,5,
				4,4,4,4,3,3,3,3,
				2,2,2,2,1,1,1,1
			};
			auto lmd1 = [](int i, int j)->bool {return i > j; };

			kkli::sort(kkli::begin(arr1), kkli::end(arr1));
			EXPECT_EQ_ARR(arr1, comp1, 8);
			kkli::sort(kkli::begin(arr1), kkli::end(arr1), lmd1);
			EXPECT_EQ_ARR(arr1, comp2, 8);
			
			kkli::sort(kkli::begin(arr2), kkli::end(arr2));
			EXPECT_EQ_ARR(arr2, comp3, 40);
			kkli::sort(kkli::begin(arr2), kkli::end(arr2), lmd1);
			EXPECT_EQ_ARR(arr2, comp4, 40);
		}
	}
}