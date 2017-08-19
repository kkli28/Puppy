#pragma once

#include "stdafx.h"
#include "test.h"
#include "vector.h"

namespace test {
	namespace vector_test {

		using std::cout;
		using std::endl;
		using kkli::vector;

		//前置声明
		void test_constructor();
		void test_destructor();
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
		void tset_capacity();
		void test_clear();
		void test_insert();
		void test_erase();
		void test_push_back();
		void test_pop_back();
		void test_resize();
		void test_swap();
		void test_operators();		//test: operator == / != ...

		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: vector.h " << endl;
			cout << "========================================" << endl;

			test_constructor();
			//test_destructor();
			//test_op_assign();
			//test_assign();
			//test_at();
			//test_op_square_bracket();
			//test_front_and_back();
			//test_data();
			//test_begin_and_end();
			//test_rbegin_and_rend();
			//test_empty();
			//test_size();
			//test_reserve();
			//tset_capacity();
			//test_clear();
			//test_insert();
			//test_erase();
			//test_push_back();
			//test_pop_back();
			//test_resize();
			//test_swap();
			//test_operators();
		}

		//测试 constructor
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
	}
}
