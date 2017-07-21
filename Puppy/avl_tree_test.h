#pragma once

#include "stdafx.h"
#include "avl_tree.h"

namespace test {
	namespace avl_tree_test {

		using std::cout;
		using std::endl;
		//�������
		void test() {
			cout << "\n========================================" << endl;
			cout << "          test: avl_tree " << endl;
			cout << "========================================" << endl;
			kkli::avl_tree<int> at;
			for (int i = 0; i < 20; ++i) {
				cout << "\n========== ���� " << i << "==========" << endl;
				at.insert_elem(i);
				at.print();
				cout << "���ڵ�߶�: ";
				auto ptr = at.get_root();
				if (ptr != nullptr) cout << ptr->height << endl;
				else cout << "����" << endl;
			}
			for (int i = 19; i >= 0; --i) {
				cout << "\n========== ɾ�� " << i << "==========" << endl;
				at.delete_elem(i);
				at.print();
				cout << "���ڵ�߶�: ";
				auto ptr = at.get_root();
				if (ptr != nullptr) cout << ptr->height << endl;
				else cout << "����" << endl;
			}
		}
	}
}