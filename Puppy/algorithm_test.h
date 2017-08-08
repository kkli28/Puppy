#pragma once

#include "stdafx.h"
#include "test.h"
#include "algorithm.h"
#include "string.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;
		using kkli::string;

		//前置声明
		void test_part1();
		void test_part2();
		void test_part3();
		void test_part4();
		void test_part5();
		void test_part6();
		void test_part7();
		void test_part8();

		//整体测试
		void test() {
			cout << "\n========== test: algorithm.h ==========" << endl;

			test_part1();
			//test_part2();
			//test_part3();
			//test_part4();
			//test_part5();
			//test_part6();
			//test_part7();
			//test_part8();
		}

		//测试 part1
		void test_part1() {
			cout << "test: part1" << endl;

			//all_of
			string str1;
			string str2("aaaa");
			char c1 = 'a';
			auto lmd1 = [&](char c)->bool {return c == c1; };
			EXPECT_EQ_VAL(kkli::all_of(str1.begin(), str1.end(), lmd1), true);
			EXPECT_EQ_VAL(kkli::all_of(str2.begin(), str2.end(), lmd1), true);
			c1 = 'b';
			EXPECT_EQ_VAL(kkli::all_of(str1.begin(), str1.end(), lmd1), true);
			EXPECT_EQ_VAL(kkli::all_of(str2.begin(), str2.end(), lmd1), false);

			//any_of
			string str3("abcd");
			EXPECT_EQ_VAL(kkli::any_of(str1.begin(), str1.end(), lmd1), false);
			EXPECT_EQ_VAL(kkli::any_of(str3.begin(), str3.end(), lmd1), true);
			c1 = 'e';
			EXPECT_EQ_VAL(kkli::any_of(str3.begin(), str3.end(), lmd1), false);

			//non_of
			EXPECT_EQ_VAL(kkli::none_of(str1.begin(), str1.end(), lmd1), true);
			EXPECT_EQ_VAL(kkli::none_of(str3.begin(), str3.end(), lmd1), true);
			c1 = 'a';
			EXPECT_EQ_VAL(kkli::none_of(str3.begin(), str3.end(), lmd1), false);

			//TODO: 
		}
	}
}