#pragma once

#include "stdafx.h"
#include "list.h"

namespace test {
	namespace list_test {

		using std::cout;
		using std::endl;
		using kkli::list;

		//��������
		void test_iterator();
		void test_constructor();
		void test_destructor();
		void test_op_assgin();			//operator =
		void test_assgin();
		void test_front_and_back();
		void test_begin_and_end();
		void test_empty();
		void test_size();
		void test_max_size();
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
		
		//�������
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: list " << endl;
			cout << "========================================" << endl;

			test_iterator();
			test_constructor();
			//test_destructor();
			//test_op_assgin();			//operator =
			//test_assgin();
			//test_front_and_back();
			//test_begin_and_end();
			//test_empty();
			//test_size();
			//test_max_size();
			//test_clear();
			//test_insert();
			//test_erase();
			//test_push_back();
			//test_pop_back();
			//test_push_front();
			//test_pop_front();
			//test_resize();
			//test_swap();
			//test_merge();
			//test_splice();
			//test_remove();
			//test_remove_if();
			//test_reverse();
			//test_unique();
			//test_sort();
			//test_operators();			//operator == / != / < / <= / > / >=
		}

		//���� iterator
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

		//���� constructor
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			list<int> list1;			//list()
			list1.print("list1");

			list<int> list2(4, 1);		//list(count, value)
			list2.print("list2");

			list<int> list3(4);			//list(count)
			list3.print("list3");

			list<int> list4(list2);		//list(rhs)
			list4.print("list4");

			list<int> list5(std::move(list4));		//list(&&rhs)
			list5.print("list5");
			list4.print("list4");

			list<int> list6({ 1,2,3,4 });			//list(il)
			list6.print("list6");
		}
	}
}