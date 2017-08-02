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

		//ǰ����������Ա����
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
		//void test_find();						//�ú�����δʵ��
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
		
		//ǰ���������ǳ�Ա����
		void test_op_add();						//operator +
		void test_op_compare();					//operator == != < <= > >=
		void test_op_stream();					//operator << >>
		void test_get_line();
		//void test_stox();						//������δʵ��

		//�������
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: string " << endl;
			cout << "========================================" << endl;

			//���ԣ���Ա����
			test_constructor();
			test_op_assign();			//operator =
			test_op_square_bracket();	//operator []
			test_op_add_equal();		//operator +=
			test_assign();
			test_insert();
			test_erase();
			test_append();
			test_compare();
			//test_replace();
			//test_find();				//�ú�����δʵ��
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

			//���ԣ��ǳ�Ա����
			//test_op_add();				//operator +
			//test_op_compare();			//operator == != < <= > >=
			//test_op_stream();			//operator << >>
			//test_get_line();
			//test_stox();				//������δʵ��
		}

		//���� constructor
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			//string()
			string str1;
			str1.print("str1");				//(��)

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
			string str8(4);					//(��)
			str8.print("str8");

			//string(first, last)
			string str9(str7.cbegin(), str7.cend());
			str9.print("str9");				//abcd

			//string(rhs)
			string str10(str9);
			str10.print("str10");			//abcd

			//string(&&rhs)
			string str11(std::move(str10));
			str11.print("str11");			//(��)

			//string(init)
			string str12({ 'a','b','c','d' });
			str12.print("str12");			//abcd
		}

		//���� operator =
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

		//���� operator []
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

		//���� operator +=
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

		//���� assign
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

		//���� insert
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

		//���� erase
		void test_erase() {
			cout << "\ntest_erase()" << endl;

			string str1("abcd");
			string str2 = str1;

			//erase(first, last)
			str2.erase(str2.begin() + 1, str2.begin() + 2);
			str2.print("str2");					//acd

			str2.erase(str2.begin(), str2.end());
			str2.print("str2");					//(��)

			//erase(index, count)
			str2 = str1;
			str2.erase(0, 2);
			str2.print("str2");					//cd

			str2.erase(1);						//c
			str2.print("str2");

			str2.erase((std::size_t)0);
			str2.print("str2");					//(��)

			//erase(pos)
			str2 = str1;
			for (std::size_t i = 0; i < 4; ++i) {
				str2.erase(str2.begin());
				str2.print("str2");
			}
		}

		//���� append
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

		//���� compare
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

		//TODO: 
	}
}