#pragma once

#include "stdafx.h"
#include "pair.h"

namespace test {
	namespace pair_test {
		using std::cout;
		using std::endl;
		using std::string;

		using kkli::pair;
		using kkli::swap;
		using kkli::get;
		using kkli::make_pair;

		int i = 1;
		string str = "C++";

		//函数前置声明
		void test_constructor();
		void test_types();
		void test_op_equal();
		void test_swap();
		void test_make_pair();
		void test_op_logical();
		void test_get();
		void test_tuple_size();
		void test_tuple_element();

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: pair " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_types();
			test_op_equal();
			test_swap();
			test_make_pair();
			test_op_logical();
			test_get();
			test_tuple_size();
			test_tuple_element();
		}

		//测试 pair
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			//pair()
			cout << "mp1: ";
			pair<int, int> mp1;

			//pair<const T1&, const T2&>

			//WRONG: 为何运行后全部都是pair<T1&&, T2&&> ???
			//WRONG !!!!!!;

			int ival = 1;
			string sval = "C++";
			cout << "mp2: ";
			pair<int, string> mp2(ival, sval);
			cout << "mp3: ";
			pair<int, string> mp3 = mp2;

			//pair<T1&&, T2&&>
			cout << "mp4: ";
			pair<int, int> mp4(1, 2);
			cout << "mp5: ";
			pair<int, string> mp5(1, "mp3");
			cout << "mp6: ";
			pair<string, int> mp6("mp4", 2);
			cout << "mp7: ";
			pair<int, string> mp7(std::move(ival), std::move(sval));
			cout << "mp8: ";
			pair<int, string> mp8(std::move(mp7));
		}

		//测试 first_type/second_type/first/second
		void test_types() {
			cout << "\ntest_types()" << endl;

			//first_type/second_type
			
			//first/second
			pair<int, string> mp(i, str);
			pair<int, string>::first_type ft = i;
			pair<int, string>::second_type st = str;
			
			cout << "ft: " << i << "    st: " << st << endl;
			cout << "first: " << mp.first << "    second: " << mp.second << endl;
		}

		//测试 operator=
		void test_op_equal() {
			cout << "\ntest_op_equal()" << endl;

			//operator=
			pair<int, string> mp1(i, str);
			pair<int, string> mp2;
			mp2 = mp1;
			cout << "mp2.first: " << mp2.first << "    mp2.second: " << mp2.second << endl;
		}
		
		//测试 member swap/non-member swap
		void test_swap() {
			cout << "\ntest_swap()" << endl;

			pair<int, string> mp1(i, str);
			pair<int, string> mp2(2,"C#");

			mp1.swap(mp2);
			cout << "mp1.first: " << mp1.first << "    mp1.second: " << mp1.second << endl;
			cout << "mp2.first: " << mp2.first << "    mp2.second: " << mp2.second << endl;

			swap(mp1, mp2);
			cout << "mp1.first: " << mp1.first << "    mp1.second: " << mp1.second << endl;
			cout << "mp2.first: " << mp2.first << "    mp2.second: " << mp2.second << endl;
		}

		//测试 make_pair
		void test_make_pair() {
			cout << "\ntest_make_pair()" << endl;

			pair<int, string> mp = kkli::make_pair(i, str);
			cout << "mp.first: " << mp.first << "    mp.second: " << mp.second << endl;
		}

		//测试 operator < <= > >= == !=
		void test_op_logical() {
			cout << "\ntest_op_logical()" << endl;

			pair<int, string> mp1(i, str);
			pair<int, string> mp2(i, str);
			pair<int, string> mp3(i, str + "C++");
			pair<int, int> mp4(1, 2);
			pair<int, int> mp5(3, 4);

			//operator ==
			cout << (mp1 == mp1 ? "==" : "!=") << endl;
			cout << (mp1 == mp2 ? "==" : "!=") << endl;
			cout << (mp1 == mp3 ? "==" : "!=") << endl;
			cout << (mp4 == mp4 ? "==" : "!=") << endl;
			cout << (mp4 == mp5 ? "==" : "!=") << endl << endl;

			//operator !=
			cout << (mp1 != mp1 ? "!=" : "==") << endl;
			cout << (mp1 != mp2 ? "!=" : "==") << endl;
			cout << (mp1 != mp3 ? "!=" : "==") << endl;
			cout << (mp4 != mp4 ? "!=" : "==") << endl;
			cout << (mp4 != mp5 ? "!=" : "==") << endl << endl;

			//operator <
			cout << (mp1 < mp1 ? "<" : ">=") << endl;
			cout << (mp1 < mp2 ? "<" : ">=") << endl;
			cout << (mp1 < mp3 ? "<" : ">=") << endl;
			cout << (mp4 < mp4 ? "<" : ">=") << endl;
			cout << (mp4 < mp5 ? "<" : ">=") << endl << endl;

			//operator <=
			cout << (mp1 <= mp1 ? "<=" : ">") << endl;
			cout << (mp1 <= mp2 ? "<=" : ">") << endl;
			cout << (mp1 <= mp3 ? "<=" : ">") << endl;
			cout << (mp4 <= mp4 ? "<=" : ">") << endl;
			cout << (mp4 <= mp5 ? "<=" : ">") << endl << endl;

			//operator >
			cout << (mp1 > mp1 ? ">" : "<=") << endl;
			cout << (mp1 > mp2 ? ">" : "<=") << endl;
			cout << (mp1 > mp3 ? ">" : "<=") << endl;
			cout << (mp4 > mp4 ? ">" : "<=") << endl;
			cout << (mp4 > mp5 ? ">" : "<=") << endl << endl;

			//operator >=
			cout << (mp1 >= mp1 ? ">=" : "<") << endl;
			cout << (mp1 >= mp2 ? ">=" : "<") << endl;
			cout << (mp1 >= mp3 ? ">=" : "<") << endl;
			cout << (mp4 >= mp4 ? ">=" : "<") << endl;
			cout << (mp4 >= mp5 ? ">=" : "<") << endl << endl;
		}

		//测试 get
		void test_get() {
			cout << "\ntest_get()" << endl;

			pair<int, string> mp(i, str);
			cout << "get<0>: " << get<0>(mp) << endl;
			cout << "get<1>: " << get<1>(mp) << endl;
		}

		//测试 tuple_size
		void test_tuple_size() {
			cout << "\ntest_tuple_size()" << endl;

			cout << kkli::tuple_size<pair<int, string>>::value << endl;
		}

		//测试 tuple_elememt
		void test_tuple_element() {
			cout << "\ntest_tuple_element()" << endl;

			kkli::tuple_element<0, pair<int, string>>::type t1 = 1;
			kkli::tuple_element<1, pair<int, string>>::type t2 = "C++";
			cout << t1 << " " << t2 << endl;
		}
	}
}