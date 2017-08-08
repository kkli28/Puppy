#pragma once

#include "stdafx.h"
#include "utility.h"
#include "iterator_traits.h"
#include "functional.h"
#include "pair.h"

//================================================================================
//part1: non-modifying sequence operations
//================================================================================

namespace kkli {

	//======== [all_of], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	bool all_of(InputIt first, InputIt last, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (!pred(*first)) return false;
		return true;
	}

	//======== [any_of], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	bool any_of(InputIt first, InputIt last, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (pred(*first)) return true;
		return false;
	}

	//======== [none_of], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	bool none_of(InputIt first, InputIt last, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (pred(*first)) return false;
		return true;
	}

	//======== [for_each], O(n) ========
	template<typename InputIt, typename UnaryFunction>
	UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
		for (; first != last; ++first) f(*first);
		return std::move(f);
	}

	//======== [count], O(n) ========
	template<typename InputIt, typename T>
	typename iterator_traits<InputIt>::difference_type count(
		InputIt first, InputIt last, const T& value) {
		typename iterator_traits<InputIt>::difference_type cnt = 0;
		for (; first != last; ++first)
			if (kkli::equal_to(*first, value)) ++cnt;
		return cnt;
	}

	//======== [count_if], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	typename iterator_traits<InputIt>::difference_type count_if(
		InputIt first, InputIt last, UnaryPredicate pred) {
		typename iterator_trait<InputIt>::difference_type cnt = 0;
		for (; first != last; ++first)
			if (pred(*first)) ++cnt;
		return cnt;
	}

	//======== [mismatch], O(n) ========
	template<typename InputIt1, typename InputIt2>
	kkli::pair<InputIt1, InputIt2> mismatch(
		InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!kkli::equal_to(*first1, *first2)) break;
		}
		return kkli::make_pair<InputIt1, InputIt2>(first1, first2);
	}
	template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	kkli::pair<InputIt1, InputIt2> mismatch(
		InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2) {
			if (pred(*first1, *first2)) break;
		}
		return kkli::make_pair<InputIt1, InputIt2>(first1, first2);
	}
	template<typename InputIt1, typename InputIt2>
	kkli::pair<InputIt1, InputIt2> mismatch(
		InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		return mismatch(first1, last1, first2);
	}
	template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	kkli::pair<InputIt1, InputIt2> mismatch(
		InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
		BinaryPredicate pred) {
		return mismatch(first1, last1, first2, pred);
	}

	//======== [equal], O(n) ========
	template<typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2)
			if (!kkli::equal_to(*first1, *first2)) return false;
		return true;
	}
	template<typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		return equal(first1, last1, first2);
	}
	template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2)
			if (!kkli::equal_to(*first1, *fist2)) return false;
		return true;
	}
	template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
		BinaryPredicate pred) {
		return equal(first1, last1, first2, pred);
	}

	//======== [find], O(n) ========
	template<typename InputIt, typename T>
	InputIt find(InputIt first, InputIt last, const T& value) {
		for (; first != last; ++first)
			if (kkli::equal_to(*first, val)) break;
		return first;
	}

	//======== [find_if], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	InputIt find_if(InputIt first, InputIt last, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (pred(*first)) break;
		return first;
	}

	//======== [find_if_not], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (!pred(*first)) break;
		return first;
	}

	//======== [find_end], O(n*m) ========
	//可以使用KMP算法优化，但是暂时不想写，好麻烦
	template<typename ForwardIt1, typename ForwardIt2>
	ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
		ForwardIt2 s_first, ForwardIt2 s_last) {
		auto end = first;	//[first, end)用于与[s_first, s_last)比较
		for (auto iter = s_first; iter != s_last; ++iter, ++end);
		auto result = last;
		for (; end != last; ++first, ++end) {
			if (equal(first, end, s_first, s_last)) result = first;
		}
		return result;
	}
	template<typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
	ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
		ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate pred) {
		auto end = first;	//[first, end)用于与[s_first, s_last)比较
		for (auto iter = s_first; iter != s_last; ++iter, ++end);
		auto result = last;
		for (; end != last; ++first, ++end) {
			bool equal = true;
			auto iter1 = first;
			auto iter2 = s_first;
			while (iter1 != end) {
				if (!pred(*iter1, *iter2)) {
					equal = false;
					break;
				}
				++iter1;
				++iter2;
			}
			if (equal) result = first;
		}
		return result;
	}

	//======== [find_first_of], O(n*m) ========
	template<typename ForwardIt1, typename ForwardIt2>
	ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last,
		ForwardIt2 s_first, ForwardIt2 s_last) {
		for (; first != last; ++first) {
			for (auto iter = s_first; iter != s_last; ++iter)
				if (kkli::equal_to(*first, *iter)) return first;
		}
		return last;
	}
	template<typename ForwardIt1, typename ForwardIt2,typename BinaryPredicate>
	ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last,
		ForwardIt2 s_first, ForwardIt2 s_last,BinaryPredicate pred) {
		for (; first != last; ++first) {
			for (auto iter = s_first; iter != s_last; ++iter)
				if (pred(*first, *iter)) return first;
		}
		return last;
	}

	//======== [adjacent_find], O(n) ========
	template<typename ForwardIt>
	ForwardIt adjacent_find(ForwardIt first, ForwardIt last) {
		if (first == last)return first;
		auto iter = first;
		++iter;
		for (; iter != last; ++first, ++iter)
			if (kkli::equal_to(*first, *iter)) return first;
		return last;
	}
	template<typename ForwardIt,typename BinaryPredicate>
	ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate pred) {
		if (first == last)return first;
		auto iter = first;
		++iter;
		for (; iter != last; ++first, ++iter)
			if (pred(*first, *iter)) return first;
		return last;
	}

	//======== [search], O(n*m) ========
	template<typename ForwardIt1,typename ForwardIt2>
	ForwardIt1 search(ForwardIt1 first, ForwardIt2 last,
		ForwardIt2 s_first, ForwardIt2 s_last) {
		if (s_first == s_last) return first;
		auto end = first; //[first, end) vs [s_first, s_last)
		for (auto iter = s_first; iter != s_last; ++iter, ++end);
		for (; end != last; ++first,++end) {
			if (equal(first, end, s_first, s_last)) return first;
		}
		return last;
	}
	template<typename ForwardIt1, typename ForwardIt2,typename BinaryPredicate>
	ForwardIt1 search(ForwardIt1 first, ForwardIt2 last,
		ForwardIt2 s_first, ForwardIt2 s_last,BinaryPredicate pred) {
		if (s_first == s_last) return first;
		auto end = first; //[first, end) vs [s_first, s_last)
		for (auto iter = s_first; iter != s_last; ++iter, ++end);
		for (; end != last; ++first, ++end) {
			bool equal = true;
			auto iter1 = first;
			auto iter2 = s_first;
			while (iter1 != end) {
				if (!pred(*iter1, *iter2)) {
					equal = false;
					break;
				}
				++iter1;
				++iter2;
			}
			if (equal) return first;
		}
		return last;
	}

	//======== [search_n], O(n*m) ========
	template<typename ForwardIt,typename Size,typename T>
	ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value) {
		auto end = first;
		for (Size i = 0; i < count; ++i, ++end); //[first, end) vs [count values]
		for (; end != last; ++first, ++end) {
			bool equal = true;
			for (auto iter = first; iter != last; ++iter) {
				if (!kkli::equal_to(*iter, value)) {
					equal = false;
					break;
				}
			}
			if (equal) return first;
		}
		return last;
	}
	template<typename ForwardIt, typename Size, typename T,typename BinaryPredicate>
	ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value,
		BinaryPredicate pred) {
		auto end = first;
		for (Size i = 0; i < count; ++i, ++end); //[first, end) vs [count values]
		for (; end != last; ++first, ++end) {
			bool equal = true;
			for (auto iter = first; iter != last; ++iter) {
				if (!pred(*iter, value)) {
					equal = false;
					break;
				}
			}
			if (equal) return first;
		}
		return last;
	}
}


//注释格式需要更改
//================================================================================
//algorithm:	sort(first, last)
//complexity:	O(nlogn)
//aux_function:	__partition(first, last), __insertion_sort
//================================================================================

namespace kkli {

	//__aux_partition(first, last, comp)
	template<typename RandomAccessIterator, typename Compare>
	RandomAccessIterator __aux_partition(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<decltype(*first)>()) {
		//三数中值法
		auto end = last - 1;
		auto mid = first + (last - first) / 2;
		if (*first > *mid) kkli::swap(*first, *mid);
		if (*end > *mid) kkli::swap(*mid, *end);
		if (*first > *end) kkli::swap(*first, *end);

		//定位守卫
		auto iter = first - 1;
		auto prev_end = end - 1;
		auto guard = *end;
		for (auto i = first; i < prev_end; ++i) {
			if (comp(*i, guard)) kkli::swap(*i, *(++iter));
		}
		*end = *(++iter);
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
		//元素少于20个，进行插入排序
		if (last - first < 20) __aux_insertion_sort(first, last, comp);
		else if (first < last) {
			auto iter = __aux_partition(first, last, comp);
			kkli::sort(first, iter, comp);
			kkli::sort(iter + 1, last, comp);
		}
	}
}