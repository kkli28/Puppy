#pragma once

#include "stdafx.h"
#include "array.h"

namespace test {
	namespace array_test {

		using std::cout;
		using std::endl;
		using kkli::array;

		//∫Ø ˝…˘√˜
		void test_constructor();
		void test_at();
		void test_front_and_back();
		void test_data();
		void test_begin_and_end();
		void test_rbegin_and_rend();
		void test_fill();
		void test_swap();
		void test_assign();					//operator =
		void test_op_square_bracket();		//operator []
		void test_operators();				//operator == != < <= > >=
		void test_get();					//get
		void test_tuple_size();				//tuple_size
		void test_tuple_element();			//tuple_element

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: array " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_at();
			test_front_and_back();
			test_data();
			test_begin_and_end();
			test_rbegin_and_rend();
			test_fill();
			test_swap();
			test_assign();
			test_op_square_bracket();
			test_operators();
			test_get();
			test_tuple_size();
			test_tuple_element();
		}

		//≤‚ ‘ constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			array<int, 4> arr1;
			array<int, 4> arr2{ 1,2,3,4 };
			array<int, 0> arr3;

			EXPECT_EQ_VAL(arr1, array<int, 4>{ 0, 0, 0, 0 });
			EXPECT_EQ_VAL(arr2, array<int, 4>{1, 2, 3, 4});
			EXPECT_EQ_VAL(arr2[1], 2);
			EXPECT_EQ_VAL(arr3, array<int, 0>());
		}

		//≤‚ ‘ at
		void test_at() {
			cout << "test: at()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			EXPECT_EQ_VAL(arr1.at(0), 1);
			EXPECT_EQ_VAL(arr1.at(1), 2);
			EXPECT_EQ_VAL(arr1.at(2), 3);
			EXPECT_EQ_VAL(arr1.at(3), 4);
		}

		//≤‚ ‘ front
		void test_front_and_back() {
			cout << "test: front()" << endl;
			cout << "test: back()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			EXPECT_EQ_VAL(arr1.front(), 1);
			EXPECT_EQ_VAL(arr1.back(), 4);
		}

		//≤‚ ‘ data
		void test_data() {
			cout << "test: data()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			int* data1 = arr1.data();
			EXPECT_EQ_VAL(data1[0], 1);
			EXPECT_EQ_VAL(data1[2], 3);
		}

		//≤‚ ‘ begin∫Õend
		void test_begin_and_end() {
			cout << "test: begin()" << endl;
			cout << "test: end()" << endl;
			cout << "test: cbegin()" << endl;
			cout << "test: cend()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			EXPECT_EQ_VAL(arr1.begin(), arr1.data());
			EXPECT_EQ_VAL(*(arr1.begin()), 1);
			EXPECT_EQ_VAL(*(arr1.end()-1), 4);

			const array<int, 4> arr2{ 1,2,3,4 };
			EXPECT_EQ_VAL(arr2.cbegin(), arr2.data());
			EXPECT_EQ_VAL(*(arr1.cbegin()), 1);
			EXPECT_EQ_VAL(*(arr1.cend() - 1), 4);
		}

		//≤‚ ‘ rbegin∫Õrend
		void test_rbegin_and_rend() {
			cout << "test: rbegin()" << endl;
			cout << "test: rend()" << endl;
			cout << "test: crbegin()" << endl;
			cout << "test: crend()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			EXPECT_EQ_VAL(*(arr1.rbegin()), 4);
			EXPECT_EQ_VAL(*(arr1.rend() - 1), 1);
			
			const array<int, 4> arr2{ 1,2,3,4 };
			EXPECT_EQ_VAL(*(arr1.crbegin()), 4);
			EXPECT_EQ_VAL(*(arr1.crend() - 1), 1);
		}

		//≤‚ ‘ fill
		void test_fill() {
			cout << "test: fill()" << endl;

			array<int, 4> arr1;
			EXPECT_EQ_VAL(arr1, array<int, 4>{0, 0, 0, 0});
			arr1.fill(1);
			EXPECT_EQ_VAL(arr1, array<int, 4>{1, 1, 1, 1});
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			array<int, 4> arr2{ 5,6,7,8 };
			arr1.swap(arr2);
			EXPECT_EQ_VAL(arr1, array<int, 4>{5, 6, 7, 8});
			EXPECT_EQ_VAL(arr2, array<int, 4>{1, 2, 3, 4});
		}

		//≤‚ ‘ operator =
		void test_assign() {
			cout << "test: operator=" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			arr1 = array<int, 4>{5, 6, 7, 8};
			EXPECT_EQ_VAL(arr1, array<int, 4>{5, 6, 7, 8});
		}

		//≤‚ ‘ operator []
		void test_op_square_bracket() {
			cout << "test: operator[]" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			EXPECT_EQ_VAL(arr1[0], 1);
			EXPECT_EQ_VAL(arr1[1], 2);
			EXPECT_EQ_VAL(arr1[2], 3);
			EXPECT_EQ_VAL(arr1[3], 4);
		}

		//≤‚ ‘ operator == < >
		void test_operators() {
			cout << "test: operator==" << endl;
			cout << "test: operator!=" << endl;
			cout << "test: operator<" << endl;
			cout << "test: operator>" << endl;
			cout << "test: operator<=" << endl;
			cout << "test: operator>=" << endl;

			array<int, 4> arr1;
			array<int, 4> arr2{ 0,0,0,0 };
			array<int, 4> arr3{ 1,2,3,4 };
			array<int, 4> arr4{ 1,2,3,5 };

			//==
			EXPECT_EQ_VAL(arr1 == arr1, true);
			EXPECT_EQ_VAL(arr1 == arr2, true);
			EXPECT_EQ_VAL(arr1 == arr3, false);
			EXPECT_EQ_VAL(arr1 == arr4, false);

			EXPECT_EQ_VAL(arr2 == arr1, true);
			EXPECT_EQ_VAL(arr2 == arr2, true);
			EXPECT_EQ_VAL(arr2 == arr3, false);
			EXPECT_EQ_VAL(arr2 == arr4, false);

			EXPECT_EQ_VAL(arr3 == arr1, false);
			EXPECT_EQ_VAL(arr3 == arr2, false);
			EXPECT_EQ_VAL(arr3 == arr3, true);
			EXPECT_EQ_VAL(arr3 == arr4, false);

			EXPECT_EQ_VAL(arr4 == arr1, false);
			EXPECT_EQ_VAL(arr4 == arr2, false);
			EXPECT_EQ_VAL(arr4 == arr3, false);
			EXPECT_EQ_VAL(arr4 == arr4, true);

			//<
			EXPECT_EQ_VAL(arr1 < arr1, false);
			EXPECT_EQ_VAL(arr1 < arr2, false);
			EXPECT_EQ_VAL(arr1 < arr3, true);
			EXPECT_EQ_VAL(arr1 < arr4, true);

			EXPECT_EQ_VAL(arr2 < arr1, false);
			EXPECT_EQ_VAL(arr2 < arr2, false);
			EXPECT_EQ_VAL(arr2 < arr3, true);
			EXPECT_EQ_VAL(arr2 < arr4, true);

			EXPECT_EQ_VAL(arr3 < arr1, false);
			EXPECT_EQ_VAL(arr3 < arr2, false);
			EXPECT_EQ_VAL(arr3 < arr3, false);
			EXPECT_EQ_VAL(arr3 < arr4, true);

			EXPECT_EQ_VAL(arr4 < arr1, false);
			EXPECT_EQ_VAL(arr4 < arr2, false);
			EXPECT_EQ_VAL(arr4 < arr3, false);
			EXPECT_EQ_VAL(arr4 < arr4, false);

			//>
			EXPECT_EQ_VAL(arr1 > arr1, false);
			EXPECT_EQ_VAL(arr1 > arr2, false);
			EXPECT_EQ_VAL(arr1 > arr3, false);
			EXPECT_EQ_VAL(arr1 > arr4, false);

			EXPECT_EQ_VAL(arr2 > arr1, false);
			EXPECT_EQ_VAL(arr2 > arr2, false);
			EXPECT_EQ_VAL(arr2 > arr3, false);
			EXPECT_EQ_VAL(arr2 > arr4, false);

			EXPECT_EQ_VAL(arr3 > arr1, true);
			EXPECT_EQ_VAL(arr3 > arr2, true);
			EXPECT_EQ_VAL(arr3 > arr3, false);
			EXPECT_EQ_VAL(arr3 > arr4, false);

			EXPECT_EQ_VAL(arr4 > arr1, true);
			EXPECT_EQ_VAL(arr4 > arr2, true);
			EXPECT_EQ_VAL(arr4 > arr3, true);
			EXPECT_EQ_VAL(arr4 > arr4, false);
		}

		//≤‚ ‘ get
		void test_get() {
			cout << "test: get()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			EXPECT_EQ_VAL(kkli::get<0>(arr1), 1);
			EXPECT_EQ_VAL(kkli::get<1>(arr1), 2);
			EXPECT_EQ_VAL(kkli::get<2>(arr1), 3);
			EXPECT_EQ_VAL(kkli::get<3>(arr1), 4);
		}

		//≤‚ ‘ tuple_size
		void test_tuple_size() {
			cout << "test: tuple_size()" << endl;

			EXPECT_EQ_VAL(kkli::tuple_size<array<int, 4>>::value, 4);
		}

		//≤‚ ‘ tuple_element
		void test_tuple_element() {
			cout << "test: tuple_element()" << endl;

			kkli::tuple_element<1, array<int, 4>>::type i = 1;
			EXPECT_EQ_VAL(i, 1);
		}
	}
}