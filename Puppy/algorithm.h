#pragma once

#include "stdafx.h"
#include "utility.h"
#include "iterator.h"
#include "functional.h"
#include "pair.h"

//算法根据 cppreference 的Algorithms Library板块的分类实现

//算法中有很多奇怪的代码，例如可以用operator==或者operator>直接解决，却
//坚持用类似(!operator<)来说实现，是为了减少类型需要满足的条件，即类型只需要
//定义了operator<就可以使用该算法。若使用operator==，而类型没有定义operator==，
//则类型不能使用该算法

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
		while (++first != last)
			if (!(*first == *dest)) *(++dest) = *first;
		return ++dest;
	}

	template<typename InputIt,typename OutputIt, typename BinaryPredicate>
	OutputIt unique_copy(InputIt first, InputIt last, OutputIt dest,
		BinaryPredicate pred) {
		if (first == last) return dest;
		*dest = *first;
		while (++first != last)
			if (!pred(*first, *dest)) *(++dest) = *first;
		return ++dest;
	}
}

//================================================================================
//part3: partitioning operations
//================================================================================

namespace kkli {

	//======== [is_partitioned], O(n) ========
	template<typename InputIt, typename UnaryPredicate>
	bool is_partitioned(InputIt first, InputIt last, UnaryPredicate pred) {
		for (; first != last; ++first) if (!pred(*first)) break;
		for (; first != last; ++first) if (pred(*first)) return false;
		return true;
	}

	//======== [partition], O(n) ========
	template<typename ForwardIt, typename UnaryPredicate>
	ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate pred) {
		first = kkli::find_if_not(first, last, pred);
		if (first == last) return first;
		for (ForwardIt iter = kkli::next(first); iter != last; ++iter)
			if (pred(*iter)) kkli::iter_swap(iter, first++);
		return first;
	}

	//======== [partition_copy], O(n) ========
	template<typename InputIt,typename OutputIt1,typename OutputIt2,
		typename UnaryPredicate>
		kkli::pair<OutputIt1, OutputIt2> partition_copy(InputIt first,
			InputIt last, OutputIt1 dest_true, OutputIt2 dest_false,
			UnaryPredicate pred) {
		while (first != last) {
			if (pred(*first)) {
				*dest_true = *first;
				++dest_true;
			}
			else {
				*dest_false = *first;
				++dest_false;
			}
			++first;
		}
		return kkli::pair<OutputIt1, OutputIt2>(dest_true, dest_false);
	}

	//======== [stable_partition], O(n) ======== 尚未实现
	template<typename BidirectIt, typename UnaryPredicate>
	BidirectIt stable_partition(BidirectIt first, BidirectIt last, UnaryPredicate pred) {
		throw 1; //TODO:
	}

	//======== [partition_point], O(n) ========
	template<typename ForwardIt, typename UnaryPredicate>
	ForwardIt partition_point(ForwardIt first, ForwardIt last,
		UnaryPredicate pred) {
		for (; first != last; ++first)
			if (!pred(*first)) return first;
	}
}

//================================================================================
//part4: sorting operations
//================================================================================

namespace kkli {

	//======== [is_sorted_until], O(n) ========
	template<typename ForwardIt>
	ForwardIt is_sorted_until(ForwardIt first, ForwardIt last) {
		if (first == last) return last;
		ForwardIt next = first;
		while (++next != last) {
			if (*next < *first) return next;
			++first;
		}
		return last;
	}

