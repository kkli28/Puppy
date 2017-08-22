#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "queue.h"
#include "vector.h"

namespace test {
	namespace queue_test {

		using std::cout;
		using std::endl;
		using kkli::queue;
		using kkli::vector;

		//«∞÷√…˘√˜
		void test_constructor();
		void test_op_assign();  //operator =
		void test_get_container();
		void test_front_and_back();
		void test_empty();
		void test_size_push_pop();
		void test_swap();

		void test_op1(); //operator==
		void test_op2(); //operator<
		void test_op3(); //operator>

		void test_operators() { //operator(==/!=/<...)
			cout << "test: operator(==/!=/<...)" << endl;
			test_op1();
			test_op2();
			test_op3();
		}

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          queue.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_op_assign();
			test_get_container();
			test_front_and_back();
			test_empty();
			test_size_push_pop();
			test_swap();
			test_operators();
		}

		//≤‚ ‘ constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			queue<int> q1; //queue()
			EXPECT_EQ_VAL(q1.empty(), true);
			EXPECT_EQ_VAL(q1.size(), 0);

			vector<int> vec1{ 1,2,3,4 };
			queue<int, vector<int>> q2(vec1); //queue(c)
			EXPECT_EQ_VAL(q2.front(), 1);
			EXPECT_EQ_VAL(q2.back(), 4);
			EXPECT_EQ_VAL(q2.size(), 4);

			queue<int> q3;
			for (int i = 0; i < 4; ++i) q3.push(i);
			queue<int> q4;
			q4 = q3; //queue(rhs)
			EXPECT_EQ_VAL(q4.front(), 0);
			EXPECT_EQ_VAL(q4.back(), 3);
			EXPECT_EQ_VAL(q4.size(), 4);

