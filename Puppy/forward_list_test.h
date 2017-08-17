#pragma once

#include "stdafx.h"
#include "test.h"
#include "forward_list.h"

namespace test {
	namespace forward_list_test {

		using std::cout;
		using std::endl;
		using std::string;
		using kkli::forward_list;

		//«∞÷√…˘√˜: ≥…‘±∫Ø ˝
		void test_iterator();
		void test_constructor();
		void test_op_assign();			//operator=
		void test_assign();
		void test_front();
		void test_before_begin();
		void test_begin();
		void test_end();
		void test_empty();
		void test_clear();
		void test_insert_after();
		void test_erase_after();
		void test_push_front();
		void test_pop_front();
		void test_resize();
		void test_swap();
		void test_merge();
		void test_splice_after();
		void test_remove();
		void test_remove_if();
		void test_reverse();
		void test_unique();
		void tset_sort();
		void test_operators(); //∑«≥…‘±∫Ø ˝£∫operator == / != / < ...

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: forward_list " << endl;
			cout << "========================================" << endl;

			test_iterator();
			test_constructor();
			//test_op_assign();
			//test_assign();
			//test_front();
			//test_before_begin();
			//test_begin();
			//test_end();
			//test_empty();
			//test_clear();
			//test_insert_after();
			//test_erase_after();
			//test_push_front();
			//test_pop_front();
			//test_resize();
			//test_swap();
			//test_merge();
			//test_splice_after();
			//test_remove();
			//test_remove_if();
			//test_reverse();
			//test_unique();
			//tset_sort();
			//test_operators();
		}

		//≤‚ ‘ iterator
		void test_iterator() {
			cout << "test: iterator()" << endl;

			//constructors
			forward_list<int>::iterator iter1; //iterator()
			EXPECT_EQ_VAL(iter1.get(), nullptr);

			forward_list<int>::iterator iter2 = new kkli::forward_list_node<int>(1); //iterator(ptr)
			EXPECT_EQ_VAL(*iter2, 1);

			forward_list<int>::iterator iter3 = iter2; //iterator(rhs)
			EXPECT_EQ_VAL(*iter3, 1);

			iter1 = iter3; //operator=
			EXPECT_EQ_VAL(*iter1, 1);

			EXPECT_EQ_VAL(iter1.get()->value, 1);
			
			iter1->next = new kkli::forward_list_node<int>(2);
			iter2 = iter1;
			++iter1;
			EXPECT_EQ_VAL(*iter1, 2);	//operator++
			EXPECT_EQ_VAL(*(iter2++), 1); //operator++(int)

			EXPECT_EQ_VAL(iter1->value, 2); //operator->
			
			EXPECT_EQ_VAL(iter1 == iter2, true); //operator==
			EXPECT_EQ_VAL(iter1 != iter3, true); //operator!=
		}

