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

		//«∞÷√…˘√˜
		void test_constructor();
		void test_op_assign();  //operator =
		void test_get_container();
		void test_get_compare();
		void test_top();
		void test_empty();
		void test_size_push_pop();
		void test_swap();

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          priority_queue.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_op_assign();
			test_get_container();
			test_get_compare();
			test_top();
			test_empty();
			test_size_push_pop();
			test_swap();
		}

		//≤‚ ‘ constructor
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

		//≤‚ ‘ operator=
		void test_op_assign() {
			cout << "test: operator=()" << endl;

			priority_queue<int> p1;
			priority_queue<int> p2;
			priority_queue<int> p3;
			for (int i = 8; i > 0; --i) p1.push(i);
			for (int i = 1; i < 5; ++i) p2.push(i);

			p3 = p1; //operator=(rhs)
			auto cont1 = p3.get_container();
			EXPECT_EQ_VAL(p3.size(), 8);
			EXPECT_EQ_VAL(kkli::is_heap(cont1.begin(), cont1.end()), true);

			p3 = std::move(p2); //operator=(&&rhs)
			auto cont2 = p3.get_container();
			EXPECT_EQ_VAL(p3.size(), 4);
			EXPECT_EQ_VAL(kkli::is_heap(cont2.begin(), cont2.end()), true);
		}

		//≤‚ ‘ get_container
		void test_get_container() {
			cout << "test: get_container()" << endl;

			priority_queue<int> p1;
			priority_queue<int> p2;
			priority_queue<int> p3;
			for (int i = 8; i > 0; --i) p2.push(i);
			for (int i = 1; i < 5; ++i) p3.push(i);

			auto cont1 = p1.get_container();
			EXPECT_EQ_VAL(cont1.empty(), true);

			auto cont2 = p2.get_container();
			EXPECT_EQ_ITERLIST(cont2.begin(), cont2.end(), { 8,7,6,5,4,3,2,1 });

			auto cont3 = p3.get_container();
			EXPECT_EQ_ITERLIST(cont3.begin(), cont3.end(), { 4,3,2,1 });
		}

		//≤‚ ‘ get_compare
		void test_get_compare() {
			cout << "test: get_compare()" << endl;

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			priority_queue<int> p1;
			priority_queue<int, kkli::vector<int>, decltype(lmd1)> p2(lmd1);

			auto comp1 = p1.get_compare(); //<
			auto comp2 = p2.get_compare(); //>
			EXPECT_EQ_VAL(comp1(1, 2), true);
			EXPECT_EQ_VAL(comp1(2, 1), false);
			EXPECT_EQ_VAL(comp2(1, 2), false);
			EXPECT_EQ_VAL(comp2(2, 1), true);
		}

		//≤‚ ‘ top
		void test_top() {
			cout << "test: top()" << endl;

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			priority_queue<int> p1;
			priority_queue<int, kkli::vector<int>, decltype(lmd1)> p2(lmd1);

			p1.push(1);
			EXPECT_EQ_VAL(p1.top(), 1);
			p1.push(2);
			EXPECT_EQ_VAL(p1.top(), 2);
			for (int i = 3; i < 9; ++i) p1.push(i);
			EXPECT_EQ_VAL(p1.top(), 8);

			p2.push(8);
			EXPECT_EQ_VAL(p2.top(), 8);
			p2.push(7);
			EXPECT_EQ_VAL(p2.top(), 7);
			for (int i = 6; i > 0; --i) p2.push(i);
			EXPECT_EQ_VAL(p2.top(), 1);
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			priority_queue<int> p1;
			EXPECT_EQ_VAL(p1.empty(), true);
			p1.push(1);
			EXPECT_EQ_VAL(p1.empty(), false);
			p1.pop();
			EXPECT_EQ_VAL(p1.empty(), true);
		}

		//≤‚ ‘ size & push & pop
		void test_size_push_pop() {
			cout << "test: size()" << endl;
			cout << "test: push()" << endl;
			cout << "test: pop()" << endl;

			auto lmd1 = [](int i, int j)->bool {return i > j; };
			priority_queue<int> p1;
			priority_queue<int, kkli::vector<int>, decltype(lmd1)> p2(lmd1);

			EXPECT_EQ_VAL(p1.size(), 0);
			p1.push(1);
			EXPECT_EQ_VAL(p1.size(), 1);
			for (int i = 0; i < 4; ++i) p1.push(i);
			EXPECT_EQ_VAL(p1.size(), 5);
			for (int i = 0; i < 3; ++i) p1.pop();
			EXPECT_EQ_VAL(p1.size(), 2);

			EXPECT_EQ_VAL(p2.size(), 0);
			for (int i = 0; i < 10; ++i) p2.push(i);
			EXPECT_EQ_VAL(p2.size(), 10);
			for (int i = 0; i < 6; ++i) p2.pop();
			EXPECT_EQ_VAL(p2.size(), 4);
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			priority_queue<int> p1;
			priority_queue<int> p2;
			priority_queue<int> p3;
			for (int i = 4; i > 0; --i) p2.push(i);
			for (int i = 8; i > 0; --i) p3.push(i);

			p1.swap(p2); //swap(rhs)
			auto cont1 = p1.get_container();
			auto cont2 = p2.get_container();
			EXPECT_EQ_ITERLIST(cont1.begin(), cont1.end(), { 4,3,2,1 });
			EXPECT_EQ_VAL(cont2.empty(), true);

			p1.swap(p3);
			cont1 = p1.get_container();
			auto cont3 = p3.get_container();
			EXPECT_EQ_ITERLIST(cont1.begin(), cont1.end(), { 8,7,6,5,4,3,2,1 });
			EXPECT_EQ_ITERLIST(cont3.begin(), cont3.end(), { 4,3,2,1 });

			kkli::swap(p2, p3); //swap(lhs, rhs)
			cont2 = p2.get_container();
			cont3 = p3.get_container();
			EXPECT_EQ_ITERLIST(cont2.begin(), cont2.end(), { 4,3,2,1 });
			EXPECT_EQ_VAL(cont3.empty(), true);
		}
	}
}