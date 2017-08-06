#pragma once

#include "stdafx.h"
#include "string.h"

//================================================================================
// EXPECT_EQ : 确保参数相等
//================================================================================

namespace test {

	//EXPECT_EQ_VAL: 比较值
	template<typename T, typename U>
	void EXPECT_EQ_VAL(const T& val1, const U& val2) {
		if (val1 != val2) throw std::runtime_error();
	}

	//EXPECT_EQ_ARR: 比较数组
	template<typename T,typename U>
	void EXPECT_EQ_ARR(const T& arr1, const U& arr2, std::size_t count) {
		for (int i = 0; i < count; ++i)
			if (arr1[i] != arr2[i]) throw std::runtime_error();
	}

	//EXPECT_EQ_NVALS: 比较数组中的N个值
	template<typename T,typename U>
	void EXPECT_EQ_NVALS(const T& arr, std::size_t count, const U& val) {
		for (int i = 0; i < count; ++i)
			if (arr[i] != val) throw std::runtime_error();
	}

	//
}