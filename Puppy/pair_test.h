#pragma once

#include "stdafx.h"
#include "pair.h"
#include "string.h"
#include "test.h"

namespace test {
	namespace pair_test {

		using std::cout;
		using std::endl;
		using kkli::pair;
		using kkli::string;

		//∫Ø ˝«∞÷√…˘√˜
		void test_constructor();
		void test_op_equal();
		void test_swap();
		void test_make_pair();
		void test_op_logical();
		void test_get();
		void test_tuple_size();
		void test_tuple_element();

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "            pair.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_op_equal();
			test_swap();
			test_make_pair();
			test_op_logical();
			test_get();
			test_tuple_size();
			test_tuple_element();
		}

		//≤‚ ‘ pair
		void test_constructor() {
			cout << "test: constructor()" << endl;

			//constructor
			pair<int, string> p1;		//pair()
			EXPECT_EQ_VAL(p1.first, 0);
			EXPECT_EQ_VAL(p1.second, "");

			int i1 = 1;
			string str1 = "abcd";
			pair<int, string> p2(i1, str1); //pair(f,s)
			EXPECT_EQ_VAL(p2.first, 1);
			EXPECT_EQ_VAL(p2.second, "abcd");

			pair<int, string> p3(std::move(i1), std::move(str1)); //pair(&&f, &&s)
			EXPECT_EQ_VAL(p3.first, 1);
			EXPECT_EQ_VAL(p3.second, "abcd");

			pair<int, string> aux_p4(2, "abcd");
			pair<int, string> p4(aux_p4);	//pair(rhs)
			EXPECT_EQ_VAL(p4.first, 2);
			EXPECT_EQ_VAL(p4.second, "abcd");

			pair<int, string> p5(std::move(aux_p4)); //pair(&&rhs)
			EXPECT_EQ_VAL(p5.first, 2);
			EXPECT_EQ_VAL(p5.second, "abcd");
		}

		//≤‚ ‘ operator=
		void test_op_equal() {
			cout << "test: operator=()" << endl;

			//operator=
			pair<int, string> p1(1, "abcd");
			pair<int, string> p2;
			p2 = p1;		//operator =(rhs)
			EXPECT_EQ_VAL(p2.first, 1);
			EXPECT_EQ_VAL(p2.second, "abcd");
			
			pair<int, string> p3;		//operator =(&&rhs)
			p3 = std::move(p1);
			EXPECT_EQ_VAL(p3.first, 1);
			EXPECT_EQ_VAL(p3.second, "abcd");
		}
		
		//≤‚ ‘ member swap/non-member swap
		void test_swap() {
			cout << "test: swap()" << endl;

			int i1 = 1;
			string str1 = "abcd";
			int i2 = 2;
			string str2 = "efgh";
			pair<int, string> p1(i1, str1);
			pair<int, string> p2(i2, str2);

			p1.swap(p2);
			EXPECT_EQ_VAL(p1.first, 2);
			EXPECT_EQ_VAL(p1.second, "efgh");
			EXPECT_EQ_VAL(p2.first, 1);
			EXPECT_EQ_VAL(p2.second, "abcd");

			kkli::swap(p1, p2);
			EXPECT_EQ_VAL(p1.first, 1);
			EXPECT_EQ_VAL(p1.second, "abcd");
			EXPECT_EQ_VAL(p2.first, 2);
			EXPECT_EQ_VAL(p2.second, "efgh");
		}

		//≤‚ ‘ make_pair
		void test_make_pair() {
			cout << "test: make_pair()" << endl;

			pair<int, string> p1 = kkli::make_pair<int, string>(1, "abcd");
			EXPECT_EQ_VAL(p1.first, 1);
			EXPECT_EQ_VAL(p1.second, "abcd");
			pair<int, double> p2 = kkli::make_pair<int, double>(2, 2.2);
			EXPECT_EQ_VAL(p2.first, 2);
			EXPECT_EQ_VAL(p2.second, 2.2);
		}

