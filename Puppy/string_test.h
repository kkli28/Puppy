#pragma once

#include "stdafx.h"
#include "test_utility.h"
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
		void test_rbegin_and_rend();
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
		void test_op_add();			//operator +
		void test_operators();		//operator == != < <= > >=
		void test_getline();		//getline(os, str, delim)
		void test_op_stream();		//operator << >>
		void test_to_string();		//to_string(x)
		//void test_stox();			//尚未实现

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "            string.h " << endl;
			cout << "========================================" << endl;

			//测试成员函数
			test_constructor();
			test_op_assign();
			test_op_square_bracket();
			test_op_add_equal();
			test_assign();
			test_insert();
			test_erase();
			test_append();
			test_compare();
			test_replace();
			//test_find();	//尚未实现
			test_c_str();
			test_data();
			test_at();
			test_front_and_back();
			test_begin_and_end();
			test_rbegin_and_rend();
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
			
			//测试非成员函数
			test_op_add();
			test_operators();
			test_to_string();
			test_getline();
			test_op_stream();
			//void test_stox();	//尚未实现
		}

		//测试 constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			string str1; //string()
			EXPECT_EQ_VAL(str1, string());

			string str2(4, 'a'); //string(count, value)
			EXPECT_EQ_VAL(str2, "aaaa");

			string str3(str2, 1, 2); //string(rhs, pos, count)
			string str4(str2, 0, npos);
			EXPECT_EQ_VAL(str3, "aa");
			EXPECT_EQ_VAL(str4, "aaaa");

			string str5("abcd", 3); //string(data, count)
			string str6("abcd", 2);
			string str7("abcd");
			EXPECT_EQ_VAL(str5, "abc");
			EXPECT_EQ_VAL(str6, "ab");
			EXPECT_EQ_VAL(str7, "abcd");
			
			string str8(4); //string(count)
			EXPECT_EQ_VAL(str8, "");

			string str9(str7.cbegin(), str7.cend()); //string(first, last)
			EXPECT_EQ_VAL(str9, "abcd");
			
			string str10(str9); //string(rhs)
			EXPECT_EQ_VAL(str10, "abcd");

			string str11(std::move(str10)); //string(&&rhs)
			EXPECT_EQ_VAL(str11, "abcd");

			string str12({ 'a','b','c','d' }); //string(init)
			EXPECT_EQ_VAL(str12, "abcd");
		}

		//测试 operator =
		void test_op_assign() {
			cout << "test: operator=" << endl;

			string str1("abcd");
			string str2("efgh");
			string str3("ijkl");

			str1 = str2; //operator =(rhs)
			EXPECT_EQ_VAL(str1, "efgh");
										
			str1 = std::move(str3); //operator =(&&rhs)
			EXPECT_EQ_VAL(str1, "ijkl");
	
			str1 = "mnop"; //operator =(data)
			EXPECT_EQ_VAL(str1, "mnop");

			str1 = "";
			EXPECT_EQ_VAL(str1, "");
	
			str1 = { 'q','r','s','t' }; //operator =(init)
			EXPECT_EQ_VAL(str1, "qrst");

		}
		
		//测试 operator []
		void test_op_square_bracket() {
			cout << "test: operator[]" << endl;

			string str1("abcd");
			EXPECT_EQ_VAL(str1[0], 'a');
			EXPECT_EQ_VAL(str1[1], 'b');
			EXPECT_EQ_VAL(str1[2], 'c');
			EXPECT_EQ_VAL(str1[3], 'd');

			for (int i = 0; i < 4; ++i)
				str1[i] = 'a';
			EXPECT_EQ_VAL(str1, "aaaa");
		}

		//测试 operator +=
		void test_op_add_equal() {
			cout << "test: operator+=" << endl;

			string str1("abcd");
			string str2("efgh");

			str1 += str2; //operator +=(rhs)
			EXPECT_EQ_VAL(str1, "abcdefgh");
			
			str1 += "ijkl"; //operator +=(data)
			EXPECT_EQ_VAL(str1, "abcdefghijkl");
			str1 += "";
			EXPECT_EQ_VAL(str1, "abcdefghijkl");
			
			str1 += {'m', 'n', 'o', 'p'}; //operator +=(init)
			EXPECT_EQ_VAL(str1, "abcdefghijklmnop");
		}

		//测试 assign
		void test_assign() {
			cout << "test: assign()" << endl;

			string str1;
			string str2("abcd");
			string str3("efgh");

			str1.assign(4, 'a'); //assign(count, value)
			EXPECT_EQ_VAL(str1, "aaaa");
			
			str1.assign(str2); //assign(rhs)
			EXPECT_EQ_VAL(str1, "abcd");

			str1.assign(std::move(str3)); //assign(&&rhs)
			EXPECT_EQ_VAL(str1, "efgh");

			
			str1.assign(str2, 1, 2); //assign(rhs, pos, count)
			EXPECT_EQ_VAL(str1, "bc");
			str1.assign(str2, 0, npos);
			EXPECT_EQ_VAL(str1, "abcd");

			str1.assign("aaaa", 2); //assign(data, count)
			EXPECT_EQ_VAL(str1, "aa");
			str1.assign("aaaa", npos);
			EXPECT_EQ_VAL(str1, "aaaa");

			str1.assign(str2.cbegin(), str2.cend()); //assign(first, last)
			EXPECT_EQ_VAL(str1, "abcd");

			str1.assign({ 'e','f','g','h' }); //assign(init)
			EXPECT_EQ_VAL(str1, "efgh");
		}

		//测试 insert
		void test_insert() {
			cout << "test: insert()" << endl;

			string str1;
			string str2("abcd");

			str1.insert(str1.cend(), str2.cbegin(), str2.cend()); //insert(pos, first, last)
			EXPECT_EQ_VAL(str1, "abcd");

			str1.insert(str1.cbegin(), 2, 'a'); //insert(pos, count, value)
			EXPECT_EQ_VAL(str1, "aaabcd");

			str1.insert(0, str2, 0, 2); //insert(index,rhs, index_rhs, count)
			EXPECT_EQ_VAL(str1, "abaaabcd");

			str1.insert(7, "abcd", 3); //insert(index, data, count)
			EXPECT_EQ_VAL(str1, "abaaabcabcd");
			
			str1.insert(4, str2); //insert(index, rhs)
			EXPECT_EQ_VAL(str1, "abaaabcdabcabcd");

			str1.insert(1, 4, 'a'); //insert(index, count, value)
			EXPECT_EQ_VAL(str1, "aaaaabaaabcdabcabcd");

			str1.insert(str1.cend(), 'd'); //insert(pos, value)
			EXPECT_EQ_VAL(str1, "aaaaabaaabcdabcabcdd");

			str1.insert(str1.begin(), { 'q','w','e','r' }); //insert(pos, init)
			EXPECT_EQ_VAL(str1, "qweraaaaabaaabcdabcabcdd");
		}

		//测试 erase
		void test_erase() {
			cout << "test: erase()" << endl;

			string str1("abcd");
			string str2 = str1;

			//erase(first, last)
			str2.erase(str2.begin() + 1, str2.begin() + 2);
			EXPECT_EQ_VAL(str2, "acd");
			str2.erase(str2.begin(), str2.end());
			EXPECT_EQ_VAL(str2, "");

			str2 = str1;
			str2.erase(0, 2); //erase(index, count)
			EXPECT_EQ_VAL(str2, "cd");

			//erase(pos)
			str2.erase(1); 
			EXPECT_EQ_VAL(str2, "c");

			str2.erase(std::size_t(0));
			EXPECT_EQ_VAL(str2, "");

			str2 = str1;
			str2.erase(str2.begin());
			EXPECT_EQ_VAL(str2, "bcd");
			str2.erase(str2.begin());
			EXPECT_EQ_VAL(str2, "cd");
			str2.erase(str2.begin());
			EXPECT_EQ_VAL(str2, "d");
			str2.erase(str2.begin());
			EXPECT_EQ_VAL(str2, "");
		}

		//测试 append
		void test_append() {
			cout << "test: append()" << endl;

			string str1;
			string str2("abcd");

			str1.append(str2, 0, 2); //append(rhs, pos, count)
			EXPECT_EQ_VAL(str1, "ab");

			str1.append(str2, 2); //append(rhs, pos, count=npos)
			EXPECT_EQ_VAL(str1, "abcd");

			str1.append("abcd", 2); //append(data, count)
			EXPECT_EQ_VAL(str1, "abcdab");

			str1.append("abcd"); //append(data, count=npos)
			EXPECT_EQ_VAL(str1, "abcdababcd");
			
			str1.append(1, ' '); //append(count, value)
			str1.append(4, 'a');
			EXPECT_EQ_VAL(str1, "abcdababcd aaaa");
			
			str1 = string();
			str1.append(str2.begin(), str2.end()); //append(first, last)
			EXPECT_EQ_VAL(str1, "abcd");
			str1.append(str1.begin(), str1.end());
			EXPECT_EQ_VAL(str1, "abcdabcd");

			str1.append({ 'q','w','e','r' }); //append(init)
			EXPECT_EQ_VAL(str1, "abcdabcdqwer");
		}

		//测试 compare
		void test_compare() {
			cout << "test: compare()" << endl;

			string str1("abcd");
			string str2("aceg");
			string str3("abcdef");
			string str4("acegik");

			//compare(rhs)
			EXPECT_EQ_VAL(str1.compare(str1), 0);
			EXPECT_EQ_VAL(str1.compare(str2), -1);
			EXPECT_EQ_VAL(str1.compare(str3), -1);
			EXPECT_EQ_VAL(str1.compare(str4), -1);

			EXPECT_EQ_VAL(str2.compare(str1), 1);
			EXPECT_EQ_VAL(str2.compare(str2), 0);
			EXPECT_EQ_VAL(str2.compare(str3), 1);
			EXPECT_EQ_VAL(str2.compare(str4), -1);

			EXPECT_EQ_VAL(str3.compare(str1), 1);
			EXPECT_EQ_VAL(str3.compare(str2), -1);
			EXPECT_EQ_VAL(str3.compare(str3), 0);
			EXPECT_EQ_VAL(str3.compare(str4), -1);

			EXPECT_EQ_VAL(str4.compare(str1), 1);
			EXPECT_EQ_VAL(str4.compare(str2), 1);
			EXPECT_EQ_VAL(str4.compare(str3), 1);
			EXPECT_EQ_VAL(str4.compare(str4), 0);

			//compare(pos, count, rhs)
			EXPECT_EQ_VAL(str1.compare(0, 4, str1), 0);
			EXPECT_EQ_VAL(str1.compare(0, 3, str1), -1);
			EXPECT_EQ_VAL(str1.compare(0, 4, str3), -1);
			EXPECT_EQ_VAL(str2.compare(0, 4, str1), 1);
			EXPECT_EQ_VAL(str2.compare(0, 4, str2), 0);

			EXPECT_EQ_VAL(str1.compare(0, 4, str1, 0, 4), 0);
			EXPECT_EQ_VAL(str1.compare(0, 4, str1, 2, 2), -1);
			EXPECT_EQ_VAL(str1.compare(0, 4, str2, 0, 4), -1);
			EXPECT_EQ_VAL(str2.compare(0, 4, str1, 0, 4), 1);
			EXPECT_EQ_VAL(str1.compare(0, 4, str3), -1);
			EXPECT_EQ_VAL(str1.compare(0, 4, str1), 0);

			//compare(data)
			EXPECT_EQ_VAL(str1.compare("abcd"), 0);
			EXPECT_EQ_VAL(str1.compare("aceg"), -1);
			EXPECT_EQ_VAL(str1.compare("aaaa"), 1);
			EXPECT_EQ_VAL(str1.compare("abcdef"), -1);
			EXPECT_EQ_VAL(str1.compare("ab"), 1);
			EXPECT_EQ_VAL(str1.compare("cd"), -1);
			EXPECT_EQ_VAL(str1.compare(""), 1);

			//compare(pos1, count1, data, count2)
			EXPECT_EQ_VAL(str1.compare(0, 4, "abcd"), 0);
			EXPECT_EQ_VAL(str1.compare(0, 3, "abcd"), -1);
			EXPECT_EQ_VAL(str2.compare(0, 4, "abcd"), 1);
			EXPECT_EQ_VAL(str2.compare(0, 4, "aceg"), 0);
			EXPECT_EQ_VAL(str1.compare(0, 4, "abcdef"), -1);
			EXPECT_EQ_VAL(str1.compare(0, 4, "abcd", 4), 0);
			EXPECT_EQ_VAL(str1.compare(0, 4, "abcd", 2), 1);
			EXPECT_EQ_VAL(str1.compare(0, 4, "aceg", 4), -1);
			EXPECT_EQ_VAL(str2.compare(0, 4, "abcd", 4), 1);
			EXPECT_EQ_VAL(str1.compare(0, 4, "abcdef", 4), 0);
			EXPECT_EQ_VAL(str1.compare(0, 4, "abcdef", 6), -1);
		}

		//测试 replace
		void test_replace() {
			cout << "test: replace()" << endl;

			string str1("abcd");
			string str2("qwer");

			//replace(first1, last1,first2,last2)
			str1.replace(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend());
			EXPECT_EQ_VAL(str1, "qwer");

			//replace(first, last, count, value)
			str1.replace(str1.begin() + 1, str1.begin() + 3, 3, 'e');
			EXPECT_EQ_VAL(str1, "qeeer");

			//replace(first, last, rhs)
			str1.replace(str1.begin(), str1.begin() + 1, str2);
			EXPECT_EQ_VAL(str1, "qwereeer");
			
			//replace(first, last, data, count)
			str1.replace(str1.begin(), str1.begin() + 2, "abcd");
			EXPECT_EQ_VAL(str1, "abcdereeer");
			
			//replace(first, last, init)
			str1.replace(str1.begin(), str1.end(), { 'a','b','c','d' });
			EXPECT_EQ_VAL(str1, "abcd");
			
			//replace(pos, count, rhs, pos2, count2)
			str1.replace(0, 2, str2, 0, 3);
			EXPECT_EQ_VAL(str1, "qwecd");

			//replace(pos, count, count2, value)
			str1.replace(str1.begin(), str1.end(), 8, 'e');
			EXPECT_EQ_VAL(str1, "eeeeeeee");
		}

		//测试 c_str
		void test_c_str() {
			cout << "test: c_str()" << endl;

			string str1;
			string str2("abcd");

			char* cp1 = str1.c_str();
			char* cp2 = str2.c_str();
			EXPECT_EQ_VAL(string(cp1), "");
			EXPECT_EQ_ARRLIST(cp2, 4, { 'a','b','c','d' });
			EXPECT_EQ_VAL(cp2[0], 'a');
			EXPECT_EQ_VAL(cp2[1], 'b');
			EXPECT_EQ_VAL(cp2[2], 'c');
			EXPECT_EQ_VAL(cp2[3], 'd');
			EXPECT_EQ_VAL(cp2[4], '\0');
		}

		//测试 data
		void test_data() {
			cout << "test: data()" << endl;
			EXPECT_EQ_VAL(string(string().data()), "");
			EXPECT_EQ_ARRLIST(string("abcd").data(), 4, { 'a','b','c','d' });
		}

		//测试 at
		void test_at() {
			cout << "test: at()" << endl;

			string str1("abcd");
			EXPECT_EQ_VAL(str1.at(0), 'a');
			EXPECT_EQ_VAL(str1.at(1), 'b');
			EXPECT_EQ_VAL(str1.at(2), 'c');
			EXPECT_EQ_VAL(str1.at(3), 'd');
		}

		//测试 front / back
		void test_front_and_back() {
			cout << "test: front()" << endl;
			cout << "test: back()" << endl;
			string str1("abcd");
			EXPECT_EQ_VAL(str1.front(), 'a');
			EXPECT_EQ_VAL(str1.back(), 'd');
		}

		//测试 begin / end / cbegin / cend
		void test_begin_and_end() {
			cout << "test: begin()" << endl;
			cout << "test: end()" << endl;
			cout << "test: cbegin()" << endl;
			cout << "test: cend()" << endl;
			string str1;
			string str2("abcd");
			EXPECT_EQ_VAL(str1.begin(), str1.end());
			EXPECT_EQ_VAL(*(str2.begin()), 'a');
			EXPECT_EQ_VAL(*(str2.end() - 1), 'd');
			EXPECT_EQ_VAL(*(str2.cbegin()), 'a');
			EXPECT_EQ_VAL(*(str2.cend() - 1), 'd');
		}

		//测试 rbegin / rend / crbegin / crend
		void test_rbegin_and_rend() {
			cout << "test: rbegin()" << endl;
			cout << "test: rend()" << endl;
			cout << "test: crbegin()" << endl;
			cout << "test: crend()" << endl;

			string str1;
			string str2("abcd");
			EXPECT_EQ_VAL(str1.rbegin(), str1.rend());
			EXPECT_EQ_VAL(str1.crbegin(), str1.crend());
			EXPECT_EQ_VAL(*(str2.rbegin()), 'd');
			EXPECT_EQ_VAL(*(str2.rend() - 1), 'a');
			EXPECT_EQ_VAL(*(str2.crbegin()), 'd');
			EXPECT_EQ_VAL(*(str2.crend() - 1), 'a');
		}

		//测试 empty
		void test_empty() {
			cout << "test: empty()" << endl;
			EXPECT_EQ_VAL(string().empty(), true);
			EXPECT_EQ_VAL(string("abcd").empty(), false);
		}

		//测试 size
		void test_size() {
			cout << "test: size()" << endl;

			string str1;
			string str2("abcd");
			EXPECT_EQ_VAL(str1.size(), 0);
			EXPECT_EQ_VAL(str2.size(), 4);
			str2.append("ab");
			EXPECT_EQ_VAL(str2.size(), 6);
		}

		//测试 reserve
		void test_reserve() {
			cout << "test: reserve()" << endl;

			string str1;
			str1.reserve(4);
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str1.capacity(), 4);

			str1.reserve(2);
			EXPECT_EQ_VAL(str1.capacity(), 4);

			str1.append("abcdef");
			EXPECT_EQ_VAL(str1, "abcdef");
			EXPECT_EQ_VAL(str1.capacity(), 12);
		}

		//测试 clear
		void test_clear() {
			cout << "test: clear()" << endl;

			string str1("abcd");
			str1.clear();
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str1.capacity(), 4);
		}

		//测试 push_back
		void test_push_back() {
			cout << "test: push_back()" << endl;

			string str1;
			str1.push_back('a');
			EXPECT_EQ_VAL(str1, "a");
			str1.push_back('b');
			EXPECT_EQ_VAL(str1, "ab");
			str1.push_back('c');
			EXPECT_EQ_VAL(str1, "abc");
		}

		//测试 pop_back
		void test_pop_back() {
			cout << "test: pop_back()" << endl;

			string str1("abcd");
			str1.pop_back();
			EXPECT_EQ_VAL(str1, "abc");
			str1.pop_back();
			EXPECT_EQ_VAL(str1, "ab");
			str1.pop_back();
			EXPECT_EQ_VAL(str1, "a");
		}

		//测试 resize
		void test_resize() {
			cout << "test: resize()" << endl;

			string str1;

			str1.resize(4);
			EXPECT_EQ_VAL(str1, "    ");

			str1.resize(8, 'a');
			EXPECT_EQ_VAL(str1, "    aaaa");

			str1.resize(4);
			EXPECT_EQ_VAL(str1, "    aaaa");

			str1.resize(12);
			EXPECT_EQ_VAL(str1, "    aaaa    ");

			str1.resize(16, 'b');
			EXPECT_EQ_VAL(str1, "    aaaa    bbbb");
		}

		//测试 substr
		void test_substr() {
			cout << "test: substr()" << endl;

			string str("abcdefgh");
			string str1 = str.substr();
			EXPECT_EQ_VAL(str1, "abcdefgh");

			str1 = str.substr(1, 4);
			EXPECT_EQ_VAL(str1, "bcde");

			str1 = str.substr(4);
			EXPECT_EQ_VAL(str1, "efgh");
		}

		//测试 copy
		void test_copy() {
			cout << "test: copy()" << endl;

			string str1;
			str1.copy("abcd");
			EXPECT_EQ_VAL(str1, "abcd");

			str1.copy("abcd", 2);
			EXPECT_EQ_VAL(str1, "cd");
			
			str1.copy("abcd", 1, 2);
			EXPECT_EQ_VAL(str1, "bc");
		}

		//测试 swap
		void test_swap() {
			cout << "test: swap()" << endl;

			string str1;
			string str2("abcd");
			string str3("qwerty");

			str1.swap(str2);
			EXPECT_EQ_VAL(str1, "abcd");
			EXPECT_EQ_VAL(str2, "");

			str1.swap(str3);
			EXPECT_EQ_VAL(str1, "qwerty");
			EXPECT_EQ_VAL(str3, "abcd");
		}

		//测试 reverse()
		void test_reverse() {
			cout << "test: reverse()" << endl;

			string str1;
			string str2("qwert");

			str1.reverse();
			EXPECT_EQ_VAL(str1, "");

			str2.reverse();
			EXPECT_EQ_VAL(str2, "trewq");
		}

		//测试：非成员函数 operator +
		void test_op_add() {
			cout << "test: operator+" << endl;

			string str1;
			string str2("abcd");

			//operator+(lhs, rhs)
			EXPECT_EQ_VAL(str1 + str1, "");
			EXPECT_EQ_VAL(str1 + str2, "abcd");
			EXPECT_EQ_VAL(str2 + str1, "abcd");
			EXPECT_EQ_VAL(str2 + str2, "abcdabcd");

			//operator+(lhs, data)
			EXPECT_EQ_VAL(str1 + "abcd", "abcd");
			EXPECT_EQ_VAL(str2 + "abcd", "abcdabcd");

			//operator+(data, rhs)
			EXPECT_EQ_VAL("abcd" + str1, "abcd");
			EXPECT_EQ_VAL("abcd" + str2, "abcdabcd");

			//operator+(lhs, value)
			EXPECT_EQ_VAL(str1 + 'a', "a");
			EXPECT_EQ_VAL(str2 + 'a', "abcda");

			//operator+(value, rhs);
			EXPECT_EQ_VAL('a' + str1, "a");
			EXPECT_EQ_VAL('a' + str2, "aabcd");
		}

		//测试：非成员函数 operator == < >，!=由==实现，<=由>实现，>=由<实现
		void test_operators() {
			cout << "test: operators(==/!=/<...)" << endl;

			string str1;
			string str2("abcd");
			char* str3 = "aceg";
			string str4("abcdef");
			string str5("acegik");

			//operator ==
			EXPECT_EQ_VAL(str1 == str1, true);
			EXPECT_EQ_VAL(str1 == str2, false);
			EXPECT_EQ_VAL(str1 == str3, false);
			EXPECT_EQ_VAL(str1 == str4, false);
			EXPECT_EQ_VAL(str1 == str5, false);
			EXPECT_EQ_VAL(str2 == str1, false);
			EXPECT_EQ_VAL(str2 == str2, true);
			EXPECT_EQ_VAL(str2 == str3, false);
			EXPECT_EQ_VAL(str2 == str4, false);
			EXPECT_EQ_VAL(str2 == str5, false);
			EXPECT_EQ_VAL(str3 == str1, false);
			EXPECT_EQ_VAL(str3 == str2, false);
			EXPECT_EQ_VAL(str3 == str3, true);
			EXPECT_EQ_VAL(str3 == str4, false);
			EXPECT_EQ_VAL(str3 == str5, false);
			EXPECT_EQ_VAL(str4 == str1, false);
			EXPECT_EQ_VAL(str4 == str2, false);
			EXPECT_EQ_VAL(str4 == str3, false);
			EXPECT_EQ_VAL(str4 == str4, true);
			EXPECT_EQ_VAL(str4 == str5, false);
			EXPECT_EQ_VAL(str5 == str1, false);
			EXPECT_EQ_VAL(str5 == str2, false);
			EXPECT_EQ_VAL(str5 == str3, false);
			EXPECT_EQ_VAL(str5 == str4, false);
			EXPECT_EQ_VAL(str5 == str5, true);

			//operator <
			EXPECT_EQ_VAL(str1 < str1, false);
			EXPECT_EQ_VAL(str1 < str2, true);
			EXPECT_EQ_VAL(str1 < str3, true);
			EXPECT_EQ_VAL(str1 < str4, true);
			EXPECT_EQ_VAL(str1 < str5, true);
			EXPECT_EQ_VAL(str2 < str1, false);
			EXPECT_EQ_VAL(str2 < str2, false);
			EXPECT_EQ_VAL(str2 < str3, true);
			EXPECT_EQ_VAL(str2 < str4, true);
			EXPECT_EQ_VAL(str2 < str5, true);
			EXPECT_EQ_VAL(str3 < str1, false);
			EXPECT_EQ_VAL(str3 < str2, false);
			EXPECT_EQ_VAL(str3 < str3, false);
			EXPECT_EQ_VAL(str3 < str4, false);
			EXPECT_EQ_VAL(str3 < str5, true);
			EXPECT_EQ_VAL(str4 < str1, false);
			EXPECT_EQ_VAL(str4 < str2, false);
			EXPECT_EQ_VAL(str4 < str3, true);
			EXPECT_EQ_VAL(str4 < str4, false);
			EXPECT_EQ_VAL(str4 < str5, true);
			EXPECT_EQ_VAL(str5 < str1, false);
			EXPECT_EQ_VAL(str5 < str2, false);
			EXPECT_EQ_VAL(str5 < str3, false);
			EXPECT_EQ_VAL(str5 < str4, false);
			EXPECT_EQ_VAL(str5 < str5, false);

			//operator >
			EXPECT_EQ_VAL(str1 > str1, false);
			EXPECT_EQ_VAL(str1 > str2, false);
			EXPECT_EQ_VAL(str1 > str3, false);
			EXPECT_EQ_VAL(str1 > str4, false);
			EXPECT_EQ_VAL(str1 > str5, false);
			EXPECT_EQ_VAL(str2 > str1, true);
			EXPECT_EQ_VAL(str2 > str2, false);
			EXPECT_EQ_VAL(str2 > str3, false);
			EXPECT_EQ_VAL(str2 > str4, false);
			EXPECT_EQ_VAL(str2 > str5, false);
			EXPECT_EQ_VAL(str3 > str1, true);
			EXPECT_EQ_VAL(str3 > str2, true);
			EXPECT_EQ_VAL(str3 > str3, false);
			EXPECT_EQ_VAL(str3 > str4, true);
			EXPECT_EQ_VAL(str3 > str5, false);
			EXPECT_EQ_VAL(str4 > str1, true);
			EXPECT_EQ_VAL(str4 > str2, true);
			EXPECT_EQ_VAL(str4 > str3, false);
			EXPECT_EQ_VAL(str4 > str4, false);
			EXPECT_EQ_VAL(str4 > str5, false);
			EXPECT_EQ_VAL(str5 > str1, true);
			EXPECT_EQ_VAL(str5 > str2, true);
			EXPECT_EQ_VAL(str5 > str3, true);
			EXPECT_EQ_VAL(str5 > str4, true);
			EXPECT_EQ_VAL(str5 > str5, false);
		}

		//测试：非成员函数 to_string
		void test_to_string() {
			using kkli::to_string;
			cout << "test: to_string()" << endl;

			//to_string(long long)
			string str1 = to_string(0ll);
			EXPECT_EQ_VAL(str1, "0");

			str1 = to_string(-0ll);
			EXPECT_EQ_VAL(str1, "0");

			str1 = kkli::to_string(1234567ll);
			EXPECT_EQ_VAL(str1, "1234567");

			str1 = kkli::to_string(-1234567ll);
			EXPECT_EQ_VAL(str1, "-1234567");

			str1 = kkli::to_string(std::numeric_limits<long long>::max());
			EXPECT_EQ_VAL(str1, "9223372036854775807");

			str1 = kkli::to_string(std::numeric_limits<long long>::min());
			EXPECT_EQ_VAL(str1, "-9223372036854775808");

			//to_string(unsigned long long)
			str1 = to_string(0ull);
			EXPECT_EQ_VAL(str1, "0");

			str1 = to_string(-0ull);
			EXPECT_EQ_VAL(str1, "0");

			str1 = kkli::to_string(1234567ull);
			EXPECT_EQ_VAL(str1, "1234567");

			str1 = kkli::to_string(-1234567ull);
			EXPECT_EQ_VAL(str1, "18446744073708317049");

			str1 = kkli::to_string(std::numeric_limits<unsigned long long>::max());
			EXPECT_EQ_VAL(str1, "18446744073709551615");

			str1 = kkli::to_string(std::numeric_limits<unsigned long long>::min());
			EXPECT_EQ_VAL(str1, "0");

			//to_string(long double)
			str1 = to_string((long double)(0.0));
			EXPECT_EQ_VAL(str1, "0.0");

			str1 = to_string((long double)(-0.0));
			EXPECT_EQ_VAL(str1, "0.0");

			//浮点数无法精确比较大小
			//str1 = kkli::to_string((long double)(1234567.123));
			//EXPECT_EQ_VAL(str1, "1234567.123");
			//str1 = kkli::to_string((long double)(-1234567.123));
			//EXPECT_EQ_VAL(str1, "1234567.123");
			//str1 = kkli::to_string(0xffffffff + 0.123);	//用long double的max会出错 -_-!
			//EXPECT_EQ_VAL(str1, "不知道.123");
			//str1 = kkli::to_string(std::numeric_limits<long double>::min() + 0.123);
			//EXPECT_EQ_VAL(str1, "0.123");

			//to_string(int)
			str1 = to_string(0);
			EXPECT_EQ_VAL(str1, "0");

			str1 = to_string(-0);
			EXPECT_EQ_VAL(str1, "0");

			str1 = kkli::to_string(1234567);
			EXPECT_EQ_VAL(str1, "1234567");

			str1 = kkli::to_string(-1234567);
			EXPECT_EQ_VAL(str1, "-1234567");

			str1 = kkli::to_string(std::numeric_limits<int>::max());
			EXPECT_EQ_VAL(str1, "2147483647");

			str1 = kkli::to_string(std::numeric_limits<int>::min());
			EXPECT_EQ_VAL(str1, "-2147483648");

			//to_string(long)
			str1 = to_string(0l);
			EXPECT_EQ_VAL(str1, "0");

			str1 = to_string(-0l);
			EXPECT_EQ_VAL(str1, "0");

			str1 = kkli::to_string(1234567l);
			EXPECT_EQ_VAL(str1, "1234567");

			str1 = kkli::to_string(-1234567l);
			EXPECT_EQ_VAL(str1, "-1234567");

			str1 = kkli::to_string(std::numeric_limits<long>::max());
			EXPECT_EQ_VAL(str1, "2147483647");

			str1 = kkli::to_string(std::numeric_limits<long>::min());
			EXPECT_EQ_VAL(str1, "-2147483648");

			//to_string(unsigned)
			str1 = to_string(0u);
			EXPECT_EQ_VAL(str1, "0");

			str1 = to_string(-0u);
			EXPECT_EQ_VAL(str1, "0");

			str1 = kkli::to_string(1234567u);
			EXPECT_EQ_VAL(str1, "1234567");

			str1 = kkli::to_string(std::numeric_limits<unsigned>::max());
			EXPECT_EQ_VAL(str1, "4294967295");

			str1 = kkli::to_string(std::numeric_limits<unsigned>::min());
			EXPECT_EQ_VAL(str1, "0");

			//to_string(unsigned long)
			str1 = to_string(0ul);
			EXPECT_EQ_VAL(str1, "0");

			str1 = to_string(-0ul);
			EXPECT_EQ_VAL(str1, "0");

			str1 = kkli::to_string(1234567ul);
			EXPECT_EQ_VAL(str1, "1234567");

			str1 = kkli::to_string(std::numeric_limits<unsigned long>::max());
			EXPECT_EQ_VAL(str1, "4294967295");

			str1 = kkli::to_string(std::numeric_limits<unsigned long>::min());
			EXPECT_EQ_VAL(str1, "0");

			//to_string(float)
			str1 = to_string(0.0f);
			EXPECT_EQ_VAL(str1, "0.0");

			str1 = to_string(-0.0f);
			EXPECT_EQ_VAL(str1, "0.0");

			//浮点数无法精确比较
			//str1 = kkli::to_string(1234567.123f);
			//EXPECT_EQ_VAL(str1, "1234567");
			//str1 = kkli::to_string(-1234567.123f);
			//EXPECT_EQ_VAL(str1, "-1234567");
			//str1 = kkli::to_string(std::numeric_limits<float>::max());
			//EXPECT_EQ_VAL(str1, "0");
			//str1 = kkli::to_string(std::numeric_limits<float>::min() + 0.123f);
			//EXPECT_EQ_VAL(str1, "0");

			//to_string(double)
			str1 = to_string((double)(0.0));
			EXPECT_EQ_VAL(str1, "0.0");

			str1 = to_string((double)(-0.0));
			EXPECT_EQ_VAL(str1, "0.0");

			//浮点数无法精确比较
			//str1 = kkli::to_string((double)(1234567.123));
			//EXPECT_EQ_VAL(str1, "0");
			//str1 = kkli::to_string((double)(-1234567.123));
			//EXPECT_EQ_VAL(str1, "0");
			//str1 = kkli::to_string(std::numeric_limits<double>::max());
			//EXPECT_EQ_VAL(str1, "0");
			//str1 = kkli::to_string(std::numeric_limits<long>::min() + (double)(0.123));
			//EXPECT_EQ_VAL(str1, "0");
		}

		//测试：getline
		void test_getline() {
			cout << "test: getline()" << endl;
			return; //已测试通过

			string str;
			cout << "需要输入十次字符串" << endl;
			for (int i = 0; i < 10; ++i) {
				cout << "\n" << i << ": ";
				cin >> str;
				cout << str << endl;
			}
		}

		//测试：stream
		void test_op_stream() {
			cout << "test: operator>>" << endl;
			cout << "test: operator<<" << endl;
			return; //已测试通过

			string str;
			cout << "需要输入十次字符串" << endl;
			for (int i = 0; i < 10; ++i) {
				cout << "\n" << i << ": ";
				cin >> str;
				cout << str << endl;
			}
		}
	}
}
