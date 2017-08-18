#pragma once

#include "stdafx.h"
#include "test.h"
#include "list.h"

namespace test {
	namespace list_test {

		using std::cout;
		using std::endl;
		using kkli::list;

		//º¯ÊıÉùÃ÷
		void test_iterator();
		void test_constructor();
		void test_op_assign();			//operator =
		void test_assign();
		void test_front_and_back();
		void test_begin_and_end();
		void test_rbegin_and_rend();
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
			test_op_assign();
			test_assign();
			//test_front_and_back();
			//test_begin_and_end();
			//test_rbegin_and_rend();
			//test_empty();
			//test_size();
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
			//test_reverse();
			//test_unique();
			//test_sort();
			//test_operators();
		}

		//²âÊÔ iterator
		void test_iterator() {
			cout << "test: iterator()" << endl;

			//constructors
			list<int>::iterator iter1; //iterator()
			EXPECT_EQ_VAL(iter1.get(), nullptr); //get()

			list<int>::iterator iter2(new kkli::list_node<int>(1)); //iterator(ptr)
			EXPECT_EQ_VAL(*iter2, 1); //operator *

			list<int>::iterator iter3(1); //iterator(value)
			EXPECT_EQ_VAL(*iter3, 1);

			list<int>::iterator iter4(std::move(2)); //iterator(&&value)
			EXPECT_EQ_VAL(*iter4, 2);

			iter1 = iter2; //operator =
			EXPECT_EQ_VAL(*iter1, 1); //iterator(rhs)

			//operator ++
			list<int>::iterator iter5(1);
			iter5->next = new kkli::list_node<int>(2); //operator ->
			list<int>::iterator iter6 = iter5;
			++iter6;
			iter6->prev = iter5.get();
			EXPECT_EQ_VAL(*iter6, 2);

			//operator ++(int)
			EXPECT_EQ_VAL(*(iter6++), 2);
			EXPECT_EQ_VAL(iter6.get(), nullptr);

			//operator --
			iter6 = kkli::next(iter5);
			--iter6;
			EXPECT_EQ_VAL(*iter6, 1);

			//operator --(int)
			EXPECT_EQ_VAL(*(iter6--), 1);
			EXPECT_EQ_VAL(iter6.get(), nullptr);

			//operator ==
			iter6 = iter5;
			EXPECT_EQ_VAL(iter6 == iter5, true);
			++iter6;
			EXPECT_EQ_VAL(iter6 == iter5, false);
		}

		//²âÊÔ constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			list<int> lst1; //list()
			EXPECT_EQ_VAL(lst1.empty(), true);

			list<int> lst2(4, 1); //list(count, value)
			EXPECT_EQ_ITERVAL(lst2.begin(), lst2.end(), 1);

			list<int> lst3(4); //list(count)
			EXPECT_EQ_ITERVAL(lst3.begin(), lst3.end(), 0);

			list<int> lst4(lst2); //list(rhs)
			EXPECT_EQ_ITERVAL(lst4.begin(), lst4.end(), 1);

			list<int> lst5(std::move(lst3)); //list(&&rhs)
			EXPECT_EQ_ITERVAL(lst5.begin(), lst5.end(), 0);

