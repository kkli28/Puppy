#pragma once

#include "stdafx.h"
#include "array.h"

namespace test {
	namespace array_test {

		using std::cout;
		using std::endl;
		using kkli::array;

		//º¯ÊıÉùÃ÷
		void test_constructor();
		void test_at();
		void test_front_and_back();
		void test_data();
		void test_begin_and_end();
		void test_fill();
		void test_swap();
		void test_assign();					//operator =
		void test_op_square_bracket();		//operator []
		void test_op_equal();				//operator == / !=
		void test_op_less();				//operator <  / >=
		void test_op_greater();				//operator >  / <=
		void test_get();					//get
		void test_tuple_size();				//tuple_size
		void test_tuple_element();			//tuple_element

		//ÕûÌå²âÊÔ
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: array " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_at();
			test_front_and_back();
			test_data();
			test_begin_and_end();
			test_fill();
			test_swap();
			test_assign();
			test_op_square_bracket();
			test_op_equal();
			test_op_less();
			test_op_greater();
			test_get();
			test_tuple_size();
			test_tuple_element();
		}

		//²âÊÔ ¹¹Ôìº¯Êı
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			array<int, 4> arr1;
			array<int, 4> arr2{ 1,2,3,4 };
			array<int, 0> arr3;
			array<int, 4> arr4{ 1,2 };
			arr1.print();
			arr2.print();
			arr3.print();
			arr4.print();
		}

		//²âÊÔ at()º¯Êı
		void test_at() {
			cout << "\ntest_at()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			cout << arr1.at(0) << endl;
			cout << arr1.at(1) << endl;
			cout << arr1.at(2) << endl;
			cout << arr1.at(3) << endl;
			try {
				cout << arr1.at(4) << endl;
			}
			catch (const std::runtime_error& e) {
				e.what();
			}
		}

		//²âÊÔ frontºÍback
		void test_front_and_back() {
			cout << "\ntest_front_and_back()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			cout << "front: " << arr1.front() << endl;
			cout << "back: " << arr1.back() << endl;

			array<int, 0> arr2;
			try {
				cout << "front: " << arr2.front() << endl;
				cout << "back: " << arr2.back() << endl;
			}
			catch (const std::runtime_error& e) {
				cout << e.what() << endl;
			}
		}

		//²âÊÔ data
		void test_data() {
			cout << "\ntest_data()" << endl;

			array<int, 4> arr{ 1,2,3,4 };
			auto data = arr.data();
			for (int i = 0; i < 4; ++i)
				cout << data[i] << " ";
			cout << endl;
		}

		//²âÊÔ beginºÍend
		void test_begin_and_end() {
			cout << "\ntest_begin_and_end()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			cout << "begin: " << *(arr1.begin()) << endl;

			cout << "arr1 [foreach]: ";
			for (auto a : arr1) cout << a << " ";
			cout << endl;

			cout << "arr1: ";
			arr1.print();

			cout << "arr2: ";
			array<int, 0> arr2;
			arr2.print();
		}

		//²âÊÔ fill
		void test_fill() {
			cout << "\ntest_fill()" << endl;

			array<int, 4> arr;
			arr.fill(1);
			arr.print();
		}

		//²âÊÔ swap
		void test_swap() {
			cout << "\ntest_swap()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			array<int, 4> arr2{ 5,6,7,8 };
			arr1.swap(arr2);
			arr1.print();
			arr2.print();

			kkli::swap(arr1, arr2);
			arr1.print();
			arr2.print();
		}

		//²âÊÔ operator =
		void test_assign() {
			cout << "\ntest_assign()" << endl;

			array<int, 4> arr1{ 1,2,3,4 };
			arr1 = array<int, 4>{5, 6, 7, 8};
			arr1.print();
		}

		//²âÊÔ operator []
		void test_op_square_bracket() {
			cout << "\ntest_op_square_bracket()" << endl;

			array<int, 4> arr{ 1,2,3,4 };
			for (int i = 0; i < 4; ++i)
				cout << arr[i] << " ";
			cout << endl;
		}

		//²âÊÔ operator == / !=
		void test_op_equal() {
			cout << "\ntest_op_equal()" << endl;

			array<int, 4> arr1;
			array<int, 4> arr2{};
			array<int, 4> arr3{ 1,2,3,4 };
			array<int, 4> arr4{ 1,2,3,4 };
			array<int, 5> arr5;

			if (arr1 == arr2)
				cout << "arr1 == arr2" << endl;
			else cout << "arr1 != arr2" << endl;

			if (arr3 == arr4)
				cout << "arr3 == arr4" << endl;
			else cout << "arr3 != arr4" << endl;

			if (arr1 == arr3)
				cout << "arr1 == arr3" << endl;
			else cout << "arr1 != arr3" << endl;
		}

		//²âÊÔ operator < / >=
		void test_op_less() {
			cout << "\ntest_op_less()" << endl;

			array<int, 4> arr1;
			array<int, 4> arr2{};
			array<int, 4> arr3{ 1,2,3,4 };
			array<int, 4> arr4{ 1,3,4,5 };
			if (arr1 < arr2)
				cout << "arr1 <  arr2" << endl;
			else cout << "arr1 >= arr2" << endl;

			if (arr3 < arr4)
				cout << "arr3 <  arr4" << endl;
			else cout << "arr3 >= arr4" << endl;

			if (arr1 < arr3)
				cout << "arr1 <  arr3" << endl;
			else cout << "arr1 >= arr3" << endl;
		}

		//²âÊÔ operator > / <=
		void test_op_greater() {
			cout << "\ntest_op_greater()" << endl;

			array<int, 4> arr1;
			array<int, 4> arr2{};
			array<int, 4> arr3{ 1,2,3,4 };
			array<int, 4> arr4{ 1,3,4,5 };
			if (arr1 > arr2)
				cout << "arr1 >  arr2" << endl;
			else cout << "arr1 <= arr2" << endl;

			if (arr4 > arr3)
				cout << "arr4 >  arr3" << endl;
			else cout << "arr4 <= arr3" << endl;

			if (arr3 > arr1)
				cout << "arr3 >  arr1" << endl;
			else cout << "arr3 <= arr1" << endl;
		}

		//²âÊÔ get
		void test_get() {
			cout << "\ntest_get()" << endl;

			using kkli::get;
			array<int, 4> arr{ 1,2,3,4 };

			cout << get<0>(arr) << endl;
			cout << get<1>(arr) << endl;
			cout << get<2>(arr) << endl;
			cout << get<3>(arr) << endl;
			try {
				cout << get<4>(arr) << endl;
			}
			catch (const std::runtime_error& e) {
				cout << e.what() << endl;
			}
		}

		//²âÊÔ tuple_size
		void test_tuple_size() {
			cout << "\ntest_tuple_size()" << endl;

			cout << kkli::tuple_size<array<int, 4>>::value << endl;
		}

		//²âÊÔ tuple_element
		void test_tuple_element() {
			cout << "\ntest_tuple_element()" << endl;

			kkli::tuple_element<0, array<int, 4>>::type t1 = 1;
			cout << t1 << endl;
		}
	}
}