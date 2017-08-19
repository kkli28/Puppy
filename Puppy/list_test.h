#pragma once

#include "stdafx.h"
#include "test.h"
#include "list.h"

namespace test {
	namespace list_test {

		using std::cout;
		using std::endl;
		using kkli::list;

		//∫Ø ˝…˘√˜
		void test_iterator();
		void test_constructor();
		void test_op_assign();			//operator =
		void test_assign();
		void test_front_and_back();
		void test_begin_and_end();
		void test_rbegin_and_rend();
		void test_empty();
		void test_size();
		void test_clear();
		void test_insert();
		void test_erase();
		void test_push_back();
		void test_pop_back();
		void test_push_front();
		void test_pop_front();
		void test_resize();
		void test_swap();
		void test_merge();
		void test_splice();
		void test_remove();
		void test_reverse();
		void test_unique();
		void test_sort();
		void test_operators();		//operator == / != / < / <= / > / >=

		//’˚ÃÂ≤‚ ‘
		void test() {
			cout << "\n========================================" << endl;
			cout << "            list.h " << endl;
			cout << "========================================" << endl;

			test_iterator();
			test_constructor();
			test_op_assign();
			test_assign();
			test_front_and_back();
			test_begin_and_end();
			test_rbegin_and_rend();
			test_empty();
			test_size();
			test_clear();
			test_insert();
			test_erase();
			test_push_back();
			test_pop_back();
			test_push_front();
			test_pop_front();
			test_resize();
			test_swap();
			test_merge();
			test_splice();
			test_remove();
			test_reverse();
			test_unique();
			test_sort();
			test_operators();
		}

		//≤‚ ‘ iterator
		void test_iterator() {
			cout << "test: iterator()" << endl;

			//constructors
			list<int>::iterator iter1; //iterator()
			EXPECT_EQ_VAL(iter1.get(), nullptr); //get()

			list<int>::iterator iter2(new kkli::list_node<int>(1)); //iterator(ptr)
			EXPECT_EQ_VAL(*iter2, 1); //operator *

			list<int>::iterator iter3(1); //iterator(value)
			EXPECT_EQ_VAL(*iter3, 1);

			list<int>::iterator iter4(std::move(2)); //iterator(&&value)
			EXPECT_EQ_VAL(*iter4, 2);

			iter1 = iter2; //operator =
			EXPECT_EQ_VAL(*iter1, 1); //iterator(rhs)

			//operator ++
			list<int>::iterator iter5(1);
			iter5->next = new kkli::list_node<int>(2); //operator ->
			list<int>::iterator iter6 = iter5;
			++iter6;
			iter6->prev = iter5.get();
			EXPECT_EQ_VAL(*iter6, 2);

			//operator ++(int)
			EXPECT_EQ_VAL(*(iter6++), 2);
			EXPECT_EQ_VAL(iter6.get(), nullptr);

			//operator --
			iter6 = kkli::next(iter5);
			--iter6;
			EXPECT_EQ_VAL(*iter6, 1);

			//operator --(int)
			EXPECT_EQ_VAL(*(iter6--), 1);
			EXPECT_EQ_VAL(iter6.get(), nullptr);

			//operator ==
			iter6 = iter5;
			EXPECT_EQ_VAL(iter6 == iter5, true);
			++iter6;
			EXPECT_EQ_VAL(iter6 == iter5, false);
		}

		//≤‚ ‘ constructor
		void test_constructor() {
			cout << "test: constructor()" << endl;

			list<int> lst1; //list()
			EXPECT_EQ_VAL(lst1.empty(), true);

			list<int> lst2(4, 1); //list(count, value)
			EXPECT_EQ_ITERVAL(lst2.begin(), lst2.end(), 1);

			list<int> lst3(4); //list(count)
			EXPECT_EQ_ITERVAL(lst3.begin(), lst3.end(), 0);

			list<int> lst4(lst2); //list(rhs)
			EXPECT_EQ_ITERVAL(lst4.begin(), lst4.end(), 1);

			list<int> lst5(std::move(lst3)); //list(&&rhs)
			EXPECT_EQ_ITERVAL(lst5.begin(), lst5.end(), 0);

			list<int> lst6{ 1,2,3,4 };
			EXPECT_EQ_ITERLIST(lst6.begin(), lst6.end(), { 1,2,3,4 });
		}

