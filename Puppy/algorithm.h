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
			if (kkli::equal_to<typename iterator_traits<InputIt>::value_type>()(*first, value)) ++cnt;
		return cnt;
	}

	//======== [count_if], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	typename iterator_traits<InputIt>::difference_type count_if(
		InputIt first, InputIt last, UnaryPredicate pred) {
		typename iterator_traits<InputIt>::difference_type cnt = 0;
		for (; first != last; ++first)
			if (pred(*first)) ++cnt;
		return cnt;
	}

	//======== [mismatch], O(n) ========
	template<typename InputIt1, typename InputIt2>
	kkli::pair<InputIt1, InputIt2> mismatch(
		InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!kkli::equal_to<typename iterator_traits<InputIt1>::value_type>()(*first1, *first2)) break;
		}
		return kkli::make_pair<InputIt1, InputIt2>(std::move(first1), std::move(first2));
	}
	
	template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	kkli::pair<InputIt1, InputIt2> mismatch(
		InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2) {
			if (pred(*first1, *first2)) break;
		}
		return kkli::make_pair<InputIt1, InputIt2>(std::move(first1), std::move(first2));
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
			if (!kkli::equal_to<typename iterator_traits<InputIt1>::value_type>()(*first1, *first2)) return false;
		return true;
	}
	
	template<typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		return equal(first1, last1, first2);
	}
	
	template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2)
			if (!pred(*first1, *first2)) return false;
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
			if (kkli::equal_to<typename iterator_traits<InputIt>::value_type>()(*first, value)) break;
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
		if (first == last) return first;
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
		if (first == last) return first;
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
	template<typename InputIt, typename ForwardIt>
	InputIt find_first_of(InputIt first, InputIt last,
		ForwardIt s_first, ForwardIt s_last) {
		for (; first != last; ++first) {
			for (auto iter = s_first; iter != s_last; ++iter)
				if (kkli::equal_to<typename iterator_traits<InputIt>::value_type>()(*first, *iter)) return first;
		}
		return last;
	}
	
	template<typename InputIt, typename ForwardIt,typename BinaryPredicate>
	InputIt find_first_of(InputIt first, InputIt last,
		ForwardIt s_first, ForwardIt s_last,BinaryPredicate pred) {
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
			if (kkli::equal_to<typename iterator_traits<ForwardIt>::value_type>()(*first, *iter)) return first;
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
		auto result = last;
		auto end = first;	//[first, end) vs [s_first, s_last)
		for (auto iter = s_first; iter != s_last; ++iter, ++end);

		++last;	//当end==last时，[first, end)是合法范围，但是下方循环会退出，因此将last后移
		for (; end != last; ++first,++end) {
			if (equal(first, end, s_first, s_last)) {
				result = first;
				break;
			}
		}
		return result;
	}
	template<typename ForwardIt1, typename ForwardIt2,typename BinaryPredicate>
	ForwardIt1 search(ForwardIt1 first, ForwardIt2 last,
		ForwardIt2 s_first, ForwardIt2 s_last,BinaryPredicate pred) {
		if (s_first == s_last) return first;
		auto result = last;
		auto end = first; //[first, end) vs [s_first, s_last)
		for (auto iter = s_first; iter != s_last; ++iter, ++end);

		++last;		//见上方
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
			if (equal) {
				result = first;
				break;
			}
		}
		return result;
	}

	//======== [search_n], O(n*m) ========
	template<typename ForwardIt,typename Size,typename T>
	ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value) {
		if (first == last) return last;
		auto end = first;
		for (Size i = 0; i < count; ++i, ++end); //[first, end) vs [count values]

		auto old_last = last;
		++last;
		for (; end != last; ++first, ++end) {
			bool equal = true;
			for (auto iter = first; iter != end; ++iter) {
				if (!kkli::equal_to<typename iterator_traits<ForwardIt>::value_type>()(*iter, value)) {
					equal = false;
					break;
				}
			}
			if (equal) return first;
		}
		return old_last;
	}
	
	template<typename ForwardIt, typename Size, typename T,typename BinaryPredicate>
	ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value,
		BinaryPredicate pred) {
		if (first == last) return last;
		auto end = first;
		for (Size i = 0; i < count; ++i, ++end); //[first, end) vs [count values]

		auto old_last = last;
		++last;
		for (; end != last; ++first, ++end) {
			bool equal = true;
			for (auto iter = first; iter != end; ++iter) {
				if (!pred(*iter, value)) {
					equal = false;
					break;
				}
			}
			if (equal) return first;
		}
		return old_last;
	}
}

