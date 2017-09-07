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

		//«∞÷√…˘√˜
		void test_is_heap();
		void test_is_heap_until();
		void test_push_heap();
		void test_pop_heap();
		void test_sort_heap();
		void test_make_heap_normal();
		void test_make_heap_pred();
		void test_make_heap() {
			cout << "test: make_heap()" << endl;
			test_make_heap_normal();
			test_make_heap_pred();
		}

		//≤ø∑÷≤‚ ‘ part7
		void test_part7() {
			test_is_heap();
			test_is_heap_until();
			test_make_heap();
			test_push_heap();
			test_pop_heap();
			test_sort_heap();
		}

		//≤‚ ‘ is_heap
		void test_is_heap() {
			cout << "test: is_heap()" << endl;

			int arr1[4] = { 7,4,2,1 };
			int arr2[4] = { 7,4,2,5 };
			int arr3[8] = { 9,7,8,4,2,7,4,3 };
			int arr4[8] = { 9,7,8,9,2,7,4,3 };
			bool b0 = kkli::is_heap(arr1, arr1);
			bool b1 = kkli::is_heap(arr1, arr1 + 4);
			bool b2 = kkli::is_heap(arr2, arr2 + 4);
			bool b3 = kkli::is_heap(arr3, arr3 + 8);
			bool b4 = kkli::is_heap(arr4, arr4 + 8);
			EXPECT_EQ_VAL(b0, true);
			EXPECT_EQ_VAL(b1, true);
			EXPECT_EQ_VAL(b2, false);
			EXPECT_EQ_VAL(b3, true);
			EXPECT_EQ_VAL(b4, false);

			int arr5[4] = { 1,4,2,7 };
			int arr6[4] = { 1,4,2,2 };
			int arr7[8] = { 1,4,2,7,6,3,4,8 };
			int arr8[8] = { 1,4,2,7,2,3,1,8 };
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			bool b5 = kkli::is_heap(arr5, arr5 + 4, lmd1);
			bool b6 = kkli::is_heap(arr6, arr6 + 4, lmd1);
			bool b7 = kkli::is_heap(arr7, arr7 + 8, lmd1);
			bool b8 = kkli::is_heap(arr8, arr8 + 8, lmd1);
			EXPECT_EQ_VAL(b5, true);
			EXPECT_EQ_VAL(b6, false);
			EXPECT_EQ_VAL(b7, true);
			EXPECT_EQ_VAL(b8, false);
		}

		//≤‚ ‘ is_heap_until
		void test_is_heap_until() {
			cout << "test: is_heap_until()" << endl;


			int arr1[4] = { 7,4,2,1 };
			int arr2[4] = { 7,4,2,5 };
			int arr3[8] = { 9,7,8,4,2,7,4,3 };
			int arr4[8] = { 9,7,8,9,2,7,4,3 };
			auto iter0 = kkli::is_heap_until(arr1, arr1);
			auto iter1 = kkli::is_heap_until(arr1, arr1 + 4);
			auto iter2 = kkli::is_heap_until(arr2, arr2 + 4);
			auto iter3 = kkli::is_heap_until(arr3, arr3 + 8);
			auto iter4 = kkli::is_heap_until(arr4, arr4 + 8);
			EXPECT_EQ_VAL(iter0, arr1);
			EXPECT_EQ_VAL(iter1, arr1+4);
			EXPECT_EQ_VAL(*iter2, 5);
			EXPECT_EQ_VAL(iter3, arr3 + 8);
			EXPECT_EQ_VAL(*iter4, 9);

			int arr5[4] = { 1,4,2,7 };
			int arr6[4] = { 1,4,2,2 };
			int arr7[8] = { 1,4,2,7,6,3,4,8 };
			int arr8[8] = { 1,4,2,7,2,3,1,8 };
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			auto iter5 = kkli::is_heap_until(arr5, arr5 + 4, lmd1);
			auto iter6 = kkli::is_heap_until(arr6, arr6 + 4, lmd1);
			auto iter7 = kkli::is_heap_until(arr7, arr7 + 8, lmd1);
			auto iter8 = kkli::is_heap_until(arr8, arr8 + 8, lmd1);
			EXPECT_EQ_VAL(iter5, arr5 + 4);
			EXPECT_EQ_VAL(*iter6, 2);
			EXPECT_EQ_VAL(iter7, arr7 + 8);
			EXPECT_EQ_VAL(*iter8, 2);
		}

		//≤‚ ‘ make_heap_normal
		void test_make_heap_normal() {
			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,2,4 };
			int arr3[4] = { 4,3,2,1 };
			int arr4[8] = { 1,2,3,4,5,6,7,8 };
			int arr5[8] = { 1,3,5,7,2,6,4,8 };
			int arr6[8] = { 8,7,6,5,4,3,2,1 };
			int comp0[4] = { 1,2,3,4 };
			int comp1[4] = { 4,2,3,1 };
			int comp2[4] = { 4,3,2,1 };
			int comp4[8] = { 8,5,7,4,1,6,3,2 };
			int comp5[8] = { 8,7,6,3,2,5,4,1 };
			int comp6[8] = { 8,7,6,5,4,3,2,1 };

			kkli::make_heap(arr1, arr1);
			EXPECT_EQ_ARR(arr1, comp0, 4);

			kkli::make_heap(arr1, arr1 + 4);
			EXPECT_EQ_ARR(arr1, comp1, 4);
			
			kkli::make_heap(arr2, arr2 + 4);
			EXPECT_EQ_ARR(arr2, comp2, 4);

			kkli::make_heap(arr3, arr3 + 4);
			EXPECT_EQ_ARR(arr3, comp2, 4);

			kkli::make_heap(arr4, arr4 + 8);
			EXPECT_EQ_ARR(arr4, comp4, 8);

			kkli::make_heap(arr5, arr5 + 8);
			EXPECT_EQ_ARR(arr5, comp5, 8);

			kkli::make_heap(arr6, arr6 + 8);
			EXPECT_EQ_ARR(arr6, comp6, 8);
		}

		//≤‚ ‘ make_heap_pred
		void test_make_heap_pred() {
			int arr1[4] = { 1,2,3,4 };
			int arr2[4] = { 1,3,2,4 };
			int arr3[4] = { 4,3,2,1 };
			int arr4[8] = { 1,2,3,4,5,6,7,8 };
			int arr5[8] = { 1,3,5,7,2,6,4,8 };
			int arr6[8] = { 8,7,6,5,4,3,2,1 };
			int comp1[4] = { 1,2,3,4 };
			int comp2[4] = { 1,3,2,4 };
			int comp4[8] = { 1,2,3,4,5,6,7,8 };
			int comp5[8] = { 1,2,4,7,3,6,5,8 };
			int comp6[8] = { 1,4,2,5,8,3,6,7 };

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			kkli::make_heap(arr1, arr1 + 4, lmd1);
			EXPECT_EQ_ARR(arr1, comp1, 4);
			
			kkli::make_heap(arr2, arr2 + 4, lmd1);
			EXPECT_EQ_ARR(arr2, comp2, 4);

			kkli::make_heap(arr3, arr3 + 4, lmd1);
			EXPECT_EQ_ARR(arr3, comp2, 4);

			kkli::make_heap(arr4, arr4 + 8, lmd1);
			EXPECT_EQ_ARR(arr4, comp4, 8);

			kkli::make_heap(arr5, arr5 + 8, lmd1);
			EXPECT_EQ_ARR(arr5, comp5, 8);

			kkli::make_heap(arr6, arr6 + 8, lmd1);
			EXPECT_EQ_ARR(arr6, comp6, 8);
		}

		//≤‚ ‘ push_heap
		void test_push_heap() {
			cout << "test: push_heap()" << endl;

			int arr1[4] = { 3,2,1,4 };
			int arr2[4] = { 4,3,2,1 };
			int arr3[8] = { 1,2,3,4,5,6,7,8 };
			int comp1[4] = { 4,3,1,2 };
			int comp2[4] = { 4,3,2,1 };
			int comp3[4] = { 2,4,3,1 };

			int comp4[8] = { 2,1,3,4,5,6,7,8 };
			int comp5[8] = { 3,1,2,4,5,6,7,8 };
			int comp6[8] = { 4,3,2,1,5,6,7,8 };
			int comp7[8] = { 5,4,2,1,3,6,7,8 };
			int comp8[8] = { 6,4,5,1,3,2,7,8 };
			int comp9[8] = { 7,4,6,1,3,2,5,8 };
			int comp10[8] = { 8,7,6,4,3,2,5,1 };

			kkli::push_heap(arr1, arr1 + 4); //1 2 3 4
			EXPECT_EQ_ARR(arr1, comp1, 4);
			
			kkli::push_heap(arr2, arr2 + 4);
			EXPECT_EQ_ARR(arr2, comp2, 4);

			//arr3
			kkli::push_heap(arr3, arr3 + 2); //+2
			EXPECT_EQ_ARR(arr3, comp4, 8);
			kkli::push_heap(arr3, arr3 + 3); //+3
			EXPECT_EQ_ARR(arr3, comp5, 8);
			kkli::push_heap(arr3, arr3 + 4); //+4
			EXPECT_EQ_ARR(arr3, comp6, 8);
			kkli::push_heap(arr3, arr3 + 5); //+5
			EXPECT_EQ_ARR(arr3, comp7, 8);
			kkli::push_heap(arr3, arr3 + 6); //+6
			EXPECT_EQ_ARR(arr3, comp8, 8);
			kkli::push_heap(arr3, arr3 + 7); //+7
			EXPECT_EQ_ARR(arr3, comp9, 8);
			kkli::push_heap(arr3, arr3 + 8); //+8
			EXPECT_EQ_ARR(arr3, comp10, 8);

			//push_heap(first, last, comp)
		}

		//≤‚ ‘ pop_heap
		void test_pop_heap() {
			cout << "test: pop_heap()" << endl;

			int arr1[8] = { 1,2,3,4,5,6,7,8 };
			int comp1[8] = { 8,5,7,4,1,6,3,2 };
			int comp2[8] = { 7,5,6,4,1,2,3,8 };
			int comp3[8] = { 6,5,3,4,1,2,7,8 };
			int comp4[8] = { 5,4,3,2,1,6,7,8 };
			int comp5[8] = { 4,2,3,1,5,6,7,8 };
			int comp6[8] = { 3,2,1,4,5,6,7,8 };
			int comp7[8] = { 2,1,3,4,5,6,7,8 };
			int comp8[8] = { 1,2,3,4,5,6,7,8 };

			kkli::make_heap(arr1, arr1 + 8);
			EXPECT_EQ_ARR(arr1, comp1, 8);

			kkli::pop_heap(arr1, arr1 + 8);
			EXPECT_EQ_ARR(arr1, comp2, 8);

			kkli::pop_heap(arr1, arr1 + 7);
			EXPECT_EQ_ARR(arr1, comp3, 8);

			kkli::pop_heap(arr1, arr1 + 6);
			EXPECT_EQ_ARR(arr1, comp4, 8);

			kkli::pop_heap(arr1, arr1 + 5);
			EXPECT_EQ_ARR(arr1, comp5, 8);

			kkli::pop_heap(arr1, arr1 + 4);
			EXPECT_EQ_ARR(arr1, comp6, 8);

			kkli::pop_heap(arr1, arr1 + 3);
			EXPECT_EQ_ARR(arr1, comp7, 8);

			kkli::pop_heap(arr1, arr1 + 2);
			EXPECT_EQ_ARR(arr1, comp8, 8);

			kkli::pop_heap(arr1, arr1 + 1);
			EXPECT_EQ_ARR(arr1, comp8, 8);

			kkli::pop_heap(arr1, arr1);
			EXPECT_EQ_ARR(arr1, comp8, 8);

			//pop_heap(first, last, comp)
		}

		//≤‚ ‘ sort_heap
		void test_sort_heap() {
			cout << "test: sort_heap()" << endl;

			int arr1[8] = { 8,5,7,4,1,6,3,2 };
			int arr2[8] = { 8,6,7,4,3,5,1,2 };
			int comp1[8] = { 1,2,3,4,5,6,7,8 };

			kkli::sort_heap(arr1, arr1 + 8);
			EXPECT_EQ_ARR(arr1, comp1, 8);

			kkli::sort_heap(arr2, arr2 + 8);
			EXPECT_EQ_ARR(arr2, comp1, 8);
		}
	}
}