		//≤‚ ‘ operator=
		void test_op_assign() {
			cout << "test: operator=" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			list<int> lst3{ 5,6,7,8 };
			list<int> lst4;

			lst1 = lst2; //operator(rhs)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
			
			lst1 = lst4;
			EXPECT_EQ_VAL(lst1.empty(), true);

			lst1 = std::move(lst3); //operator(&&rhs)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 5,6,7,8 });

			lst1 = std::move(lst4);
			EXPECT_EQ_VAL(lst1.empty(), true);
		}

		//≤‚ ‘ assign
		void test_assign() {
			cout << "test: assign()" << endl;

			list<int> lst1;

			lst1.assign(4, 1); //assign(count, value)
			EXPECT_EQ_ITERVAL(lst1.begin(), lst1.end(), 1);

			lst1.assign({ 1,2,3,4 }); //assign(init)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
		}

		//≤‚ ‘ front ∫Õ back
		void test_front_and_back() {
			cout << "test: front()" << endl;
			cout << "test: back()" << endl;

			list<int> lst1{ 1,2,3,4 };
			const list<int> lst2{ 1,2,3,4 };

			EXPECT_EQ_VAL(lst1.front(), 1); //front
			EXPECT_EQ_VAL(lst2.front(), 1);
			
			EXPECT_EQ_VAL(lst1.back(), 4); //back
			EXPECT_EQ_VAL(lst2.back(), 4);
		}

		//≤‚ ‘ begin & end & cbegin & cend
		void test_begin_and_end() {
			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			const list<int> lst3{ 5,6,7,8 };

			cout << "test: begin()" << endl;
			cout << "test: end()" << endl;
			EXPECT_EQ_VAL(lst1.begin(), lst1.end());
			EXPECT_EQ_VAL(*(lst2.begin()), 1);
			EXPECT_EQ_VAL(*(kkli::prev(lst2.end())), 4);

			cout << "test: cbegin()" << endl;
			cout << "test: cend()" << endl;
			EXPECT_EQ_VAL(*(lst3.cbegin()), 5);
			EXPECT_EQ_VAL(*(kkli::prev(lst3.cend())), 8);
		}

		//≤‚ ‘ rbegin & rend & crbegin & crend
		void test_rbegin_and_rend() {
			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			const list<int> lst3{ 5,6,7,8 };

			cout << "test: rbegin()" << endl;
			cout << "test: rend()" << endl;
			auto riter1 = lst1.rbegin();
			auto riter2 = lst1.rend();
			EXPECT_EQ_VAL(riter1, riter2);

			riter1 = lst2.rbegin(); //rbegin
			EXPECT_EQ_VAL(*(riter1++), 4);
			EXPECT_EQ_VAL(*(riter1++), 3);
			EXPECT_EQ_VAL(*(riter1++), 2);
			EXPECT_EQ_VAL(*(riter1++), 1);
			EXPECT_EQ_VAL(*(kkli::prev(lst2.rend())), 1); //rend

			cout << "test: crbegin()" << endl;
			cout << "test: crend()" << endl;
			auto criter1 = lst3.crbegin(); //crbegin
			EXPECT_EQ_VAL(*(criter1++), 8);
			EXPECT_EQ_VAL(*(criter1++), 7);
			EXPECT_EQ_VAL(*(criter1++), 6);
			EXPECT_EQ_VAL(*(criter1++), 5);
			EXPECT_EQ_VAL(*(kkli::prev(lst3.crend())), 5); //crend
		}

		//≤‚ ‘ empty
		void test_empty() {
			cout << "test: empty()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			EXPECT_EQ_VAL(lst1.empty(), true);
			EXPECT_EQ_VAL(lst2.empty(), false);
		}

		//≤‚ ‘ size
		void test_size() {
			cout << "test: size()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			EXPECT_EQ_VAL(lst1.size(), 0);
			EXPECT_EQ_VAL(lst2.size(), 4);
		}

		//≤‚ ‘ clear
		void test_clear() {
			cout << "test: clear()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };

			lst1.clear();
			EXPECT_EQ_VAL(lst1.empty(), true);
			EXPECT_EQ_VAL(lst1.size(), 0);

			lst2.clear();
			EXPECT_EQ_VAL(lst2.empty(), true);
			EXPECT_EQ_VAL(lst2.size(), 0);
		}

