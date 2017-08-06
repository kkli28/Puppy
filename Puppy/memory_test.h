#pragma once

#include "stdafx.h"
#include "vector.h"
#include "string.h"
#include "memory.h"
#include "test.h"

namespace test {
	namespace memory_test {

		using std::cin;
		using std::cout;
		using std::endl;

		//前置声明
		void test_uninitialized_x();
		void test_shared_ptr();
		void test_weak_ptr();
		void test_unique_ptr();

		//整体测试
		void test() {
			test_uninitialized_x();
			//test_shared_ptr();
			//test_weak_ptr();
			//test_unique_ptr();
		}

		//测试 uninitialized_x
		void test_uninitialized_x() {
			cout << "\ntest_uninitalized_x()" << endl;

			int arr[8] = { 1,2,3,4,5,6,7,8 };

			//uninitialized_copy(first, last, dest)
			kkli::allocator<int> alloc;
			auto ptr1 = alloc.allocate(8);
			kkli::uninitialized_copy(arr, arr + 8, ptr1);
			EXPECT_EQ_ARR(arr, ptr1, 8);

			//uninitialized_copy_n(first, count, dest)
			kkli::uninitialized_copy_n(arr, 8, ptr1);
			EXPECT_EQ_ARR(arr, ptr1, 8);

			//uninitialized_fill
			kkli::uninitialized_fill(ptr1, ptr1 + 8, 1);
			EXPECT_EQ_NVALS(ptr1, 8, 1);

			//uninitialized_fill_n
			kkli::uninitialized_fill_n(ptr1, 8, 2);
			EXPECT_EQ_NVALS(ptr1, 8, 2);

			//uninitialized_move
			//kkli::uninitialized_move
			//TODO: 
		}
	}
}