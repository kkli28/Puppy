// XJBX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "my_pair_test.h"
#include "forward_list_test.h"
#include "avl_tree_test.h"
#include "array_test.h"
#include "vector_test.h"
#include "list_test.h"
#include "algorithm.h"
using namespace std;

int main() {
	//test::my_pair_test::test();
	//test::forward_list_test::test();
	//test::avl_tree_test::test();
	//test::array_test::test();
	//test::vector_test::test();
	//test::list_test::test();
	int arr[50] = { 1,3,5,7,9,2,4,10,8,6,1,3,5,7,9,2,4,10,8,6,1,3,5,7,9,2,4,10,8,6,1,3,5,7,9,2,4,10,8,6,1,3,5,7,9,2,4,10,8,6 };
	kkli::sort(begin(arr), end(arr), std::less<int>());
	for (auto a : arr) cout << a << " ";
	cout << endl;
	system("pause");
    return 0;
}