		//≤‚ ‘ insert
		void test_insert() {
			cout << "test: insert()" << endl;

			list<int> lst1{ 1,2,3,4 };

			lst1.insert(lst1.begin(), std::move(1)); //insert(pos, &&value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,1,2,3,4 });

			lst1.insert(kkli::next(lst1.begin(), 2), 2, 4); //insert(pos, count, value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,1,2,4,4,3,4 });

			lst1.insert(kkli::next(lst1.begin(), 6), 5); //insert(pos, value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,1,2,4,4,3,4,5 });

			lst1.insert(lst1.begin(), { 1,2,3,4 }); //insert(pos, init)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,1,2,3,4,1,2,4,4,3,4,5 });
		}

		//≤‚ ‘ erase
		void test_erase() {
			cout << "test: erase()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4,5,6,7,8 };

			lst1.erase(lst1.begin(), lst1.end()); //erase(first, last)
			EXPECT_EQ_VAL(lst1.empty(), true);
			EXPECT_EQ_VAL(lst1.size(), 0);
			lst2.erase(lst2.begin(), kkli::next(lst2.begin(), 2)); 
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 3,4,5,6,7,8 });

			lst2.erase(lst2.begin()); //erase(pos)
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 4,5,6,7,8 });
			lst2.erase(kkli::next(lst2.begin(), 2));
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 4,5,7,8 });
		}

		//≤‚ ‘ push_back
		void test_push_back() {
			cout << "test: push_back()" << endl;

			list<int> lst1;
			
			lst1.push_back(1); //push_back(value)
			EXPECT_EQ_VAL(*(lst1.begin()), 1);
			lst1.push_back(2);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2 });

			lst1.push_back(std::move(3)); //push_back(&&value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3 });
		}

		//≤‚ ‘ pop_back
		void test_pop_back() {
			cout << "test: pop_back()" << endl;

			list<int> lst1{ 1,2,3,4 };
			lst1.pop_back();
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3 });
			lst1.pop_back();
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2 });
			lst1.pop_back();
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1 });
			lst1.pop_back();
			EXPECT_EQ_VAL(lst1.empty(), true);
		}

		//≤‚ ‘ push_front
		void test_push_front() {
			cout << "test: push_front()" << endl;

			list<int> lst1;

			lst1.push_front(4); //push_front(value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 4 });
			lst1.push_front(3);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 3,4 });

			lst1.push_front(std::move(2)); //push_front(&&value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 2,3,4 });
			lst1.push_front(std::move(1));
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
		}

		//≤‚ ‘ pop_front
		void test_pop_front() {
			cout << "test: pop_front()" << endl;

			list<int> lst1{ 1,2,3,4 };
			lst1.pop_front();
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 2,3,4 });
			lst1.pop_front();
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 3,4 });
			lst1.pop_front();
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 4 });
			lst1.pop_front();
			EXPECT_EQ_VAL(lst1.empty(), true);
		}
		
		//≤‚ ‘ resize
		void test_resize() {
			cout << "test: resize()" << endl;

			list<int> lst1;

			lst1.resize(4);  //resize(count)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 0,0,0,0 });
			lst1.resize(2);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 0,0,0,0 });

			lst1.resize(8, 1); //resize(count, value)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 0,0,0,0,1,1,1,1 });
			lst1.resize(4, 1);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 0,0,0,0,1,1,1,1 });
		}

		//≤‚ ‘ swap
		void test_swap() {
			cout << "test: swap()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			list<int> lst3{ 5,6,7,8 };
			
			lst1.swap(lst2); //member function: swap(rhs)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(lst2.empty(), true);
			lst1.swap(lst3);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 5,6,7,8 });
			EXPECT_EQ_ITERLIST(lst3.begin(), lst3.end(), { 1,2,3,4 });

			kkli::swap(lst2, lst3);
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 1,2,3,4 });
			EXPECT_EQ_VAL(lst3.empty(), true);
			kkli::swap(lst1, lst2);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 5,6,7,8 });
		}

		//≤‚ ‘ merge
		void test_merge() {
			cout << "test: merge()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };
			list<int> lst3{ 1,3,5,7 };
			list<int> lst4{ 2,4,6,8 };
			list<int> lst5{ 1,3,5,8 };
			list<int> lst6{ 2,4,6,7 };

			lst1.merge(lst2); //merge(rhs)
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,4 });
			lst3.merge(lst4);
			EXPECT_EQ_ITERLIST(lst3.begin(), lst3.end(), { 1,2,3,4,5,6,7,8 });
			lst5.merge(lst6);
			EXPECT_EQ_ITERLIST(lst5.begin(), lst5.end(), { 1,2,3,4,5,6,7,8 });

			list<int> lst7{ 8,6,4,2 };
			list<int> lst8{ 7,5,3,3 };
			auto lmd1 = [](int i, int j)->bool {return i > j; };
			lst7.merge(lst8, lmd1); //merge(rhs, comp)
			EXPECT_EQ_ITERLIST(lst7.begin(), lst7.end(), { 8,7,6,5,4,3,3,2 });
		}

		//≤‚ ‘ splice
		void test_splice() {
			cout << "test: splice()" << endl;

			list<int> lst1{ 1,2,3,4 };
			list<int> lst2{ 1,2,3,4,5,6,7,8 };

			//splice(pos, rhs, first, last)
			lst1.splice(lst1.begin(), lst2, kkli::next(lst2.begin()), kkli::next(lst2.begin(), 3));
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,2,3,4 });
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 1,4,5,6,7,8 });

			//splice(pos, rhs, it)
			lst1.splice(kkli::next(lst1.begin(), 4), lst2, lst2.begin(), kkli::next(lst2.begin(), 2));
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,2,3,2,3,1,4,4 });
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 5,6,7,8 });
			
			//splice(pos, rhs)
			lst1.splice(lst1.begin(), lst2);
			EXPECT_EQ_ITERLIST(lst1.begin(), lst1.end(), { 1,5,6,7,8,2,3,2,3,1,4,4 });
			EXPECT_EQ_VAL(lst2.empty(), true);
		}

		//≤‚ ‘ remove
		void test_remove() {
			list<int> lst1;
			list<int> lst2{ 1,1,2,2,3,3,4,5, };
			
			cout << "test: remove()" << endl;
			lst1.remove(2); //remove(value)
			EXPECT_EQ_VAL(lst1.empty(), true);
			lst2.remove(2);
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 1,1,3,3,4,5, });

			cout << "test: remove_if()" << endl;
			auto lmd1 = [](int i)->bool {return i % 2; };
			lst2.remove_if(lmd1); //remove_if(pred)
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 4 });
		}

		//≤‚ ‘ reverse
		void test_reverse() {
			cout << "test: reverse()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,2,3,4 };

			lst1.reverse();
			lst2.reverse();
			EXPECT_EQ_VAL(lst1.empty(), true);
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 4,3,2,1 });
		}

		//≤‚ ‘ unique
		void test_unique() {
			cout << "test: unique()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,1,2,2,3,3,4,4 };

			lst1.unique(); //unique()
			lst2.unique();
			EXPECT_EQ_VAL(lst1.empty(), true);
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 1,2,3,4 });

			list<int> lst3{ 1,3,5,6,7,7,9,10 };
			auto lmd1 = [](int i, int j)->bool {return i % 2 && j % 2; }; //¡¨–¯∆Ê ˝
			lst3.unique(lmd1); //unique(pred)
			EXPECT_EQ_ITERLIST(lst3.begin(), lst3.end(), { 1,6,7,10 });
		}

		//≤‚ ‘ sort
		void test_sort() {
			cout << "test: sort()" << endl;

			list<int> lst1;
			list<int> lst2{ 1,3,7,5,8,4,6,2 };

			lst1.sort(); //sort()
			lst2.sort();
			EXPECT_EQ_VAL(lst1.empty(), true);
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 1,2,3,4,5,6,7,8 });

			auto lmd1 = [](int i, int j)->bool { return i > j; };
			lst2.sort(lmd1); //sort(comp)
			EXPECT_EQ_ITERLIST(lst2.begin(), lst2.end(), { 8,7,6,5,4,3,2,1 });
		}
		
		//≤‚ ‘ operator == / != / < / <= / > / >=
		void test_operators() {
			list<int> list1;
			list<int> list2{ 1,1,1,1 };
			list<int> list3{ 1,2,3,4 };
			list<int> list4{ 1,2,3,4,5 };
			list<int> list5{ 1,3,5,7,9 };

			cout << "test: operator==" << endl;
			cout << "test: operator!=" << endl; //”…operator== µœ÷
			EXPECT_EQ_VAL(list1 == list1, true);
			EXPECT_EQ_VAL(list1 == list2, false);
			EXPECT_EQ_VAL(list1 == list3, false);
			EXPECT_EQ_VAL(list1 == list4, false);
			EXPECT_EQ_VAL(list1 == list5, false);
			EXPECT_EQ_VAL(list2 == list1, false);
			EXPECT_EQ_VAL(list2 == list2, true);
			EXPECT_EQ_VAL(list2 == list3, false);
			EXPECT_EQ_VAL(list2 == list4, false);
			EXPECT_EQ_VAL(list2 == list5, false);
			EXPECT_EQ_VAL(list3 == list1, false);
			EXPECT_EQ_VAL(list3 == list2, false);
			EXPECT_EQ_VAL(list3 == list3, true);
			EXPECT_EQ_VAL(list3 == list4, false);
			EXPECT_EQ_VAL(list3 == list5, false);
			EXPECT_EQ_VAL(list4 == list1, false);
			EXPECT_EQ_VAL(list4 == list2, false);
			EXPECT_EQ_VAL(list4 == list3, false);
			EXPECT_EQ_VAL(list4 == list4, true);
			EXPECT_EQ_VAL(list4 == list5, false);
			EXPECT_EQ_VAL(list5 == list1, false);
			EXPECT_EQ_VAL(list5 == list2, false);
			EXPECT_EQ_VAL(list5 == list3, false);
			EXPECT_EQ_VAL(list5 == list4, false);
			EXPECT_EQ_VAL(list5 == list5, true);
			

			cout << "test: operator<" << endl;
			cout << "test: operator>=" << endl;
			EXPECT_EQ_VAL(list1 < list1, false);
			EXPECT_EQ_VAL(list1 < list2, true);
			EXPECT_EQ_VAL(list1 < list3, true);
			EXPECT_EQ_VAL(list1 < list4, true);
			EXPECT_EQ_VAL(list1 < list5, true);
			EXPECT_EQ_VAL(list2 < list1, false);
			EXPECT_EQ_VAL(list2 < list2, false);
			EXPECT_EQ_VAL(list2 < list3, true);
			EXPECT_EQ_VAL(list2 < list4, true);
			EXPECT_EQ_VAL(list2 < list5, true);
			EXPECT_EQ_VAL(list3 < list1, false);
			EXPECT_EQ_VAL(list3 < list2, false);
			EXPECT_EQ_VAL(list3 < list3, false);
			EXPECT_EQ_VAL(list3 < list4, true);
			EXPECT_EQ_VAL(list3 < list5, true);
			EXPECT_EQ_VAL(list4 < list1, false);
			EXPECT_EQ_VAL(list4 < list2, false);
			EXPECT_EQ_VAL(list4 < list3, false);
			EXPECT_EQ_VAL(list4 < list4, false);
			EXPECT_EQ_VAL(list4 < list5, true);
			EXPECT_EQ_VAL(list5 < list1, false);
			EXPECT_EQ_VAL(list5 < list2, false);
			EXPECT_EQ_VAL(list5 < list3, false);
			EXPECT_EQ_VAL(list5 < list4, false);
			EXPECT_EQ_VAL(list5 < list5, false);

			//operator >
			cout << "test: operator>" << endl;
			cout << "test: operator<=" << endl;
			EXPECT_EQ_VAL(list1 > list1, false);
			EXPECT_EQ_VAL(list1 > list2, false);
			EXPECT_EQ_VAL(list1 > list3, false);
			EXPECT_EQ_VAL(list1 > list4, false);
			EXPECT_EQ_VAL(list1 > list5, false);
			EXPECT_EQ_VAL(list2 > list1, true);
			EXPECT_EQ_VAL(list2 > list2, false);
			EXPECT_EQ_VAL(list2 > list3, false);
			EXPECT_EQ_VAL(list2 > list4, false);
			EXPECT_EQ_VAL(list2 > list5, false);
			EXPECT_EQ_VAL(list3 > list1, true);
			EXPECT_EQ_VAL(list3 > list2, true);
			EXPECT_EQ_VAL(list3 > list3, false);
			EXPECT_EQ_VAL(list3 > list4, false);
			EXPECT_EQ_VAL(list3 > list5, false);
			EXPECT_EQ_VAL(list4 > list1, true);
			EXPECT_EQ_VAL(list4 > list2, true);
			EXPECT_EQ_VAL(list4 > list3, true);
			EXPECT_EQ_VAL(list4 > list4, false);
			EXPECT_EQ_VAL(list4 > list5, false);
			EXPECT_EQ_VAL(list5 > list1, true);
			EXPECT_EQ_VAL(list5 > list2, true);
			EXPECT_EQ_VAL(list5 > list3, true);
			EXPECT_EQ_VAL(list5 > list4, true);
			EXPECT_EQ_VAL(list5 > list5, false);
		}
	}
}
