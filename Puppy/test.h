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
		for (int i = 0; i < count; ++i)
			if (arr[i] != val) throw std::runtime_error("EXPECT_EQ_NVALS");
	}

	//EXPECT_EQ_ITER: ȷ����������Χ�ڵ�����Ԫ�����
	template<typename InputIt>
	void EXPECT_EQ_ITER(InputIt first1, InputIt last1, InputIt first2, InputIt last2) {
		auto iter1 = first1;
		auto iter2 = first2;
		for (; iter1 != last1; ++iter1, ++iter2)
			if (*iter1 != *iter2) throw std::runtime_error("EXPECT_EQ_ITER");
	}

	//EXPECT_EQ_ITERVAL: ȷ����������Χ�ڵ�����Ԫ�ص���val
	template<typename InputIt,typename V>
	void EXPECT_EQ_ITERVAL(InputIt first, InputIt last, const V& val) {
		for (auto iter=first; iter != last; ++iter)
			if (*iter != val) throw std::runtime_error("EXPECT_EQ_ITER");
	}
}