// XJBX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "my_pair_test.h"
#include "my_pair.h"
//#include "forward_list.h"
#include <forward_list>
using namespace std;

int main(){
	test::my_pair_test::test();
	forward_list<int> fl{ 1,2,3,4 };
	auto begin = fl.begin();
	system("pause");
    return 0;
}

