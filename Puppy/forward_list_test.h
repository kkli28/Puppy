#pragma once

#include "stdafx.h"
#include "forward_list.h"

namespace test {
	namespace forward_list_test {
		using std::cout;
		using std::endl;
		using std::string;

		using kkli::forward_list;

		//ǰ������
		void test_iterator();
		void test_constructor();
		void test_destructor();
		void test_begin_end();
		void test_push_front();
		void test_pop_front();
		void test_insert_after();
		void test_erase_after();
		void test_remove();
		void test_resize();
		void test_operator();
		void test_assign();
		void test_swap();

		//�������
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: forward_list " << endl;
			cout << "========================================" << endl;

			test_iterator();
			test_constructor();
			test_destructor();
			test_begin_end();
			test_push_front();
			test_pop_front();
			test_insert_after();
			test_erase_after();
			test_remove();
			test_resize();
			test_operator();
			test_assign();
			test_swap();
		}

		//���� iterator
		void test_iterator() {
			cout << "\ntest_iterator()" << endl;

			//constructors
			forward_list<int>::iterator it1 = 1;
			cout << *it1 << endl;			//operator*
			forward_list<int>::iterator it2 = it1;
			cout << *it2 << endl;

			//operators
			it2 = it1;			//operator=
			cout << *it1 << "  " << *it2 << endl;
			cout << *(it1++) << endl;		//operator++(int)
			//cout << *(++it2) << endl;		//operator++
			it1 = forward_list<int>::iterator(1);
			it2 = it1;
			if (it1 == it2) cout << "it1==it2" << endl;
			else if(it1!=it2) cout << "it1!=it2" << endl;
			else cout << "WRONG!" << endl;

			cout << it1->value << endl;		//operator->
			it1->value = 2;
			cout << it1->value << endl;

			const forward_list<int>::iterator cit = 1;	//operator->
			cout << cit->value << endl;
		}

		//���� constructor
		void test_constructor(){
			cout << "\ntest_constructor()" << endl;

			forward_list<int> fl1;
			cout << (fl1.empty() ? "empty" : "not-empty") << endl;
			forward_list<int> fl2{ 1,2,3,4 };
			forward_list<int> fl3(fl2);
			cout << "fl2: ";
			fl2.print();
			cout << "fl3: ";
			fl3.print();

			forward_list<int> fl4(std::move(fl2));
			cout << "fl2: ";
			fl2.print();
			cout << "fl4: ";
			fl4.print();
			
			forward_list<int> fl5(4);
			cout << "fl5: ";
			fl5.print();

			forward_list<int> fl6(4, 1);
			cout << "fl6: ";
			fl6.print();

			forward_list<int> fl7(fl6.begin(), fl6.end());
			cout << "fl7: ";
			fl7.print();
		}

		//���� destructor
		void test_destructor() {
			cout << "\ntest_destructor()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			fl.~forward_list();
			fl.print();
		}

		//���� begin / end
		void test_begin_end() {
			cout << "\ntest_begin_end()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			cout << *(fl.begin()) << endl;
			cout << *(fl.cbegin()) << endl;
		}

		//���� push_front
		void test_push_front() {
			cout << "\ntest_push_front()" << endl;

			forward_list<int> fl;
			for (int i = 0; i < 4; ++i)
				fl.push_front(i);
			fl.print();
		}

		//���� pop_front
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

		//���� insert_after
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

		//���� erase_after
		void test_erase_after() {
			cout << "\ntest_erase_after()" << endl;

			forward_list<int> fl{ 1,2,3,4 };
			fl.erase_after(0);
			fl.erase_after(1);
			fl.print();
			
			fl.erase_after(0);
			fl.print();
		}

		//���� remove
		void test_remove() {
			cout << "\ntest_remove()" << endl;

			forward_list<int> fl{ 1,2,3,4,1,2,3,4 };
			fl.remove(1);
			fl.print();
			fl.remove(4);
			fl.print();

			forward_list<int> fl1{ 1,2,3,4,5,6 };
			//ȥ������
			fl1.remove_if([](const int& elem) -> bool { return elem % 2; });
			fl1.print();
		}

		//���� resize
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

		//���� operators
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

		//���� assign
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

		//���� swap
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
	}
}
