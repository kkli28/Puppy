// XJBX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "my_pair_test.h"
#include "forward_list_test.h"
#include "forward_list.h"
using namespace std;

double pow(int n, int p) {
	return std::pow(n, p);
}

int main() {
	//test::my_pair_test::test();
	//test::forward_list_test::test();
	cout << pow(99999999, 9999999) << endl;
	system("pause");
    return 0;
}
