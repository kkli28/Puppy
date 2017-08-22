#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "vector.h"
#include "priority_queue.h"

namespace test {
	namespace priority_queue_test {
		using std::cout;
		using std::endl;
		using kkli::vector;
		using kkli::priority_queue;

		//前置声明
		void test_constructor();
		void test_op_assign();  //operator =
		void test_get_container();
		void test_get_compare();
		void test_top();
		void test_empty();
		void test_size();
		void tet_push();
		void test_pop();
		void test_swap();

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          priority_queue.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			//test_op_assign();
			//test_get_container();
			//test_get_compare();
			//test_top();
			//test_empty();
			//test_size();
			//tet_push();
			//test_pop();
			//test_swap();
		}

		//测试 constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			priority_queue<int> p1; //priority_queue()
			EXPECT_EQ_VAL(p1.size(), 0);
			EXPECT_EQ_VAL(p1.empty(), true);

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			priority_queue<int, kkli::vector<int>, decltype(lmd1) > p2(lmd1); //priority_queue(comp)
			EXPECT_EQ_VAL(p1.size(), 0);
			EXPECT_EQ_VAL(p1.empty(), true);
			for (int i = 0; i < 12; ++i) p2.push(rand() % 12);
			auto cont2 = p2.get_container();
			EXPECT_EQ_VAL(kkli::is_heap(cont2.begin(), cont2.end(), lmd1), true);

			vector<int> vec1{ 1,8,7,6,2,3,4,5 };
			priority_queue<int> p3(vec1); //priority_queue(c)
			auto cont3 = p3.get_container();
			EXPECT_EQ_VAL(kkli::is_heap(cont3.begin(), cont3.end()), true);

			priority_queue<int, kkli::vector<int>, decltype(lmd1)> p4(lmd1, vec1); //priority_queue(comp, cont)
			auto cont4 = p4.get_container();
			EXPECT_EQ_VAL(kkli::is_heap(cont4.begin(), cont4.end(), lmd1), true);

			priority_queue<int> p5(p3); //priority_queue(rhs)
			auto cont5 = p5.get_container();
			EXPECT_EQ_VAL(kkli::is_heap(cont5.begin(), cont5.end()), true);
			
			priority_queue<int, kkli::vector<int>, decltype(lmd1)> p6(std::move(p4)); //priority_queue(&&rhs)
			auto cont6 = p6.get_container();
			EXPECT_EQ_VAL(kkli::is_heap(cont6.begin(), cont6.end(), p6.get_compare()), true);
		}
	}
}