		//≤‚ ‘ constructor
		void test_constructor(){
			cout << "test: constructor()" << endl;

			forward_list<int> fl1; //forward_list()
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), {1}); //fl1Œ™ø’£¨≤ªª·”Î1≈–∂œ

			forward_list<int> fl2(4, 1); //forward_list(count, value)
			EXPECT_EQ_ITERVAL(fl2.begin(), fl2.end(), 1);

			forward_list<int> fl3(fl2); //forward_list(rhs)
			EXPECT_EQ_ITERVAL(fl3.begin(), fl3.end(), 1);

			forward_list<int> fl4(std::move(fl3)); //forward_list(&&rhs)
			EXPECT_EQ_ITERVAL(fl4.begin(), fl4.end(), 1);

			forward_list<int> fl5{ 1,2,3,4 }; //forward_list(init)
			EXPECT_EQ_ITERLIST(fl5.begin(), fl5.end(), { 1,2,3,4 });
		}

		/*
		//≤‚ ‘ destructor
		void test_destructor() {
			cout << "\ntest_destructor()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			fl.~forward_list();
			fl.print();
		}

		//≤‚ ‘ begin / end
		void test_begin_end() {
			cout << "\ntest_begin_end()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			cout << *(fl.begin()) << endl;
			cout << *(fl.cbegin()) << endl;
		}

		//≤‚ ‘ push_front
		void test_push_front() {
			cout << "\ntest_push_front()" << endl;

			forward_list<int> fl;
			for (int i = 0; i < 4; ++i)
				fl.push_front(i);
			fl.print();
		}

		//≤‚ ‘ pop_front
		void test_pop_front() {
			cout << "\ntest_pop_front()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			for (int i = 0; i < 4; ++i) {
				cout << *(fl.begin()) << endl;
				fl.pop_front();
			}

			//runtime_error
			//fl.pop_front();
		}

		//≤‚ ‘ insert_after
		void test_insert_after() {
			cout << "\ntest_insert_after()" << endl;

			forward_list<int> fl{ 1,2,3,4 };

			//insert_after(pos, n)
			fl.insert_after(0, 1);
			fl.insert_after(4, 4);
			fl.print();

			//insert_after(pos, n, elem)
			fl.insert_after(0, 2, 1);
			fl.insert_after(4, 2, 4);
			fl.print();

			//insert_after(pos, beg, end)
			fl.insert_after(0, fl.begin(), fl.end());
			fl.print();

			//insert_after(pos, initializer_list)
			fl.insert_after(0, { 11,12,13,14 });
			fl.print();
		}

		//≤‚ ‘ erase_after
		void test_erase_after() {
			cout << "\ntest_erase_after()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			fl.erase_after(0);
			fl.erase_after(1);
			fl.print();

			fl.erase_after(0);
			fl.print();
		}

		//≤‚ ‘ remove
		void test_remove() {
			cout << "\ntest_remove()" << endl;

			forward_list<int> fl{ 1,2,3,4,1,2,3,4 };
			fl.remove(1);
			fl.print();
			fl.remove(4);
			fl.print();

			forward_list<int> fl1{ 1,2,3,4,5,6 };
			//»•µÙ∆Ê ˝
			fl1.remove_if([](const int& elem) -> bool { return elem % 2; });
			fl1.print();
		}

		//≤‚ ‘ resize
		void test_resize() {
			cout << "\ntest_resize()" << endl;

			forward_list<int> fl1;
			fl1.resize(4);
			fl1.print();

			forward_list<int> fl2{ 1,2,3,4 };
			fl2.resize(8);
			fl2.print();
			fl2.resize(2);
			fl2.print();
			fl2.resize(0);
			fl2.print();

			forward_list<int> fl3{ 1,2,3,4 };
			fl3.resize(8, 4);
			fl3.print();
			fl3.resize(2);
			fl3.print();
		}

		//≤‚ ‘ operators
		void test_operator() {
			cout << "\ntest_operator()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2;
			forward_list<int> fl3{ 1,2,3,4 };
			forward_list<int> fl4{ 1,2,3,4 };
			forward_list<int> fl5{ 1,1 };
			forward_list<int> fl6{ 1,1,1,1 };
			forward_list<int> fl7{ 2,3,4,5 };
			forward_list<int> fl8{ 1,2,3,4,5,6,7,8 };

			//operator== / !=
			cout << "operator == / !=" << endl;
			cout << (fl1 == fl2 ? "==" : "!=") << endl;
			cout << (fl1 == fl3 ? "==" : "!=") << endl;
			cout << (fl3 == fl4 ? "==" : "!=") << endl;
			cout << (fl3 == fl5 ? "==" : "!=") << endl;

			//operator < >=
			cout << "operator < / >=" << endl;
			cout << (fl1 < fl2 ? "<" : ">=") << endl;
			cout << (fl1 < fl3 ? "<" : ">=") << endl;
			cout << (fl3 < fl4 ? "<" : ">=") << endl;
			cout << (fl4 < fl5 ? "<" : ">=") << endl;
			cout << (fl5 < fl6 ? "<" : ">=") << endl;
			cout << (fl3 < fl7 ? "<" : ">=") << endl;
			cout << (fl3 < fl8 ? "<" : ">=") << endl;

			//operator > <=
			cout << "operator > / <=" << endl;
			cout << (fl1 > fl2 ? ">" : "<=") << endl;
			cout << (fl1 > fl3 ? ">" : "<=") << endl;
			cout << (fl3 > fl4 ? ">" : "<=") << endl;
			cout << (fl4 > fl5 ? ">" : "<=") << endl;
			cout << (fl5 > fl6 ? ">" : "<=") << endl;
			cout << (fl3 > fl7 ? ">" : "<=") << endl;
			cout << (fl3 > fl8 ? ">" : "<=") << endl;
		}

		//≤‚ ‘ assign
		void test_assign() {
			cout << "\ntest_assign()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			fl.assign(4, 1);
			fl.print();
			fl.assign(0, 10);
			fl.print();
			forward_list<int> fl1{ 1,2,3,4 };
			fl.assign(fl1.begin(), fl1.end());
			fl.print();
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "\ntest_swap()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };
			forward_list<int> fl2(fl1);
			forward_list<int> fl3{ 5,6,7,8 };
			fl1.print();
			fl2.print();

			cout << "fl1.swap(fl2)" << endl;
			fl1.swap(fl2);
			fl1.print();
			fl2.print();

			cout << "swap(fl1,fl3)" << endl;
			kkli::swap(fl1, fl3);
			fl1.print();
			fl2.print();
			fl3.print();
		}
		*/
	}
}
