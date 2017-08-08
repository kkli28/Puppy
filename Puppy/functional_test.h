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
		using kkli::less;
		using kkli::equal_to;

		//«∞÷√…˘√˜
		void test_less();
		void test_equal_to();

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========== test: functional.h ==========" << endl;

			test_less();
			test_equal_to();
		}

		//≤‚ ‘ less
		void test_less() {
			cout << "test: less" << endl;

			less<int> ls1;
			less<string> ls2;
			EXPECT_EQ_VAL(ls1(1, 1), false);
			EXPECT_EQ_VAL(ls1(1, 2), true);
			EXPECT_EQ_VAL(ls2("abcd", "abcd"), false);
			EXPECT_EQ_VAL(ls2("abcd", "efgh"), true);
		}

		//≤‚ ‘ equal_to
		void test_equal_to() {
			cout << "test: equal_to" << endl;

			equal_to<int> eq1;
			equal_to<string> eq2;
			EXPECT_EQ_VAL(eq1(1, 1), true);
			EXPECT_EQ_VAL(eq1(1, 2), false);
			EXPECT_EQ_VAL(eq2("abcd", "abcd"), true);
			EXPECT_EQ_VAL(eq2("abcd", "efgh"), false);
		}
	}
}
