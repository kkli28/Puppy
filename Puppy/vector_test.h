#pragma once

#include "stdafx.h"
#include "vector.h"

namespace test {
	namespace vector_test {

		using std::cout;
		using std::endl;
		using std::string;
		using kkli::vector;

		//«∞÷√…˘√˜
		void test_constructor();
		void test_destructor();
		void test_op_assign();				//test: operator =
		void test_assign();
		void test_op_square_bracket();		//test: operator []
		void test_begin_and_end();
		void test_front_and_back();
		void test_data();
		void test_empty();
		void test_size();
		void test_reserve();
		void test_shrink_to_fit();
		void test_clear();
		void test_insert();
		void test_erase();
		void test_push_back();
		void test_pop_back();
		void test_resize();
		void test_swap();
		void test_op_compare();				//test: operator == / != ...

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: vector " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_destructor();
			test_op_assign();
			test_assign();
			test_op_square_bracket();
			test_begin_and_end();
			test_front_and_back();
			test_data();
			test_empty();
			test_size();
			test_reserve();
			test_shrink_to_fit();
			test_clear();
			test_insert();
			test_erase();
			test_push_back();
			test_pop_back();
			//test_resize();
			//test_swap();
			//test_op_compare();
		}

		//≤‚ ‘ constructor
		void test_constructor() {
			cout << "\ntest_constructor()" << endl;

			//vector()
			vector<int> vec1;
			vec1.print("vec1: ");

			//vector(size_type, const T&, const Allocator&)
			vector<int> vec2(4);
			vec2.print("vec2: ");
			vector<int> vec3(4, 1);
			vec3.print("vec3: ");
			vector<int,std::allocator<int>> vec4(4, 2, std::allocator<int>());
			vec4.print("vec4: ");

			//vector(InputIterator, InputIterator) -- ∏√ππ‘Ï√ª”–∂®“Â£¨–Ë“™ π”√SFINAE£¨≤ªª·£°£°£°
			//vector<int> vec5(vec3.begin(), vec3.end());
			//vec5.print("vec5: ");

			//vector(const vector&)
			vector<int> vec5(vec1);
			vec5.print("vec5: ");
			vector<int> vec6(vec3);
			vec6.print("vec6: ");
			
			//vector(vector&&)
			vector<int> vec7(std::move(vec6));
			vec7.print("vec7: ");
			vec6.print("vec6: ");

			//vector(initializer_list)
			vector<int> vec8{ 1,2,3,4 };
			vec8.print("vec8: ");
		}

		//≤‚ ‘ destructor
		void test_destructor() {
			cout << "\ntest_destructor()" << endl;

			vector<int> vec{ 1,2,3,4 };
			vec.~vector();
			if (vec.data() == nullptr) cout << "Œˆππ≥…π¶" << endl;
		}

		//≤‚ ‘ operator =
		void test_op_assign() {
			cout << "\ntest_op_assign()" << endl;

			vector<int> vec1;
			vector<int> vec2;
			vec2 = vec1;
			vec2.print("vec2: ");

			vector<int> vec3{ 1,2,3,4 };
			vec2 = vec3;
			vec2.print("vec2: ");
			
			vec3 = vec1;
			vec3.print("vec3: ");
		}

		//≤‚ ‘ assign
		void test_assign() {
			cout << "\ntest_assign()" << endl;

			vector<int> vec1;
			vec1.assign(4, 1);
			vec1.print("vec1: ");

			vec1.assign({ 1,2,3,4 });
			vec1.print("vec1: ");
		}

		//≤‚ ‘ operator []
		void test_op_square_bracket() {
			cout << "\ntest_op_square_bracket()" << endl;

			vector<int> vec{ 1,2,3,4 };
			cout << vec[0] << " " << vec[1] << " ";
			cout << vec[2] << " " << vec[3] << endl;
		}

