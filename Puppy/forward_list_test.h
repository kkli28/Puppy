#pragma once

#include "stdafx.h"
#include "test.h"
#include "forward_list.h"
#include "iterator.h"

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

			//test_iterator();
			//test_constructor();
			//test_op_assign();
			//test_assign();
			//test_front();
			//test_before_begin();
			//test_begin();
			//test_end();
			//test_empty();
			//test_clear();
			test_insert_after();
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
			EXPECT_EQ_VAL(fl1.empty(), true);

			forward_list<int> fl2(4, 1); //forward_list(count, value)
			EXPECT_EQ_ITERVAL(fl2.begin(), fl2.end(), 1);

			forward_list<int> fl3(fl2); //forward_list(rhs)
			EXPECT_EQ_ITERVAL(fl3.begin(), fl3.end(), 1);

			forward_list<int> fl4(std::move(fl3)); //forward_list(&&rhs)
			EXPECT_EQ_ITERVAL(fl4.begin(), fl4.end(), 1);

			forward_list<int> fl5{ 1,2,3,4 }; //forward_list(init)
			EXPECT_EQ_ITERLIST(fl5.begin(), fl5.end(), { 1,2,3,4 });
		}

		//≤‚ ‘ operator=
		void test_op_assign() {
			cout << "test: operator=" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2(4, 1);
			forward_list<int> fl3({ 1,2,3,4 });
			forward_list<int> fl4;
			
			//operator =(rhs)
			fl4 = fl1;
			EXPECT_EQ_VAL(fl4.empty(), true);
			fl4 = fl2;
			EXPECT_EQ_ITERLIST(fl4.begin(), fl4.end(), { 1,1,1,1 });

			//operator =(&&rhs)
			fl4 = std::move(fl3);
			EXPECT_EQ_ITERLIST(fl4.begin(), fl4.end(), { 1,2,3,4 });

			//operator =(init)
			fl4 = { 1,1,2,2 };
			EXPECT_EQ_ITERLIST(fl4.begin(), fl4.end(), { 1,1,2,2 });
		}

		//≤‚ ‘ assign
		void test_assign() {
			cout << "test: assign()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2 = { 1,2,3,4 };

			fl1.assign(4, 1); //assign(count, value)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,1,1,1 });

			fl1.assign_range(fl2.begin(), fl2.end()); //assign_range(first, last)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,2,3,4 });

			fl1.assign({ 1,1,2,2 });
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,1,2,2 });
		}

		//≤‚ ‘ front
		void test_front() {
			cout << "test: front()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };
			const forward_list<int> fl2{ 2,2,2,2 };

			EXPECT_EQ_VAL(fl1.front(), 1);
			EXPECT_EQ_VAL(fl2.front(), 2);
		}

		//≤‚ ‘ before_begin
		void test_before_begin() {
			cout << "test: before_begin()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };
			const forward_list<int> fl2 = fl1;
			EXPECT_EQ_VAL(*(fl1.before_begin()), 0);
			EXPECT_EQ_VAL(*(++fl1.before_begin()), 1);
			EXPECT_EQ_VAL(*(fl2.before_begin()), 0);
			EXPECT_EQ_VAL(*(++fl2.before_begin()), 1);
		}

		//≤‚ ‘ begin
		void test_begin() {
			cout << "test: begin()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };
			const forward_list<int> fl2 = fl1;

			EXPECT_EQ_VAL(*(fl1.begin()), 1);
			EXPECT_EQ_VAL(*(fl2.begin()), 1);
		}

		//≤‚ ‘ end
		void test_end() {
			cout << "test: end()" << endl;
			
			forward_list<int> fl1{ 1,1,1,1 };
			auto end = fl1.end();
			for (auto beg = fl1.begin(); beg != end; ++beg)
				EXPECT_EQ_VAL(*beg, 1);
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2{ 1,2,3,4 };

			EXPECT_EQ_VAL(fl1.empty(), true);
			EXPECT_EQ_VAL(fl2.empty(), false);
		}

		//≤‚ ‘ clear
		void test_clear() {
			cout << "test: clear()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2{ 1,2,3,4 };

			fl1.clear();
			EXPECT_EQ_VAL(fl1.empty(), true);
			fl2.clear();
			EXPECT_EQ_VAL(fl2.empty(), true);
			fl2 = { 1,2,3,4 };
			EXPECT_EQ_VAL(fl2.empty(), false);
		}

		//≤‚ ‘ insert_after
		void test_insert_after() {
			cout << "test: insert_after()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };

			auto iter1 = fl1.insert_after(fl1.begin(), 2, 1); //insert_after(pos, count, value)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,1,1,2,3,4 });
			EXPECT_EQ_VAL(*iter1, 1);
			EXPECT_EQ_VAL(*(kkli::next(iter1)), 2);

			auto iter2 = fl1.insert_after(kkli::next(fl1.begin(), 5), 9); //insert_after(pos, value)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,1,1,2,3,4,9 });
			EXPECT_EQ_VAL(*iter2, 9);

			auto iter3 = fl1.insert_after(fl1.begin(), std::move(1)); //insert_after(pos, &&value)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,1,1,1,2,3,4,9 });
			EXPECT_EQ_VAL(iter3, kkli::next(fl1.begin()));

			forward_list<int> fl2{ 1 }; //insert_after(pos, first, last)
			auto iter4 = fl2.insert_after_range(fl2.begin(), fl1.begin(), kkli::next(fl1.begin(), 4));
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 1,1,1,1,1 });
			EXPECT_EQ_VAL(iter4, kkli::next(fl2.begin(), 4));
			
			auto iter5 = fl2.insert_after(kkli::next(fl2.begin()), { 1,2,3,4 });
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 1,1,1,2,3,4,1,1,1 });
			EXPECT_EQ_VAL(*iter5, 4);
		}
	}
}