//================================================================================
//part2: modifying sequence operations
//================================================================================

namespace kkli {

	//======== [copy], O(n) ========
	template<typename InputIt, typename OutputIt>
	OutputIt copy(InputIt first, InputIt last, OutputIt dest) {
		for (; first != last; ++first, ++dest) *dest = *first;
		return dest;
	}

	//======== [copy_if], O(n) ========
	template<typename InputIt, typename OutputIt, typename UnaryPredicate >
	OutputIt copy_if(InputIt first, InputIt last, OutputIt dest, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (pred(*first)) {
				*dest = *first;
				++dest;
			}
		return dest;
	}

	//======== [copy_n], O(n) ========
	template<typename InputIt,typename Size, typename OutputIt>
	OutputIt copy_n(InputIt first, Size count, OutputIt dest) {
		for (; count > 0; --count, ++first, ++dest) *dest = *first;
		return dest;
	}

	//======== [copy_backward], O(n) ========
	template<typename BidirectIt1,typename BidirectIt2>
	BidirectIt2 copy_backward(BidirectIt1 first, BidirectIt1 last, BidirectIt2 dest) {
		while (first != last) *(--dest) = *(--last);
		return dest;
	}

	//======== [move], O(n) ========
	template<typename InputIt, typename OutputIt>
	OutputIt move(InputIt first, InputIt last, OutputIt dest) {
		for (; first != last; ++first, ++dest) *dest = std::move(*first);
		return dest;
	}

	//======== [move_backward], O(n) ========
	template<typename BidirectIt1,typename BidirectIt2>
	BidirectIt2 move_backward(BidirectIt1 first, BidirectIt1 last, BidirectIt2 dest) {
		while (first != last) *(--dest) = std::move(*(--last));
		return dest;
	}

	//======== [fill], O(n) ========
	template<typename ForwardIt,typename T>
	void fill(ForwardIt first, ForwardIt last, const T& value) {
		for (; first != last; ++first) *first = value;
	}

	//======== [fill_n], O(n) ========
	template<typename OutputIt,typename Size,typename T>
	void fill_n(OutputIt first, Size count, const T& value) {
		for (; count > 0; --count, ++first) *first = value;
	}

	//======== [transform], O(n) ========
	template<typename InputIt, typename OutputIt, typename UnaryOperation>
	OutputIt transform(InputIt first, InputIt last, OutputIt dest, UnaryOperation unary_op) {
		for (; first != last; ++first, ++dest) *dest = unary_op(*first);
		return dest;
	}

	//======== [generate], O(n) ========
	template<typename ForwardIt, typename Generate>
	void generate(ForwardIt first, ForwardIt last, Generate g) {
		for (; first != last; ++first) *first = g();
	}

	//======== [generate_n], O(n) ========
	template<typename ForwardIt, typename Size, typename Generator>
	ForwardIt generate_n(ForwardIt first, Size count, Generator g) {
		for (; count > 0; --count, ++first) *first = g();
		return first;
	}

	//======== [remove], O(n) ========
	template<typename ForwardIt,typename T>
	ForwardIt remove(ForwardIt first, ForwardIt last, const T& value) {
		first = kkli::find(first, last, value);
		if (first != last) {
			for (auto iter = first; ++iter != last;)
				if (!(*iter == value)) *(first++) = std::move(*iter);
		}
		return first;
	}

