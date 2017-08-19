// XJBX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iterator_test.h"
#include "memory_test.h"
#include "pair_test.h"
#include "functional_test.h"
#include "algorithm_test.h"
#include "array_test.h"
#include "forward_list_test.h"
#include "list_test.h"

#include "avl_tree_test.h"
#include "vector_test.h"
#include "string_test.h"

using namespace std;

int main() {
	test::iterator_test::test();
	test::memory_test::test();
	test::pair_test::test();
	test::functional_test::test();
	test::algorithm_test::test();
	test::array_test::test();
	test::string_test::test();
	test::forward_list_test::test();
	test::list_test::test();

	/*
	test::avl_tree_test::test();
	test::vector_test::test();
	*/

	system("pause");
    return 0;
}
