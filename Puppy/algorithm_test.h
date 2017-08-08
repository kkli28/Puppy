#pragma once

#include "stdafx.h"
#include "test.h"
#include "algorithm.h"
#include "string.h"
#include "pair.h"

namespace test {
	namespace algorithm_test {

		using std::cout;
		using std::endl;
		using kkli::string;

		//part1
		void test_xxx_of();
		void test_for_each();
		void test_count();
		void test_count_if();
		void test_mismatch();
		void test_equal();
		void test_find();
		void test_find_if();
		void test_find_if_not();
		void test_find_end();
		void test_find_first_of();
		void test_adjacent_find();
		void test_search();
		void test_search_n();

		//part2
		//TODO: 

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========== test: algorithm.h ==========" << endl;

			test_xxx_of();	//part1
			test_for_each();
			test_count();
			test_count_if();
			test_mismatch();
			test_equal();
			test_find();
			test_find_if();
			test_find_if_not();
			test_find_end();
			test_find_first_of();
			test_adjacent_find();
			test_search();
			test_search_n();
		}

		//≤‚ ‘ all_of / any_of / none_of
		void test_xxx_of() {
			cout << "test: xxx_of()" << endl;

			string str1;
			string str2("aaaa");
			string str3("abcd");
			char c1 = 'a';
			auto lmd1 = [&](char c)->bool {return c == c1; };

			//all_of
			EXPECT_EQ_VAL(kkli::all_of(str1.begin(), str1.end(), lmd1), true);
			EXPECT_EQ_VAL(kkli::all_of(str2.begin(), str2.end(), lmd1), true);
			c1 = 'b';
			EXPECT_EQ_VAL(kkli::all_of(str1.begin(), str1.end(), lmd1), true);
			EXPECT_EQ_VAL(kkli::all_of(str2.begin(), str2.end(), lmd1), false);

			//any_of
			EXPECT_EQ_VAL(kkli::any_of(str1.begin(), str1.end(), lmd1), false);
			EXPECT_EQ_VAL(kkli::any_of(str3.begin(), str3.end(), lmd1), true);
			c1 = 'e';
			EXPECT_EQ_VAL(kkli::any_of(str3.begin(), str3.end(), lmd1), false);

			//non_of
			EXPECT_EQ_VAL(kkli::none_of(str1.begin(), str1.end(), lmd1), true);
			EXPECT_EQ_VAL(kkli::none_of(str3.begin(), str3.end(), lmd1), true);
			c1 = 'a';
			EXPECT_EQ_VAL(kkli::none_of(str3.begin(), str3.end(), lmd1), false);
		}
		
		//≤‚ ‘ for_each
		void test_for_each() {
			cout << "test: for_each()" << endl;

			string str1;
			string str2("abcd");
			auto lmd = [&](char& c)->void {c = 'a'; };
			kkli::for_each(str1.begin(), str1.end(), lmd);
			kkli::for_each(str2.begin(), str2.end(), lmd);
			EXPECT_EQ_VAL(str1, "");
			EXPECT_EQ_VAL(str2, "aaaa");
		}

		//≤‚ ‘ count
		void test_count() {
			cout << "test: count()" << endl;

			string str1("aabbbccccddddd");
			EXPECT_EQ_VAL(kkli::count(str1.begin(), str1.end(), 'a'), 2);
			EXPECT_EQ_VAL(kkli::count(str1.begin(), str1.end(), 'b'), 3);
			EXPECT_EQ_VAL(kkli::count(str1.begin(), str1.end(), 'c'), 4);
			EXPECT_EQ_VAL(kkli::count(str1.begin(), str1.end(), 'd'), 5);
		}

		//≤‚ ‘ count_if
		void test_count_if() {
			cout << "test: count_if()" << endl;
			string str1("aabbbccccddddd");
			char c1 = 'a';
			auto lmd1 = [&](char c)->bool {return c == c1; };

			EXPECT_EQ_VAL(kkli::count_if(str1.begin(), str1.end(), lmd1), 2);
			c1 = 'b';
			EXPECT_EQ_VAL(kkli::count_if(str1.begin(), str1.end(), lmd1), 3);
			c1 = 'c';
			EXPECT_EQ_VAL(kkli::count_if(str1.begin(), str1.end(), lmd1), 4);
			c1 = 'd';
			EXPECT_EQ_VAL(kkli::count_if(str1.begin(), str1.end(), lmd1), 5);
		}