		//≤‚ ‘ begin / cbegin / end / cend
		void test_begin_and_end() {
			cout << "\ntest_begin_and_end()" << endl;

			vector<int> vec{ 1,2,3,4 };
			cout << "vec: ";
			for (auto iter = vec.begin(); iter != vec.end(); ++iter)
				cout << *iter << " ";
			cout << endl;

			cout << "vec: ";
			for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter)
				cout << *iter << " ";
			cout << endl;
		}

		//≤‚ ‘ front / back
		void test_front_and_back() {
			cout << "\ntest_front_and_back()" << endl;

			vector<int> vec{ 1,2,3,4 };
			cout << vec.front() << "  " << vec.back() << endl;
		}

		//≤‚ ‘ data
		void test_data() {
			cout << "\ntest_data()" << endl;

			vector<int> vec{ 1,2,3,4 };
			auto ptr = vec.data();
			for (int i = 0; i < vec.size(); ++i)
				cout << ptr[i] << " ";
			cout << endl;
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "\ntest_empty()" << endl;

			cout << "vec1: " << (vector<int>().empty() ? "empty" : "non-empty") << endl;
			cout << "vec2: " << (vector<int>{1, 2, 3, 4}.empty() ? "empty" : "not empty") << endl;
		}

		//≤‚ ‘ size
		void test_size() {
			cout << "\ntest_size()" << endl;

			cout << vector<int>().size() << endl;
			cout << vector<int>{1, 2, 3, 4}.size() << endl;
		}

		//≤‚ ‘ reserve
		void test_reserve() {
			cout << "\ntest_reserve()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			vec1.reserve(4);
			vec1.print("vec1: ");
			vec2.reserve(2);
			vec2.print("vec2: ");
			auto old_data = vec2.data();
			vec2.reserve(8);
			vec2.print("vec2: ");
			auto new_data = vec2.data();
			cout << (old_data == new_data ? "not allocate memory" : "allocate memory") << endl;
		}

		//≤‚ ‘ shrink_to_fit
		void test_shrink_to_fit() {
			cout << "\ntest_shrink_to_fit()" << endl;

			vector<int> vec{ 1,2,3,4 };
			vec.shrink_to_fit();
			vec.print("vec: ");

			vec.push_back(5);
			vec.print("vec: ");

			vec.shrink_to_fit();
			vec.print("vec: ");
		}

		//≤‚ ‘ clear
		void test_clear() {
			cout << "\ntest_clear()" << endl;

			vector<int> vec{ 1,2,3,4 };
			vec.clear();
			vec.print("vec: ");
		}

		//≤‚ ‘ insert
		void test_insert() {
			cout << "\ntest_insert()" << endl;

			vector<int> vec{ 1,2,3,4 };

			//insert(pos, il);
			vec.insert(vec.begin(), { 1,2,3,4 });
			vec.print("vec: ");
			
			//insert(pos, n, val)
			vec.insert(vec.begin(), 4, 1);
			vec.print("vec: ");

			//insert(pos, val);
			vec.insert(vec.begin(), 4);
			vec.print("vec: ");
		}

		//≤‚ ‘ erase
		void test_erase() {
			cout << "\ntest_erase()" << endl;

			vector<int> vec{ 1,2,3,4 };
			vec.erase(vec.begin(), vec.begin() + 2);
			vec.print("vec: ");
			vec.erase(vec.begin(), vec.end());
			vec.print("vec: ");
		}

		//≤‚ ‘ push_back
		void test_push_back() {
			cout << "\ntset_push_back()" << endl;

			vector<int> vec;
			vec.print("vec: ");

			vec.push_back(1);
			vec.print("vec: ");
			
			vec.push_back(2);
			vec.print("vec: ");
			
			for (int i = 3; i < 9; ++i)
				vec.push_back(i);
			vec.print("vec: ");

			vec.push_back(9);
			vec.print("vec: ");
		}

		//≤‚ ‘ pop_back
		void test_pop_back() {
			cout << "\ntest_pop_back()" << endl;

			vector<int> vec{ 1,2,3,4 };
			for (int i = 0; i < 4; ++i) {
				vec.pop_back();
				vec.print("vec: ");
			}
		}

		//≤‚ ‘ resize
		void test_resize() {
			cout << "\ntest_resize()" << endl;

			//TODO: 
		}
	}
}