		//≤‚ ‘ operators
		void test_op_logical() {
			cout << "test: operators(==/!=...)" << endl;

			pair<int, string> p1(1, "");
			pair<int, string> p2(1, "abcd");
			pair<int, string> p3(1, "abcdef");
			pair<int, string> p4(1, "aceg");
			pair<int, string> p5(2, "");

			//operator ==
			EXPECT_EQ_VAL(p1 == p1, true);
			EXPECT_EQ_VAL(p1 == p2, false);
			EXPECT_EQ_VAL(p1 == p3, false);
			EXPECT_EQ_VAL(p1 == p4, false);
			EXPECT_EQ_VAL(p1 == p5, false);

			EXPECT_EQ_VAL(p2 == p1, false);
			EXPECT_EQ_VAL(p2 == p2, true);
			EXPECT_EQ_VAL(p2 == p3, false);
			EXPECT_EQ_VAL(p2 == p4, false);
			EXPECT_EQ_VAL(p2 == p5, false);

			EXPECT_EQ_VAL(p3 == p1, false);
			EXPECT_EQ_VAL(p3 == p2, false);
			EXPECT_EQ_VAL(p3 == p3, true);
			EXPECT_EQ_VAL(p3 == p4, false);
			EXPECT_EQ_VAL(p3 == p5, false);

			EXPECT_EQ_VAL(p4 == p1, false);
			EXPECT_EQ_VAL(p4 == p2, false);
			EXPECT_EQ_VAL(p4 == p3, false);
			EXPECT_EQ_VAL(p4 == p4, true);
			EXPECT_EQ_VAL(p4 == p5, false);

			EXPECT_EQ_VAL(p5 == p1, false);
			EXPECT_EQ_VAL(p5 == p2, false);
			EXPECT_EQ_VAL(p5 == p3, false);
			EXPECT_EQ_VAL(p5 == p4, false);
			EXPECT_EQ_VAL(p5 == p5, true);

			//operator !=
			EXPECT_EQ_VAL(p1 != p1, false);
			EXPECT_EQ_VAL(p1 != p2, true);
			EXPECT_EQ_VAL(p1 != p3, true);
			EXPECT_EQ_VAL(p1 != p4, true);
			EXPECT_EQ_VAL(p1 != p5, true);

			EXPECT_EQ_VAL(p2 != p1, true);
			EXPECT_EQ_VAL(p2 != p2, false);
			EXPECT_EQ_VAL(p2 != p3, true);
			EXPECT_EQ_VAL(p2 != p4, true);
			EXPECT_EQ_VAL(p2 != p5, true);

			EXPECT_EQ_VAL(p3 != p1, true);
			EXPECT_EQ_VAL(p3 != p2, true);
			EXPECT_EQ_VAL(p3 != p3, false);
			EXPECT_EQ_VAL(p3 != p4, true);
			EXPECT_EQ_VAL(p3 != p5, true);

			EXPECT_EQ_VAL(p4 != p1, true);
			EXPECT_EQ_VAL(p4 != p2, true);
			EXPECT_EQ_VAL(p4 != p3, true);
			EXPECT_EQ_VAL(p4 != p4, false);
			EXPECT_EQ_VAL(p4 != p5, true);

			EXPECT_EQ_VAL(p5 != p1, true);
			EXPECT_EQ_VAL(p5 != p2, true);
			EXPECT_EQ_VAL(p5 != p3, true);
			EXPECT_EQ_VAL(p5 != p4, true);
			EXPECT_EQ_VAL(p5 != p5, false);

			//operator <
			EXPECT_EQ_VAL(p1 < p1, false);
			EXPECT_EQ_VAL(p1 < p2, true);
			EXPECT_EQ_VAL(p1 < p3, true);
			EXPECT_EQ_VAL(p1 < p4, true);
			EXPECT_EQ_VAL(p1 < p5, true);

			EXPECT_EQ_VAL(p2 < p1, false);
			EXPECT_EQ_VAL(p2 < p2, false);
			EXPECT_EQ_VAL(p2 < p3, true);
			EXPECT_EQ_VAL(p2 < p4, true);
			EXPECT_EQ_VAL(p2 < p5, true);

			EXPECT_EQ_VAL(p3 < p1, false);
			EXPECT_EQ_VAL(p3 < p2, false);
			EXPECT_EQ_VAL(p3 < p3, false);
			EXPECT_EQ_VAL(p3 < p4, true);
			EXPECT_EQ_VAL(p3 < p5, true);

			EXPECT_EQ_VAL(p4 < p1, false);
			EXPECT_EQ_VAL(p4 < p2, false);
			EXPECT_EQ_VAL(p4 < p3, false);
			EXPECT_EQ_VAL(p4 < p4, false);
			EXPECT_EQ_VAL(p4 < p5, true);

			EXPECT_EQ_VAL(p5 < p1, false);
			EXPECT_EQ_VAL(p5 < p2, false);
			EXPECT_EQ_VAL(p5 < p3, false);
			EXPECT_EQ_VAL(p5 < p4, false);
			EXPECT_EQ_VAL(p5 < p5, false);

			//operator <=
			EXPECT_EQ_VAL(p1 <= p1, true);
			EXPECT_EQ_VAL(p1 <= p2, true);
			EXPECT_EQ_VAL(p1 <= p3, true);
			EXPECT_EQ_VAL(p1 <= p4, true);
			EXPECT_EQ_VAL(p1 <= p5, true);

			EXPECT_EQ_VAL(p2 <= p1, false);
			EXPECT_EQ_VAL(p2 <= p2, true);
			EXPECT_EQ_VAL(p2 <= p3, true);
			EXPECT_EQ_VAL(p2 <= p4, true);
			EXPECT_EQ_VAL(p2 <= p5, true);

			EXPECT_EQ_VAL(p3 <= p1, false);
			EXPECT_EQ_VAL(p3 <= p2, false);
			EXPECT_EQ_VAL(p3 <= p3, true);
			EXPECT_EQ_VAL(p3 <= p4, true);
			EXPECT_EQ_VAL(p3 <= p5, true);

			EXPECT_EQ_VAL(p4 <= p1, false);
			EXPECT_EQ_VAL(p4 <= p2, false);
			EXPECT_EQ_VAL(p4 <= p3, false);
			EXPECT_EQ_VAL(p4 <= p4, true);
			EXPECT_EQ_VAL(p4 <= p5, true);

			EXPECT_EQ_VAL(p5 <= p1, false);
			EXPECT_EQ_VAL(p5 <= p2, false);
			EXPECT_EQ_VAL(p5 <= p3, false);
			EXPECT_EQ_VAL(p5 <= p4, false);
			EXPECT_EQ_VAL(p5 <= p5, true);

			//operator >
			EXPECT_EQ_VAL(p1 > p1, false);
			EXPECT_EQ_VAL(p1 > p2, false);
			EXPECT_EQ_VAL(p1 > p3, false);
			EXPECT_EQ_VAL(p1 > p4, false);
			EXPECT_EQ_VAL(p1 > p5, false);

			EXPECT_EQ_VAL(p2 > p1, true);
			EXPECT_EQ_VAL(p2 > p2, false);
			EXPECT_EQ_VAL(p2 > p3, false);
			EXPECT_EQ_VAL(p2 > p4, false);
			EXPECT_EQ_VAL(p2 > p5, false);

			EXPECT_EQ_VAL(p3 > p1, true);
			EXPECT_EQ_VAL(p3 > p2, true);
			EXPECT_EQ_VAL(p3 > p3, false);
			EXPECT_EQ_VAL(p3 > p4, false);
			EXPECT_EQ_VAL(p3 > p5, false);

			EXPECT_EQ_VAL(p4 > p1, true);
			EXPECT_EQ_VAL(p4 > p2, true);
			EXPECT_EQ_VAL(p4 > p3, true);
			EXPECT_EQ_VAL(p4 > p4, false);
			EXPECT_EQ_VAL(p4 > p5, false);

			EXPECT_EQ_VAL(p5 > p1, true);
			EXPECT_EQ_VAL(p5 > p2, true);
			EXPECT_EQ_VAL(p5 > p3, true);
			EXPECT_EQ_VAL(p5 > p4, true);
			EXPECT_EQ_VAL(p5 > p5, false);

			//operator >=
			EXPECT_EQ_VAL(p1 >= p1, true);
			EXPECT_EQ_VAL(p1 >= p2, false);
			EXPECT_EQ_VAL(p1 >= p3, false);
			EXPECT_EQ_VAL(p1 >= p4, false);
			EXPECT_EQ_VAL(p1 >= p5, false);

			EXPECT_EQ_VAL(p2 >= p1, true);
			EXPECT_EQ_VAL(p2 >= p2, true);
			EXPECT_EQ_VAL(p2 >= p3, false);
			EXPECT_EQ_VAL(p2 >= p4, false);
			EXPECT_EQ_VAL(p2 >= p5, false);

			EXPECT_EQ_VAL(p3 >= p1, true);
			EXPECT_EQ_VAL(p3 >= p2, true);
			EXPECT_EQ_VAL(p3 >= p3, true);
			EXPECT_EQ_VAL(p3 >= p4, false);
			EXPECT_EQ_VAL(p3 >= p5, false);

			EXPECT_EQ_VAL(p4 >= p1, true);
			EXPECT_EQ_VAL(p4 >= p2, true);
			EXPECT_EQ_VAL(p4 >= p3, true);
			EXPECT_EQ_VAL(p4 >= p4, true);
			EXPECT_EQ_VAL(p4 >= p5, false);

			EXPECT_EQ_VAL(p5 >= p1, true);
			EXPECT_EQ_VAL(p5 >= p2, true);
			EXPECT_EQ_VAL(p5 >= p3, true);
			EXPECT_EQ_VAL(p5 >= p4, true);
			EXPECT_EQ_VAL(p5 >= p5, true);
			EXPECT_EQ_VAL(p5 >= p5, true);
		}

		//≤‚ ‘ get
		void test_get() {
			cout << "test: get()" << endl;

			pair<int, string> p1(1, "abcd");
			EXPECT_EQ_VAL(kkli::get<0>(p1), 1);
			EXPECT_EQ_VAL(kkli::get<1>(p1), "abcd");

			pair<double, char> p2(2.2, 'a');
			EXPECT_EQ_VAL(kkli::get<0>(p2), 2.2);
			EXPECT_EQ_VAL(kkli::get<1>(p2), 'a');
		}

		//≤‚ ‘ tuple_size
		void test_tuple_size() {
			cout << "test: tuple_size()" << endl;
						
			EXPECT_EQ_VAL(kkli::tuple_size<pair<int, string>>::value, 2);
			EXPECT_EQ_VAL(kkli::tuple_size<pair<int, double>>::value, 2);
		}

		//≤‚ ‘ tuple_element
		void test_tuple_element() {
			cout << "test: tuple_element()" << endl;

			pair<int, string> p1;
			kkli::tuple_element<0, pair<int, string>>::type i = 1;
			kkli::tuple_element<1, pair<int, string>>::type str = "abcd";
			EXPECT_EQ_VAL(i, 1);
			EXPECT_EQ_VAL(str, "abcd");
		}
	}
}