	template<typename ForwardIt, typename Compare>
	ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp) {
		if (first == last) return last;
		ForwardIt next = first;
		while (++next != last) {
			if (comp(*next, *first)) return next;
			++first;
		}
		return last;
	}

	//======== [is_sorted], O(n) ========
	template<typename ForwardIt>
	bool is_sorted(ForwardIt first, ForwardIt last) {
		return is_sorted_until(first, last) == last;
	}

	template<typename ForwardIt, typename Compare>
	bool is_sorted(ForwardIt first, ForwardIt last, Compare comp) {
		return is_sorted_until(first, last, comp) == last;
	}

	//======== [insertion_sort], O(n^2) ========
	template<typename BidirectIt,
		typename Compare = kkli::less<typename kkli::iterator_traits<BidirectIt>::value_type>>
		void insertion_sort(BidirectIt first, BidirectIt last,
			Compare comp = Compare()) {
		if (first == last) return;
		auto index = first;
		while (++index != last) {
			auto iter = kkli::prev(index);
			auto end_iter = kkli::prev(first);
			auto value = *index;
			while (iter != end_iter) {
				if (!comp(*iter, value)) {
					auto next_iter = kkli::next(iter);
					*next_iter = *iter;
					--iter;
				}
				else break;
			}
			*(++iter) = value;
		}
	}

	//======== [sort], O(nlogn) ========
	template<typename RandomAccessIt,
		typename Compare = kkli::less<typename kkli::iterator_traits<RandomAccessIt>::value_type>>
		RandomAccessIt __aux_partition(RandomAccessIt first, RandomAccessIt last,
			Compare comp = Compare()) {
		//三数中值法
		auto end = last - 1;
		auto mid = first + (last - first) / 2;
		if (*first > *mid) kkli::swap(*first, *mid);
		if (*end > *mid) kkli::swap(*mid, *end);
		if (*first > *end) kkli::swap(*first, *end);

		//定位守卫
		auto iter = first - 1;
		auto guard = *end;
		for (auto i = first; i < end; ++i)
			if (comp(*i, guard)) kkli::swap(*i, *(++iter));
		*end = *(++iter);
		*iter = guard;
		return iter;
	}

	template<typename RandomAccessIt,
		typename Compare = kkli::less<typename kkli::iterator_traits<RandomAccessIt>::value_type>>
		void sort(RandomAccessIt first, RandomAccessIt last,
			Compare comp = Compare()) {
		if (last - first < 32) insertion_sort(first, last, comp);
		else if (first < last) {
			auto iter = __aux_partition(first, last, comp);
			kkli::sort(first, iter, comp);
			kkli::sort(iter + 1, last, comp);
		}
	}

	//======== [partial_sort], O(nlogn) ======= 尚未实现
	template<typename RandomAccessIt, typename Compare>
	void partial_sort(RandomAccessIt first, RandomAccessIt middle,
		RandomAccessIt last, Compare comp) {
		throw 1; //TODO:
	}

	//======== [partial_sort_copy], O(X) ======== 尚未实现
	template<typename InputIt, typename RandomAccessIt, typename Compare>
	RandomAccessIt partial_sort_copy(InputIt first, InputIt last, RandomAccessIt dest,
		Compare comp = kkli::less<typename kkli::iterator_traits<InputIt>::value_type>()) {
		throw 1; //TODO:
	}

	//======== [stable_sort], O(X) ======== 尚未实现
	template<typename RandomAccessIt, typename Compare>
	void stable_sort(RandomAccessIt first, RandomAccessIt last,
		Compare comp = kkli::less<typename kkli::iterator_traits<RandomAccessIt>::value_type>()) {
		throw 1; //TODO:
	}

	//======== [nth_element], O(nlogn) ======== 尚未实现
	template<typename RandomAccessIt, typename Compare>
	void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last,
		Compare comp = kkli::less<typename kkli::iterator_traits<RandomAccessIt>::value_type>()) {
		throw 1; //TODO: 
	}
}

//================================================================================
//part5: binary search operations(on sorted ranges)
//================================================================================

namespace kkli {

