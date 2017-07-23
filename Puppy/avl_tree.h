#pragma once

#include "stdafx.h"

//================================================================================
// avl_node<T> 类定义
//================================================================================

namespace kkli {

	//avl_node<T>
	template<typename T>
	class avl_node {
	public:
		T value;					//存储的值
		int height;					//当前节点高度
		avl_node* parent;			//父指针
		avl_node* left_child;		//左子指针
		avl_node* right_child;		//右子指针

									//avl_node(const T&)
		avl_node(const T& val) :value(val), height(0), parent(nullptr),
			left_child(nullptr), right_child(nullptr) {}

		//avl_node(T&&)
		avl_node(T&& val) :value(val), height(0),				//默认高度为1
			parent(nullptr), left_child(nullptr), right_child(nullptr) {}

		//avl_node()
		avl_node() : avl_node(std::move(T())) {}

		//avl_node(avl_node&&)
		avl_node(avl_node&& nd) :value(std::movd(nd.value)), height(nd.height),
			parent(nd.parent), left_child(nd.left_child), right_child(nd.right_child) {}

		//更新高度值，并返回高度值是否更改
		static bool update_height(avl_node* const nd) {
			int h = nd->height;						//存储原本的高度值

			//根节点高度为左右子树最大高度+1，sh: subtree_height，即子树高度
			std::pair<int, int> sh = get_subtree_height(nd);
			nd->height = (sh.first >= sh.second ? sh.first : sh.second) + 1;

			if (nd->height == h) return false;
			else return true;
		}

		//获取子树高度
		static std::pair<int, int> get_subtree_height(const avl_node* const nd) {
			int lh = -1;			//左子树高度
			int rh = -1;			//右子树高度

			if (nd->left_child != nullptr) lh = nd->left_child->height;
			if (nd->right_child != nullptr) rh = nd->right_child->height;
			return { lh,rh };
		}
	};
}

//================================================================================
// avl_tree<T> 类定义
//================================================================================

namespace kkli {

	template<typename T>
	class avl_tree {
	private:
		avl_node<T>* root;			//树根节点

		static void clear(avl_node<T>* const nd);				//删除以nd为根的树
		void rotate_left(avl_node<T>* const nd);				//左旋转
		void rotate_right(avl_node<T>* const nd);				//右旋转
		avl_node<T>* get_insert_pos(const T& elem)const;		//找到插入点
		avl_node<T>* get_delete_parent_pos(const T& elem)const;		//找到删除点的父节点
		avl_node<T>* get_balance_node(avl_node<T>* const nd);	//从nd到root，找到需要平衡的节点
		void balance(avl_node<T>* const nd);					//平衡节点

		//前序/中序 遍历输出
		void pre_print(const avl_node<T>* const nd) const;
		void in_print(const avl_node<T>* const nd) const;
	public:

		//avl_tree()
		avl_tree() :root(nullptr) {}

		//avl_tree(initializer_list)
		avl_tree(std::initializer_list<T> il) :root(nullptr) { insert_elem(il); }

		//avl_tree(n, elem)
		avl_tree(int n, const T& elem) :root(nullptr) { insert_elem(n, elem); }

		//avl_tree(arr,n)
		avl_tree(T* const arr, int n) :root(nullptr) {
			for (int i = 0; i < n; ++i) insert_elem(arr[i]);
		}

		//~avl_tree
		~avl_tree() { clear(root); root = nullptr; }

		//避免复制构造 / 赋值
		avl_tree(const avl_tree&) = delete;
		avl_tree& operator=(const avl_tree&) = delete;

		//获取根节点指针
		avl_node<T>* get_root()const { return root; }

		//插入
		void insert_elem(const T& elem);					//插入元素elem
		void insert_elem(std::initializer_list<T> il);		//插入元素列表
		void insert_elem(int n, const T& elem);				//插入n个elem

		void delete_elem(const T& elem);					//删除

		//输出树节点，分别采用前序遍历和中序遍历
		void print()const;
	};
}

//================================================================================
// avl_tree<T> 成员函数定义
//================================================================================

namespace kkli{

	//clear
	template<typename T>
	void avl_tree<T>::clear(avl_node<T>* const nd) {
		if (nd == nullptr) return;
		if (nd->left_child != nullptr) clear(nd->left_child);
		if (nd->right_child != nullptr) clear(nd->right_child);
		delete nd;
	}

