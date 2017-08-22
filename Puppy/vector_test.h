#pragma once

#include "stdafx.h"
#include "test_utility.h"
#include "vector.h"

namespace test {
	namespace vector_test {

		using std::cout;
		using std::endl;
		using kkli::vector;

		//«∞÷√…˘√˜
		void test_constructor();
		void test_op_assign();			//test: operator =
		void test_assign();
		void test_at();
		void test_op_square_bracket();	//test: operator []
		void test_front_and_back();
		void test_data();
		void test_begin_and_end();
		void test_rbegin_and_rend();
		void test_empty();
		void test_size();
		void test_reserve();
		void test_capacity();
		void test_clear();
		void test_insert();
		void test_erase();
		void test_push_back();
		void test_pop_back();
		void test_resize();
		void test_swap();
		void test_operators();		//test: operator == / != ...

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "          vector.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			test_op_assign();
			test_assign();
			test_at();
			test_op_square_bracket();
			test_front_and_back();
			test_data();
			test_begin_and_end();
			test_rbegin_and_rend();
			test_empty();
			test_size();
			test_reserve();
			test_capacity();
			test_clear();
			test_insert();
			test_erase();
			test_push_back();
			test_pop_back();
			test_resize();
			test_swap();
			test_operators();
		}

		//≤‚ ‘ constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			vector<int> vec1; //vector()
			EXPECT_EQ_VAL(vec1.empty(), true);
			EXPECT_EQ_VAL(vec1.size(), 0);
			EXPECT_EQ_VAL(vec1.capacity(), 0);

			vector<int> vec2{ kkli::allocator<int>() }; //vector(alloc)
			EXPECT_EQ_VAL(vec2.empty(), true);
			EXPECT_EQ_VAL(vec2.size(), 0);
			EXPECT_EQ_VAL(vec2.capacity(), 0);

			vector<int> vec3(4, 1); //vector(count, value)
			EXPECT_EQ_ITERVAL(vec3.begin(), vec3.end(), 1);
			EXPECT_EQ_VAL(vec3.size(), 4);
			EXPECT_EQ_VAL(vec3.capacity(), 4);

			vector<int> vec4(4); //vector(count)
			EXPECT_EQ_ITERVAL(vec4.begin(), vec4.end(), 0);
			EXPECT_EQ_VAL(vec4.size(), 4);
			EXPECT_EQ_VAL(vec4.capacity(), 4);

			vector<int> vec5(vec3); //vector(rhs)
			EXPECT_EQ_ITERVAL(vec5.begin(), vec5.end(), 1);
			EXPECT_EQ_VAL(vec5.size(), 4);
			EXPECT_EQ_VAL(vec5.capacity(), 4);

			vector<int> vec6(std::move(vec3)); //vector(&&rhs)
			EXPECT_EQ_ITERVAL(vec6.begin(), vec6.end(), 1);
			EXPECT_EQ_VAL(vec6.size(), 4);
			EXPECT_EQ_VAL(vec6.capacity(), 4);
			EXPECT_EQ_VAL(vec3.empty(), true);
			EXPECT_EQ_VAL(vec3.size(), 0);
			EXPECT_EQ_VAL(vec3.capacity(), 0);

			vector<int> vec7{ 1,2,3,4 }; //vector(init)
			EXPECT_EQ_ITERLIST(vec7.begin(), vec7.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(vec7.size(), 4);
			EXPECT_EQ_VAL(vec7.capacity(), 4);
		}

		//≤‚ ‘ operator=
		void test_op_assign() {
			cout << "test: operator=" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			vector<int> vec3{ 2,4,6,8 };
			vector<int> vec4;
			
			vec1 = vec2; //operator=(rhs)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,3,4 });
			vec1 = vec4;
			EXPECT_EQ_VAL(vec1.empty(), true);
			
			vec1 = std::move(vec3); //operator=(&&rhs)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 2,4,6,8 });

			vec1 = { 1,3,5,7 }; //operator=(init)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,3,5,7 });

			vec1 = vec4;
			EXPECT_EQ_VAL(vec1.empty(), true);
		}

