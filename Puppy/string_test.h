#pragma once

#include "stdafx.h"
#include "string.h"

namespace test {
	namespace string_test {

		using std::cin;
		using std::cout;
		using std::endl;
		using kkli::string;
#define npos kkli::string::npos

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
		void test_reverse();

		//前置声明：非成员函数
		void test_op_add();						//operator +
		void test_op_compare();					//operator == != < <= > >=
		void test_op_stream();					//operator << >>
		void test_getline();
		//void test_stox();						//函数暂未实现
		void test_to_string();					//to_string(x)

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
			test_erase();
			test_append();
			test_compare();
			test_replace();
			//test_find();				//该函数暂未实现
			test_c_str();
			test_at();
			test_front_and_back();
			test_begin_and_end();
			test_data();
			test_empty();
			test_size();
			test_reserve();
			test_clear();
			test_push_back();
			test_pop_back();
			test_resize();
			test_substr();
			test_copy();
			test_swap();
			test_reverse();
			
			//测试：非成员函数
			test_op_add();				//operator +
			test_op_compare();			//operator == != < <= > >=
			//test_getline();
			//test_op_stream();			//operator << >>
			//test_stox();				//函数暂未实现
			test_to_string();
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
			str1.print("str1");						//abaaabcabcd

			//insert(index, rhs)
			str1.insert(4, str2);
			str1.print("str1");						//abaaabcdabcabcd

			//insert(index, count, value)
			str1.insert(1, 4, 'a');
			str1.print("str1");						//aaaaabaaabcdabcabcd

			//insert(pos, value)
			str1.insert(str1.cend(), 'd');
			str1.print("str1");						//aaaaabaaabcdabcabcdd

			//insert(pos, init)
			str1.insert(str1.begin(), { 'q','w','e','r' });
			str1.print("str1");						//qweraaaaabaaabcdabcdabcd
		}

		//测试 erase
		void test_erase() {
			cout << "\ntest_erase()" << endl;

			string str1("abcd");
			string str2 = str1;

			//erase(first, last)
			str2.erase(str2.begin() + 1, str2.begin() + 2);
			str2.print("str2");					//acd

			str2.erase(str2.begin(), str2.end());
			str2.print("str2");					//(空)

			//erase(index, count)
			str2 = str1;
			str2.erase(0, 2);
			str2.print("str2");					//cd

			str2.erase(1);						//c
			str2.print("str2");

			str2.erase((std::size_t)0);
			str2.print("str2");					//(空)

			//erase(pos)
			str2 = str1;
			for (std::size_t i = 0; i < 4; ++i) {
				str2.erase(str2.begin());
				str2.print("str2");
			}
		}

		//测试 append
		void test_append() {
			cout << "\ntest_append()" << endl;

			string str1;
			string str2("abcd");

			//append(rhs, pos, count)
			str1.append(str2, 0, 2);
			str1.print("str1");					//ab

			str1.append(str2, 2);
			str1.print("str1");					//abcd

			//append(data, count)
			str1.append("abcd", 2);
			str1.print("str1");					//abcdab

			str1.append("abcd");
			str1.print("str1");					//abcdababcd

			//append(count, value)
			str1.append(1, ' ');
			str1.append(4, 'a');
			str1.print("str1");					//abcdababcd aaaa

			//append(first, last)
			str1 = string();
			str1.append(str2.begin(), str2.end());
			str1.print("str1");					//abcd

			str1.append(str1.begin(), str1.end());
			str1.print("str1");					//abcdabcd

			//append(init)
			str1.append({ 'q','w','e','r' });
			str1.print("str1");					//abcdabcdqwer
		}

