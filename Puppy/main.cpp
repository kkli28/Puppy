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
	for (int i = 1; i < 21; ++i) {
		at.insert_elem(i);
		at.print();
	}
	for (int i = 0; i < 22; ++i) at.delete_elem(i);
	
	system("pause");
    return 0;
}