	//======== [lower_bound], O(logn) ========
	template<typename ForwardIt, typename T>
	ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value) {
		typename kkli::iterator_traits<ForwardIt>::difference_type count, step;
		count = kkli::distance(first, last);
		ForwardIt iter;
		while (count > 0) {
			iter = first;
			step = count / 2;
			kkli::advance(iter, step);
			if (*iter < value) {
				first = ++iter;
				count -= step + 1;
			}
			else count = step;
		}
		return first;
	}

	template<typename ForwardIt, typename T, typename Compare>
	ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value,
		Compare comp) {
		typename kkli::iterator_traits<ForwardIt>::difference_type count, step;
		count = kkli::distance(first, last);
		ForwardIt iter;
		while (count > 0) {
			iter = first;
			step = count / 2;
			kkli::advance(iter, step);
			if (comp(*iter,value)) {
				first = ++iter;
				count -= step + 1;
			}
			else count = step;
		}
		return first;
	}

	//======== [upper_bound], O(logn) ========
	template<typename ForwardIt, typename T>
	ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value) {
		typename kkli::iterator_traits<ForwardIt>::difference_type count, step;
		count = kkli::distance(first, last);
		ForwardIt iter;
		while (count > 0) {
			iter = first;
			step = count / 2;
			kkli::advance(iter, step);
			if (!(value < *iter)) {
				first = ++iter;
				count -= step + 1;
			}
			else count = step;
		}
		return first;
	}

	template<typename ForwardIt, typename T, typename Compare>
	ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value,
		Compare comp) {
		typename kkli::iterator_traits<ForwardIt>::difference_type count, step;
		count = kkli::distance(first, last);
		ForwardIt iter;
		while (count > 0) {
			iter = first;
			step = count / 2;
			kkli::advance(iter, step);
			if (!comp(value, *iter)) {
				first = ++iter;
				count -= step + 1;
			}
			else count = step;
		}
		return first;
	}

	//======== [binary_search], O(logn) ========
	template<typename ForwardIt, typename T>
	bool binary_search(ForwardIt first, ForwardIt last, const T& value) {
		first = kkli::lower_bound(first, last, value);
		return (!(first == last)) && (!(value < *first));
	}

	template<typename ForwardIt, typename T,typename Compare>
	bool binary_search(ForwardIt first, ForwardIt last, const T& value,
		Compare comp) {
		first = kkli::lower_bound(first, last, value, comp);
		return (!(first == last)) && (!comp(value, *first));
	}

	//======== [equal_range], O(logn) ========
	template<typename ForwardIt, typename T>
	kkli::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first,
		ForwardIt last, const T& value) {
		return kkli::make_pair(
			kkli::lower_bound(first, last, value),
			kkli::upper_bound(first, last, value));
	}

	template<typename ForwardIt, typename T, typename Compare>
	kkli::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first,
		ForwardIt last, const T& value, Compare comp) {
		return kkli::make_pair(
			kkli::lower_bound(first, last, value, comp),
			kkli::upper_bound(first, last, value, comp));
	}
}

//================================================================================
//part6: set operations(on sorted ranges)
//================================================================================

namespace kkli {

