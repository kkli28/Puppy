#pragma once

#include "stdafx.h"
#include "my_pair.h"

namespace test {
	namespace my_pair_test {
		using std::cout;
		using std::endl;
		using std::string;

		using kkli::my_pair;
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

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: my_pair " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_types();
			test_op_equal();
			test_swap();
			test_make_pair();
			test_op_logical();
			test_get();
		}

		//测试 my_pair
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			//my_pair()
			cout << "mp1: ";
			my_pair<int, int> mp1;

			//my_pair<const T1&, const T2&>

			//WRONG: 为何运行后全部都是my_pair<T1&&, T2&&> ???
			//WRONG !!!!!!;

			int ival = 1;
			string sval = "C++";
			cout << "mp2: ";
			my_pair<int, string> mp2(ival, sval);
			cout << "mp3: ";
			my_pair<int, string> mp3 = mp2;

			//my_pair<T1&&, T2&&>
			cout << "mp4: ";
			my_pair<int, int> mp4(1, 2);
			cout << "mp5: ";
			my_pair<int, string> mp5(1, "mp3");
			cout << "mp6: ";
			my_pair<string, int> mp6("mp4", 2);
			cout << "mp7: ";
			my_pair<int, string> mp7(std::move(ival), std::move(sval));
			cout << "mp8: ";
			my_pair<int, string> mp8(std::move(mp7));
		}

		//测试 first_type/second_type/first/second
		void test_types() {
			cout << "\ntest_types()" << endl;

			//first_type/second_type
			
			//first/second
			my_pair<int, string> mp(i, str);
			my_pair<int, string>::first_type ft = i;
			my_pair<int, string>::second_type st = str;
			
			cout << "ft: " << i << "    st: " << st << endl;
			cout << "first: " << mp.first << "    second: " << mp.second << endl;
		}

		//测试 operator=
		void test_op_equal() {
			cout << "\ntest_op_equal()" << endl;

			//operator=
			my_pair<int, string> mp1(i, str);
			my_pair<int, string> mp2;
			mp2 = mp1;
			cout << "mp2.first: " << mp2.first << "    mp2.second: " << mp2.second << endl;
		}
		
		//测试 member swap/non-member swap
		void test_swap() {
			cout << "\ntest_swap()" << endl;

			my_pair<int, string> mp1(i, str);
			my_pair<int, string> mp2(2,"C#");

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

			my_pair<int, string> mp = kkli::make_pair(i, str);
			cout << "mp.first: " << mp.first << "    mp.second: " << mp.second << endl;
		}

		//测试 operator < <= > >= == !=
		void test_op_logical() {
			cout << "\ntest_op_logical()" << endl;

			my_pair<int, string> mp1(i, str);
			my_pair<int, string> mp2(i, str);
			my_pair<int, string> mp3(i, str + "C++");
			my_pair<int, int> mp4(1, 2);
			my_pair<int, int> mp5(3, 4);

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

			my_pair<int, string> mp(i, str);
			cout << "get<0>: " << get<0>(mp) << endl;
			cout << "get<1>: " << get<1>(mp) << endl;
		}
	}
}