#pragma once

#include "stdafx.h"
#include "string.h"

namespace test {
	namespace string_test {

		using std::cin;
		using std::cout;
		using std::endl;
		using string = kkli::string<char>;
#define npos kkli::string<char>::npos

		//前置声明：成员函数
		void test_constructor();
		void test_op_assign();					//operator =
		void test_op_square_bracket();			//operator []
		void test_op_add_equal();				//operator +=
		void test_assign();
		void test_insert();
		void test_erase();
		void test_append();
		void test_compare();
		void test_replace();
		//void test_find();						//该函数暂未实现
		void test_c_str();
		void test_at();
		void test_front_and_back();
		void test_begin_and_end();
		void test_data();
		void test_empty();
		void test_size();
		void test_reserve();
		void test_clear();
		void test_push_back();
		void test_pop_back();
		void test_resize();
		void test_substr();
		void test_copy();
		void test_swap();
		
		//前置声明：非成员函数
		void test_op_add();						//operator +
		void test_op_compare();					//operator == != < <= > >=
		void test_op_stream();					//operator << >>
		void test_get_line();
		//void test_stox();						//函数暂未实现

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: string " << endl;
			cout << "========================================" << endl;

			//测试：成员函数
			test_constructor();
			test_op_assign();			//operator =
			test_op_square_bracket();	//operator []
			test_op_add_equal();		//operator +=
			test_assign();
			test_insert();
			//test_erase();
			//test_append();
			//test_compare();
			//test_replace();
			//test_find();				//该函数暂未实现
			//test_c_str();
			//test_at();
			//test_front_and_back();
			//test_begin_and_end();
			//test_data();
			//test_empty();
			//test_size();
			//test_reserve();
			//test_clear();
			//test_push_back();
			//test_pop_back();
			//test_resize();
			//test_substr();
			//test_copy();
			//test_swap();

			//测试：非成员函数
			//test_op_add();				//operator +
			//test_op_compare();			//operator == != < <= > >=
			//test_op_stream();			//operator << >>
			//test_get_line();
			//test_stox();				//函数暂未实现
		}

		//测试 constructor
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			//string()
			string str1;
			str1.print("str1");				//(空)

			//string(count, value)
			string str2(4, 'a');
			str2.print("str2");				//aaaa

			//string(rhs, pos, count)
			string str3(str2, 1, 2);
			string str4(str2, 0, npos);
			str3.print("str3");				//aa
			str4.print("str4");				//aaaa

			//string(data, count)
			string str5("abcd", 3);
			string str6("abcd", 2);
			string str7("abcd");
			str5.print("str5");				//abc
			str6.print("str6");				//ab
			str7.print("str7");				//abcd

			//string(count)
			string str8(4);					//(空)
			str8.print("str8");

			//string(first, last)
			string str9(str7.cbegin(), str7.cend());
			str9.print("str9");				//abcd

			//string(rhs)
			string str10(str9);
			str10.print("str10");			//abcd

			//string(&&rhs)
			string str11(std::move(str10));
			str11.print("str11");			//(空)

			//string(init)
			string str12({ 'a','b','c','d' });
			str12.print("str12");			//abcd
		}

		//测试 operator =
		void test_op_assign() {
			cout << "\ntest_op_assign()" << endl;

			string str1("abcd");
			string str2("efgh");
			string str3("ijkl");

			//operator =(rhs)
			str1 = str2;
			str1.print("str1");			//efgh

			//operator =(&&rhs)
			str1 = std::move(str3);
			str1.print("str1");			//ijkl

			//operator =(data)
			str1 = "mnop";
			str1.print("str1");			//mnop

			//operator =(init)
			str1 = { 'q','r','s','t' };
			str1.print("str1");			//qrst
		}

		//测试 operator []
		void test_op_square_bracket() {
			cout << "\ntest_square_bracket()" << endl;

			string str1("abcd");

			for (int i = 0; i < 4; ++i)
				cout << str1[i];
			cout << endl;

			for (int i = 0; i < 4; ++i)
				str1[i] = 'a';

			for (int i = 0; i < 4; ++i)
				cout << str1[i];
			cout << endl;
		}

		//测试 operator +=
		void test_op_add_equal() {
			cout << "\ntest_op_add_equal()" << endl;

			string str1("abcd");
			string str2("efgh");

			//operator +=(rhs)
			str1 += str2;
			str1.print("str1");				//abcdefgh

			//operator +=(data)
			str1 += "ijkl";
			str1.print("str1");				//abcdefghijkl

			//operator +=(init)
			str1 += {'m', 'n', 'o', 'p'};
			str1.print("str1");				//abcdefghijklmnop
		}

		//测试 assign
		void test_assign() {
			cout << "\ntest_assign()" << endl;

			string str1;
			string str2("abcd");
			string str3("efgh");

			//assign(count, value)
			str1.assign(4, 'a');
			str1.print("str1");				//aaaa

			//assign(rhs)
			str1.assign(str2);
			str1.print("str1");				//abcd

			//assign(&&rhs)
			str1.assign(std::move(str3));
			str1.print("str1");				//efgh

			//assign(rhs, pos, count)
			str1.assign(str2, 1, 2);
			str1.print("str1");				//bc
			str1.assign(str2, 0, npos);
			str1.print("str1");				//abcd

			//assign(data, count)
			str1.assign("aaaa", 2);
			str1.print("str1");				//aa
			str1.assign("aaaa", npos);
			str1.print("str1");				//aaaa

			//assign(first, last)
			str1.assign(str2.cbegin(), str2.cend());
			str1.print("str1");				//abcd

			//assign(init)
			str1.assign({ 'e','f','g','h' });
			str1.print("str1");
		}

		//测试 insert
		void test_insert() {
			cout << "\ntest_insert()" << endl;

			string str1;
			string str2("abcd");

			//insert(pos, first, last)
			str1.insert(str1.cend(), str2.cbegin(), str2.cend());
			str1.print("str1");						//abcd

			//insert(pos, count, value)
			str1.insert(str1.cbegin(), 2, 'a');
			str1.print("str1");						//aaabcd

			//insert(index,rhs, index_rhs, count)
			str1.insert(0, str2, 0, 2);
			str1.print("str1");						//abaaabcd

			//insert(index, data, count)
			str1.insert(7, "abcd", 3);
			str1.print("str1");						//abaaabcdabc

			//insert(index, rhs)
			str1.insert(4, str2);
			str1.print("str1");						//abaaabcdabcdabc

			//insert(index, count, value)
			str1.insert(1, 4, 'a');
			str1.print("str1");						//aaaaabaaabcdabcdabc

			//insert(pos, value)
			str1.insert(str1.cend(), 'd');
			str1.print("str1");						//aaaaabaaabcdabcdabcd

			//insert(pos, init)
			str1.insert(0, { 'q','w','e','r' });
			str1.print("str1");						//qertaaaaabaaabcdabcdabcd
		}
	}
}