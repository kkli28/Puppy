#pragma once

#include "stdafx.h"
#include "list.h"

namespace test {
	namespace list_test {

		using std::cout;
		using std::endl;
		using kkli::list;

		//º¯ÊıÉùÃ÷
		void test_iterator();
		void test_constructor();
		void test_destructor();
		void test_op_assign();			//operator =
		void test_assign();
		void test_front_and_back();
		void test_begin_and_end();
		void test_empty();
		void test_size();
		void test_clear();
		void test_insert();
		void test_erase();
		void test_push_back();
		void test_pop_back();
		void test_push_front();
		void test_pop_front();
		void test_resize();
		void test_swap();
		void test_merge();
		void test_splice();
		void test_remove();
		void test_remove_if();
		void test_reverse();
		void test_unique();
		void test_sort();
		void test_operators();		//operator == / != / < / <= / > / >=
		
		//ÕûÌå²âÊÔ
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: list " << endl;
			cout << "========================================" << endl;

			test_iterator();
			test_constructor();
			test_destructor();
			test_op_assign();			//operator =
			test_assign();
			test_front_and_back();
			test_begin_and_end();
			test_empty();
			test_size();
			test_clear();
			test_insert();
			test_erase();
			test_push_back();
			test_pop_back();
			test_push_front();
			test_pop_front();
			test_resize();
			test_swap();
			//test_merge();
			//test_splice();
			//test_remove();
			//test_remove_if();
			//test_reverse();
			//test_unique();
			//test_sort();
			//test_operators();			//operator == / != / < / <= / > / >=
		}

		//²âÊÔ iterator
		void test_iterator() {
			cout << "\ntest_iterator()" << endl;

			//constructors
			list<int>::iterator it1 = 1;
			cout << *it1 << endl;				//1
			list<int>::iterator it2 = it1;
			cout << *it2 << endl;				//1

			//operator =
			list<int>::iterator it3 = 3;
			it3 = it1;
			cout << *it3 << endl;				//1

			//get
			cout << it1.get()->value << endl;	//1

			//operator ++
			it1->next = new kkli::list_node<int>(2);
			it1->next->prev = it1.get();
			++it1;
			cout << *it1 << endl;				//2

			//operator ++(int)
			it1 = it2;
			cout << *(it1++) << endl;			//1
			cout << *it1 << endl;				//2

			//operator --
			--it1;
			cout << *it1 << endl;				//1
			
			//operator --(int)
			++it1;
			cout << (*it1--) << endl;			//2

			//operator ==
			list<int>::iterator it4(1);
			cout << (it1 == it4 ? "true" : "false") << endl;	//false
			list<int>::iterator it5(it4);
			cout << (it4 == it5 ? "true" : "false") << endl;	//true

			//operator *
			const list<int>::iterator it6(2);
			cout << *it4 << endl;		//1
			cout << *it6 << endl;		//2
			*it4 = 2;
			cout << *it4 << endl;		//2

			//operator ->
			cout << it4->value << endl;		//2
			cout << it6->value << endl;		//2
			it4->value = 1;
			cout << it4->value << endl;		//1
		}

		//²âÊÔ constructor
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			list<int> list1;			//list()
			list1.print("list1");

			list<int> list2(4, 1);		//list(count, value)
			list2.print("list2");

			list<int> list3(2);			//list(count)
			list3.print("list3");

			list<int> list4(list2);		//list(rhs)
			list4.print("list4");

			list<int> list5(std::move(list4));		//list(&&rhs)
			list5.print("list5");
			list4.print("list4");

