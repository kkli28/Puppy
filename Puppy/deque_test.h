#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "deque.h"

namespace test {
	namespace deque_test {
		using std::cout;
		using std::endl;
		using kkli::deque;

		//«∞÷√…˘√˜
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

		void test_op1(); //operator==
		void test_op2(); //operator<
		void test_op3(); //operator>
		void test_operators() {
			cout << "test: operator(==/!=/<...)" << endl;
			test_op1();
			test_op2();
			test_op3();
		}

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "            deque.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_op_assign();
			test_assign();
			test_at();
			test_op_square_bracket();
			test_front_and_back();
			test_begin_and_end();
			test_rbegin_and_rend();
			test_insert();
			test_erase();
			test_resize();
			test_empty();
			test_size();
			test_clear();
			test_push_front();
			test_push_back();
			test_pop_front();
			test_pop_back();
			test_swap();
			test_operators();
		}

		//≤‚ ‘ constructor
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

		//≤‚ ‘ operator=
		void test_op_assign() {
			cout << "test: operator=" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3(18, 1);

			d1 = d2; //operator=(rhs)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d1.size(), 4);
			d1 = d3;
			EXPECT_EQ_ITERVAL(d1.begin(), d1.end(), 1);
			EXPECT_EQ_VAL(d1.size(), 18);

			d1 = std::move(d2); //operator=(&&rhs)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d1.size(), 4);
			d1 = std::move(d3);
			EXPECT_EQ_ITERVAL(d1.begin(), d1.end(), 1);
			EXPECT_EQ_VAL(d1.size(), 18);

			d1 = { 1,2,3,4 }; //operator=(init)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d1.size(), 4);
			d1 = { 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8 };
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8 });
			EXPECT_EQ_VAL(d1.size(), 16);
		}

		//≤‚ ‘ assign
		void test_assign() {
			cout << "test: assign()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5,6,7,8,9,10 };

			//assign(count, value)
			d1.assign(4, 1);
			EXPECT_EQ_ITERVAL(d1.begin(), d1.end(), 1);
			EXPECT_EQ_VAL(d1.size(), 4);

			d1.assign(10, 2);
			EXPECT_EQ_ITERVAL(d1.begin(), d1.end(), 2);
			EXPECT_EQ_VAL(d1.size(), 10);

			d2.assign(4, 1);
			EXPECT_EQ_ITERVAL(d2.begin(), d2.end(), 1);
			EXPECT_EQ_VAL(d2.size(), 4);

			d2.assign(10, 2);
			EXPECT_EQ_ITERVAL(d2.begin(), d2.end(), 2);
			EXPECT_EQ_VAL(d2.size(), 10);

			d3.assign(4, 1);
			EXPECT_EQ_ITERVAL(d3.begin(), d3.end(), 1);
			EXPECT_EQ_VAL(d3.size(), 4);

			d3.assign(10, 2);
			EXPECT_EQ_ITERVAL(d3.begin(), d3.end(), 2);
			EXPECT_EQ_VAL(d3.size(), 10);

			//assign_range(first, last)
			deque<int> d4{ 1,2,3,4,5,6 };
			deque<int> d5{ 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 };
			d1.assign_range(d4.begin(), d4.end());
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4,5,6, });
			EXPECT_EQ_VAL(d1.size(), 6);

			d1.assign_range(d5.begin(), d5.end());
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_VAL(d1.size(), 18);

			d2.assign_range(d4.begin(), d4.end());
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6, });
			EXPECT_EQ_VAL(d2.size(), 6);

			d2.assign_range(d5.begin(), d5.end());
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_VAL(d2.size(), 18);
			
			d3.assign_range(d4.begin(), d4.end());
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,2,3,4,5,6, });
			EXPECT_EQ_VAL(d3.size(), 6);

			d3.assign_range(d5.begin(), d5.end());
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_VAL(d3.size(), 18);

			//assign(init)
			d1.assign({ 1,2,3,4 });
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d1.size(), 4);
			d1.assign({ 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_VAL(d1.size(), 18);

			d2.assign({ 1,2,3,4 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d2.size(), 4);
			d2.assign({ 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_VAL(d2.size(), 18);

			d3.assign({ 1,2,3,4 });
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d3.size(), 4);
			d3.assign({ 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6 });
			EXPECT_EQ_VAL(d3.size(), 18);

		}

		//≤‚ ‘ at
		void test_at() {
			cout << "test: at()" << endl;

			deque<int> d1{ 0,1,2,3 };
			deque<int> d2{ 0,1,2,3,4,5,6,7,8,9 };

			EXPECT_EQ_VAL(d1.at(0), 0);
			EXPECT_EQ_VAL(d1.at(1), 1);
			EXPECT_EQ_VAL(d1.at(2), 2);
			EXPECT_EQ_VAL(d1.at(3), 3);

			EXPECT_EQ_VAL(d2.at(0), 0);
			EXPECT_EQ_VAL(d2.at(3), 3);
			EXPECT_EQ_VAL(d2.at(7), 7);
			EXPECT_EQ_VAL(d2.at(9), 9);
		}

		//≤‚ ‘ operator[]
		void test_op_square_bracket() {
			cout << "test: operator[]" << endl;

			deque<int> d1{ 0,1,2,3 };
			deque<int> d2{ 0,1,2,3,4,5,6,7,8,9 };

			EXPECT_EQ_VAL(d1[0], 0);
			EXPECT_EQ_VAL(d1[1], 1);
			EXPECT_EQ_VAL(d1[2], 2);
			EXPECT_EQ_VAL(d1[3], 3);

			EXPECT_EQ_VAL(d2[0], 0);
			EXPECT_EQ_VAL(d2[3], 3);
			EXPECT_EQ_VAL(d2[7], 7);
			EXPECT_EQ_VAL(d2[9], 9);
		}

		//≤‚ ‘ front & back
		void test_front_and_back() {
			deque<int> d1{ 0,1,2,3 };
			deque<int> d2{ 0,1,2,3,4,5,6,7,8,9 };

			cout << "test: front()" << endl;
			EXPECT_EQ_VAL(d1.front(), 0);
			EXPECT_EQ_VAL(d2.front(), 0);

			cout << "test: back()" << endl;
			EXPECT_EQ_VAL(d2.back(), 9);
			EXPECT_EQ_VAL(d1.back(), 3);
		}

		//≤‚ ‘ begin & end
		void test_begin_and_end() {
			deque<int> d1{ 0,1,2,3 };
			deque<int> d2{ 0,1,2,3,4,5,6,7,8,9 };
			const deque<int> d3 = d2;

			cout << "test: begin()" << endl;
			cout << "test: cbegin()" << endl;
			EXPECT_EQ_VAL(*(d1.begin()), 0);
			EXPECT_EQ_VAL(*(d2.begin()), 0);
			EXPECT_EQ_VAL(*(d3.cbegin()), 0);

			cout << "test: end()" << endl;
			cout << "test: cend()" << endl;
			EXPECT_EQ_VAL(*kkli::prev(d1.end()), 3);
			EXPECT_EQ_VAL(*kkli::prev(d2.end()), 9);
			EXPECT_EQ_VAL(*kkli::prev(d3.cend()), 9);

			EXPECT_EQ_VAL(d1.end() - d1.begin(), 4);
			EXPECT_EQ_VAL(d2.end() - d2.begin(), 10);
			EXPECT_EQ_VAL(d3.cend() - d3.cbegin(), 10);
		}

		//≤‚ ‘ rbegin & rend
		void test_rbegin_and_rend() {
			deque<int> d1{ 0,1,2,3 };
			deque<int> d2{ 0,1,2,3,4,5,6,7,8,9 };
			const deque<int> d3 = d2;

			cout << "test: rbegin()" << endl;
			cout << "test: crbegin()" << endl;
			EXPECT_EQ_VAL(*(d1.rbegin()), 3);
			EXPECT_EQ_VAL(*(d2.rbegin()), 9);
			EXPECT_EQ_VAL(*(d3.crbegin()), 9);

			cout << "test: rend()" << endl;
			cout << "test: crend()" << endl;
			EXPECT_EQ_VAL(*kkli::prev(d1.rend()), 0);
			EXPECT_EQ_VAL(*kkli::prev(d2.rend()), 0);
			EXPECT_EQ_VAL(*kkli::prev(d3.crend()), 0);
		}

		//≤‚ ‘ insert
		void test_insert() {
			cout << "test: insert()" << endl;

			deque<int> d1{ 0,1,2,3 };
			deque<int> d2{ 0,1,2,3,4,5,6,7,8,9 };

			d1.insert(kkli::next(d1.begin(), 2), 2, 1); //insert(pos, count, value)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 0,1,1,1,2,3 });
			d2.insert(d2.begin(), 3, 2);
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 2,2,2,0,1,2,3,4,5,6,7,8,9 });

			d1.insert(kkli::prev(d1.end()), 1); //insert(pos, value)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 0,1,1,1,2,1,3 });
			d2.insert(kkli::prev(d2.end(), 4), 4);
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 2,2,2,0,1,2,3,4,5,4,6,7,8,9 });

			d1 = { 1,2,3,4 };
			d2= { 0,1,2,3,4,5,6,7,8,9 };
			deque<int> d3{ 1,2,3,4,5,6,7,8 };
			d1.insert_range(d1.begin(), d3.begin(), kkli::next(d3.begin(), 4)); //insert_range(pos, first, last)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4,1,2,3,4 });
			d2.insert_range(kkli::next(d2.begin()), d3.begin(), d3.end());
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 0,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,9 });
		}

		//≤‚ ‘ erase
		void test_erase() {
			cout << "test: erase()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5,6,7,8,9,10 };
			
			d1.erase(d1.begin(), d1.end()); //erase(first, last)
			EXPECT_EQ_VAL(d1.empty(), true);
			d2.erase(d2.begin(), kkli::next(d2.begin()));
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 2,3,4 });
			d3.erase(kkli::next(d3.begin()), kkli::next(d3.begin(), 4));
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,5,6,7,8,9,10 });

			d2.erase(d2.begin()); //erase(pos)
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 3,4 });
			d3.erase(kkli::prev(d3.end()));
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,5,6,7,8,9 });
		}

		//≤‚ ‘ resize
		void test_resize() {
			cout << "test: resize()" << endl;

			deque<int> d1;

			d1.resize(4, 1); //resize(count, value)
			EXPECT_EQ_ITERVAL(d1.begin(), d1.end(), 1);
			EXPECT_EQ_VAL(d1.size(), 4);
			d1.resize(2, 2);
			EXPECT_EQ_ITERVAL(d1.begin(), d1.end(), 1);
			EXPECT_EQ_VAL(d1.size(), 4);

			d1.resize(8); //resize(count)
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,1,1,1,0,0,0,0 });
			EXPECT_EQ_VAL(d1.size(), 8);
			d1.resize(4);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,1,1,1,0,0,0,0 });
			EXPECT_EQ_VAL(d1.size(), 8);
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			
			EXPECT_EQ_VAL(d1.empty(), true);
			EXPECT_EQ_VAL(d2.empty(), false);
		}

		//≤‚ ‘ size
		void test_size() {
			cout << "test: size()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5,6,7,8,9,10 };

			EXPECT_EQ_VAL(d1.size(), 0);
			EXPECT_EQ_VAL(d2.size(), 4);
			EXPECT_EQ_VAL(d3.size(), 10);
		}

		//≤‚ ‘ clear
		void test_clear() {
			cout << "test: clear()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4,5,6,7,8,9,10 };

			d1.clear();
			d2.clear();
			EXPECT_EQ_VAL(d1.empty(), true);
			EXPECT_EQ_VAL(d2.empty(), true);
		}

		//≤‚ ‘ push_front
		void test_push_front() {
			cout << "test: push_front()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4,5,6,7,8,9,10 };

			d1.push_front(1);
			d2.push_front(1);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,1,2,3,4,5,6,7,8,9,10 });
			d1.push_front(2);
			d2.push_front(2);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 2,1 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 2,1,1,2,3,4,5,6,7,8,9,10 });
		}

		//≤‚ ‘ push_back
		void test_push_back() {
			cout << "test: push_back()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4,5,6,7,8,9,10 };

			d1.push_back(1);
			d2.push_back(1);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,7,8,9,10,1 });
			d1.push_back(2);
			d2.push_back(2);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,7,8,9,10,1,2 });
		}

		//≤‚ ‘ pop_front
		void test_pop_front() {
			cout << "test: pop_front()" << endl;
						
			deque<int> d1{ 1,2,3,4 };
			deque<int> d2{ 1,2,3,4,5,6,7,8,9,10 };

			d1.pop_front();
			d2.pop_front();
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 2,3,4 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 2,3,4,5,6,7,8,9,10 });
			d1.pop_front();
			d2.pop_front();
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 3,4 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 3,4,5,6,7,8,9,10 });
		}
		
		//≤‚ ‘ pop_back
		void test_pop_back() {
			cout << "test: pop_back()" << endl;

			deque<int> d1{ 1,2,3,4 };
			deque<int> d2{ 1,2,3,4,5,6,7,8,9,10 };

			d1.pop_back();
			d2.pop_back();
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,7,8,9 });
			d1.pop_back();
			d2.pop_back();
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,7,8 });
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5,6,7,8,9,10 };

			d1.swap(d2);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d2.empty(), true);
			d1.swap(d3);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4,5,6,7,8,9,10 });
			EXPECT_EQ_ITERLIST(d3.begin(), d3.end(), { 1,2,3,4 });
			d2.swap(d3);
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(d3.empty(), true);

			kkli::swap(d1, d2);
			EXPECT_EQ_ITERLIST(d1.begin(), d1.end(), { 1,2,3,4 });
			EXPECT_EQ_ITERLIST(d2.begin(), d2.end(), { 1,2,3,4,5,6,7,8,9,10 });
		}

		//≤‚ ‘ operator==
		void test_op1() {
			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5 };
			deque<int> d4{ 1,2,4,6 };
			deque<int> d5{ 1,2,5,7,9 };
			
			EXPECT_EQ_VAL(d1 == d1, true);
			EXPECT_EQ_VAL(d1 == d2, false);
			EXPECT_EQ_VAL(d1 == d3, false);
			EXPECT_EQ_VAL(d1 == d4, false);
			EXPECT_EQ_VAL(d1 == d5, false);

			EXPECT_EQ_VAL(d2 == d1, false);
			EXPECT_EQ_VAL(d2 == d2, true);
			EXPECT_EQ_VAL(d2 == d3, false);
			EXPECT_EQ_VAL(d2 == d4, false);
			EXPECT_EQ_VAL(d2 == d5, false);

			EXPECT_EQ_VAL(d3 == d1, false);
			EXPECT_EQ_VAL(d3 == d2, false);
			EXPECT_EQ_VAL(d3 == d3, true);
			EXPECT_EQ_VAL(d3 == d4, false);
			EXPECT_EQ_VAL(d3 == d5, false);

			EXPECT_EQ_VAL(d4 == d1, false);
			EXPECT_EQ_VAL(d4 == d2, false);
			EXPECT_EQ_VAL(d4 == d3, false);
			EXPECT_EQ_VAL(d4 == d4, true);
			EXPECT_EQ_VAL(d4 == d5, false);

			EXPECT_EQ_VAL(d5 == d1, false);
			EXPECT_EQ_VAL(d5 == d2, false);
			EXPECT_EQ_VAL(d5 == d3, false);
			EXPECT_EQ_VAL(d5 == d4, false);
			EXPECT_EQ_VAL(d5 == d5, true);
		}

		//≤‚ ‘ operator<
		void test_op2() {
			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5 };
			deque<int> d4{ 1,2,4,6 };
			deque<int> d5{ 1,2,5,7,9 };

			EXPECT_EQ_VAL(d1 < d1, false);
			EXPECT_EQ_VAL(d1 < d2, true);
			EXPECT_EQ_VAL(d1 < d3, true);
			EXPECT_EQ_VAL(d1 < d4, true);
			EXPECT_EQ_VAL(d1 < d5, true);

			EXPECT_EQ_VAL(d2 < d1, false);
			EXPECT_EQ_VAL(d2 < d2, false);
			EXPECT_EQ_VAL(d2 < d3, true);
			EXPECT_EQ_VAL(d2 < d4, true);
			EXPECT_EQ_VAL(d2 < d5, true);

			EXPECT_EQ_VAL(d3 < d1, false);
			EXPECT_EQ_VAL(d3 < d2, false);
			EXPECT_EQ_VAL(d3 < d3, false);
			EXPECT_EQ_VAL(d3 < d4, true);
			EXPECT_EQ_VAL(d3 < d5, true);

			EXPECT_EQ_VAL(d4 < d1, false);
			EXPECT_EQ_VAL(d4 < d2, false);
			EXPECT_EQ_VAL(d4 < d3, false);
			EXPECT_EQ_VAL(d4 < d4, false);
			EXPECT_EQ_VAL(d4 < d5, true);

			EXPECT_EQ_VAL(d5 < d1, false);
			EXPECT_EQ_VAL(d5 < d2, false);
			EXPECT_EQ_VAL(d5 < d3, false);
			EXPECT_EQ_VAL(d5 < d4, false);
			EXPECT_EQ_VAL(d5 < d5, false);
		}

		//≤‚ ‘ operator>
		void test_op3() {
			deque<int> d1;
			deque<int> d2{ 1,2,3,4 };
			deque<int> d3{ 1,2,3,4,5 };
			deque<int> d4{ 1,2,4,6 };
			deque<int> d5{ 1,2,5,7,9 };

			EXPECT_EQ_VAL(d1 > d1, false);
			EXPECT_EQ_VAL(d1 > d2, false);
			EXPECT_EQ_VAL(d1 > d3, false);
			EXPECT_EQ_VAL(d1 > d4, false);
			EXPECT_EQ_VAL(d1 > d5, false);

			EXPECT_EQ_VAL(d2 > d1, true);
			EXPECT_EQ_VAL(d2 > d2, false);
			EXPECT_EQ_VAL(d2 > d3, false);
			EXPECT_EQ_VAL(d2 > d4, false);
			EXPECT_EQ_VAL(d2 > d5, false);

			EXPECT_EQ_VAL(d3 > d1, true);
			EXPECT_EQ_VAL(d3 > d2, true);
			EXPECT_EQ_VAL(d3 > d3, false);
			EXPECT_EQ_VAL(d3 > d4, false);
			EXPECT_EQ_VAL(d3 > d5, false);

			EXPECT_EQ_VAL(d4 > d1, true);
			EXPECT_EQ_VAL(d4 > d2, true);
			EXPECT_EQ_VAL(d4 > d3, true);
			EXPECT_EQ_VAL(d4 > d4, false);
			EXPECT_EQ_VAL(d4 > d5, false);

			EXPECT_EQ_VAL(d5 > d1, true);
			EXPECT_EQ_VAL(d5 > d2, true);
			EXPECT_EQ_VAL(d5 > d3, true);
			EXPECT_EQ_VAL(d5 > d4, true);
			EXPECT_EQ_VAL(d5 > d5, false);
		}
	}
}