	//rotate_left
	template<typename T>
	void avl_tree<T>::rotate_left(avl_node<T>* nd) {
		bool is_root = false;
		avl_node<T>* ptr_rightchild = nd->right_child;	    //右节点指针

		if (nd == root) {				//待左旋的节点为根节点
			is_root = true;

			//root的右子指针指向其右子节点的左子节点，若该节点不为空，则更新其parent
			root->right_child = ptr_rightchild->left_child;
			if (root->right_child != nullptr) root->right_child->parent = root;

			//root的原本右子节点的左子指针指向root，再让root指向之（更新root），并更新root的parent为nullptr
			ptr_rightchild->left_child = root;
			root->parent = ptr_rightchild;
			root = ptr_rightchild;
			root->parent = nullptr;
		}
		else {				//旋转点不是根节点
			avl_node<T>* ptr_parent = nd->parent;

			//nd的右子指针指向其右子节点的左子节点，若该节点不为空，则更新其parent指向nd
			nd->right_child = ptr_rightchild->left_child;
			if (nd->right_child != nullptr) nd->right_child->parent = nd;

			//nd的原右子节点的左子指针指向nd，更新nd的parent指向该节点
			ptr_rightchild->left_child = nd;
			nd->parent = ptr_rightchild;

			//更新nd的父节点与nd的连接指针
			if (ptr_parent->left_child == nd) ptr_parent->left_child = ptr_rightchild;
			else ptr_parent->right_child = ptr_rightchild;

			ptr_rightchild->parent = ptr_parent;
		}

		//更新节点高度
		avl_node<T>::update_height(nd);
		avl_node<T>::update_height(ptr_rightchild);

		//如果旋转点不是根节点，则需要更新父节点高度值
		if (!is_root) avl_node<T>::update_height(ptr_rightchild->parent);
	}

	//rotate_right
	template<typename T>
	void avl_tree<T>::rotate_right(avl_node<T>* nd) {
		bool is_root = false;				//标记nd是否是根节点
		avl_node<T>* ptr_leftchild = nd->left_child;	    //左节点指针

		if (nd == root) {	//待旋转点是根节点
			is_root = true;

			//root的左子指针指向其左子节点的右子节点，若该节点不为空，则更新其parent
			root->left_child = ptr_leftchild->right_child;
			if (root->left_child != nullptr) root->left_child->parent = root;

			//root的原本左子节点的右子指针指向root，再让root的父指针指向之
			ptr_leftchild->right_child = root;
			root->parent = ptr_leftchild;

			//更新root，并更新root的parent为nullptr
			root = ptr_leftchild;
			root->parent = nullptr;
		}
		else {	//非根节点
			avl_node<T>* ptr_parent = nd->parent;

			//nd的左子指针指向其左子节点的右子节点，若该节点不为空，则更新其parent指向nd
			nd->left_child = ptr_leftchild->right_child;
			if (nd->left_child != nullptr) nd->left_child->parent = nd;

			//nd的原左子节点的右子指针指向nd，更新nd的parent指向该节点
			ptr_leftchild->right_child = nd;
			nd->parent = ptr_leftchild;

			//更新nd的父节点与nd的连接指针
			if (ptr_parent->left_child == nd) ptr_parent->left_child = ptr_leftchild;
			else ptr_parent->right_child = ptr_leftchild;

			ptr_leftchild->parent = ptr_parent;
		}

		//更新节点高度
		avl_node<T>::update_height(nd);
		avl_node<T>::update_height(ptr_leftchild);

		//如果旋转点不是根节点，则需要更新父节点高度值
		if (!is_root) avl_node<T>::update_height(nd->parent);
	}

	//get_insert_pos
	template<typename T>
	avl_node<T>* avl_tree<T>::get_insert_pos(const T& elem)const {
		avl_node<T>* ptr = root;				//插入位置
		avl_node<T>* ptr_parent = root;			//插入节点的父节点
		if (elem <= ptr->value) ptr = ptr->left_child;
		else ptr = ptr->right_child;

		//ptr_parent指向待插入位置的父节点
		while (ptr != nullptr) {
			ptr_parent = ptr;
			if (elem <= ptr->value) ptr = ptr->left_child;
			else ptr = ptr->right_child;
		}
		return ptr_parent;
	}

	//get_delete_pos
	template<typename T>
	avl_node<T>* avl_tree<T>::get_delete_parent_pos(const T& elem)const {
		if (root == nullptr) return nullptr;

		avl_node<T>* ptr = root;				//待删除的节点
		avl_node<T>* ptr_parent = root;			//待删除节点的父节点
		if (elem < ptr->value) ptr = ptr->left_child;
		else ptr = ptr->right_child;

		//ptr_parent指向待插入位置的父节点
		while (ptr != nullptr && ptr->value != elem) {
			ptr_parent = ptr;
			if (elem <= ptr->value) ptr = ptr->left_child;
			else ptr = ptr->right_child;
		}

		//若ptr为nullptr，则表明没有找到值为elem的节点
		if (ptr == nullptr) return nullptr;
		else return ptr_parent;
	}

