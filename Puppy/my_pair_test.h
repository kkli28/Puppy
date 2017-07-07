#pragma once

#include "stdafx.h"
#include "my_pair.h"

namespace test {
	namespace my_pair_test {
		using std::cout;
		using std::endl;
		using std::string;

		using kkli::my_pair;
		using kkli::get;

		//ÕûÌå²âÊÔ
		void test() {

			//test: my_pair()
			my_pair<int, int> mp1;

			//test: my_pair<T1&&, T2&&>
			my_pair<int, int> mp2(1, 2);

			//test: my_pair<const T1&, const T2&>
			int i = 1;
			string str = "C++";
			my_pair<int, string> mp3(i, ref(str));
			cout << mp3.first << "  " << mp3.second << endl;
			cout << get<0>(mp3) << endl;
			cout << get<1>(mp3) << endl;
		}
	}
}