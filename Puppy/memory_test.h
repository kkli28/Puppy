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
		using kkli::string;
		using kkli::shared_ptr;

		//前置声明
		void test_uninitialized_x();
		void test_shared_ptr_member_function();
		void test_shared_ptr_non_member_function();
		void test_weak_ptr();
		void test_unique_ptr();

		//整体测试
		void test() {
			test_uninitialized_x();
			test_shared_ptr_member_function();
			test_shared_ptr_non_member_function();
			//test_weak_ptr();
			//test_unique_ptr();
		}

		//测试 uninitialized_x
		void test_uninitialized_x() {
			cout << "\ntest_uninitalized_x()" << endl;

			int arr[8] = { 1,2,3,4,5,6,7,8 };

			//uninitialized_copy(first, last, dest)
			kkli::allocator<int> alloc1;
			auto ptr1 = alloc1.allocate(8);
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

			//下方待测函数需要使用的数据
			string str1[4]{ "abcd","efgh","123456","zczczczc" };			//to move
			string str2[4]{ "abcd","efgh","123456","zczczczc" };			//to move
			const string comp[4]{ "abcd","efgh","123456","zczczczc" };		//to compare

			kkli::allocator<string> alloc2;
			auto ptr2 = alloc2.allocate(4);
			auto ptr3 = alloc2.allocate(4);
			auto ptr4 = alloc2.allocate(4);
			auto ptr5 = alloc2.allocate(4);

			//uninitialized_move
			kkli::uninitialized_move(str1, str1 + 4, ptr2);
			EXPECT_EQ_ARR(ptr2, comp, 4);

			//uninitialized_move_n
			kkli::uninitialized_move_n(str2, 4, ptr3);
			EXPECT_EQ_ARR(ptr3, comp, 4);

			//uninitialized_default_construct
			kkli::uninitialized_default_construct(ptr4, ptr4 + 4);
			EXPECT_EQ_NVALS(ptr4, 4, "");

			//uninitialized_default_construct
			kkli::uninitialized_default_construct_n(ptr5, 4);
			EXPECT_EQ_NVALS(ptr5, 4, "");

			//destroy_at
			kkli::destroy_at(ptr2);			//析构ptr2的第一个元素

			//destroy
			kkli::destroy(ptr2+1 , ptr2 + 4);	//析构ptr2的后三个元素

			//destroy_n
			kkli::destroy_n(ptr3, 4);		//析构ptr3中4个元素
		}

		//测试 shared_ptr 成员函数
		void test_shared_ptr_member_function() {
			cout << "\ntest_shared_ptr_member_function()" << endl;

			auto deleter = [](const int* ptr) {delete[] ptr; };
			int comp1[4]{ 0,1,2,3 };
			int comp2[8]{ 4,5,6,7,8,9,10,11 };

			//constructor
			shared_ptr<int> sp1;		//shared_ptr()
			EXPECT_EQ_VAL(sp1.get(), nullptr);
			EXPECT_EQ_VAL(sp1.use_count(), 1);

			shared_ptr<int> sp2(nullptr);	//shared_ptr(nullptr)
			EXPECT_EQ_VAL(sp2.get(), nullptr);
			EXPECT_EQ_VAL(sp2.use_count(), 1);

			shared_ptr<int> sp3(new int(1));	//shared_ptr(ptr)
			EXPECT_EQ_VAL(*sp3, 1);
			EXPECT_EQ_VAL(sp3.use_count(), 1);

			shared_ptr<int, decltype(deleter)> sp4(new int[4], deleter); //shared_ptr(ptr, d)
			for (int i = 0; i < 4; ++i)
				sp4.get()[i] = i;
			EXPECT_EQ_ARR(sp4.get(), comp1, 4);
			EXPECT_EQ_VAL(sp4.use_count(), 1);

			shared_ptr<int, decltype(deleter)> sp5(nullptr, deleter);	//shared_ptr(nullptr, d)
			EXPECT_EQ_VAL(sp5.get(), nullptr);
			EXPECT_EQ_VAL(sp5.use_count(), 1);

			shared_ptr<int> sp6(new int(2));
			shared_ptr<int> sp7(sp6);		//shared_ptr(rhs)
			EXPECT_EQ_VAL(sp6.get(), sp7.get());
			EXPECT_EQ_VAL(*sp7, 2);
			EXPECT_EQ_VAL(sp6.use_count(), 2);
			EXPECT_EQ_VAL(sp7.use_count(), 2);

			shared_ptr<int> sp8(std::move(sp7));		//shared_ptr(&&rhs)
			EXPECT_EQ_VAL(*sp8, 2);
			EXPECT_EQ_VAL(sp8.use_count(), 2);
			EXPECT_EQ_VAL(sp7.get(), nullptr);
			EXPECT_EQ_VAL(sp7.use_count(), 1);

			//shared_ptr(weak_ptr<U>)
			//shared_ptr(unique_ptr<U>)

			//reset
			sp3.reset();
			EXPECT_EQ_VAL(sp3.get(), nullptr);
			EXPECT_EQ_VAL(sp3.use_count(), 1);

			sp3.reset(new int(2));
			EXPECT_EQ_VAL(*sp3, 2);
			EXPECT_EQ_VAL(sp3.use_count(), 1);

			//swap
			shared_ptr<int, decltype(deleter)> sp9(new int[8], deleter);
			for (int i = 4; i < 12; ++i)
				sp9.get()[i - 4] = i;
			swap(sp4, sp9);
			EXPECT_EQ_ARR(sp4.get(), comp2, 8);
			EXPECT_EQ_ARR(sp9.get(), comp1, 4);
			EXPECT_EQ_VAL(sp4.use_count(), 1);
			EXPECT_EQ_VAL(sp9.use_count(), 1);

			//operator []
			EXPECT_EQ_VAL(sp9[0], 0);
			EXPECT_EQ_VAL(sp9[1], 1);
			EXPECT_EQ_VAL(sp9[2], 2);
			EXPECT_EQ_VAL(sp9[3], 3);

			//unique
			EXPECT_EQ_VAL(sp4.unique(), true);
			EXPECT_EQ_VAL(sp9.unique(), true);

			//operator bool
			EXPECT_EQ_VAL(bool(sp4), true);
			EXPECT_EQ_VAL(bool(sp9), true);

			//get_deleter
			int* new_arr = new int[4]{ 1,2,3,4 };
			sp9.get_deleter()(new_arr);

		}

		//测试 shared_ptr 非成员函数
		void test_shared_ptr_non_member_function() {
			cout << "\ntest_shared_ptr_non_member_function()" << endl;

			auto deleter = [](const int* ptr) {delete[] ptr; };
			int comp1[4]{ 0,1,2,3 };
			int comp2[8]{ 4,5,6,7,8,9,10,11 };

			//make_shared
			shared_ptr<int> sp1 = kkli::make_shared<int>(1);
			EXPECT_EQ_VAL(*sp1, 1);
			EXPECT_EQ_VAL(sp1.use_count(), 1);
		}
	}
}