		//≤‚ ‘ mismatch
		void test_mismatch() {
			cout << "test: mismatch()" << endl;

			string str1;
			string str2("abcd");
			string str3("abef");
			kkli::pair<string::iterator, string::iterator>
				p1 = kkli::mismatch(str1.begin(), str1.end(), str2.begin());

			EXPECT_EQ_VAL(p1.first, str1.begin());
			EXPECT_EQ_VAL(*(p1.second), 'a');

			p1 = kkli::mismatch(str2.begin(), str2.end(), str3.begin());
			EXPECT_EQ_VAL(*(p1.first), 'c');
			EXPECT_EQ_VAL(*(p1.second), 'e');

			p1 = kkli::mismatch(str2.begin(), str2.end(), str2.begin());
			EXPECT_EQ_VAL(p1.first, str2.end());
			EXPECT_EQ_VAL(p1.second, str2.end());

			auto lmd1 = [&](char c1, char c2)->bool {return c1 > c2; };
			p1 = kkli::mismatch(str3.begin(), str3.end(), str2.begin(), lmd1);
			EXPECT_EQ_VAL(*(p1.first), 'e');
			EXPECT_EQ_VAL(*(p1.second), 'c');
		}

		//≤‚ ‘ equal
		void test_equal() {
			cout << "test: equal()" << endl;

			string str1;
			string str2("abcd");
			string str3("abef");
			bool eq1 = kkli::equal(str1.begin(), str1.end(), str1.begin());
			bool eq2 = kkli::equal(str2.begin(), str2.end(), str2.begin());
			bool eq3 = kkli::equal(str2.begin(), str2.end(), str3.begin());
			EXPECT_EQ_VAL(eq1, true);
			EXPECT_EQ_VAL(eq2, true);
			EXPECT_EQ_VAL(eq3, false);

			auto lmd1 = [](char c1, char c2)->bool {return c1 != c2; };
			eq1 = kkli::equal(str1.begin(), str1.end(), str1.begin(), lmd1);
			eq2 = kkli::equal(str2.begin(), str2.end(), str2.begin(), lmd1);
			eq3 = kkli::equal(str2.begin(), str2.end(), str3.begin(), lmd1);
			EXPECT_EQ_VAL(eq1, true);
			EXPECT_EQ_VAL(eq2, false);
			EXPECT_EQ_VAL(eq3, false);
		}

		//≤‚ ‘ find
		void test_find() {
			cout << "test: find()" << endl;

			string str1("abcd");
			auto iter1 = kkli::find(str1.begin(), str1.end(), 'b');
			EXPECT_EQ_VAL(*iter1, 'b');
			iter1 = kkli::find(str1.begin(), str1.end(), 'e');
			EXPECT_EQ_VAL(iter1, str1.end());
		}

		//≤‚ ‘ find_if
		void test_find_if() {
			//find_if
			string str1("abcd");
			auto lmd1 = [](char c)->bool {return c == 'c'; };
			auto iter1 = kkli::find_if(str1.begin(), str1.end(), lmd1);
			EXPECT_EQ_VAL(*iter1, 'c');
		}

		//≤‚ ‘ find_if_not
		void test_find_if_not() {
			//find_if_not
			string str1("abcd");
			auto lmd1 = [](char c)->bool {return c == 'c'; };
			auto iter1 = kkli::find_if_not(str1.begin(), str1.end(), lmd1);
			EXPECT_EQ_VAL(*iter1, 'a');
		}