		//测试 compare
		void test_compare() {
			cout << "\ntest_compare()" << endl;

			string str1("abcd");
			string str2("aceg");
			string str3("abcdef");
			string str4("acegik");

			//compare(rhs)
			cout << "-- 1 --" << endl;
			cout << str1.compare(str1) << endl;				//0
			cout << str1.compare(str2) << endl;				//-1
			cout << str1.compare(str3) << endl;				//-1
			cout << str1.compare(str4) << endl;				//-1

			cout << str2.compare(str1) << endl;				//1
			cout << str2.compare(str2) << endl;				//0
			cout << str2.compare(str3) << endl;				//1
			cout << str2.compare(str4) << endl;				//-1

			cout << str3.compare(str1) << endl;				//1
			cout << str3.compare(str2) << endl;				//-1
			cout << str3.compare(str3) << endl;				//0
			cout << str3.compare(str4) << endl;				//-1

			cout << str4.compare(str1) << endl;				//1
			cout << str4.compare(str2) << endl;				//1
			cout << str4.compare(str3) << endl;				//1
			cout << str4.compare(str4) << endl;				//0

			//compare(pos, count, rhs)
			cout << "-- 2 --" << endl;
			cout << str1.compare(0, 4, str1) << endl;		//0
			cout << str1.compare(0, 3, str1) << endl;		//-1
			cout << str2.compare(0, 4, str1) << endl;		//1
			cout << str2.compare(0, 4, str2) << endl;		//0
			cout << str1.compare(0, 4, str3) << endl;		//-1

			cout << str1.compare(0, 4, str1, 0, 4) << endl;			//0
			cout << str1.compare(0, 4, str1, 2, 2) << endl;			//-1
			cout << str1.compare(0, 4, str2, 0, 4) << endl;			//-1
			cout << str2.compare(0, 4, str1, 0, 4) << endl;			//1
			cout << str1.compare(0, 4, str3) << endl;				//-1
			cout << str1.compare(0, 4, str1) << endl;				//0

			//compare(data)
			cout << "-- 3 --" << endl;
			cout << str1.compare("abcd") << endl;			//0
			cout << str1.compare("aceg") << endl;			//-1
			cout << str1.compare("aaaa") << endl;			//1
			cout << str1.compare("abcdef") << endl;			//-1
			cout << str1.compare("ab") << endl;				//1
			cout << str1.compare("cd") << endl;				//-1
			cout << str1.compare("") << endl;				//1

			//compare(pos1, count1, data, count2)
			cout << "-- 4 --" << endl;
			cout << str1.compare(0, 4, "abcd") << endl;		//0
			cout << str1.compare(0, 3, "abcd") << endl;		//-1
			cout << str2.compare(0, 4, "abcd") << endl;		//1
			cout << str2.compare(0, 4, "aceg") << endl;		//0
			cout << str1.compare(0, 4, "abcdef") << endl;	//-1

			cout << str1.compare(0, 4, "abcd", 4) << endl;		//0
			cout << str1.compare(0, 4, "abcd", 2) << endl;		//1
			cout << str1.compare(0, 4, "aceg", 4) << endl;		//-1
			cout << str2.compare(0, 4, "abcd", 4) << endl;		//1
			cout << str1.compare(0, 4, "abcdef", 4) << endl;	//0
			cout << str1.compare(0, 4, "abcdef", 6) << endl;	//-1
		}

		//测试 replace --- buggy
		void test_replace() {
			cout << "\ntest_replace()" << endl;

			string str1("abcd");
			string str2("qwer");

			//replace(first, last, first2, last2)无法正常匹配，故跳过
			str1.replace(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend());
			str1.print("str1");					//qwer

			//replace(first, last, count, value)
			str1.replace(str1.begin() + 1, str1.begin() + 3, 3, 'e');
			str1.print("str1");					//qeeer

			//replace(first, last, rhs)
			str1.replace(str1.begin(), str1.begin() + 1, str2);
			str1.print("str1");					//qwerqeeer

			//replace(first, last, data, count)
			str1.replace(str1.begin(), str1.begin() + 2, "abcd");
			str1.print("str1");					//abcderqeeer

			//replace(first, last, init)
			str1.replace(str1.begin(), str1.end(), { 'a','b','c','d' });
			str1.print("str1");					//abcd

			//replace(pos, count, rhs, pos2, count2)
			str1.replace(0, 2, str2, 0, 3);
			str1.print("str1");					//qwecd

			//replace(pos, count, count2, value)
			str1.replace(str1.begin(), str1.end(), 8, 'e');
			str1.print("str1");					//eeeeeeee
		}

		//测试 c_str
		void test_c_str() {
			cout << "\ntest_c_str()" << endl;

			string str1;
			string str2("abcd");

			char* cp1 = str1.c_str();
			char* cp2 = str2.c_str();
			cout << "str1: " << cp1 << endl;			//(空)
			cout << "str2: " << cp2 << endl;			//abcd

			cout << "str2对应位置字符: " << endl;
			for (int i = 0;; ++i) {
				if (cp2[i] == '\0') break;
				cout << i << ": " << cp2[i] << endl;
			}
		}

