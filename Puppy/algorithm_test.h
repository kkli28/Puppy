#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "string.h"
#include "pair.h"
#include "algorithm_test_part1.h"
#include "algorithm_test_part2.h"
#include "algorithm_test_part3.h"
#include "algorithm_test_part4.h"
#include "algorithm_test_part5.h"
#include "algorithm_test_part6.h"
#include "algorithm_test_Part7.h"
#include "algorithm_test_Part8.h"
#include "algorithm_test_Part9.h"

namespace test {
	namespace algorithm_test {

		//ÕûÌå²âÊÔ
		void test() {
			cout << "\n========================================" << endl;
			cout << "            algorithm.h " << endl;
			cout << "========================================" << endl;

			test_part1();
			test_part2();
			test_part3();
			test_part4();
			test_part5();
			test_part6();
			test_part7();
			test_part8();
			test_part9();
		}
	}
}