			list<int> lst6{ 1,2,3,4 };
			EXPECT_EQ_ITERLIST(lst6.begin(), lst6.end(), { 1,2,3,4 });
		}

		//²âÊÔ operator=
		void test_op_assign() {
			cout << "test: operator=" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			list<int> lst3{ 5,6,7,8 };
			list<int> lst4;

			lst1 = lst2; //operator(rhs)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
			
			lst1 = lst4;
			EXPECT_EQ_VAL(lst1.empty(), true);

			lst1 = std::move(lst3); //operator(&&rhs)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 5,6,7,8 });

			lst1 = std::move(lst4);
			EXPECT_EQ_VAL(lst1.empty(), true);
		}

		//²âÊÔ assign
		//TODO: 
		
		/*
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

		//²âÊÔ merge
		void test_merge() {
			cout << "\ntest_merge()" << endl;

			list<int> list1;
			list<int> list2{ 1,2,3,4 };
			list1.merge(std::move(list2));
			list1.print("list1");			//list1: 1 2 3 4
			list2.print("list2");			//list2: 
			
			list<int> list3{ 1,3,5,7 };
			list<int> list4{ 2,4,6,8 };
			list3.merge(std::move(list4), [](int val1, int val2)->bool {return val1 < val2; });
			list3.print("list3");
			list4.print("list4");

			list1.merge(std::move(list3));
			list1.print("list1");
			list3.print("list3");
		}

		//²âÊÔ splice
		void test_splice() {
			cout << "\ntest_splice()" << endl;

			list<int> list1{ 1 };
			list<int> list2{ 1,2,3,4 };
			list1.splice(list1.begin(), list2, list2.begin(), list2.end());
			list1.print("list1");			//list1: 1 1 2 3 4
			list2.print("list2");			//list2: 

			list<int> list3{ 1,2,3,4 };
			list<int>::iterator l3_iter = list3.begin();
			++l3_iter;
			list<int>::iterator l1_iter = list1.begin();
			++++++++l1_iter;
			list1.splice(l1_iter, list3, l3_iter, list3.end());
			list3.print("list3");			//list3: 1
			list1.print("list1");			//list1: 1 1 2 3 4 2 3 4
		}

		//²âÊÔ remove
		void test_remove() {
			cout << "\ntest_remove()" << endl;

			list<int> list1{ 1,2,3,4 };
			for (int i = 1; i < 5; ++i) {
				list1.remove(i);
				list1.print("list1");
			}
			list1.remove(1);
			list1.print("list1");		//list1: 
		}

		//²âÊÔ remove_if
		void test_remove_if() {
			cout << "\ntest_remove_if()" << endl;

			list<int> list1{ 1,1,2,2,3,3,4,4 };
			list1.remove_if([](int i)->bool {return i % 2; });		//ÒÆ³ıÆæÊı
			list1.print("list1");		//list1: 2 2 4 4
			list1.remove_if([](int i)->bool {return i == 2; });		//ÒÆ³ı2
			list1.print("list1");		//list1: 4 4
		}

		//²âÊÔ reverse
		void test_reverse() {
			cout << "\ntest_reverse()" << endl;

			list<int> list1;
			list1.reverse();
			list1.print("list1");		//list1: 

			list<int> list2{ 1,2,3,4 };
			list2.reverse();
			list2.print("list2");		//list2: 4 3 2 1
		}

		//²âÊÔ unique
		void test_unique() {
			cout << "\ntest_unique()" << endl;

			list<int> list1;
			list1.unique();
			list1.print("list1");		//list1: 

			list<int> list2{ 1,1,2,2,3,3,4,5,6,6,7,8,8 };
			list2.unique();
			list2.print("list2");		//list2: 1 2 3 4 5 6 7 8

			list<int> list3{ 1,2,3,4 };
			list3.unique();
			list3.print("list3");		//list3: 1 2 3 4
		}

		//²âÊÔ sort
		void test_sort() {
			cout << "\ntest_sort()" << endl;

			list<int> list1;
			list1.sort();
			list1.print("list1");		//list1: 

			list<int> list2{ 1,3,4,2 };
			list2.sort();
			list2.print("list2");		//list2: 1 2 3 4

			list<int> list3{ 1,1,4,3,3,4,2,2 };
			list3.sort();
			list3.print("list3");		//list3: 1 1 2 2 3 3 4 4

			list<int> list4{
				1,2,3,4,7,6,5,8,10,9
				,1,2,3,4,7,6,5,8,10,9
				,1,2,3,4,7,6,5,8,10,9
				,1,2,3,4,7,6,5,8,10,9
				,1,2,3,4,7,6,5,8,10,9
			};
			list4.sort();
			list4.print("list4");
		}

		//²âÊÔ operator == / != / < / <= / > / >=
		void test_operators() {
			cout << "\ntest_operators()" << endl;


			list<int> list1;
			list<int> list2{ 1,1,1,1 };
			list<int> list3{ 1,2,3,4 };
			list<int> list4{ 1,2,3,4,5 };
			list<int> list5{ 1,3,5,7,9 };

			//operator ==
			cout << "operator==" << endl;
			cout << (list1 == list1 ? "true" : "false") << endl;		//true
			cout << (list2 == list2 ? "true" : "false") << endl;		//true
			cout << (list1 == list2 ? "true" : "false") << endl;		//false;
			cout << (list2 == list3 ? "true" : "false") << endl;		//false
			cout << (list3 == list4 ? "true" : "false") << endl;		//false
			cout << endl;
			
			//operator !=
			cout << "operator!=" << endl;
			cout << (list1 != list1 ? "true" : "false") << endl;		//fals
			cout << (list2 != list2 ? "true" : "false") << endl;		//false
			cout << (list1 != list2 ? "true" : "false") << endl;		//true
			cout << (list2 != list3 ? "true" : "false") << endl;		//true
			cout << (list3 != list4 ? "true" : "false") << endl;		//true
			cout << endl;

			//operator <
			cout << "operator<" << endl;
			cout << (list1 < list1 ? "true" : "false") << endl;			//false
			cout << (list1 < list2 ? "true" : "false") << endl;			//true
			cout << (list2 < list2 ? "true" : "false") << endl;			//false
			cout << (list2 < list3 ? "true" : "false") << endl;			//true
			cout << (list2 < list1 ? "true" : "false") << endl;			//false
			cout << (list3 < list2 ? "true" : "false") << endl;			//false
			cout << (list3 < list4 ? "true" : "false") << endl;			//true
			cout << (list4 < list3 ? "true" : "false") << endl;			//false
			cout << (list3 < list5 ? "true" : "false") << endl;			//true
			cout << endl;

			//operator <=
			cout << "operator<=" << endl;
			cout << (list1 <= list1 ? "true" : "false") << endl;		//true
			cout << (list1 <= list2 ? "true" : "false") << endl;		//true
			cout << (list2 <= list3 ? "true" : "false") << endl;		//true
			cout << (list2 <= list1 ? "true" : "false") << endl;		//false
			cout << (list3 <= list2 ? "true" : "false") << endl;		//false
			cout << (list3 <= list5 ? "true" : "false") << endl;		//true
			cout << endl;

			//operator >
			cout << "operator>" << endl;
			cout << (list1 > list1 ? "true" : "false") << endl;			//false
			cout << (list1 > list2 ? "true" : "false") << endl;			//false
			cout << (list2 > list2 ? "true" : "false") << endl;			//false
			cout << (list2 > list3 ? "true" : "false") << endl;			//false
			cout << (list2 > list1 ? "true" : "false") << endl;			//true
			cout << (list3 > list2 ? "true" : "false") << endl;			//true
			cout << (list3 > list4 ? "true" : "false") << endl;			//false
			cout << (list4 > list3 ? "true" : "false") << endl;			//true
			cout << (list3 > list5 ? "true" : "false") << endl;			//false
			cout << endl;

			//operator >=
			cout << "operator>=" << endl;
			cout << (list1 >= list1 ? "true" : "false") << endl;		//true
			cout << (list1 >= list2 ? "true" : "false") << endl;		//false
			cout << (list2 >= list2 ? "true" : "false") << endl;		//true
			cout << (list2 >= list3 ? "true" : "false") << endl;		//false
			cout << (list2 >= list1 ? "true" : "false") << endl;		//true
			cout << (list3 >= list2 ? "true" : "false") << endl;		//true
			cout << (list3 >= list4 ? "true" : "false") << endl;		//false
			cout << (list4 >= list3 ? "true" : "false") << endl;		//true
			cout << (list3 >= list5 ? "true" : "false") << endl;		//false
		}
		*/
	}
}