		//测试 at
		void test_at() {
			cout << "\ntest_at()" << endl;

			string str1("abcd");

			for (int i = 0; i < 4; ++i)
				cout << str1.at(i) << endl;
		}

		//测试 front和back
		void test_front_and_back() {
			cout << "\ntest_front_and_back()" << endl;

			string str1("abcd");
			cout << str1.front() << endl;
			cout << str1.back() << endl;
		}

		//测试 begin和end
		void test_begin_and_end() {
			cout << "\ntest_begin_and_end()" << endl;

			string str1;
			string str2("abcd");
			for (auto s : str1) cout << s;
			cout << endl;

			for (auto s : str2) cout << s;
			cout << endl;

			for (auto iter = str1.begin(); iter != str1.end(); ++iter)
				cout << *iter;
			cout << endl;

			for (auto iter = str2.begin(); iter != str2.end(); ++iter)
				cout << *iter;
			cout << endl;
		}

		//测试 data
		void test_data() {
			cout << "\ntest_data()" << endl;

			//可能内存访问越界导致异常
			cout << string().data() << endl;
			cout << string("abcd").data() << endl;
			cout << "上述乱码并不是程序错误，应为string::data()直接返回首地址，没有在末尾添加字符'\\0'" << endl;
		}

		//测试 empty
		void test_empty() {
			cout << "\ntest_empty()" << endl;

			cout << (string().empty() ? "empty" : "not empty") << endl;
			cout << (string("abcd").empty() ? "empty" : "not empty") << endl;
		}

		//测试 size
		void test_size() {
			cout << "\ntest_size()" << endl;

			string str1("abcd");
			cout << string().size() << endl;
			cout << str1.size() << endl;
			str1.append("ab");
			cout << str1.size() << endl;
			str1.print("str1");
		}

		//测试 reserve
		void test_reserve() {
			cout << "\ntest_reserve()" << endl;

			string str1;
			str1.reserve(4);
			str1.print("str1");				//(空)
			str1.reserve(2);
			str1.print("str1");				//(空)

			str1.append("abcdef");
			str1.print("str1");				//abcdef
			str1.reserve(24);
			str1.print("str1");				//abcdef
		}

		//测试 clear
		void test_clear() {
			cout << "\ntest_clear()" << endl;

			string str1("abcd");
			str1.clear();
			str1.print("str1");			//(空)
		}

		//测试 push_back
		void test_push_back() {
			cout << "\ntest_push_back()" << endl;

			string str1;
			for (int i = 0; i < 4; ++i) {
				str1.push_back('a');
				str1.print("str1");
			}
		}

		//测试 pop_back
		void test_pop_back() {
			cout << "\ntest_pop_back()" << endl;

			string str1("abcd");
			for (int i = 0; i < 4; ++i) {
				str1.pop_back();
				str1.print("str1");
			}
		}

		//测试 resize
		void test_resize() {
			cout << "\ntest_resize()" << endl;

			string str1;
			str1.resize(4);
			str1.print("str1");				//(空)

			str1.resize(8, 'a');
			str1.print("str1");				//aaaaaaaa
			
			str1.resize(4);
			str1.print("str1");				//aaaaaaaa
		}

		//测试 substr
		void test_substr() {
			cout << "\ntest_substr()" << endl;

			string str("abcdefgh");
			string str1 = str.substr();
			str1.print("str1");					//abcdefgh

			str1 = str.substr(1, 4);
			str1.print("str1");					//bcde

			str1 = str.substr(4);
			str1.print("str1");					//efgh
		}

		//测试 copy
		void test_copy() {
			cout << "\ntest_copy()" << endl;

			string str1;
			cout << str1.copy("abcd") << endl;
			str1.print("str1");					//abcd

			cout << str1.copy("abcd", 2) << endl;
			str1.print("str1");					//cd

			cout << str1.copy("abcd", 1, 2) << endl;
			str1.print("str1");					//bc
		}

		//测试 swap
		void test_swap() {
			cout << "\ntest_swap()" << endl;

			string str1;
			string str2("abcd");
			string str3("qwerty");

			str1.swap(str2);
			str1.print("str1");			//abcd
			str2.print("str2");			//(空)

			str1.swap(str3);
			str1.print("str1");			//qwerty
			str3.print("str3");			//abcd
		}

