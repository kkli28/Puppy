#pragma once

#include "stdafx.h"
#include "test.h"
#include "stack.h"
#include "vector.h"

namespace test {
	namespace stack_test {

		using std::cout;
		using std::endl;
		using kkli::stack;
		using kkli::vector;

		//«∞÷√…˘√˜
		void test_constructor();
		void test_op_assign(); //operaot =
		void test_get_container();
		void test_top();
		void test_empty();
		void test_size_push_pop();
		void test_swap();
		void test_operators(); //operator ==/!=/<...

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          stack.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_op_assign();
			test_get_container();
			test_top();
			test_empty();
			test_size_push_pop();
			test_swap();
			test_operators();
		}

		//≤‚ ‘ constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			stack<int, vector<int>> s1; //stack(c)
			EXPECT_EQ_VAL(s1.empty(), true);
			EXPECT_EQ_VAL(s1.size(), 0);

			stack<int> s2; //stack()
			EXPECT_EQ_VAL(s2.empty(), true);
			EXPECT_EQ_VAL(s2.size(), 0);

			stack<int,vector<int>> s3(std::move(s1));
			EXPECT_EQ_VAL(s2.empty(), true);
			EXPECT_EQ_VAL(s2.size(), 0);
		}

		//≤‚ ‘ op_assign
		void test_op_assign() {
			cout << "test: operator=" << endl;

			stack<int> s1;
			stack<int> s2;
			s2.push(1);
			s2.push(2);

			s1 = s2; //operator=(rhs)
			EXPECT_EQ_VAL(s1.empty(), false);
			EXPECT_EQ_VAL(s1.size(), 2);
			EXPECT_EQ_VAL(s2.size(), 2);

			s1.pop();
			s1.pop();
			EXPECT_EQ_VAL(s1.empty(), true);
			EXPECT_EQ_VAL(s1.size(), 0);

			s1 = std::move(s2); //operator=(&&rhs)
			EXPECT_EQ_VAL(s1.empty(), false);
			EXPECT_EQ_VAL(s1.size(), 2);
		}

		//≤‚ ‘ get_container
		void test_get_container() {
			cout << "test: get_container()" << endl;

			stack<int> s1;
			s1.push(1);
			s1.push(2);

			auto cont1 = s1.get_container();
			EXPECT_EQ_ITERLIST(cont1.begin(), cont1.end(), { 1,2 });
		}

		//≤‚ ‘ top
		void test_top() {
			cout << "test: top()" << endl;

			stack<int> s1;

			s1.push(1);
			EXPECT_EQ_VAL(s1.top(), 1);
			s1.push(2);
			EXPECT_EQ_VAL(s1.top(), 2);
			s1.pop();
			EXPECT_EQ_VAL(s1.top(), 1);
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			stack<int> s1;
			stack<int> s2;
			s2.push(1);

			EXPECT_EQ_VAL(s1.empty(), true);
			EXPECT_EQ_VAL(s2.empty(), false);
		}

		//≤‚ ‘ size
		void test_size_push_pop() {
			cout << "test: size()" << endl;

			stack<int> s1;
			EXPECT_EQ_VAL(s1.size(), 0);

			//push
			cout << "test: push()" << endl;
			s1.push(1);
			EXPECT_EQ_VAL(s1.size(), 1);

			for (int i = 0; i < 10; ++i) s1.push(i);
			EXPECT_EQ_VAL(s1.size(), 11);

			//pop
			cout << "test: pop()" << endl;
			s1.pop();
			EXPECT_EQ_VAL(s1.size(), 10);

			for (int i = 0; i < 5; ++i) s1.pop();
			EXPECT_EQ_VAL(s1.size(), 5);
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;
			
			stack<int> s1;
			stack<int> s2;
			stack<int> s3;
			for (int i = 0; i < 4; ++i) s2.push(i); //[0~4)
			for (int i = 4; i < 10; ++i) s3.push(i); //[4~10)

			s1.swap(s2);
			EXPECT_EQ_VAL(s1.size(), 4);
			EXPECT_EQ_VAL(s2.size(), 0);

			s1.swap(s3);
			EXPECT_EQ_VAL(s1.size(), 6);
			EXPECT_EQ_VAL(s3.size(), 4);

			kkli::swap(s2, s3);
			EXPECT_EQ_VAL(s2.size(), 4);
			EXPECT_EQ_VAL(s3.size(), 0);
		}

		//≤‚ ‘ operators
		void test_operators() {
			cout << "test: operator(==/!=/<...)" << endl;

			stack<int> s1; //{ }
			stack<int> s2; //{0,1,2,3}
			stack<int> s3; //{0,1,2,3,4,5}
			stack<int> s4; //{1,2,3,4}
			for (int i = 0; i < 4; ++i) s2.push(i);
			for (int i = 0; i < 6; ++i) s3.push(i);
			for (int i = 1; i < 5; ++i) s4.push(i);
			
			//operator ==
			EXPECT_EQ_VAL(s1 == s1, true);
			EXPECT_EQ_VAL(s1 == s2, false);
			EXPECT_EQ_VAL(s1 == s3, false);
			EXPECT_EQ_VAL(s1 == s4, false);

			EXPECT_EQ_VAL(s2 == s1, false);
			EXPECT_EQ_VAL(s2 == s2, true);
			EXPECT_EQ_VAL(s2 == s3, false);
			EXPECT_EQ_VAL(s2 == s4, false);

			EXPECT_EQ_VAL(s3 == s1, false);
			EXPECT_EQ_VAL(s3 == s2, false);
			EXPECT_EQ_VAL(s3 == s3, true);
			EXPECT_EQ_VAL(s3 == s4, false);

			EXPECT_EQ_VAL(s4 == s1, false);
			EXPECT_EQ_VAL(s4 == s2, false);
			EXPECT_EQ_VAL(s4 == s3, false);
			EXPECT_EQ_VAL(s4 == s4, true);

			//operator <
			EXPECT_EQ_VAL(s1 < s1, false);
			EXPECT_EQ_VAL(s1 < s2, true);
			EXPECT_EQ_VAL(s1 < s3, true);
			EXPECT_EQ_VAL(s1 < s4, true);

			EXPECT_EQ_VAL(s2 < s1, false);
			EXPECT_EQ_VAL(s2 < s2, false);
			EXPECT_EQ_VAL(s2 < s3, true);
			EXPECT_EQ_VAL(s2 < s4, true);

			EXPECT_EQ_VAL(s3 < s1, false);
			EXPECT_EQ_VAL(s3 < s2, false);
			EXPECT_EQ_VAL(s3 < s3, false);
			EXPECT_EQ_VAL(s3 < s4, true);

			EXPECT_EQ_VAL(s4 < s1, false);
			EXPECT_EQ_VAL(s4 < s2, false);
			EXPECT_EQ_VAL(s4 < s3, false);
			EXPECT_EQ_VAL(s4 < s4, false);

			//operator ==
			EXPECT_EQ_VAL(s1 > s1, false);
			EXPECT_EQ_VAL(s1 > s2, false);
			EXPECT_EQ_VAL(s1 > s3, false);
			EXPECT_EQ_VAL(s1 > s4, false);

			EXPECT_EQ_VAL(s2 > s1, true);
			EXPECT_EQ_VAL(s2 > s2, false);
			EXPECT_EQ_VAL(s2 > s3, false);
			EXPECT_EQ_VAL(s2 > s4, false);

			EXPECT_EQ_VAL(s3 > s1, true);
			EXPECT_EQ_VAL(s3 > s2, true);
			EXPECT_EQ_VAL(s3 > s3, false);
			EXPECT_EQ_VAL(s3 > s4, false);

			EXPECT_EQ_VAL(s4 > s1, true);
			EXPECT_EQ_VAL(s4 > s2, true);
			EXPECT_EQ_VAL(s4 > s3, true);
			EXPECT_EQ_VAL(s4 > s4, false);
		}
	}
}