	//======== [remove_if], O(n) ========
	template<typename ForwardIt, typename UnaryPredicate>
	ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate pred) {
		first = kkli::find_if(first, last, pred);
		if (first != last) {
			for (auto iter = first; ++iter != last;)
				if (!pred(*iter)) *(first++) = std::move(*iter);
		}
		return first;
	}

	//======== [remove_copy], O(n) ========
	template<typename InputIt, typename OutputIt, typename T>
	OutputIt remove_copy(InputIt first, InputIt last, OutputIt dest, const T& value) {
		for (; first != last; ++first)
			if (!(*first == value)) *(dest++) = *first;
		return dest;
	}

	//======== [remove_copy_if], O(n) ========
	template<typename InputIt,typename OutputIt,typename UnaryPredicate>
	OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt dest, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (!pred(*first)) *(dest++) = *first;
		return dest;
	}

	//======== [replace], O(n) ========
	template<typename ForwardIt, typename T>
	void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value) {
		for (; first != last; ++first)
			if (*first == old_value) *first = new_value;
	}

	//======== [replace_if], O(n) ========
	template<typename ForwardIt, typename UnaryPredicate, typename T>
	void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate pred, const T& new_value) {
		for (; first != last; ++first)
			if (pred(*first)) *first = new_value;
	}

	//======== [replace_copy], O(n) ========
	template<typename InputIt, typename OutputIt, typename T>
	OutputIt replace_copy(InputIt first, InputIt last, OutputIt dest,
		const T& old_value, const T& new_value) {
		for (; first != last; ++first)
			*(dest++) = (*first == old_value) ? new_value : *first;
		return dest;
	}

	//======== [replace_copy_if], O(n) ========
	template<typename InputIt,typename OutputIt, typename UnaryPredicate, typename T>
	OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt dest,
		UnaryPredicate pred, const T& new_value) {
		for (; first != last; ++first)
			*(dest++) = pred(*first) ? new_value : *first;
		return dest;
	}

	//======== [swap], O(1) =======
	template<typename T>
	void swap(T& a, T& b) {
		auto temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	}

	//======== [swap(array)], O(n) ========
	template<typename T,std::size_t N>
	void swap(T(&a)[N], T(&b)[N]) {
		for (std::size_t i = 0; i < N; ++i)
			kkli::swap(a[i], b[i]);
	}

	//======== [swap_ranges], O(n) ========
	template<typename ForwardIt1, typename ForwardIt2>
	ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) {
		for (; first1 != last1; ++first1, ++first2)
			kkli::swap(*first1, *first2);
		return first2;
	}

	//======== [iter_swap], O(n) ========
	template<typename ForwardIt1, typename ForwardIt2>
	void iter_swap(ForwardIt1 a, ForwardIt2 b) {
		kkli::swap(*a, *b);
	}

	//======== [reverse], O(n) ========
	template<typename BidirectIt>
	void reverse(BidirectIt first, BidirectIt last) {
		while (first != last && first != (--last))
			kkli::iter_swap(first++, last);
	}

	//======== [reverse_copy], O(n) ========
	template<typename BidirectIt, typename OutputIt>
	OutputIt reverse_copy(BidirectIt first, BidirectIt last, OutputIt dest) {
		while (first != last) *(dest++) = *(--last);
		return dest;
	}

	//======== [rotate], O(n) ========
	template<typename ForwardIt>
	ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
		if (first == n_first) return last;
		if (n_first == last) return first;
		ForwardIt next = n_first;
		while(true) {
			kkli::iter_swap(first++, next++);
			if (first == n_first) n_first = next;
			if (next == last) break;
		}
		ForwardIt ret = first;
		next = n_first;
		while (next != last) {
			kkli::iter_swap(first++, next++);
			if (first == n_first) n_first = next;
			else if (next == last) next = n_first;
		}
		return ret;
	}

	//======== [rotate_copy], O(n) ========
	template<typename ForwardIt, typename OutputIt>
	OutputIt rotate_copy(ForwardIt first, ForwardIt n_first,
		ForwardIt last, OutputIt dest) {
		dest = kkli::copy(n_first, last, dest);
		return copy(first, n_first, dest);
	}

	//======== [unique], O(n) ========
	template<typename ForwardIt>
	ForwardIt unique(ForwardIt first, ForwardIt last) {
		if (first == last) return last;
		ForwardIt result = first;
		while (++first != last) {
			if ((!(*result == *first)) && ++result != first) *result = std::move(*first);
		}
		return ++result;
	}

	//======== [unique_copy], O(n) ========
	template<typename InputIt, typename OutputIt>
	OutputIt unique_copy(InputIt first, InputIt last, OutputIt dest) {
		if (first == last) return dest;
		*dest = *first;
		while (++first != last) {
			if (!(*dest == *first)) *dest = *first;
			++dest;
		}
		return dest;
	}

	//======== [unique_copy], O(n) ========
	template<typename InputIt,typename OutputIt, typename BinaryPredicate>
	OutputIt unique_copy(InputIt first, InputIt last, OutputIt dest,
		BinaryPredicate pred) {
		if (first == last) return dest;
		*dest = *first;
		while (++first != last) {
			if (!pred(*first,*dest)) *dest = *first;
		}
		return dest;
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