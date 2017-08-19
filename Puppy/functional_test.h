#pragma once

#include "stdafx.h"
#include "functional.h"
#include "string.h"
#include "test.h"

namespace test {
	namespace functional_test {

		using std::cout;
		using std::endl;
		using kkli::string;

		//«∞÷√…˘√˜
		void test_less();
		void test_equal_to();
		void test_plus();
		void test_minus();
		void test_multiplies();
		void test_divides();

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "            functional.h " << endl;
			cout << "========================================" << endl;

			test_less();
			test_equal_to();
			test_plus();
			test_minus();
			test_multiplies();
			test_divides();
		}

		//≤‚ ‘ less
		void test_less() {
			cout << "test: less" << endl;

			kkli::less<int> ls1;
			kkli::less<string> ls2;
			EXPECT_EQ_VAL(ls1(1, 1), false);
			EXPECT_EQ_VAL(ls1(1, 2), true);
			EXPECT_EQ_VAL(ls2("abcd", "abcd"), false);
			EXPECT_EQ_VAL(ls2("abcd", "efgh"), true);
		}

		//≤‚ ‘ equal_to
		void test_equal_to() {
			cout << "test: equal_to" << endl;

			kkli::equal_to<int> eq1;
			kkli::equal_to<string> eq2;
			EXPECT_EQ_VAL(eq1(1, 1), true);
			EXPECT_EQ_VAL(eq1(1, 2), false);
			EXPECT_EQ_VAL(eq2("abcd", "abcd"), true);
			EXPECT_EQ_VAL(eq2("abcd", "efgh"), false);
		}

		//≤‚ ‘ plus
		void test_plus() {
			cout << "test: plus" << endl;

			kkli::plus<int> pls1;
			EXPECT_EQ_VAL(pls1(1, 1), 2);
			EXPECT_EQ_VAL(pls1(2, 3), 5);
		}

		//≤‚ ‘ minus
		void test_minus() {
			cout << "test: minus" << endl;

			kkli::minus<int> mns1;
			EXPECT_EQ_VAL(mns1(2, 1), 1);
			EXPECT_EQ_VAL(mns1(4, 2), 2);
		}

		//≤‚ ‘ multiplies
		void test_multiplies() {
			cout << "test: multiplies" << endl;

			kkli::multiplies<int> mp1;
			EXPECT_EQ_VAL(mp1(1, 2), 2);
			EXPECT_EQ_VAL(mp1(2, 3), 6);
		}

		//≤‚ ‘ divides
		void test_divides() {
			cout << "test: divides" << endl;

			kkli::divides<int> dvd1;
			EXPECT_EQ_VAL(dvd1(2, 1), 2);
			EXPECT_EQ_VAL(dvd1(6, 3), 2);
		}
	}
}