		//≤‚ ‘ assign
		void test_assign() {
			cout << "test: assign()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };

			vec1.assign(4, 1); //assign(count, value)
			EXPECT_EQ_ITERVAL(vec1.begin(), vec1.end(), 1);

			vec1.assign_range(vec2.begin(), vec2.end()); //assign_range(first, last)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,3,4 });

			vec1.assign({ 2,4,6,8 }); //assign(init)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 2,4,6,8 });
		}

		//≤‚ ‘ at
		void test_at() {
			cout << "test: at()" << endl;

			vector<int> vec1{ 0,1,2,3 };

			EXPECT_EQ_VAL(vec1.at(0), 0);
			EXPECT_EQ_VAL(vec1.at(1), 1);
			EXPECT_EQ_VAL(vec1.at(2), 2);
			EXPECT_EQ_VAL(vec1.at(3), 3);
		}

		//≤‚ ‘ operator[]
		void test_op_square_bracket() {
			cout << "test: operator[]" << endl;

			vector<int> vec1{ 0,1,2,3 };

			EXPECT_EQ_VAL(vec1[0], 0);
			EXPECT_EQ_VAL(vec1[1], 1);
			EXPECT_EQ_VAL(vec1[2], 2);
			EXPECT_EQ_VAL(vec1[3], 3);
		}

		//≤‚ ‘ front & back
		void test_front_and_back() {
			vector<int> vec1{ 1,2,3,4 };

			cout << "test: front()" << endl;
			EXPECT_EQ_VAL(vec1.front(), 1);

			cout << "test: back()" << endl;
			EXPECT_EQ_VAL(vec1.back(), 4);
		}

		//≤‚ ‘ data
		void test_data() {
			cout << "test: data()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			auto iter1 = vec1.data();
			auto iter2 = vec2.data();

			EXPECT_EQ_VAL(iter1, nullptr);
			EXPECT_EQ_VAL(*(iter2++), 1);
			EXPECT_EQ_VAL(*(iter2++), 2);
			EXPECT_EQ_VAL(*(iter2++), 3);
			EXPECT_EQ_VAL(*(iter2++), 4);
		}

		//≤‚ ‘ begin & end & cbegin & cend
		void test_begin_and_end() {
			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			const vector<int> vec3{ 1,2,3,4 };

			cout << "test: begin()" << endl;
			EXPECT_EQ_VAL(vec1.begin(), nullptr);
			EXPECT_EQ_VAL(*(vec2.begin()), 1);

			cout << "test: cbegin()" << endl;
			EXPECT_EQ_VAL(*(vec3.cbegin()), 1);

			cout << "test: end()" << endl;
			EXPECT_EQ_VAL(vec1.end(), nullptr);
			EXPECT_EQ_VAL(*(kkli::prev(vec2.end())), 4);

			cout << "test: cend()" << endl;
			EXPECT_EQ_VAL(*(kkli::prev(vec3.cend())), 4);
		}

		//≤‚ ‘ rbegin & rend & crbegin & crend
		void test_rbegin_and_rend() {
			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			const vector<int> vec3{ 1,2,3,4 };

			cout << "test: rbegin()" << endl;
			EXPECT_EQ_VAL(vec1.rbegin(), vec1.rend());
			EXPECT_EQ_VAL(*(vec2.rbegin()), 4);

			cout << "test: crbegin()" << endl;
			EXPECT_EQ_VAL(*(vec3.crbegin()), 4);

			cout << "test: rend()" << endl;
			EXPECT_EQ_VAL(*(kkli::prev(vec2.rend())), 1);

			cout << "test: crend()" << endl;
			EXPECT_EQ_VAL(*(kkli::prev(vec3.crend())), 1);
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };

			EXPECT_EQ_VAL(vec1.empty(), true);
			EXPECT_EQ_VAL(vec2.empty(), false);
		}

		//≤‚ ‘ size
		void test_size() {
			cout << "test: size()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };

			EXPECT_EQ_VAL(vec1.size(), 0);
			EXPECT_EQ_VAL(vec2.size(), 4);
		}

		//≤‚ ‘ reserve
		void test_reserve() {
			cout << "test: reserve()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };

			vec1.reserve(4);
			EXPECT_EQ_VAL(vec1.empty(), true);
			EXPECT_EQ_VAL(vec1.capacity(), 4);

			vec2.reserve(2);
			EXPECT_EQ_ITERLIST(vec2.begin(), vec2.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(vec2.capacity(), 4);

			vec2.reserve(8);
			EXPECT_EQ_ITERLIST(vec2.begin(), vec2.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(vec2.size(), 4);
			EXPECT_EQ_VAL(vec2.capacity(), 8);
		}

		//≤‚ ‘ capacity
		void test_capacity() {
			cout << "test: capacity()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };

			EXPECT_EQ_VAL(vec1.capacity(), 0);
			EXPECT_EQ_VAL(vec2.capacity(), 4);

			vec1 = { 1,2,3,4 };
			EXPECT_EQ_VAL(vec1.capacity(), 4);

			vec2 = { 1,2,3,4,5 };
			EXPECT_EQ_VAL(vec2.capacity(), 5);
		}

		//≤‚ ‘ clear
		void test_clear() {
			cout << "test: clear()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };

			vec1.clear();
			EXPECT_EQ_VAL(vec1.empty(), true);

			vec2.clear();
			EXPECT_EQ_VAL(vec2.empty(), true);
		}

		//≤‚ ‘ insert
		void test_insert() {
			cout << "test: insert()" << endl;

			vector<int> vec1{ 1,2,3,4 };
			vector<int> vec2 = vec1;

			vec1.insert(kkli::next(vec1.begin(), 2), 2, 1); //insert(pos, count, value)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,1,1,3,4 });

			vec1.insert(vec1.begin(), 4); //insert(pos, value)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 4,1,2,1,1,3,4 });

			vec1.insert(kkli::next(vec1.begin()), std::move(2)); //insert(pos, &&value)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 4,2,1,2,1,1,3,4 });

			vec1.insert_range(vec1.begin(), vec2.begin(), vec2.begin() + 2); //insert_range(pos, first, last)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,4,2,1,2,1,1,3,4 });

			vec1.insert(kkli::prev(vec1.end(), 2), { 1,2,3,4 }); //insert(pos, init)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,4,2,1,2,1,1,1,2,3,4,3,4 });
		}

		//≤‚ ‘ erase
		void test_erase() {
			cout << "test: erase()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4,5,6,7,8 };
			
			vec1.erase(vec1.begin(), vec1.end()); //erase(first, last)
			EXPECT_EQ_VAL(vec1.empty(), true);
			vec2.erase(vec2.begin(), kkli::next(vec2.begin(), 3));
			EXPECT_EQ_ITERLIST(vec2.begin(), vec2.end(), { 4,5,6,7,8 });

			vec2.erase(vec2.begin()); //erase(pos)
			EXPECT_EQ_ITERLIST(vec2.begin(), vec2.end(), { 5,6,7,8 });
		}

		//≤‚ ‘ push_back
		void test_push_back() {
			cout << "test: push_back()" << endl;

			vector<int> vec1;
			
			vec1.push_back(1); //push_back(value)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1 });

			vec1.push_back(std::move(2)); //push_back(&&value)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2 });
		}

		//≤‚ ‘ pop_back
		void test_pop_back() {
			cout << "test: pop_back()" << endl;

			vector<int> vec1{ 1,2 };

			vec1.pop_back();
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1 });
			vec1.pop_back();
			EXPECT_EQ_VAL(vec1.empty(), true);
		}

		//≤‚ ‘ resize
		void test_resize() {
			cout << "test: resize()" << endl;

			vector<int> vec1;

			vec1.resize(2, 1); //resize(count, value)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,1 });
			vec1.resize(1, 1);
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,1 });

			vec1.resize(4); //resize(count)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,1,0,0 });
			vec1.resize(2);
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,1,0,0 });
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			vector<int> vec3 = { 1,3,5,7 };
			
			vec1.swap(vec2); //lhs.swap(rhs)
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(vec2.empty(), true);
			vec1.swap(vec3);
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,3,5,7 });
			EXPECT_EQ_ITERLIST(vec3.begin(), vec3.end(), { 1,2,3,4 });

			swap(vec2, vec3); //swap(lhs, rhs)
			EXPECT_EQ_VAL(vec3.empty(), true);
			EXPECT_EQ_ITERLIST(vec2.begin(), vec2.end(), { 1,2,3,4 });
			swap(vec1, vec2);
			EXPECT_EQ_ITERLIST(vec1.begin(), vec1.end(), { 1,2,3,4 });
			EXPECT_EQ_ITERLIST(vec2.begin(), vec2.end(), { 1,3,5,7 });
		}

		//≤‚ ‘ operators(==/!=/<...)
		void test_operators() {
			vector<int> vec1;
			vector<int> vec2{ 1,2,3,4 };
			vector<int> vec3{ 1,2,3,4,5 };
			vector<int> vec4{ 1,3,5,7 };

			cout << "test: operator==" << endl;
			cout << "test: operator!=" << endl;
			EXPECT_EQ_VAL(vec1 == vec1, true);
			EXPECT_EQ_VAL(vec1 == vec2, false);
			EXPECT_EQ_VAL(vec1 == vec3, false);
			EXPECT_EQ_VAL(vec1 == vec4, false);
			EXPECT_EQ_VAL(vec2 == vec1, false);
			EXPECT_EQ_VAL(vec2 == vec2, true);
			EXPECT_EQ_VAL(vec2 == vec3, false);
			EXPECT_EQ_VAL(vec2 == vec4, false);
			EXPECT_EQ_VAL(vec3 == vec1, false);
			EXPECT_EQ_VAL(vec3 == vec2, false);
			EXPECT_EQ_VAL(vec3 == vec3, true);
			EXPECT_EQ_VAL(vec3 == vec4, false);
			EXPECT_EQ_VAL(vec4 == vec1, false);
			EXPECT_EQ_VAL(vec4 == vec2, false);
			EXPECT_EQ_VAL(vec4 == vec3, false);
			EXPECT_EQ_VAL(vec4 == vec4, true);

			cout << "test: operator<" << endl;
			cout << "test: operator>=" << endl;
			EXPECT_EQ_VAL(vec1 < vec1, false);
			EXPECT_EQ_VAL(vec1 < vec2, true);
			EXPECT_EQ_VAL(vec1 < vec3, true);
			EXPECT_EQ_VAL(vec1 < vec4, true);
			EXPECT_EQ_VAL(vec2 < vec1, false);
			EXPECT_EQ_VAL(vec2 < vec2, false);
			EXPECT_EQ_VAL(vec2 < vec3, true);
			EXPECT_EQ_VAL(vec2 < vec4, true);
			EXPECT_EQ_VAL(vec3 < vec1, false);
			EXPECT_EQ_VAL(vec3 < vec2, false);
			EXPECT_EQ_VAL(vec3 < vec3, false);
			EXPECT_EQ_VAL(vec3 < vec4, true);
			EXPECT_EQ_VAL(vec4 < vec1, false);
			EXPECT_EQ_VAL(vec4 < vec2, false);
			EXPECT_EQ_VAL(vec4 < vec3, false);
			EXPECT_EQ_VAL(vec4 < vec4, false);

			cout << "test: operator>" << endl;
			cout << "test: operator<=" << endl;
			EXPECT_EQ_VAL(vec1 > vec1, false);
			EXPECT_EQ_VAL(vec1 > vec2, false);
			EXPECT_EQ_VAL(vec1 > vec3, false);
			EXPECT_EQ_VAL(vec1 > vec4, false);
			EXPECT_EQ_VAL(vec2 > vec1, true);
			EXPECT_EQ_VAL(vec2 > vec2, false);
			EXPECT_EQ_VAL(vec2 > vec3, false);
			EXPECT_EQ_VAL(vec2 > vec4, false);
			EXPECT_EQ_VAL(vec3 > vec1, true);
			EXPECT_EQ_VAL(vec3 > vec2, true);
			EXPECT_EQ_VAL(vec3 > vec3, false);
			EXPECT_EQ_VAL(vec3 > vec4, false);
			EXPECT_EQ_VAL(vec4 > vec1, true);
			EXPECT_EQ_VAL(vec4 > vec2, true);
			EXPECT_EQ_VAL(vec4 > vec3, true);
			EXPECT_EQ_VAL(vec4 > vec4, false);
		}
	}
}
