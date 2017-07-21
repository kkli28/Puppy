// XJBX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "my_pair_test.h"
#include "forward_list_test.h"
#include "forward_list.h"
#include "avl_tree.h"
using namespace std;

int main() {
	//test::my_pair_test::test();
	//test::forward_list_test::test();
	kkli::avl_tree<int> at;
	//int arr[20] = { 3,10,8,1,13,11,18,7,17,12,4,19,9,20,5,6,14,15,16,2 };
	int arr[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	for (int i = 0; i < 20; ++i) {
		at.insert_elem(arr[i]);
		at.print();
	}
	for (int i = 19; i >= 0; --i) {
		at.delete_elem(arr[i]);
		at.print();
	}
	
	system("pause");
    return 0;
}
