#pragma once

#include "stdafx.h"

namespace kkli {

	//================================================================================
	//algorithm:	sort(first, last)
	//complexity:	O(nlogn)
	//aux_function:	__partition(first, last), __insertion_sort
	//================================================================================
	
	//__partition
	template<typename RandomAccessIterator>
	RandomAccessIterator __aux_partition(RandomAccessIterator first, RandomAccessIterator last) {
		return first;
		//TODO: 
	}
	template<typename RandomAccessIterator, typename Compare>
	RandomAccessIterator __aux_partition(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp) {
		return first;
		//TODO: 
	}

	//__insertion_sort
	template<typename InputIterator>
	void __aux_insertion_sort(InputIterator first, InputIterator last) {
		//TODO: 
	}
	template<typename InputIterator, typename Compare>
	void __aux_insertion_sort(InputIterator first, InputIterator last, Compare comp) {
		//TODO: 
	}

	//sort
	template<typename RandomAccessIterator>
	void sort(RandomAccessIterator first, RandomAccessIterator last) {
		throw std::runtime_error("函数暂未实现!");

		//元素少于20个，则进行插入排序
		if (last - first < 20) {
			__aux_insertion_sort(first, last);
		}
		if (first < last) {
			auto iter = __partition(first, last);
			sort(first, iter);
			sort(iter + 1, last);
		}
	}
	template<typename RandomAccessIterator, typename Compare>
	void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		throw std::runtime_error("函数暂未实现!");

		//元素少于20个，则进行插入排序
		if (last - first < 20) {
			__aux_insertion_sort(first, last, comp);
		}
		if (first < last) {
			auto iter = __partition(first, last, comp);
			sort(first, iter);
			sort(iter + 1, last);
		}
	}
}