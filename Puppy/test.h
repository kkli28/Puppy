#pragma once

#include "stdafx.h"
#include "string.h"

namespace test {

	//EXPECT_EQ_VAL: 确保值相等
	template<typename T, typename U>
	void EXPECT_EQ_VAL(const T& val1, const U& val2) {
		if (!(val1 == val2)) throw std::runtime_error("EXPECT_EQ_VAL");

	}

	//EXPECT_EQ_ARR: 确保两个数组元素相等
	template<typename T,typename U>
	void EXPECT_EQ_ARR(const T& arr1, const U& arr2, std::size_t count) {
		for (int i = 0; i < count; ++i) 
			if (!(arr1[i] == arr2[i])) throw std::runtime_error("EXPECT_EQ_ARR");
	}

	//EXPECT_EQ_ARRLIST: 确保数组和列表内的所有元素相等
	template<typename T, typename Size>
	void EXPECT_EQ_ARRLIST(T* arr, Size count, std::initializer_list<T> il) {
		auto iter = il.begin();
		for (std::size_t i = 0; i < count; ++i, ++iter)
			if (!(arr[i] == *iter)) throw std::runtime_error("EXPECT_EQ_ARRLIST");
	}

	//EXPECT_EQ_NVALS: 确保数组中所有元素等于val
	template<typename T,typename U>
	void EXPECT_EQ_NVALS(const T& arr, std::size_t count, const U& val) {
		for (int i = 0; i < count; ++i)
			if (!(arr[i] == val)) throw std::runtime_error("EXPECT_EQ_NVALS");
	}

	//EXPECT_EQ_ITER: 确保迭代器范围内的所有元素相等
	template<typename InputIt>
	void EXPECT_EQ_ITER(InputIt first1, InputIt last1, InputIt first2, InputIt last2) {
		auto iter1 = first1;
		auto iter2 = first2;
		for (; iter1 != last1; ++iter1, ++iter2)
			if (!(*iter1 == *iter2)) throw std::runtime_error("EXPECT_EQ_ITER");
	}

	//EXPECT_EQ_ITERVAL: 确保迭代器范围内的所有元素等于val
	template<typename InputIt,typename V>
	void EXPECT_EQ_ITERVAL(InputIt first, InputIt last, const V& val) {
		for (auto iter=first; iter != last; ++iter)
			if (!(*iter == val)) throw std::runtime_error("EXPECT_EQ_ITER");
	}

	//EXPECT_EQ_ITERLIST: 确保迭代器范围内的元素与列表元素相等
	template<typename InputIt, typename T>
	void EXPECT_EQ_ITERLIST(InputIt first, InputIt last, std::initializer_list<T> init) {
		auto iter1 = first;
		auto iter2 = init.begin();
		for (; iter1 != last; ++iter1, ++iter2)
			if (!(*iter1 == *iter2)) throw std::runtime_error("EXPECT_EQ_ITERLIST");

	}

	//PRINT_ARR: 输出数组元素
	template<typename T, typename Size>
	void PRINT_ARR(T* arr, Size N) {
		for (int i = 0; i < N; ++i) cout << arr[i] << " "; cout << endl;
	}

	//PRINT_RANGE: 输出给定范围的值
	template<typename InputIt>
	void PRINT_RANGE(InputIt first, InputIt last) {
		for (auto iter = first; iter != last; ++iter) cout << *iter << " "; cout << endl;
	}
}