#pragma once

#include "stdafx.h"
#include "forward_list.h"

namespace test {
	namespace forward_list_test {
		using std::cout;
		using std::endl;
		using std::string;

		using kkli::forward_list;
		using kkli::Node;

		//º¯ÊıÇ°ÖÃÉùÃ÷
		void test_constructors();
		void test_iterator();
		void test_typedefs();
		void test_ops();
		void test_pointer_ops();
		void test_begin_end();

		//ÕûÌå²âÊÔ
		void test() {
			cout << "========== test: forward_list ==========" << endl;

			test_constructors();
			test_iterator();
			test_typedefs();
			test_ops();
			test_pointer_ops();
			test_begin_end();
		}

		//²âÊÔ constructor
		void test_constructors() {
			cout << "========== test: constructor ==========" << endl;

			forward_list<int> fl1;
			fl1.print();
			
			forward_list<int> fl2{ 0,1,2,3 };
			fl2.print();

			forward_list<int> fl3(fl2);
			fl3.print();
		}

		//²âÊÔ iterator
		void test_iterator() {
			cout << "========== test: constructor ==========" << endl;
			forward_list<int> fl1{ 0,1,2,3 };
			cout << *(fl1.begin()) << endl;
			cout << *(fl1.end()) << endl;
			for (auto begin=fl1.begin(); begin != fl1.end(); ++begin) {
				cout << *begin << " ";
			}
			cout << endl;
		}

		//²âÊÔ typedefs
		void test_typedefs() {
			//typedefs
			/*
			typedef T					value_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef Node<T>*			pointer;
			typedef const Node<T>*		const_pointer;

			typedef Iter				iterator;
			typedef const iterator		const_iterator;
			*/
			//value_type / size_type / difference_type
			cout << forward_list<int>::value_type(1) << endl;
			cout << forward_list<int>::size_type(1) << endl;
			cout << forward_list<int>::difference_type(1) << endl;

			//reference / const_reference
			int i = 1;
			forward_list<int>::reference r = i;
			cout << r << endl;
			forward_list<int>::const_reference cr = i;
			cout << cr << endl;

			//iterator / const_iterator
			forward_list<int> fl{ 1,2,3,4 };
			forward_list<int>::iterator iter = fl.begin();
			cout << *iter << endl;
			iter = ++fl.begin();
			cout << *iter << endl;
			++iter;
			cout << *iter << endl;

			forward_list<int>::const_iterator citer = fl.begin();
			cout << *citer << endl;
		}

		//²âÊÔ operator++ / operator++(int) / operator== / operator!= / operator= / operator*

		void test_ops() {

		}
	}
}