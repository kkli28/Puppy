#pragma once

#include "stdafx.h"

namespace kkli {

	//================================================================================
	//algorithm:	sort(first, last)
	//complexity:	O(nlogn)
	//aux_function:	__partition(first, last), __insertion_sort
	//================================================================================
	
	//__aux_partition(first, last, comp)
	template<typename RandomAccessIterator, typename Compare>
	RandomAccessIterator __aux_partition(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<decltype(*first)>()) {
		//������ֵ����ȡ�ס��С�β����ֵ����ֵ��Ϊ��������ˣ�
		std::size_t count = last - first;
		auto end = last - 1;

		auto mid_iter = first + count / 2;
		if (*first > *mid_iter) {		//���ֵ���м�
			auto temp = *first;
			*first = *mid_iter;
			*mid_iter = temp;
		}
		if (*end > *mid_iter) {
			auto temp = *mid_iter;
			*mid_iter = *end;
			*end = temp;
		}
		if (*first > *end) {			//��ֵ��ĩβ
			auto temp = *first;
			*first = *end;
			*end = temp;
		}

		//��������λ
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

	//__aux_insertion_sort(first, last, comp)
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

	//sort(first, last, comp)
	template<typename RandomAccessIterator, typename Compare>
	void sort(RandomAccessIterator first, RandomAccessIterator last, 
		Compare comp = std::less<decltype(*first)>()) {
		//Ԫ������20�������в�������
		if (last - first < 20) {
			__aux_insertion_sort(first, last, comp);
		}
		else if (first < last) {
			auto iter = __aux_partition(first, last, comp);
			kkli::sort(first, iter, comp);
			kkli::sort(iter + 1, last, comp);
		}
	}


	//================================================================================
	//algorithm:	find(first, last, first, last)
	//complexity:	O(n*m)
	//aux_function:	__aux_partial_match_table(first, last)
	//================================================================================
	template<typename InputIterator>
	InputIterator find(InputIterator first1, InputIterator last1,
		InputIterator first2, InputIterator last2) {
		//д����ȥ�ˣ�����MMP
	}
}