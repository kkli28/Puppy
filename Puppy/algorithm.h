#pragma once

#include "stdafx.h"

namespace kkli {

	//================================================================================
	//algorithm:	sort(first, last)
	//complexity:	O(nlogn)
	//aux_function:	__partition(first, last), __insertion_sort
	//================================================================================
	
	/*
	//__partition
	template<typename RandomAccessIterator>
	RandomAccessIterator __aux_partition(RandomAccessIterator first, RandomAccessIterator last) {
		return __aux_partition(first, last, [](const decltype(*first)& val1, const decltype(*first)& val2)-> bool {return val1 < val2; });
	}
	*/

	template<typename RandomAccessIterator, typename Compare>
	RandomAccessIterator __aux_partition(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<decltype(*first)>()) {
		//三数中值法：取首、中、尾三个值的中值作为守卫（标杆）
		std::size_t count = last - first;
		auto end = last - 1;

		auto mid_iter = first + count / 2;
		if (*first > *mid_iter) {		//最大值放中间
			auto temp = *first;
			*first = *mid_iter;
			*mid_iter = temp;
		}
		if (*end > *mid_iter) {
			auto temp = *mid_iter;
			*mid_iter = *end;
			*end = temp;
		}
		if (*first > *end) {			//中值放末尾
			auto temp = *first;
			*first = *end;
			*end = temp;
		}

		//将守卫定位
		auto iter = first - 1;
		auto prev_end = end - 1;
		auto guard = *end;
		for (auto i = first; i < prev_end; ++i) {
			if (comp(*i, guard)) {
				++iter;
				auto temp = *iter;
				*iter = *i;
				*i = temp;
			}
		}
		++iter;
		*end = *iter;
		*iter = guard;
		return iter;
	}

	/*
	//__insertion_sort
	template<typename BidirectionalIterator>
	void __aux_insertion_sort(BidirectionalIterator first, BidirectionalIterator last) {
		__aux_insertion_sort(first, last, [](BidirectionalIterator iter1, BidirectionalIterator iter2)->bool {return *iter1 < *iter2; });
	}
	*/

	template<typename BidirectionalIterator, typename Compare>
	void __aux_insertion_sort(BidirectionalIterator first, BidirectionalIterator last, 
		Compare comp = std::less<decltype(*first)>()) {
		if (first == last) return;
		auto index = first;
		++index;
		while (index != last) {
			auto iter = index;
			--iter;
			auto end_iter = first;
			--end_iter;
			auto value = *index;
			while (iter != end_iter) {
				if (!comp(*iter, value)) {
					auto next_iter = iter;
					++next_iter;
					*next_iter = *iter;
					--iter;
				}
				else break;
			}
			*(++iter) = value;
			++index;
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void sort(RandomAccessIterator first, RandomAccessIterator last, 
		Compare comp = std::less<decltype(*first)>()) {
		//元素少于20个，进行插入排序
		if (last - first < 20) {
			__aux_insertion_sort(first, last, comp);
		}
		else if (first < last) {
			auto iter = __aux_partition(first, last, comp);
			kkli::sort(first, iter, comp);
			kkli::sort(iter + 1, last, comp);
		}
	}
}