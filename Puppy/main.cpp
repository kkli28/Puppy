// XJBX.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "my_pair_test.h"

void func(int&& i) {
	++i;
}

int main(){
	test::my_pair_test::test();
	system("pause");
    return 0;
}