		//测试 reverse()
		void test_reverse() {
			cout << "\ntest_reverse()" << endl;

			string str1("abcd");
			str1.reverse();
			str1.print("str1");			//dcba

			string str2("qwert");
			str2.reverse();
			str2.print("str2");			//trewq
		}

		//测试：非成员函数 operator +
		void test_op_add() {
			cout << "\ntest_op_add()" << endl;

			string str1;
			string str2("abcd");
			string str3("qwerty");

			cout << str1 + str2 << endl;		//abcd
			cout << str1 + str3 << endl;		//qwerty
			cout << str2 + str1 << endl;		//abcd
			cout << str2 + str3 << endl;		//abcdqwerty
			cout << str3 + str1 << endl;		//qwerty
			cout << str3 + str2 << endl;		//qwertyabcd
		}

		//测试：非成员函数 operator == < >
		//由于!=由==实现，>=由<实现，<=由>实现，因此不再单独测试!=, <=, >=
		void test_op_compare() {
			cout << "\ntest_op_compare()" << endl;

			string str1;
			string str2("abcd");
			char* str3 = "aceg";
			string str4("abcdef");
			string str5("acegik");

			//operator ==
			cout << "operator ==" << endl;
			cout << (str1 == str1 ? "true" : "false") << endl;				//true
			cout << (str1 == str2 ? "true" : "false") << endl;				//false
			cout << (str1 == str3 ? "true" : "false") << endl;				//false
			cout << (str1 == str4 ? "true" : "false") << endl;				//false
			cout << (str1 == str5 ? "true" : "false") << endl << endl;		//false
			
			cout << (str2 == str1 ? "true" : "false") << endl;				//false
			cout << (str2 == str2 ? "true" : "false") << endl;				//true
			cout << (str2 == str3 ? "true" : "false") << endl;				//false
			cout << (str2 == str4 ? "true" : "false") << endl;				//false
			cout << (str2 == str5 ? "true" : "false") << endl << endl;		//false

			cout << (str3 == str1 ? "true" : "false") << endl;				//false
			cout << (str3 == str2 ? "true" : "false") << endl;				//false
			cout << (str3 == str3 ? "true" : "false") << endl;				//true
			cout << (str3 == str4 ? "true" : "false") << endl;				//false
			cout << (str3 == str5 ? "true" : "false") << endl << endl;		//false

			cout << (str4 == str1 ? "true" : "false") << endl;				//false
			cout << (str4 == str2 ? "true" : "false") << endl;				//false
			cout << (str4 == str3 ? "true" : "false") << endl;				//false
			cout << (str4 == str4 ? "true" : "false") << endl;				//true
			cout << (str4 == str5 ? "true" : "false") << endl << endl;		//false

			cout << (str5 == str1 ? "true" : "false") << endl;				//false
			cout << (str5 == str2 ? "true" : "false") << endl;				//false
			cout << (str5 == str3 ? "true" : "false") << endl;				//false
			cout << (str5 == str4 ? "true" : "false") << endl;				//false
			cout << (str5 == str5 ? "true" : "false") << endl << endl;		//true

			//operator <
			cout << "operator <" << endl;
			cout << (str1 < str1 ? "true" : "false") << endl;				//false
			cout << (str1 < str2 ? "true" : "false") << endl;				//true
			cout << (str1 < str3 ? "true" : "false") << endl;				//true
			cout << (str1 < str4 ? "true" : "false") << endl;				//true
			cout << (str1 < str5 ? "true" : "false") << endl << endl;		//true

			cout << (str2 < str1 ? "true" : "false") << endl;				//false
			cout << (str2 < str2 ? "true" : "false") << endl;				//false
			cout << (str2 < str3 ? "true" : "false") << endl;				//true
			cout << (str2 < str4 ? "true" : "false") << endl;				//true
			cout << (str2 < str5 ? "true" : "false") << endl << endl;		//true

			cout << (str3 < str1 ? "true" : "false") << endl;				//false
			cout << (str3 < str2 ? "true" : "false") << endl;				//false
			cout << (str3 < str3 ? "true" : "false") << endl;				//false
			cout << (str3 < str4 ? "true" : "false") << endl;				//false
			cout << (str3 < str5 ? "true" : "false") << endl << endl;		//true

			cout << (str4 < str1 ? "true" : "false") << endl;				//false
			cout << (str4 < str2 ? "true" : "false") << endl;				//false
			cout << (str4 < str3 ? "true" : "false") << endl;				//true
			cout << (str4 < str4 ? "true" : "false") << endl;				//false
			cout << (str4 < str5 ? "true" : "false") << endl << endl;		//true

			cout << (str5 < str1 ? "true" : "false") << endl;				//false
			cout << (str5 < str2 ? "true" : "false") << endl;				//false
			cout << (str5 < str3 ? "true" : "false") << endl;				//false
			cout << (str5 < str4 ? "true" : "false") << endl;				//false
			cout << (str5 < str5 ? "true" : "false") << endl << endl;		//false

			//operator >
			cout << "operator >" << endl;
			cout << (str1 > str1 ? "true" : "false") << endl;				//false
			cout << (str1 > str2 ? "true" : "false") << endl;				//false
			cout << (str1 > str3 ? "true" : "false") << endl;				//false
			cout << (str1 > str4 ? "true" : "false") << endl;				//false
			cout << (str1 > str5 ? "true" : "false") << endl << endl;		//false

			cout << (str2 > str1 ? "true" : "false") << endl;				//true
			cout << (str2 > str2 ? "true" : "false") << endl;				//false
			cout << (str2 > str3 ? "true" : "false") << endl;				//false
			cout << (str2 > str4 ? "true" : "false") << endl;				//false
			cout << (str2 > str5 ? "true" : "false") << endl << endl;		//false

			cout << (str3 > str1 ? "true" : "false") << endl;				//true
			cout << (str3 > str2 ? "true" : "false") << endl;				//true
			cout << (str3 > str3 ? "true" : "false") << endl;				//false
			cout << (str3 > str4 ? "true" : "false") << endl;				//true
			cout << (str3 > str5 ? "true" : "false") << endl << endl;		//false

			cout << (str4 > str1 ? "true" : "false") << endl;				//true
			cout << (str4 > str2 ? "true" : "false") << endl;				//true
			cout << (str4 > str3 ? "true" : "false") << endl;				//false
			cout << (str4 > str4 ? "true" : "false") << endl;				//false
			cout << (str4 > str5 ? "true" : "false") << endl << endl;		//false

			cout << (str5 > str1 ? "true" : "false") << endl;				//true
			cout << (str5 > str2 ? "true" : "false") << endl;				//true
			cout << (str5 > str3 ? "true" : "false") << endl;				//true
			cout << (str5 > str4 ? "true" : "false") << endl;				//true
			cout << (str5 > str5 ? "true" : "false") << endl << endl;		//false
		}

