#pragma once

#include "stdafx.h"
#include "string.h"

namespace test {

	//EXPECT_EQ_VAL: ȷ��ֵ���
	template<typename T, typename U>
	void EXPECT_EQ_VAL(const T& val1, const U& val2) {
		if (val1 != val2) throw std::runtime_error("EXPECT_EQ_VAL");
	}

	//EXPECT_EQ_ARR: ȷ����������Ԫ�����
	template<typename T,typename U>
	void EXPECT_EQ_ARR(const T& arr1, const U& arr2, std::size_t count) {
		for (int i = 0; i < count; ++i)
			if (arr1[i] != arr2[i]) throw std::runtime_error("EXPECT_EQ_ARR");
	}

	//EXPECT_EQ_NVALS: ȷ������������Ԫ�ص���val
	template<typename T,typename U>
	void EXPECT_EQ_NVALS(const T& arr, std::size_t count, const U& val) {
		
		//log
		std::cout << "arr[0]: " << arr[0] << "    val: " << val << std::endl;

		for (int i = 0; i < count; ++i)
			if (arr[i] != val) throw std::runtime_error("EXPECT_EQ_NVALS");
	}

	//
}