#pragma once

#include "stdafx.h"
#include "test.h"
#include "string.h"
#include "pair.h"
#include "algorithm_test_part1.h"
#include "algorithm_test_part2.h"
#include "algorithm_test_part3.h"

namespace test {
	namespace algorithm_test {

		//ÕûÌå²âÊÔ
		void test() {
			cout << "\n========== test: algorithm.h ==========" << endl;

			test_part1();
			test_part2();
			test_part3();
		}
	}
}