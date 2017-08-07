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
		using kkli::weak_ptr;
		using kkli::unique_ptr;

		//前置声明
		void test_uninitialized_x();
		void test_shared_ptr_member_function();
		void test_shared_ptr_non_member_function();
		void test_weak_ptr();
		void test_unique_ptr_member_function();
		void test_unique_ptr_non_member_function();

		//整体测试
		void test() {
			test_uninitialized_x();
			test_shared_ptr_member_function();
			test_shared_ptr_non_member_function();
			test_weak_ptr();
			test_unique_ptr_member_function();
			test_unique_ptr_non_member_function();
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

			//**** shared_ptr(weak_ptr<U>) ****
			//**** shared_ptr(unique_ptr<U>) ****

			//operator =(rhs)
			shared_ptr<int> sp9(new int(1));
			sp9 = sp2;
			EXPECT_EQ_VAL(sp9.get(), nullptr);
			EXPECT_EQ_VAL(sp9.use_count(), 2);
			sp9 = sp6;
			EXPECT_EQ_VAL(*sp9, 2);
			EXPECT_EQ_VAL(sp9.use_count(), 3);

			//**** operator =(rhs<U>) ****

			//operator =(&&rhs)
			shared_ptr<int, decltype(deleter)> sp10(new int(1), deleter);
			sp10 = std::move(sp5);
			EXPECT_EQ_VAL(sp10.get(), nullptr);
			EXPECT_EQ_VAL(sp10.use_count(), 1);
			EXPECT_EQ_VAL(sp5.get(), nullptr);
			EXPECT_EQ_VAL(sp5.use_count(), 1);
			shared_ptr<int,decltype(deleter)> sp_move1(new int(2), deleter);
			decltype(sp_move1) sp_move2 = sp_move1;
			sp10 = std::move(sp_move1);
			EXPECT_EQ_VAL(*sp10, 2);
			EXPECT_EQ_VAL(sp10.use_count(), 2);
			EXPECT_EQ_VAL(sp_move1.get(), nullptr);
			EXPECT_EQ_VAL(sp_move1.use_count(), 1);
			EXPECT_EQ_VAL(*sp_move2, 2);
			EXPECT_EQ_VAL(sp_move2.use_count(), 2);
			
			//**** operator =(rhs<U>) ****

			//**** operator =(unique_ptr<U>) ****

			//reset
			sp3.reset();
			EXPECT_EQ_VAL(sp3.get(), nullptr);
			EXPECT_EQ_VAL(sp3.use_count(), 1);

			sp3.reset(new int(2));
			EXPECT_EQ_VAL(*sp3, 2);
			EXPECT_EQ_VAL(sp3.use_count(), 1);

			//swap
			shared_ptr<int, decltype(deleter)> sp11(new int[8], deleter);
			for (int i = 4; i < 12; ++i)
				sp11.get()[i - 4] = i;
			swap(sp4, sp11);
			EXPECT_EQ_ARR(sp4.get(), comp2, 8);
			EXPECT_EQ_ARR(sp11.get(), comp1, 4);
			EXPECT_EQ_VAL(sp4.use_count(), 1);
			EXPECT_EQ_VAL(sp11.use_count(), 1);

			//operator []
			EXPECT_EQ_VAL(sp11[0], 0);
			EXPECT_EQ_VAL(sp11[1], 1);
			EXPECT_EQ_VAL(sp11[2], 2);
			EXPECT_EQ_VAL(sp11[3], 3);

			//unique
			EXPECT_EQ_VAL(sp4.unique(), true);
			EXPECT_EQ_VAL(sp11.unique(), true);

			//operator bool
			EXPECT_EQ_VAL(bool(sp4), true);
			EXPECT_EQ_VAL(bool(sp11), true);

			//**** owner_before ****

			//**** get_deleter ****
		}

		//测试 shared_ptr 非成员函数
		void test_shared_ptr_non_member_function() {
			cout << "\ntest_shared_ptr_non_member_function()" << endl;

			auto deleter = [](const int* ptr) {delete[] ptr; };

			//make_shared
			shared_ptr<int> sp1 = kkli::make_shared<int>(1);
			EXPECT_EQ_VAL(*sp1, 1);
			EXPECT_EQ_VAL(sp1.use_count(), 1);

			//**** xxxx_pointer_cast ****
			//**** get_allocator ****

			//operator ==
			shared_ptr<int> sp2(sp1);
			shared_ptr<int> sp3(new int(2));
			shared_ptr<int> sp4(nullptr);

			EXPECT_EQ_VAL(sp1 == sp1, true);
			EXPECT_EQ_VAL(sp1 == sp2, true);
			EXPECT_EQ_VAL(sp1 == sp3, false);
			EXPECT_EQ_VAL(sp1 == sp4, false);

			EXPECT_EQ_VAL(sp2 == sp1, true);
			EXPECT_EQ_VAL(sp2 == sp2, true);
			EXPECT_EQ_VAL(sp2 == sp3, false);
			EXPECT_EQ_VAL(sp2 == sp4, false);

			EXPECT_EQ_VAL(sp3 == sp1, false);
			EXPECT_EQ_VAL(sp3 == sp2, false);
			EXPECT_EQ_VAL(sp3 == sp3, true);
			EXPECT_EQ_VAL(sp3 == sp4, false);
			
			EXPECT_EQ_VAL(sp4 == sp1, false);
			EXPECT_EQ_VAL(sp4 == sp2, false);
			EXPECT_EQ_VAL(sp4 == sp3, false);
			EXPECT_EQ_VAL(sp4 == sp4, true);

			//operator !=
			EXPECT_EQ_VAL(sp1 != sp1, false);
			EXPECT_EQ_VAL(sp1 != sp2, false);
			EXPECT_EQ_VAL(sp1 != sp3, true);
			EXPECT_EQ_VAL(sp1 != sp4, true);

			EXPECT_EQ_VAL(sp2 != sp1, false);
			EXPECT_EQ_VAL(sp2 != sp2, false);
			EXPECT_EQ_VAL(sp2 != sp3, true);
			EXPECT_EQ_VAL(sp2 != sp4, true);

			EXPECT_EQ_VAL(sp3 != sp1, true);
			EXPECT_EQ_VAL(sp3 != sp2, true);
			EXPECT_EQ_VAL(sp3 != sp3, false);
			EXPECT_EQ_VAL(sp3 != sp4, true);

			EXPECT_EQ_VAL(sp4 != sp1, true);
			EXPECT_EQ_VAL(sp4 != sp2, true);
			EXPECT_EQ_VAL(sp4 != sp3, true);
			EXPECT_EQ_VAL(sp4 != sp4, false);

			//**** operator < <= > >= ****

			//operator << ---- success
			/*
			cout << sp1 << endl;
			cout << sp2 << endl;
			cout << sp3 << endl;
			cout << sp4 << endl;
			*/
		}

		//测试 weak_ptr
		void test_weak_ptr() {
			cout << "\ntest_weak_ptr()" << endl;

			//shared_ptr
			shared_ptr<int> sp1 = kkli::make_shared<int>(1);
			shared_ptr<int> sp2(new int(2));
			shared_ptr<int> sp3(sp2);

			//constructor + use_count + expired
			weak_ptr<int> wp1;		//weak_ptr()
			EXPECT_EQ_VAL(wp1.use_count(), 0);
			EXPECT_EQ_VAL(wp1.expired(), true);

			weak_ptr<int> wp2(sp1); //weak_ptr(sp)
			EXPECT_EQ_VAL(wp2.use_count(), 1);
			EXPECT_EQ_VAL(wp2.expired(), false);

			weak_ptr<int> wp3(wp2);		//weak_ptr(rhs)
			EXPECT_EQ_VAL(wp3.use_count(), 1);
			
			weak_ptr<int> wp_move1(wp3);		//weak_ptr(&&rhs)
			weak_ptr<int> wp4(std::move(wp_move1));
			EXPECT_EQ_VAL(wp4.use_count(), 1);
			EXPECT_EQ_VAL(wp_move1.use_count(), 0);
			EXPECT_EQ_VAL(wp_move1.expired(), true);

			//**** weak_ptr(rhs<U>) ****

			//operator =
			weak_ptr<int> wp5;
			wp5 = wp4;		//operator =(rhs)
			EXPECT_EQ_VAL(wp5.use_count(), 1);
			
			weak_ptr<int> wp_move2(sp2);
			wp5 = std::move(wp_move2);		//operator =(&&rhs)
			EXPECT_EQ_VAL(wp5.use_count(), 2);
			EXPECT_EQ_VAL(wp_move2.use_count(), 0);

			//**** operator =(rhs<U>) ****
			//**** operator =(&&rhs<U>) ****

			weak_ptr<int> wp6;
			wp6 = sp2;		//operator =(sp)
			EXPECT_EQ_VAL(wp6.use_count(), 2);
			
			//reset
			weak_ptr<int> wp7(sp2);
			EXPECT_EQ_VAL(wp7.use_count(), 2);
			wp7.reset();
			EXPECT_EQ_VAL(wp7.use_count(), 0);
			EXPECT_EQ_VAL(wp7.expired(), true);

			//swap
			weak_ptr<int> wp8;
			weak_ptr<int> wp9(sp2);
			wp8.swap(wp9);		//lhs.swap(rhs)
			EXPECT_EQ_VAL(wp8.use_count(), 2);
			EXPECT_EQ_VAL(wp9.use_count(), 0);
			swap(wp8, wp9);		//swap(lhs, rhs)
			EXPECT_EQ_VAL(wp8.use_count(), 0);
			EXPECT_EQ_VAL(wp9.use_count(), 2);

			//lock
			weak_ptr<int> wp10(sp2);
			shared_ptr<int> sp4 = wp10.lock();
			EXPECT_EQ_VAL(sp4.use_count(), 3);
			EXPECT_EQ_VAL(*sp4, 2);
		}

		//测试 unique_ptr 成员函数
		void test_unique_ptr_member_function() {
			cout << "\ntest_unique_ptr_member_function()" << endl;

			auto deleter = [](const int* ptr) {delete[] ptr; };

			//constructor + get + operator*
			unique_ptr<int> up1;		//unique_ptr()
			EXPECT_EQ_VAL(up1.get(), nullptr);

			unique_ptr<int> up2(nullptr); //unique_ptr(nullptr)
			EXPECT_EQ_VAL(up2.get(), nullptr);
			
			unique_ptr<int> up3(new int(1)); //unique_ptr(ptr)
			EXPECT_EQ_VAL(*up3, 1);

			unique_ptr<int, decltype(deleter)> up4(new int(2), deleter); //unique_ptr(ptr, d)
			EXPECT_EQ_VAL(*up4, 2);

			unique_ptr<int> up_move1(new int(3));
			unique_ptr<int> up5(std::move(up_move1));
			EXPECT_EQ_VAL(*up5, 3);
			EXPECT_EQ_VAL(up_move1.get(), nullptr);

			//operator =
			unique_ptr<int> up6;
			unique_ptr<int> up7(new int(1));
			up6 = std::move(up7);		//operator =(&&rhs)
			EXPECT_EQ_VAL(*up6, 1);
			EXPECT_EQ_VAL(up7.get(), nullptr);
			
			up6 = nullptr;	//operator =(nullptr)
			EXPECT_EQ_VAL(up6.get(), nullptr);

			//**** operator =(rhs<U,D>) ****

			//release
			unique_ptr<int> up8(new int(1));
			int* pi1 = up8.release();
			EXPECT_EQ_VAL(up8.get(), nullptr);
			EXPECT_EQ_VAL(*pi1, 1);

			//reset
			unique_ptr<int> up9(new int(1));
			up9.reset(new int(2));
			EXPECT_EQ_VAL(*up9, 2);
			up9.reset(nullptr);
			EXPECT_EQ_VAL(up9.get(), nullptr);

			//swap
			unique_ptr<int> up10(new int(1));
			unique_ptr<int> up11(new int(2));
			up10.swap(up11);	//lhs.swap(rhs)
			EXPECT_EQ_VAL(*up10, 2);
			EXPECT_EQ_VAL(*up11, 1);

			//operator bool
			EXPECT_EQ_VAL(bool(up10), true);

			//operator ->
			EXPECT_EQ_VAL(up10.get(), up10.operator->());

			//operator []
			unique_ptr<int, decltype(deleter)> up12(new int[4]{ 0,1,2,3 }, deleter);
			EXPECT_EQ_VAL(up12[0], 0);
			EXPECT_EQ_VAL(up12[1], 1);
			EXPECT_EQ_VAL(up12[2], 2);
			EXPECT_EQ_VAL(up12[3], 3);
		}

		//测试 unique_ptr 非成员函数
		void test_unique_ptr_non_member_function() {
			cout << "\ntest_unique_ptr_non_member_function()" << endl;

			auto deleter = [](const int* ptr) {delete[] ptr; };

			//make_unique
			unique_ptr<int> up1 = kkli::make_unique<int>(1); //make_unique
			EXPECT_EQ_VAL(*up1, 1);
			
			//operator ==
			unique_ptr<int> up2;
			unique_ptr<int> up3(new int(1));
			unique_ptr<int> up4(new int(2));

			EXPECT_EQ_VAL(up2 == up2, true);
			EXPECT_EQ_VAL(up2 == up3, false);
			EXPECT_EQ_VAL(up2 == up4, false);
			EXPECT_EQ_VAL(up2 == nullptr, true);
			EXPECT_EQ_VAL(nullptr == up2, true);

			EXPECT_EQ_VAL(up3 == up2, false);
			EXPECT_EQ_VAL(up3 == up3, true);
			EXPECT_EQ_VAL(up3 == up4, false);
			EXPECT_EQ_VAL(up3 == nullptr, false);
			EXPECT_EQ_VAL(nullptr == up3, false);

			EXPECT_EQ_VAL(up4 == up2, false);
			EXPECT_EQ_VAL(up4 == up3, false);
			EXPECT_EQ_VAL(up4 == up4, true);
			EXPECT_EQ_VAL(up4 == nullptr, false);
			EXPECT_EQ_VAL(nullptr == up4, false);

			//**** operator < <= > >= ****

			//swap
			swap(up2, up3);
			EXPECT_EQ_VAL(*up2, 1);
			EXPECT_EQ_VAL(up3.get(), nullptr);
		}
	}
}