	//get_balance_node
	template<typename T>
	avl_node<T>* avl_tree<T>::get_balance_node(avl_node<T>* const nd) {
		//更新从 当前节点的父节点 到 根节点 的节点的高度值，ptr作为循环指针
		avl_node<T>* ptr = nd;
		while (ptr != nullptr) {

			//更新了高度值，故还需要继续更新父节点的高度值
			if (avl_node<T>::update_height(ptr)) {

				//获取高度差，如果是2，则不再继续更新父节点的高度值，而是平衡节点
				std::pair<int, int> sh = avl_node<T>::get_subtree_height(ptr);
				if (std::abs(sh.first - sh.second) == 2) return ptr;
				else ptr = ptr->parent;
			}

			//没有更新高度值，但是在删除节点时，若某节点高度差达到2，也需要平衡
			else {
				std::pair<int, int> sh = avl_node<T>::get_subtree_height(ptr);
				if (std::abs(sh.first - sh.second) == 2) return ptr;
				else return nullptr;
			}
		}
		return nullptr;
	}

	//balance
	template<typename T>
	void avl_tree<T>::balance(avl_node<T>* const nd) {
		//获取左右子树高度
		std::pair<int, int> subtree_height = avl_node<T>::get_subtree_height(nd);

		//左高右低
		if (subtree_height.first > subtree_height.second) {
			//获取左子树的 左右子树 高度，sh代表subtree_height
			//因为左高右低，因此左子指针必然有效
			std::pair<int, int> left_sh = avl_node<T>::get_subtree_height(nd->left_child);

			//左子树依然左高右低，或相等，则nd只需要一次右旋转即可
			if (left_sh.first >= left_sh.second) {
				rotate_right(nd);
			}
			//左子树是右高左低，则需要先对左子树进行左旋转，然后再对nd进行右旋转
			else {
				rotate_left(nd->left_child);
				rotate_right(nd);
			}
		}

		//左低右高
		else {
			std::pair<int, int> right_sh = avl_node<T>::get_subtree_height(nd->right_child);
			//依旧左低右高，或相等
			if (right_sh.first <= right_sh.second) {
				rotate_left(nd);
			}
			//左高右低
			else {
				rotate_right(nd->right_child);
				rotate_left(nd);
			}
		}
	}

	//TEST: 前序遍历输出
	template<typename T>
	void avl_tree<T>::pre_print(const avl_node<T>* const nd)const {
		if (nd == nullptr) return;
		cout << "值" << nd->value;
		cout << "\t高" << nd->height;
		cout << "\t父" << (nd->parent == nullptr ? -1 : nd->parent->value);
		cout << "\t左子" << (nd->left_child == nullptr ? -1 : nd->left_child->value);
		cout << "\t右子" << (nd->right_child == nullptr ? -1 : nd->right_child->value) << endl;
		pre_print(nd->left_child);
		pre_print(nd->right_child);
	}

	//TEST: 中序遍历输出
	template<typename T>
	void avl_tree<T>::in_print(const avl_node<T>* const nd)const {
		if (nd == nullptr) return;
		in_print(nd->left_child);
		cout << "值" << nd->value;
		cout << "\t高" << nd->height;
		cout << "\t父" << (nd->parent == nullptr ? -1 : nd->parent->value);
		cout << "\t左子" << (nd->left_child == nullptr ? -1 : nd->left_child->value);
		cout << "\t右子" << (nd->right_child == nullptr ? -1 : nd->right_child->value) << endl;
		in_print(nd->right_child);
	}

	template<typename T>
	void avl_tree<T>::insert_elem(int n, const T& elem) {
		for (int i = 0; i < n; ++i)
			insert_elem(elem);
	}

	template<typename T>
	void avl_tree<T>::insert_elem(std::initializer_list<T> il) {
		for (auto iter = il.begin(); iter != il.end(); ++iter)
			insert_elem(*iter);
	}