	//======== [merge], O(n) ========
	template<typename InputIt1, typename InputIt2, typename OutputIt>
	OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2,
		InputIt2 last2, OutputIt dest) {
		while ((first1 != last1) && (first2 != last2)) {
			if (*first1 < *first2) *(dest++) = *(first1++);
			else *(dest++) = *(first2++);
		}
		while (first1 != last1) return kkli::copy(first1, last1, dest);
		while (first2 != last2) return kkli::copy(first2, last2, dest);
	}

	template<typename InputIt1, typename InputIt2, typename OutputIt,
		typename Compare>
		OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2,
			InputIt2 last2, OutputIt dest, Compare comp) {
		while ((first1 != last1) && (first2 != last2)) {
			if (comp(*first1, *first2)) *(dest++) = *(first1++);
			else *(dest++) = *(first2++);
		}
		while (first1 != last1) return kkli::copy(first1, last1, dest);
		while (first2 != last2) return kkli::copy(first2, last2, dest);
	}

	//======== [inplace_merge], O(n) ======== 尚未实现

	//======== [includes], O(n) ========
	template<typename InputIt1, typename InputIt2>
	bool include(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		while (first2 != last2) {
			if (first1 == last1 || *first2 < *first1) return false;
			if (!(*first1 < *first2)) ++first2; //means *first1==*first2
			++first1;
		}
		return true;
	}

	template<typename InputIt1, typename InputIt2, typename Compare>
	bool include(InputIt1 first1, InputIt1 last1, InputIt2 first2,
		InputIt2 last2, Compare comp) {
		while (first2 != last2) {
			if (first1 == last1 || comp(*first2, *first1)) return false;
			if (!comp(*first1, *first2)) ++first2; //means *first1==*first2
			++first1;
		}
		return true;
	}

	//======== [set_difference], O(n) ========
	template<typename InputIt1, typename InputIt2, typename OutputIt>
	OutputIt set_difference(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2, OutputIt dest) {
		while (first1 != last1) {
			if (first2 == last2) return kkli::copy(first1, last1, dest);
			if (*first1 < *first2) *(dest++) = *(first1++);
			else {
				if (!(*first2 < *first1)) ++first1; //means *first1 == *first2
				++first2;
			}
		}
		return dest;
	}

	template<typename InputIt1, typename InputIt2, typename OutputIt,
		typename Compare>
		OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
			InputIt2 last2, OutputIt dest, Compare comp) {
		while (first1 != last1) {
			if (first2 == last2) return kkli::copy(first1, last1, dest);
			if (comp(*first1, *first2)) *(dest++) = *(first1++);
			else {
				if (!comp(*first2, *first1)) ++first1; //means *first1 == *first2
				++first2;
			}
		}
		return dest;
	}

	//======== [set_intersection], O(n) ========
	template<typename InputIt1, typename InputIt2, typename OutputIt>
	OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2,
		InputIt2 last2, OutputIt dest) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) ++first1;
			else {
				if (!(*first2 < *first1)) *(dest++) = *(first1++);
				++first2;
			}
		}
		return dest;
	}

	template<typename InputIt1, typename InputIt2, typename OutputIt,
		typename Compare>
		OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2,
			InputIt2 last2, OutputIt dest, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) ++first1;
			else {
				if (!comp(*first2, *first1)) *(dest++) = *(first1++);
				++first2;
			}
		}
		return dest;
	}

	//======== [set_symmetric_difference], O(n) ========
	template<typename InputIt1, typename InputIt2, typename OutputIt>
	OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2, OutputIt dest) {
		while (first1 != last1) {
			if (first2 == last2) return kkli::copy(first1, last1, dest);
			if (*first1 < *first2) *(dest++) = *(first1++);
			else {
				if (*first2 < *first1) *(dest++) = *first2;
				else ++first1; //*first1==*first2
				++first2;
			}
		}
		return kkli::copy(first2, last2, dest);
	}

	template<typename InputIt1, typename InputIt2, typename OutputIt,
		typename Compare>
		OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2, OutputIt dest, Compare comp) {
		while (first1 != last1) {
			if (first2 == last2) return kkli::copy(first1, last1, dest);
			if (comp(*first1, *first2)) *(dest++) = *(first1++);
			else {
				if (comp(*first2, *first1)) *(dest++) = *first2;
				else ++first1; //*first1==*first2
				++first2;
			}
		}
		return kkli::copy(first2, last2, dest);
	}

	//======== [set_union], O(n) ========
	template<typename InputIt1, typename InputIt2, typename OutputIt>
	OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2,
		InputIt2 last2, OutputIt dest) {
		while (first1 != last1) {
			if (first2 == last2) return kkli::copy(first1, last1, dest);
			if (*first2 < *first1) *(dest++) = *(first2++);
			else {
				*(dest++) = *first1;
				if (!(*first1 < *first2)) ++first2;
				++first1;
			}
		}
		return kkli::copy(first2, last2, dest);
	}

	template<typename InputIt1, typename InputIt2, typename OutputIt,
		typename Compare>
		OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2,
			InputIt2 last2, OutputIt dest, Compare comp) {
		while (first1 != last1) {
			if (first2 == last2) return kkli::copy(first1, last1, dest);
			if (comp(*first2, *first1)) *(dest++) = *(first2++);
			else {
				*(dest++) = *first1;
				if (!comp(*first1, *first2)) ++first2;
				++first1;
			}
		}
		return kkli::copy(first2, last2, dest);
	}
}