		//≤‚ ‘ find_end
		void test_find_end() {
			cout << "test: find_end()" << endl;

			string str1;
			string str2("ababcdcd");
			string str3("aabbccdd");
			string str_find1("ab");
			string str_find2("cd");
			string str_find3("cc");

			auto iter1 = kkli::find_end(str1.begin(), str1.end(), str_find1.begin(), str_find1.end());
			EXPECT_EQ_VAL(iter1, str1.begin());

			iter1 = kkli::find_end(str2.begin(), str2.end(), str_find1.begin(), str_find1.end());
			EXPECT_EQ_VAL(*iter1, 'a');
			EXPECT_EQ_VAL(*(iter1 + 2), 'c');

			iter1 = kkli::find_end(str2.begin(), str2.end(), str_find2.begin(), str_find2.end());
			EXPECT_EQ_VAL(*iter1, 'c');
			EXPECT_EQ_VAL(*(iter1 - 3), 'b');

			auto lmd1 = [](char c1, char c2) {return c1 == 'b' && c2 == 'c'; };
			iter1 = kkli::find_end(str3.begin(), str3.end(), str_find3.begin(), str_find3.end(),
				lmd1);
			EXPECT_EQ_VAL(*iter1, 'b');
			EXPECT_EQ_VAL(*(iter1 + 1), 'b');
		}

		//≤‚ ‘ find_first_of
		void test_find_first_of() {
			cout << "test: find_first_of()" << endl;

			string str1;
			string str2("abcd");
			string str_find1("cd");
			string str_find2("dc");

			auto lmd1 = [](char c)->bool {return c == 'b'; };
			auto iter1 = kkli::find_first_of(str1.begin(), str1.end(), str_find1.begin(), str_find1.end());
			EXPECT_EQ_VAL(iter1, str1.end());
			
			iter1 = kkli::find_first_of(str2.begin(), str2.end(), str_find1.begin(), str_find1.end());
			EXPECT_EQ_VAL(*iter1, 'c');
			iter1 = kkli::find_first_of(str2.begin(), str2.end(), str_find2.begin(), str_find2.end());
			EXPECT_EQ_VAL(*iter1, 'c');
		}

		//≤‚ ‘ adjacent_find
		void test_adjacent_find() {
			cout << "test: adjacent_find()" << endl;

			string str1;
			string str2("abccd");
			auto lmd1 = [](char c1, char c2)->bool {return c1 == 'c' && c2 == 'd'; };

			auto iter1 = kkli::adjacent_find(str1.begin(), str1.end());
			EXPECT_EQ_VAL(iter1, str1.begin());

			iter1 = kkli::adjacent_find(str2.begin(), str2.end());
			EXPECT_EQ_VAL(*iter1, 'c');
			EXPECT_EQ_VAL(*(iter1 + 1), 'c');

			iter1 = kkli::adjacent_find(str2.begin(), str2.end(), lmd1);
			EXPECT_EQ_VAL(*iter1, 'c');
			EXPECT_EQ_VAL(*(iter1 + 1), 'd');
		}

		//≤‚ ‘ search
		void test_search() {
			cout << "test: search()" << endl;

			string str1("abcd");
			string str2("efgh");
			string str3("abbc");
			string str_search1("cd");
			string str_search2("cc");

			auto iter1 = kkli::search(str1.begin(), str1.end(), str_search1.begin(), str_search1.end());
			EXPECT_EQ_VAL(*iter1, 'c');

			iter1 = kkli::search(str2.begin(), str2.end(), str_search1.begin(), str_search1.end());
			EXPECT_EQ_VAL(iter1, str2.end());

			auto lmd1 = [](char c1, char c2)->bool {return c1 == 'b' && c2 == 'c'; };
			iter1 = kkli::search(str3.begin(), str3.end(), str_search2.begin(), str_search2.end());
		}

		//≤‚ ‘ search_n
		void test_search_n() {
			cout << "test: search_n()" << endl;

			string str1("abcd");
			string str2("abcccdefg");
			auto lmd1 = [](char c1, char c2)->bool {return c1 > c2; };

			auto iter1 = kkli::search_n(str1.begin(), str1.end(), 3, 'c');
			EXPECT_EQ_VAL(iter1, str1.end());

			iter1 = kkli::search_n(str2.begin(), str2.end(), 3, 'c');
			EXPECT_EQ_VAL(*iter1, 'c');
			EXPECT_EQ_VAL(*(iter1 - 1), 'b');

			iter1 = kkli::search_n(str1.begin(), str1.end(), 3, 'c', lmd1);
			EXPECT_EQ_VAL(iter1, str1.end());
			iter1 = kkli::search_n(str2.begin(), str2.end(), 3, 'c', lmd1);
			EXPECT_EQ_VAL(*iter1, 'd');
		}
	}
}