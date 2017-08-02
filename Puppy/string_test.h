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
		void test_destructor();
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
			//test_constructor();
			//test_destructor();
			//test_op_assign();			//operator =
			//test_op_square_bracket();	//operator []
			//test_op_add_equal();		//operator +=
			//test_assign();
			//test_insert();
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
			str1.print("str1");

			//string(count, value)
			string str2(4, 'a');
			str2.print("str2");

			//string(rhs, pos, count)
			string str3(str2, 1, 2);
			string str4(str2, 0, npos);

			//TODO: 
		}
	}
}