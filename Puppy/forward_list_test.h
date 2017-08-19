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
		void test_reverse();
		void test_unique();
		void test_sort();
		void test_operators(); //∑«≥…‘±∫Ø ˝£∫operator == / != / < ...

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "            forward_list.h " << endl;
			cout << "========================================" << endl;

			test_iterator();
			test_constructor();
			test_op_assign();
			test_assign();
			test_front();
			test_before_begin();
			test_begin();
			test_end();
			test_empty();
			test_clear();
			test_insert_after();
			test_erase_after();
			test_push_front();
			test_pop_front();
			test_resize();
			test_swap();
			test_merge();
			test_splice_after();
			test_remove();
			test_reverse();
			test_unique();
			test_sort();
			test_operators();
		}

		//≤‚ ‘ iterator
		void test_iterator() {
			cout << "test: iterator()" << endl;

			//constructors
			forward_list<int>::iterator iter1; //iterator()
			EXPECT_EQ_VAL(iter1.get(), nullptr);

			forward_list<int>::iterator iter2(new kkli::forward_list_node<int>(1)); //iterator(ptr)
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

		//≤‚ ‘ erase_after
		void test_erase_after() {
			cout << "test: erase_after()" << endl;

			forward_list<int> fl1{ 1,2,3,4,5,6,7,8 };
			
			fl1.erase_after(fl1.begin(), kkli::next(fl1.begin(), 3)); //erase_after(pos, first ,last)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,4,5,6,7,8 });

			fl1.erase_after(fl1.begin()); //erase_after(pos)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,5,6,7,8 });
		}

		//≤‚ ‘ push_front
		void test_push_front() {
			cout << "test: push_front()" << endl;

			forward_list<int> fl1;
			
			fl1.push_front(1); //push_front(value)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1 });

			fl1.push_front(std::move(2)); //push_front(&&value)
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 2,1 });
		}

		//≤‚ ‘ pop_front
		void test_pop_front() {
			cout << "test: pop_front()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };
			
			fl1.pop_front();
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 2,3,4 });

			fl1.pop_front();
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 3,4 });
		}

		//≤‚ ‘ resize
		void test_resize() {
			cout << "test: resize()" << endl;

			forward_list<int> fl1;

			fl1.resize(2);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 0,0 });

			fl1.resize(4, 1);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 0,0,1,1 });

			fl1.resize(2);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 0,0,1,1 });
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2{ 1,2 };
			forward_list<int> fl3{ 1,2,3,4 };

			fl1.swap(fl2);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,2 });
			EXPECT_EQ_VAL(fl2.empty(), true);

			kkli::swap(fl1, fl3);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,2,3,4 });
			EXPECT_EQ_ITERLIST(fl3.begin(), fl3.end(), { 1,2 });
		}

		//≤‚ ‘ merge
		void test_merge() {
			cout << "test: merge()" << endl;

			forward_list<int> fl1{ 1,3,5,6 };
			forward_list<int> fl2{ 2,4,7,8 };
			forward_list<int> fl3{ 1,4,5,9 };

			//merge(rhs)
			forward_list<int> dest1;
			dest1.merge(fl1);
			EXPECT_EQ_ITERLIST(dest1.begin(), dest1.end(), { 1,3,5,6 });
			dest1.merge(fl2);
			EXPECT_EQ_ITERLIST(dest1.begin(), dest1.end(), { 1,2,3,4,5,6,7,8 });
			dest1.merge(fl3);
			EXPECT_EQ_ITERLIST(dest1.begin(), dest1.end(), { 1,1,2,3,4,4,5,5,6,7,8,9 });

			//merge(rhs, comp)
			forward_list<int> fl4{ 7,5,3,1 };
			forward_list<int> fl5{ 8,6,4,4 };
			dest1 = {};
			auto lmd1 = [](int i, int j)->bool {return i > j; };

			dest1.merge(fl4);
			EXPECT_EQ_ITERLIST(dest1.begin(), dest1.end(), { 7,5,3,1 });
			dest1.merge(fl5, lmd1);
			EXPECT_EQ_ITERLIST(dest1.begin(), dest1.end(), { 8,7,6,5,4,4,3,1 });
		}

		//≤‚ ‘ splice_after
		void test_splice_after() {
			cout << "test: splice_after()" << endl;

			forward_list<int> fl1{ 1,2,3,4 };
			forward_list<int> fl2{ 1,2,3,4,5,6,7,8 };

			//splice_after(pos, rhs, first, last)
			fl1.splice_after(kkli::next(fl1.begin()), fl2, fl2.begin(), kkli::next(fl2.begin(), 3));
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,2,2,3,3,4, });
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 1,4,5,6,7,8 });

			//splice_after(pos, rhs)
			fl1.splice_after(fl1.begin(), fl2);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,4,5,6,7,8,2,2,3,3,4 });
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 1 });

			//splice_after(pos, rhs, it)
			forward_list<int> fl3{ 1,2,3,4 };
			fl1.splice_after(kkli::next(fl1.begin(), 2), fl3, kkli::next(fl3.begin(), 2));
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,4,5,4,6,7,8,2,2,3,3,4 });
		}

		//≤‚ ‘ remove
		void test_remove() {
			cout << "test: remove()" << endl;
			cout << "test: remove_if()" << endl;

			forward_list<int> fl1{ 1,1,2,2,3,3,4,4 };

			fl1.remove(2); //remove
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,1,3,3,4,4 });

			auto lmd1 = [](int value)->bool {return value % 2; };
			fl1.remove_if(lmd1);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 4,4 });
		}

		//≤‚ ‘ reverse
		void test_reverse() {
			cout << "test: reverse()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2{ 1,2,3,4 };

			fl1.reverse();
			fl2.reverse();
			EXPECT_EQ_VAL(fl1.empty(), true);
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 4,3,2,1 });
		}

		//≤‚ ‘ unique
		void test_unique() {
			cout << "test: unique()" << endl;

			forward_list<int> fl1{ 1,1,2,2,3,3,4,4 };
			forward_list<int> fl2{ 1,2,3,4,1,2,3,4 };

			fl1.unique(); //unique
			EXPECT_EQ_ITERLIST(fl1.begin(), fl1.end(), { 1,2,3,4 });

			auto lmd1 = [](int i, int j)->bool {return i != j; };
			fl2.unique(lmd1);
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 1,1 });
		}

		//≤‚ ‘ sort
		void test_sort() {
			cout << "test: sort()" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2{ 1,3,5,7,9,2,6,4,10,8 };

			//sort()
			fl1.sort();
			fl2.sort();
			EXPECT_EQ_VAL(fl1.empty(), true);
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 1,2,3,4,5,6,7,8,9,10 });

			//sort(pred)
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			fl2.sort(lmd1);
			EXPECT_EQ_ITERLIST(fl2.begin(), fl2.end(), { 10,9,8,7,6,5,4,3,2,1 });
		}

		//≤‚ ‘ operator == != < <= > >=
		void test_operators() {
			cout << "test: operators(==/!=/<...)" << endl;

			forward_list<int> fl1;
			forward_list<int> fl2{ 1,2,3,4 };
			forward_list<int> fl3{ 1,2,3,5 };
			forward_list<int> fl4{ 1,2,3,4,5 };

			//operator==£®operator!=”…operator== µœ÷£©
			EXPECT_EQ_VAL(fl1 == fl1, true);
			EXPECT_EQ_VAL(fl1 == fl2, false);
			EXPECT_EQ_VAL(fl1 == fl3, false);
			EXPECT_EQ_VAL(fl1 == fl4, false);
			EXPECT_EQ_VAL(fl2 == fl1, false);
			EXPECT_EQ_VAL(fl2 == fl2, true);
			EXPECT_EQ_VAL(fl2 == fl3, false);
			EXPECT_EQ_VAL(fl2 == fl4, false);
			EXPECT_EQ_VAL(fl3 == fl1, false);
			EXPECT_EQ_VAL(fl3 == fl2, false);
			EXPECT_EQ_VAL(fl3 == fl3, true);
			EXPECT_EQ_VAL(fl3 == fl4, false);
			EXPECT_EQ_VAL(fl4 == fl1, false);
			EXPECT_EQ_VAL(fl4 == fl2, false);
			EXPECT_EQ_VAL(fl4 == fl3, false);
			EXPECT_EQ_VAL(fl4 == fl4, true);

			//operator<£®operator>=”…operator< µœ÷£©
			EXPECT_EQ_VAL(fl1 < fl1, false);
			EXPECT_EQ_VAL(fl1 < fl2, true);
			EXPECT_EQ_VAL(fl1 < fl3, true);
			EXPECT_EQ_VAL(fl1 < fl4, true);
			EXPECT_EQ_VAL(fl2 < fl1, false);
			EXPECT_EQ_VAL(fl2 < fl2, false);
			EXPECT_EQ_VAL(fl2 < fl3, true);
			EXPECT_EQ_VAL(fl2 < fl4, true);
			EXPECT_EQ_VAL(fl3 < fl1, false);
			EXPECT_EQ_VAL(fl3 < fl2, false);
			EXPECT_EQ_VAL(fl3 < fl3, false);
			EXPECT_EQ_VAL(fl3 < fl4, false);
			EXPECT_EQ_VAL(fl4 < fl1, false);
			EXPECT_EQ_VAL(fl4 < fl2, false);
			EXPECT_EQ_VAL(fl4 < fl3, true);
			EXPECT_EQ_VAL(fl4 < fl4, false);


			//operator>£®operator<=”…operator> µœ÷£©
			EXPECT_EQ_VAL(fl1 > fl1, false);
			EXPECT_EQ_VAL(fl1 > fl2, false);
			EXPECT_EQ_VAL(fl1 > fl3, false);
			EXPECT_EQ_VAL(fl1 > fl4, false);
			EXPECT_EQ_VAL(fl2 > fl1, true);
			EXPECT_EQ_VAL(fl2 > fl2, false);
			EXPECT_EQ_VAL(fl2 > fl3, false);
			EXPECT_EQ_VAL(fl2 > fl4, false);
			EXPECT_EQ_VAL(fl3 > fl1, true);
			EXPECT_EQ_VAL(fl3 > fl2, true);
			EXPECT_EQ_VAL(fl3 > fl3, false);
			EXPECT_EQ_VAL(fl3 > fl4, true);
			EXPECT_EQ_VAL(fl4 > fl1, true);
			EXPECT_EQ_VAL(fl4 > fl2, true);
			EXPECT_EQ_VAL(fl4 > fl3, false);
			EXPECT_EQ_VAL(fl4 > fl4, false);
		}
	}
}