		//测试：非成员函数 getline
		void test_getline() {
			cout << "\ntest_getline()" << endl;

			string str;
			cout << "需要输入十次字符串" << endl;
			for (int i = 0; i < 10; ++i) {
				cout << "\n" << i << ": ";
				cin >> str;
				cout << str << endl;
			}
		}

		//测试：非成员函数 stream
		void test_op_stream() {
			cout << "\ntest_op_stream()" << endl;

			string str;
			cout << "需要输入十次字符串" << endl;
			for (int i = 0; i < 10; ++i) {
				cout << "\n" << i << ": ";
				cin >> str;
				cout << str << endl;
			}
		}

		//测试：非成员函数 to_string
		void test_to_string() {
			using kkli::to_string;
			cout << "\ntest_to_string()" << endl;

			//to_string(long long)
			cout << "to_string(long long)" << endl;

			string str1 = to_string(0ll);
			str1.print("str1");					//0

			str1 = to_string(-0ll);
			str1.print("str1");					//0

			str1 = kkli::to_string(1234567ll);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(-1234567ll);
			str1.print("str1");					//-1234567

			str1 = kkli::to_string(std::numeric_limits<long long>::max());
			str1.print("str1");					//9223372036854775807

			str1 = kkli::to_string(std::numeric_limits<long long>::min());
			str1.print("str1");					//-9223372036854775808
			
			//to_string(unsigned long long)
			cout << "to_string(unsigned long long)" << endl;

			str1 = to_string(0ull);
			str1.print("str1");					//0

			str1 = to_string(-0ull);
			str1.print("str1");					//0

			str1 = kkli::to_string(1234567ull);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(-1234567ull);
			str1.print("str1");					//-1234567

			str1 = kkli::to_string(std::numeric_limits<unsigned long long>::max());
			str1.print("str1");					//0xffffffffffffffff

			str1 = kkli::to_string(std::numeric_limits<unsigned long long>::min());
			str1.print("str1");					//0

			//to_string(long double)
			cout << "to_string(long double)" << endl;

			str1 = to_string((long double)(0.0));
			str1.print("str1");					//0.0

			str1 = to_string((long double)(-0.0));
			str1.print("str1");					//0.0

			str1 = kkli::to_string((long double)(1234567.123));
			str1.print("str1");					//1234567.123

			str1 = kkli::to_string((long double)(-1234567.123));
			str1.print("str1");					//-1234567.123

			str1 = kkli::to_string( 0xffffffff + 0.123);	//用long double的max会出错 -_-!
			str1.print("str1");					//(不知道).123

			str1 = kkli::to_string(std::numeric_limits<long double>::min() + 0.123);
			str1.print("str1");					//0.123

			//下方 to_string 测试的类型都是通过类型转换调用上方的 to_string
			//例如 to_string(int val) 调用 to_string((long long)(val))

			//to_string(int)
			cout << "to_string(int)" << endl;

			str1 = to_string(0);
			str1.print("str1");					//0

			str1 = to_string(-0);
			str1.print("str1");					//0

			str1 = kkli::to_string(1234567);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(-1234567);
			str1.print("str1");					//-1234567

			str1 = kkli::to_string(std::numeric_limits<int>::max());
			str1.print("str1");					//0xffffffff

			str1 = kkli::to_string(std::numeric_limits<int>::min());
			str1.print("str1");					//0xffffffff+1

			//to_string(long)
			cout << "to_string(long)" << endl;

			str1 = to_string(0l);
			str1.print("str1");					//0

			str1 = to_string(-0l);
			str1.print("str1");					//0

			str1 = kkli::to_string(1234567l);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(-1234567l);
			str1.print("str1");					//-1234567

			str1 = kkli::to_string(std::numeric_limits<long>::max());
			str1.print("str1");					//0xffffffff

			str1 = kkli::to_string(std::numeric_limits<long>::min());
			str1.print("str1");					//0xffffffff+1

			//to_string(unsigned)
			cout << "to_string(unsigned)" << endl;

			str1 = to_string(0u);
			str1.print("str1");					//0

			str1 = to_string(-0u);
			str1.print("str1");					//0

			str1 = kkli::to_string(1234567u);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(std::numeric_limits<unsigned>::max());
			str1.print("str1");					//0xffffffff

			str1 = kkli::to_string(std::numeric_limits<unsigned>::min());
			str1.print("str1");					//0

			//to_string(unsigned long)
			cout << "to_string(unsigned long)" << endl;

			str1 = to_string(0ul);
			str1.print("str1");					//0

			str1 = to_string(-0ul);
			str1.print("str1");					//0

			str1 = kkli::to_string(1234567ul);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(std::numeric_limits<unsigned long>::max());
			str1.print("str1");					//0xffffffff

			str1 = kkli::to_string(std::numeric_limits<unsigned long>::min());
			str1.print("str1");					//0

			//to_string(float)
			cout << "to_string(float)" << endl;

			str1 = to_string(0.0f);
			str1.print("str1");					//0.0

			str1 = to_string(-0.0f);
			str1.print("str1");					//0.0

			str1 = kkli::to_string(1234567.123f);
			str1.print("str1");					//1234567

			str1 = kkli::to_string(-1234567.123f);
			str1.print("str1");					//-1234567

			str1 = kkli::to_string(std::numeric_limits<float>::max());
			str1.print("str1");					//

			str1 = kkli::to_string(std::numeric_limits<float>::min() + 0.123f);
			str1.print("str1");					//0.123xxxx

			//to_string(double)
			cout << "to_string(double)" << endl;

			str1 = to_string((double)(0.0));
			str1.print("str1");					//0.0

			str1 = to_string((double)(-0.0));
			str1.print("str1");					//0.0

			str1 = kkli::to_string((double)(1234567.123));
			str1.print("str1");					//1234567.123

			str1 = kkli::to_string((double)(-1234567.123));
			str1.print("str1");					//-1234567.123

			str1 = kkli::to_string(std::numeric_limits<double>::max());
			str1.print("str1");					//0xffffffff

			str1 = kkli::to_string(std::numeric_limits<long>::min()+(double)(0.123));
			str1.print("str1");					//
		}
	}
}