	//insert
	template<typename T>
	void avl_tree<T>::insert_elem(const T& elem) {
		if (root == nullptr) {
			root = new avl_node<T>(elem);
			return;
		}

		avl_node<T>* ptr = get_insert_pos(elem);

		//作为左子节点
		if (elem <= ptr->value) {
			ptr->left_child = new avl_node<T>(elem);
			ptr->left_child->parent = ptr;
		}
		//作为右子节点
		else {
			ptr->right_child = new avl_node<T>(elem);
			ptr->right_child->parent = ptr;
		}

		//找到需要平衡的节点
		ptr = get_balance_node(ptr);

		//有需要平衡的节点，则对节点进行平衡
		if (ptr != nullptr) balance(ptr);
	}

	//delete
	template<typename T>
	void avl_tree<T>::delete_elem(const T& elem) {
		if (root == nullptr) return;

		//需要平衡的节点
		avl_node<T>* balance_ptr = nullptr;

		//get_delete_parent_pos对root->value==elem时无效，因root没有parent
		if (root->value == elem) {

			//root的左子树为空
			if (root->left_child == nullptr) {
				avl_node<T>* ptr = root;

				root = root->right_child;
				if (root != nullptr) root->parent = nullptr;
				delete ptr;
			}

			//root的左子树非空
			else {

				//root的左子节点没有右子节点
				if (root->left_child->right_child == nullptr) {
					avl_node<T>* ptr = root->left_child;
					root->value = ptr->value;
					root->left_child = ptr->left_child;
					if (root->left_child != nullptr) root->left_child->parent = root;
					delete ptr;

					balance_ptr = get_balance_node(root);
				}

				//root的左子节点有右子节点
				else {
					avl_node<T>* replace_ptr = root->left_child;
					while (replace_ptr->right_child != nullptr) replace_ptr = replace_ptr->right_child;
					root->value = replace_ptr->value;
					replace_ptr->parent->right_child = replace_ptr->left_child;
					if (replace_ptr->left_child != nullptr) replace_ptr->parent = replace_ptr->parent;
					
					balance_ptr = get_balance_node(replace_ptr->parent);
					delete replace_ptr;
				}
			}
		}

		//root所指节点的值不是elem
		else {
			avl_node<T>* ptr_parent = get_delete_parent_pos(elem);
			if (ptr_parent == nullptr) return;

			//确定待删除节点是左子节点还是右子节点
			avl_node<T>* ptr = ptr_parent->left_child;
			if (ptr == nullptr || ptr->value != elem) ptr = ptr_parent->right_child;

			//待删除节点没有左子树
			if (ptr->left_child == nullptr) {
				if (ptr_parent->left_child == ptr) {
					ptr_parent->left_child = ptr->right_child;
					if (ptr->right_child != nullptr) ptr->right_child->parent = ptr_parent;
				}
				else {
					ptr_parent->right_child = ptr->right_child;
					if (ptr->right_child != nullptr) ptr->right_child->parent = ptr_parent;
				}
				delete ptr;

				//更新ptr_parent到root节点的高度值，并找到需要平衡的节点
				balance_ptr = get_balance_node(ptr_parent);
			}

			//待删除节点有左子树
			else {
				//找到替换节点
				avl_node<T>* replace_ptr = ptr->left_child;

				//ptr左子节点没有右子树，即其左子节点最大
				if (replace_ptr->right_child == nullptr) {
					//更新ptr的值为其左子节点的值，并更新左子节点的左子节点的parent指针
					ptr->value = replace_ptr->value;
					ptr->left_child = replace_ptr->left_child;
					if (replace_ptr->left_child != nullptr) replace_ptr->left_child->parent = ptr;

					delete replace_ptr;

					//更新ptr到root节点的高度值，并找到需要平衡的节点
					balance_ptr = get_balance_node(ptr);
				}

				//ptr左子节点有右子树
				else {
					//找到ptr的左子树中的最右节点（最大）
					while (replace_ptr->right_child != nullptr) {
						replace_ptr = replace_ptr->right_child;
					}

					//更新ptr->value的值为其左子树中节点的最大值，并更新该节点左子节点的parent指针
					ptr->value = replace_ptr->value;
					replace_ptr->parent->right_child = replace_ptr->left_child;
					if (replace_ptr->left_child != nullptr) replace_ptr->left_child->parent = replace_ptr->parent;

					balance_ptr = get_balance_node(replace_ptr->parent);
					delete replace_ptr;
				}
			}
		}

		//平衡节点
		if (balance_ptr != nullptr) balance(balance_ptr);
	}

	//print
	template<typename T>
	void avl_tree<T>::print()const {
		cout << "前序遍历:" << endl;
		pre_print(root);		//前序遍历输出
		cout << endl << "中序遍历:" << endl;
		in_print(root);			//中序遍历输出
		cout << endl;
	}
}