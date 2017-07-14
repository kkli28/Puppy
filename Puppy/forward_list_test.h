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

		//函数前置声明
		void test_constructors();
		void test_iterator();
		void test_typedefs();
		void test_ops();
		//void test_stl();			//测试与stl的兼容性，暂时无法兼容，iterator没有搞定

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: forward_list " << endl;
			cout << "========================================" << endl;

			test_constructors();
			test_iterator();
			test_typedefs();
			test_ops();
			//test_stl();
		}

		//测试 constructor
		void test_constructors() {
			cout << "========== test: constructor ==========" << endl;

			forward_list<int> fl1;
			fl1.print();
			
			forward_list<int> fl2{ 0,1,2,3 };
			fl2.print();

			forward_list<int> fl3(fl2);
			fl3.print();
		}

		//测试 iterator
		void test_iterator() {
			cout << "========== test: constructor ==========" << endl;

			forward_list<int> fl1{ 0,1,2,3 };
			cout << *(fl1.begin()) << endl;
			for (auto begin=fl1.begin(); begin != fl1.end(); ++begin) {
				cout << *begin << " ";
			}
			cout << endl;
		}

		//测试 typedefs
		void test_typedefs() {
			cout << "========== test: typedefs ==========" << endl;

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

		//测试 operator++ / operator++(int) / operator== / operator!= / operator= / operator*
		void test_ops() {
			cout << "========== test: ops ==========" << endl;

			//operator++
			forward_list<int> fl{ 1,2,3,4 };
			for (auto iter = fl.begin(); iter != fl.end(); ++iter) {
				cout << *iter << " ";
			}
			cout << endl;

			//operator++(int)
			auto iter1 = fl.begin();
			cout << *(iter1++) << endl;

			//operator== / operator!=
			auto iter2 = fl.begin();
			if (iter1 == iter2) cout << "iter1==iter2" << endl;
			else if (iter1 != iter2) cout << "iter1!=iter2" << endl;
			else cout << "iter1 ?? iter2" << endl;

			//operator=
			iter2 = iter1;

			//opertor*
			cout << *iter2 << endl;
		}
	}
}