			list<int> list6({ 1,2,3,4 });			//list(il)
			list6.print("list6");
		}

		//²âÊÔ destructor
		void test_destructor() {
			cout << "\ntest_destructor()" << endl;

			list<int> list1;
			list<int> list2{ 1,2,3,4 };
			list<int> list3(4, 1);
			list<int> list4 = list2;
			list<int> list5(std::move(list3));
		}

		//²âÊÔ operator =
		void test_op_assign() {
			cout << "\ntest_op_assign()" << endl;

			list<int> list1;
			list<int> list2;
			list2 = list1;
			list1.print("list1");		//list1: 
			list2.print("list2");		//list2: 

			list<int> list3{ 1,2,3,4 };
			list2 = list3;
			list2.print("list2");		//list2: 1 2 3 4
			list3.print("list3");		//list3: 1 2 3 4

			list1 = std::move(list3);
			list1.print("list1");		//list1: 1 2 3 4
			list3.print("list3");		//list3: 
		}

		//²âÊÔ assign
		void test_assign() {
			cout << "\ntest_assign()" << endl;

			list<int> list1;
			list1.assign(4, 1);
			list1.print("list1");			//list1: 1 1 1 1

			list1.assign({ 1,2,3,4 });
			list1.print("list1");			//list1: 1 2 3 4
		}

		//²âÊÔ front / back
		void test_front_and_back() {
			cout << "\ntest_front_and_back()" << endl;

			list<int> list1{ 1,2,3,4 };
			cout << list1.front() << endl;
			cout << list1.back() << endl;
		}

		//²âÊÔ begin / end
		void test_begin_and_end() {
			cout << "\ntest_begin_and_end()" << endl;

			list<int> list1;
			cout << "list1: ";
			for (auto iter = list1.begin(); iter != list1.end(); ++iter)
				cout << *iter << " ";
			cout << endl;

			list<int> list2{ 1,2,3,4 };
			cout << "list2: ";
			for (auto iter = list2.begin(); iter != list2.end(); ++iter)
				cout << *iter << " ";
			cout << endl;

			cout << "list2: ";
			for (auto l : list2) cout << l << " ";
			cout << endl;
		}

		//²âÊÔ empty
		void test_empty() {
			cout << "\ntest_empty()" << endl;

			list<int> list1;
			list1.print("list1");
			cout << "list1: "<< (list1.empty() ? "empty" : "not empty") << endl;

			list<int> list2{ 1,2,3,4 };
			list2.print("list2");
			cout << "list2: " << (list2.empty() ? "empty" : "not empty") << endl;

		}

		//²âÊÔ size
		void test_size() {
			cout << "\ntest_size()" << endl;

			list<int> list1;
			list<int> list2(4);
			list<int> list3(4, 1);
			list<int> list4{ 1,2,3,4 };
			list<int> list_move{ 1,2,3,4 };
			list<int> list5(std::move(list_move));
			list<int> list6;
			list6 = list5;

			cout << list1.size() << endl;		//0
			cout << list2.size() << endl;		//4
			cout << list3.size() << endl;		//4
			cout << list4.size() << endl;		//4
			cout << list5.size() << endl;		//4
			cout << list6.size() << endl;		//4

			cout << "list's max_size: " << list<int>::max_size() << endl;
		}

		//²âÊÔ clear
		void test_clear() {
			cout << "\ntest_clear()" << endl;

			list<int> list1;
			list<int> list2{ 1,2,3,4 };
			list1.print("list1");
			list2.print("list2");
			list1.clear();
			list2.clear();
			list1.print("list1");
			list2.print("list2");
		}

		//²âÊÔ insert
		void test_insert() {
			cout << "\ntest_insert()" << endl;

			list<int> list1{ 1,2,3,4 };

			list1.insert(list1.begin(), 1);		//insert(pos, value)
			list1.print("list1");				//list1: 1 1 2 3 4 
			list1.insert(list1.begin(), 4, 1);	//insert(pos, count, value)
			list1.print("list1");				//1ist1: 1 1 1 1 1 1 2 3 4
			list<int>::iterator iter = list1.begin();
			++(++(++(++iter)));
			list1.insert(iter, 1);				//list1: 1 1 1 1 1 1 1 2 3 4 
			list1.print("list1");
			list1.insert(iter, { 1,2,3,4 });	//list1: 1 1 1 1 1 1 2 3 4 1 1 2 3 4 
			list1.print("list1");
		}

		//²âÊÔ erase
		void test_erase() {
			cout << "\ntest_erase()" << endl;

			list<int> list1;
			list1.erase(list1.begin(), list1.end());
			list1.print("list1");				//list1: 

			list<int> list2{ 1,2,3,4 };
			list<int>::iterator iter = list2.begin();
			++iter;
			list2.erase(iter, list2.end());
			list2.print("list2");				//list2: 1

			list<int> list3{ 1,2,3,4 };
			list3.erase(list3.begin());
			list3.print("list3");				//list3: 2 3 4
		}

		//²âÊÔ push_back
		void test_push_back() {
			cout << "\ntest_push_back()" << endl;

			list<int> list1;
			for (int i = 1; i < 5; ++i) {
				list1.push_back(i);				//push_back(value)
				list1.print("list1");			//1 2 3 4
			}
			cout << endl;

			int i = 5;
			list1.push_back(std::move(i));		//push_back(&&value)
			list1.print("list1");				//1 2 3 4 5
		}

		//²âÊÔ pop_back
		void test_pop_back() {
			cout << "\ntest_pop_back()" << endl;

			list<int> list1{ 1,2,3,4 };
			for (int i = 0; i < 4; ++i) {
				list1.pop_back();
				list1.print("list1");
			}
		}

		//²âÊÔ push_front
		void test_push_front() {
			cout << "\ntest_push_front()" << endl;

			list<int> list1;
			for (int i = 1; i < 5; ++i) {
				list1.push_front(i);
				list1.print("list1");			//4 3 2 1
			}

			list1.push_front(5);
			list1.print("list1");				//5 4 3 2 1
		}

		//²âÊÔ pop_front
		void test_pop_front() {
			cout << "\ntest_pop_front()" << endl;

			list<int> list1{ 1,2,3,4 };
			for (int i = 0; i < 4; ++i) {
				list1.pop_front();
				list1.print("list1");
			}
		}

		//²âÊÔ resize
		void test_resize() {
			cout << "\ntest_resize()" << endl;

			list<int> list1;
			list1.resize(4);				//resize(count)
			list1.print("list1");			//0 0 0 0
			list1.resize(2);
			list1.print("list1");			//0 0 0 0

			list1.resize(8, 1);				//0 0 0 0 1 1 1 1
			list1.print("list1");
			list1.resize(4, 1);				//0 0 0 0 1 1 1 1
			list1.print("list1");
		}

		//²âÊÔ swap
		void test_swap() {
			cout << "\ntest_swap()" << endl;

			list<int> list1;
			list<int> list2{ 1,2,3,4 };
			list1.swap(list2);
			list1.print("list1");
			list2.print("list2");

			kkli::swap(list1, list2);
			list1.print("list1");
			list2.print("list2");
		}
	}
}