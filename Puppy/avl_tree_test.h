#pragma once

#include "stdafx.h"
#include "avl_tree.h"

namespace test {
	namespace avl_tree_test {

		using std::cout;
		using std::endl;
		//整体测试
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: avl_tree " << endl;
			cout << "========================================" << endl;
			kkli::avl_tree<int> at;
			for (int i = 0; i < 20; ++i) {
				cout << "\n========== 插入 " << i << "==========" << endl;
				at.insert_elem(i);
				at.print();
				cout << "根节点高度: ";
				auto ptr = at.get_root();
				if (ptr != nullptr) cout << ptr->height << endl;
				else cout << "空树" << endl;
			}
			for (int i = 19; i >= 0; --i) {
				cout << "\n========== 删除 " << i << "==========" << endl;
				at.delete_elem(i);
				at.print();
				cout << "根节点高度: ";
				auto ptr = at.get_root();
				if (ptr != nullptr) cout << ptr->height << endl;
				else cout << "空树" << endl;
			}
		}
	}
}