			queue<int> q5(std::move(q3)); //queue(&&rhs);
			EXPECT_EQ_VAL(q5.front(), 0);
			EXPECT_EQ_VAL(q5.back(), 3);
			EXPECT_EQ_VAL(q5.size(), 4);
		}

		//≤‚ ‘ operator=
		void test_op_assign() {
			cout << "test: operator=" << endl;

			queue<int> d1;
			queue<int> d2;
			queue<int> d3;
			for (int i = 0; i < 4; ++i) d2.push(i);
			for (int i = 4; i < 10; ++i) d3.push(i);

			d1 = d2; //operator=(rhs)
			EXPECT_EQ_VAL(d1.front(), 0);
			EXPECT_EQ_VAL(d1.back(), 3);
			EXPECT_EQ_VAL(d1.size(), 4);
			
			d1 = std::move(d3); //operator=(&&rhs)
			EXPECT_EQ_VAL(d1.front(), 4);
			EXPECT_EQ_VAL(d1.back(), 9);
			EXPECT_EQ_VAL(d1.size(), 6);
		}

		//≤‚ ‘ front & back
		void test_front_and_back() {
			queue<int> d1;
			queue<int, vector<int>> d2;
			for (int i = 0; i < 4; ++i) d1.push(i), d2.push(i);

			cout << "test: front()" << endl;
			EXPECT_EQ_VAL(d1.front(), 0);
			EXPECT_EQ_VAL(d2.front(), 0);

			cout << "test: back()" << endl;
			EXPECT_EQ_VAL(d1.back(), 3);
			EXPECT_EQ_VAL(d2.back(), 3);
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			queue<int> d1;
			EXPECT_EQ_VAL(d1.empty(), true);
			d1.push(1);
			EXPECT_EQ_VAL(d1.empty(), false);
		}

		//≤‚ ‘ size
		void test_size_push_pop() {
			cout << "test: size()" << endl;

			queue<int> d1;
			EXPECT_EQ_VAL(d1.size(), 0);
			d1.push(1);
			EXPECT_EQ_VAL(d1.size(), 1);

			cout << "test: push()" << endl;
			for (int i = 0; i < 100; ++i) d1.push(i);
			EXPECT_EQ_VAL(d1.size(), 101);

			cout << "test: pop()" << endl;
			d1.pop();
			EXPECT_EQ_VAL(d1.size(), 100);
			for (int i = 0; i < 50; ++i) d1.pop();
			EXPECT_EQ_VAL(d1.size(), 50);
		}
		
		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			queue<int> d1; //{}
			queue<int> d2; //{0,1,2,3}
			queue<int> d3; //{4,5,6,7,8,9}
			for (int i = 0; i < 4; ++i) d2.push(i);
			for (int i = 4; i < 10; ++i) d3.push(i);

			d1.swap(d2);
			EXPECT_EQ_VAL(d1.front(), 0);
			EXPECT_EQ_VAL(d1.back(), 3);
			EXPECT_EQ_VAL(d2.empty(), true);

			d1.swap(d3);
			EXPECT_EQ_VAL(d1.front(), 4);
			EXPECT_EQ_VAL(d1.back(), 9);
			EXPECT_EQ_VAL(d3.front(), 0);
			EXPECT_EQ_VAL(d3.back(), 3);

			kkli::swap(d2, d3);
			EXPECT_EQ_VAL(d2.front(), 0);
			EXPECT_EQ_VAL(d2.back(), 3);
			EXPECT_EQ_VAL(d3.empty(), true);
		}

		//≤‚ ‘ get_container
		void test_get_container() {
			cout << "test: get_container()" << endl;

			queue<int> d1;
			auto cont1 = d1.get_container();
			cont1.push_back(2);
			cont1.push_front(1);
			cont1.insert(cont1.begin(), { 1,2,3,4 });
			EXPECT_EQ_ITERLIST(cont1.begin(), cont1.end(), { 1,2,3,4,1,2 });
			EXPECT_EQ_VAL(d1.empty(), true);
		}

		//≤‚ ‘ operator==
		void test_op1() {
			queue<int> d1; //{}
			queue<int> d2; //{0,1,2,3}
			queue<int> d3; //{0,1,2,3,4,5}
			queue<int> d4; //{2,4,6,8}
			for (int i = 0; i < 4; ++i) d2.push(i);
			for (int i = 0; i < 6; ++i) d3.push(i);
			for (int i = 2; i < 10; i += 2) d4.push(i);

			EXPECT_EQ_VAL(d1 == d1, true);
			EXPECT_EQ_VAL(d1 == d2, false);
			EXPECT_EQ_VAL(d1 == d3, false);
			EXPECT_EQ_VAL(d1 == d4, false);

			EXPECT_EQ_VAL(d2 == d1, false);
			EXPECT_EQ_VAL(d2 == d2, true);
			EXPECT_EQ_VAL(d2 == d3, false);
			EXPECT_EQ_VAL(d2 == d4, false);

			EXPECT_EQ_VAL(d3 == d1, false);
			EXPECT_EQ_VAL(d3 == d2, false);
			EXPECT_EQ_VAL(d3 == d3, true);
			EXPECT_EQ_VAL(d3 == d4, false);

			EXPECT_EQ_VAL(d4 == d1, false);
			EXPECT_EQ_VAL(d4 == d2, false);
			EXPECT_EQ_VAL(d4 == d3, false);
			EXPECT_EQ_VAL(d4 == d4, true);
		}

		//≤‚ ‘ operator<
		void test_op2() {
			queue<int> d1; //{}
			queue<int> d2; //{0,1,2,3}
			queue<int> d3; //{0,1,2,3,4,5}
			queue<int> d4; //{2,4,6,8}
			for (int i = 0; i < 4; ++i) d2.push(i);
			for (int i = 0; i < 6; ++i) d3.push(i);
			for (int i = 2; i < 10; i += 2) d4.push(i);

			EXPECT_EQ_VAL(d1 < d1, false);
			EXPECT_EQ_VAL(d1 < d2, true);
			EXPECT_EQ_VAL(d1 < d3, true);
			EXPECT_EQ_VAL(d1 < d4, true);

			EXPECT_EQ_VAL(d2 < d1, false);
			EXPECT_EQ_VAL(d2 < d2, false);
			EXPECT_EQ_VAL(d2 < d3, true);
			EXPECT_EQ_VAL(d2 < d4, true);

			EXPECT_EQ_VAL(d3 < d1, false);
			EXPECT_EQ_VAL(d3 < d2, false);
			EXPECT_EQ_VAL(d3 < d3, false);
			EXPECT_EQ_VAL(d3 < d4, true);

			EXPECT_EQ_VAL(d4 < d1, false);
			EXPECT_EQ_VAL(d4 < d2, false);
			EXPECT_EQ_VAL(d4 < d3, false);
			EXPECT_EQ_VAL(d4 < d4, false);
		}

		//≤‚ ‘ operator>
		void test_op3() {
			queue<int> d1; //{}
			queue<int> d2; //{0,1,2,3}
			queue<int> d3; //{0,1,2,3,4,5}
			queue<int> d4; //{2,4,6,8}
			for (int i = 0; i < 4; ++i) d2.push(i);
			for (int i = 0; i < 6; ++i) d3.push(i);
			for (int i = 2; i < 10; i += 2) d4.push(i);

			EXPECT_EQ_VAL(d1 > d1, false);
			EXPECT_EQ_VAL(d1 > d2, false);
			EXPECT_EQ_VAL(d1 > d3, false);
			EXPECT_EQ_VAL(d1 > d4, false);

			EXPECT_EQ_VAL(d2 > d1, true);
			EXPECT_EQ_VAL(d2 > d2, false);
			EXPECT_EQ_VAL(d2 > d3, false);
			EXPECT_EQ_VAL(d2 > d4, false);

			EXPECT_EQ_VAL(d3 > d1, true);
			EXPECT_EQ_VAL(d3 > d2, true);
			EXPECT_EQ_VAL(d3 > d3, false);
			EXPECT_EQ_VAL(d3 > d4, false);

			EXPECT_EQ_VAL(d4 > d1, true);
			EXPECT_EQ_VAL(d4 > d2, true);
			EXPECT_EQ_VAL(d4 > d3, true);
			EXPECT_EQ_VAL(d4 > d4, false);
		}
	}
}
