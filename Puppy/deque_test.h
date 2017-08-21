#pragma once

#include "stdafx.h"
#include "test.h"
#include "deque.h"

namespace test {
	namespace deque_test {
		using std::cout;
		using std::endl;
		using kkli::deque;

		//前置声明
		void test_constructor();
		void test_op_assign();			//operator=
		void test_assign();
		void test_at();
		void test_op_square_bracket();	//operator[]
		void test_front_and_back();
		void test_begin_and_end();
		void test_rbegin_and_rend();
		void test_insert();
		void test_erase();
		void test_resize();
		void test_empty();
		void test_size();
		void test_clear();
		void test_push_front();
		void test_push_back();
		void test_pop_front();
		void test_pop_back();
		void test_swap();
		void test_operators();

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "            deque.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			//test_op_assign();
			//test_assign();
			//test_at();
			//test_op_square_bracket();
			//test_front_and_back();
			//test_begin_and_end();
			//test_rbegin_and_rend();
			//test_insert();
			//test_erase();
			//test_resize();
			//test_empty();
			//test_size();
			//test_clear();
			//test_push_front();
			//test_push_back();
			//test_pop_front();
			//test_pop_back();
			//test_swap();
			//test_operators();
		}

		//测试 constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			deque<int> d1; //deque()
			EXPECT_EQ_VAL(d1.empty(), true);

			deque<int> d2(4, 1); //deque(count, value)
			deque<int> d3(12, 2);
			deque<int> d4(100, 3);
			EXPECT_EQ_ITERVAL(d2.begin(), d2.end(), 1);
			EXPECT_EQ_VAL(d2.size(), 4);
			EXPECT_EQ_ITERVAL(d3.begin(), d3.end(), 2);
			EXPECT_EQ_VAL(d3.size(), 12);
			EXPECT_EQ_ITERVAL(d4.begin(), d4.end(), 3);
			EXPECT_EQ_VAL(d4.size(), 100);

			deque<int> d5(17); //deque(count)
			EXPECT_EQ_ITERVAL(d5.begin(), d5.end(), 0);
			EXPECT_EQ_VAL(d5.size(), 17);

			deque<int> d6{ 1,2,3,4 }; //deque(init)
			EXPECT_EQ_ITERLIST(d6.begin(), d6.end(), { 1, 2, 3, 4 });
			EXPECT_EQ_VAL(d6.size(), 4);
			deque<int> d7{ 1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4, };
			EXPECT_EQ_ITERLIST(d6.begin(), d6.end(), { 1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4, });
			EXPECT_EQ_VAL(d7.size(), 20);

			deque<int> d8(d6); //deque(rhs);
			deque<int> d9(d7);
			EXPECT_EQ_ITERLIST(d8.begin(), d8.end(), { 1, 2, 3, 4 });
			EXPECT_EQ_VAL(d8.size(), 4);
			EXPECT_EQ_ITERLIST(d9.begin(), d9.end(), { 1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4, });
			EXPECT_EQ_VAL(d9.size(), 20);

			deque<int> d10(std::move(d6)); //deque(&&rhs)
			deque<int> d11(std::move(d7));
			EXPECT_EQ_ITERLIST(d10.begin(), d10.end(), { 1, 2, 3, 4 });
			EXPECT_EQ_VAL(d10.size(), 4);
			EXPECT_EQ_ITERLIST(d11.begin(), d11.end(), { 1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4, });
			EXPECT_EQ_VAL(d11.size(), 20);
		}
	}
}