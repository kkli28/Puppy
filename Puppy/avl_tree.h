#pragma once

#include "stdafx.h"

//================================================================================
// avl_node<T> �ඨ��
//================================================================================

namespace kkli {

	//avl_node<T>
	template<typename T>
	class avl_node {
	public:
		T value;					//�洢��ֵ
		int height;					//��ǰ�ڵ�߶�
		avl_node* parent;			//��ָ��
		avl_node* left_child;		//����ָ��
		avl_node* right_child;		//����ָ��

									//avl_node(const T&)
		avl_node(const T& val) :value(val), height(0), parent(nullptr),
			left_child(nullptr), right_child(nullptr) {}

		//avl_node(T&&)
		avl_node(T&& val) :value(val), height(0),				//Ĭ�ϸ߶�Ϊ1
			parent(nullptr), left_child(nullptr), right_child(nullptr) {}

		//avl_node()
		avl_node() : avl_node(std::move(T())) {}

		//avl_node(avl_node&&)
		avl_node(avl_node&& nd) :value(std::movd(nd.value)), height(nd.height),
			parent(nd.parent), left_child(nd.left_child), right_child(nd.right_child) {}

		//���¸߶�ֵ�������ظ߶�ֵ�Ƿ����
		static bool update_height(avl_node* const nd) {
			int h = nd->height;						//�洢ԭ���ĸ߶�ֵ

			//���ڵ�߶�Ϊ�����������߶�+1��sh: subtree_height���������߶�
			std::pair<int, int> sh = get_subtree_height(nd);
			nd->height = (sh.first >= sh.second ? sh.first : sh.second) + 1;

			if (nd->height == h) return false;
			else return true;
		}

		//��ȡ�����߶�
		static std::pair<int, int> get_subtree_height(const avl_node* const nd) {
			int lh = -1;			//�������߶�
			int rh = -1;			//�������߶�

			if (nd->left_child != nullptr) lh = nd->left_child->height;
			if (nd->right_child != nullptr) rh = nd->right_child->height;
			return { lh,rh };
		}
	};
}

//================================================================================
// avl_tree<T> �ඨ��
//================================================================================

namespace kkli {

	template<typename T>
	class avl_tree {
	private:
		avl_node<T>* root;			//�����ڵ�

		static void clear(avl_node<T>* const nd);				//ɾ����ndΪ������
		void rotate_left(avl_node<T>* const nd);				//����ת
		void rotate_right(avl_node<T>* const nd);				//����ת
		avl_node<T>* get_insert_pos(const T& elem)const;		//�ҵ������
		avl_node<T>* get_delete_parent_pos(const T& elem)const;		//�ҵ�ɾ����ĸ��ڵ�
		avl_node<T>* get_balance_node(avl_node<T>* const nd);	//��nd��root���ҵ���Ҫƽ��Ľڵ�
		void balance(avl_node<T>* const nd);					//ƽ��ڵ�

		//ǰ��/���� �������
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

		//���⸴�ƹ��� / ��ֵ
		avl_tree(const avl_tree&) = delete;
		avl_tree& operator=(const avl_tree&) = delete;

		//��ȡ���ڵ�ָ��
		avl_node<T>* get_root()const { return root; }

		//����
		void insert_elem(const T& elem);					//����Ԫ��elem
		void insert_elem(std::initializer_list<T> il);		//����Ԫ���б�
		void insert_elem(int n, const T& elem);				//����n��elem

		void delete_elem(const T& elem);					//ɾ��

		//������ڵ㣬�ֱ����ǰ��������������
		void print()const;
	};
}

//================================================================================
// avl_tree<T> ��Ա��������
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
		avl_node<T>* ptr_rightchild = nd->right_child;	    //�ҽڵ�ָ��

		if (nd == root) {				//�������Ľڵ�Ϊ���ڵ�
			is_root = true;

			//root������ָ��ָ�������ӽڵ�����ӽڵ㣬���ýڵ㲻Ϊ�գ��������parent
			root->right_child = ptr_rightchild->left_child;
			if (root->right_child != nullptr) root->right_child->parent = root;

			//root��ԭ�����ӽڵ������ָ��ָ��root������rootָ��֮������root����������root��parentΪnullptr
			ptr_rightchild->left_child = root;
			root->parent = ptr_rightchild;
			root = ptr_rightchild;
			root->parent = nullptr;
		}
		else {				//��ת�㲻�Ǹ��ڵ�
			avl_node<T>* ptr_parent = nd->parent;

			//nd������ָ��ָ�������ӽڵ�����ӽڵ㣬���ýڵ㲻Ϊ�գ��������parentָ��nd
			nd->right_child = ptr_rightchild->left_child;
			if (nd->right_child != nullptr) nd->right_child->parent = nd;

			//nd��ԭ���ӽڵ������ָ��ָ��nd������nd��parentָ��ýڵ�
			ptr_rightchild->left_child = nd;
			nd->parent = ptr_rightchild;

			//����nd�ĸ��ڵ���nd������ָ��
			if (ptr_parent->left_child == nd) ptr_parent->left_child = ptr_rightchild;
			else ptr_parent->right_child = ptr_rightchild;

			ptr_rightchild->parent = ptr_parent;
		}

		//���½ڵ�߶�
		avl_node<T>::update_height(nd);
		avl_node<T>::update_height(ptr_rightchild);

		//�����ת�㲻�Ǹ��ڵ㣬����Ҫ���¸��ڵ�߶�ֵ
		if (!is_root) avl_node<T>::update_height(ptr_rightchild->parent);
	}

	//rotate_right
	template<typename T>
	void avl_tree<T>::rotate_right(avl_node<T>* nd) {
		bool is_root = false;				//���nd�Ƿ��Ǹ��ڵ�
		avl_node<T>* ptr_leftchild = nd->left_child;	    //��ڵ�ָ��

		if (nd == root) {	//����ת���Ǹ��ڵ�
			is_root = true;

			//root������ָ��ָ�������ӽڵ�����ӽڵ㣬���ýڵ㲻Ϊ�գ��������parent
			root->left_child = ptr_leftchild->right_child;
			if (root->left_child != nullptr) root->left_child->parent = root;

			//root��ԭ�����ӽڵ������ָ��ָ��root������root�ĸ�ָ��ָ��֮
			ptr_leftchild->right_child = root;
			root->parent = ptr_leftchild;

			//����root��������root��parentΪnullptr
			root = ptr_leftchild;
			root->parent = nullptr;
		}
		else {	//�Ǹ��ڵ�
			avl_node<T>* ptr_parent = nd->parent;

			//nd������ָ��ָ�������ӽڵ�����ӽڵ㣬���ýڵ㲻Ϊ�գ��������parentָ��nd
			nd->left_child = ptr_leftchild->right_child;
			if (nd->left_child != nullptr) nd->left_child->parent = nd;

			//nd��ԭ���ӽڵ������ָ��ָ��nd������nd��parentָ��ýڵ�
			ptr_leftchild->right_child = nd;
			nd->parent = ptr_leftchild;

			//����nd�ĸ��ڵ���nd������ָ��
			if (ptr_parent->left_child == nd) ptr_parent->left_child = ptr_leftchild;
			else ptr_parent->right_child = ptr_leftchild;

			ptr_leftchild->parent = ptr_parent;
		}

		//���½ڵ�߶�
		avl_node<T>::update_height(nd);
		avl_node<T>::update_height(ptr_leftchild);

		//�����ת�㲻�Ǹ��ڵ㣬����Ҫ���¸��ڵ�߶�ֵ
		if (!is_root) avl_node<T>::update_height(nd->parent);
	}

	//get_insert_pos
	template<typename T>
	avl_node<T>* avl_tree<T>::get_insert_pos(const T& elem)const {
		avl_node<T>* ptr = root;				//����λ��
		avl_node<T>* ptr_parent = root;			//����ڵ�ĸ��ڵ�
		if (elem <= ptr->value) ptr = ptr->left_child;
		else ptr = ptr->right_child;

		//ptr_parentָ�������λ�õĸ��ڵ�
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

		avl_node<T>* ptr = root;				//��ɾ���Ľڵ�
		avl_node<T>* ptr_parent = root;			//��ɾ���ڵ�ĸ��ڵ�
		if (elem < ptr->value) ptr = ptr->left_child;
		else ptr = ptr->right_child;

		//ptr_parentָ�������λ�õĸ��ڵ�
		while (ptr != nullptr && ptr->value != elem) {
			ptr_parent = ptr;
			if (elem <= ptr->value) ptr = ptr->left_child;
			else ptr = ptr->right_child;
		}

		//��ptrΪnullptr�������û���ҵ�ֵΪelem�Ľڵ�
		if (ptr == nullptr) return nullptr;
		else return ptr_parent;
	}

	//get_balance_node
	template<typename T>
	avl_node<T>* avl_tree<T>::get_balance_node(avl_node<T>* const nd) {
		//���´� ��ǰ�ڵ�ĸ��ڵ� �� ���ڵ� �Ľڵ�ĸ߶�ֵ��ptr��Ϊѭ��ָ��
		avl_node<T>* ptr = nd;
		while (ptr != nullptr) {

			//�����˸߶�ֵ���ʻ���Ҫ�������¸��ڵ�ĸ߶�ֵ
			if (avl_node<T>::update_height(ptr)) {

				//��ȡ�߶Ȳ�����2�����ټ������¸��ڵ�ĸ߶�ֵ������ƽ��ڵ�
				std::pair<int, int> sh = avl_node<T>::get_subtree_height(ptr);
				if (std::abs(sh.first - sh.second) == 2) return ptr;
				else ptr = ptr->parent;
			}

			//û�и��¸߶�ֵ��������ɾ���ڵ�ʱ����ĳ�ڵ�߶Ȳ�ﵽ2��Ҳ��Ҫƽ��
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
		//��ȡ���������߶�
		std::pair<int, int> subtree_height = avl_node<T>::get_subtree_height(nd);

		//����ҵ�
		if (subtree_height.first > subtree_height.second) {
			//��ȡ�������� �������� �߶ȣ�sh����subtree_height
			//��Ϊ����ҵͣ��������ָ���Ȼ��Ч
			std::pair<int, int> left_sh = avl_node<T>::get_subtree_height(nd->left_child);

			//��������Ȼ����ҵͣ�����ȣ���ndֻ��Ҫһ������ת����
			if (left_sh.first >= left_sh.second) {
				rotate_right(nd);
			}
			//���������Ҹ���ͣ�����Ҫ�ȶ���������������ת��Ȼ���ٶ�nd��������ת
			else {
				rotate_left(nd->left_child);
				rotate_right(nd);
			}
		}

		//����Ҹ�
		else {
			std::pair<int, int> right_sh = avl_node<T>::get_subtree_height(nd->right_child);
			//��������Ҹߣ������
			if (right_sh.first <= right_sh.second) {
				rotate_left(nd);
			}
			//����ҵ�
			else {
				rotate_right(nd->right_child);
				rotate_left(nd);
			}
		}
	}

	//TEST: ǰ��������
	template<typename T>
	void avl_tree<T>::pre_print(const avl_node<T>* const nd)const {
		if (nd == nullptr) return;
		cout << "ֵ" << nd->value;
		cout << "\t��" << nd->height;
		cout << "\t��" << (nd->parent == nullptr ? -1 : nd->parent->value);
		cout << "\t����" << (nd->left_child == nullptr ? -1 : nd->left_child->value);
		cout << "\t����" << (nd->right_child == nullptr ? -1 : nd->right_child->value) << endl;
		pre_print(nd->left_child);
		pre_print(nd->right_child);
	}

	//TEST: ����������
	template<typename T>
	void avl_tree<T>::in_print(const avl_node<T>* const nd)const {
		if (nd == nullptr) return;
		in_print(nd->left_child);
		cout << "ֵ" << nd->value;
		cout << "\t��" << nd->height;
		cout << "\t��" << (nd->parent == nullptr ? -1 : nd->parent->value);
		cout << "\t����" << (nd->left_child == nullptr ? -1 : nd->left_child->value);
		cout << "\t����" << (nd->right_child == nullptr ? -1 : nd->right_child->value) << endl;
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

		//��Ϊ���ӽڵ�
		if (elem <= ptr->value) {
			ptr->left_child = new avl_node<T>(elem);
			ptr->left_child->parent = ptr;
		}
		//��Ϊ���ӽڵ�
		else {
			ptr->right_child = new avl_node<T>(elem);
			ptr->right_child->parent = ptr;
		}

		//�ҵ���Ҫƽ��Ľڵ�
		ptr = get_balance_node(ptr);

		//����Ҫƽ��Ľڵ㣬��Խڵ����ƽ��
		if (ptr != nullptr) balance(ptr);
	}

	//delete
	template<typename T>
	void avl_tree<T>::delete_elem(const T& elem) {
		if (root == nullptr) return;

		//��Ҫƽ��Ľڵ�
		avl_node<T>* balance_ptr = nullptr;

		//get_delete_parent_pos��root->value==elemʱ��Ч����rootû��parent
		if (root->value == elem) {

			//root��������Ϊ��
			if (root->left_child == nullptr) {
				avl_node<T>* ptr = root;

				root = root->right_child;
				if (root != nullptr) root->parent = nullptr;
				delete ptr;
			}

			//root���������ǿ�
			else {

				//root�����ӽڵ�û�����ӽڵ�
				if (root->left_child->right_child == nullptr) {
					avl_node<T>* ptr = root->left_child;
					root->value = ptr->value;
					root->left_child = ptr->left_child;
					if (root->left_child != nullptr) root->left_child->parent = root;
					delete ptr;

					balance_ptr = get_balance_node(root);
				}

				//root�����ӽڵ������ӽڵ�
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

		//root��ָ�ڵ��ֵ����elem
		else {
			avl_node<T>* ptr_parent = get_delete_parent_pos(elem);
			if (ptr_parent == nullptr) return;

			//ȷ����ɾ���ڵ������ӽڵ㻹�����ӽڵ�
			avl_node<T>* ptr = ptr_parent->left_child;
			if (ptr == nullptr || ptr->value != elem) ptr = ptr_parent->right_child;

			//��ɾ���ڵ�û��������
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

				//����ptr_parent��root�ڵ�ĸ߶�ֵ�����ҵ���Ҫƽ��Ľڵ�
				balance_ptr = get_balance_node(ptr_parent);
			}

			//��ɾ���ڵ���������
			else {
				//�ҵ��滻�ڵ�
				avl_node<T>* replace_ptr = ptr->left_child;

				//ptr���ӽڵ�û�����������������ӽڵ����
				if (replace_ptr->right_child == nullptr) {
					//����ptr��ֵΪ�����ӽڵ��ֵ�����������ӽڵ�����ӽڵ��parentָ��
					ptr->value = replace_ptr->value;
					ptr->left_child = replace_ptr->left_child;
					if (replace_ptr->left_child != nullptr) replace_ptr->left_child->parent = ptr;

					delete replace_ptr;

					//����ptr��root�ڵ�ĸ߶�ֵ�����ҵ���Ҫƽ��Ľڵ�
					balance_ptr = get_balance_node(ptr);
				}

				//ptr���ӽڵ���������
				else {
					//�ҵ�ptr���������е����ҽڵ㣨���
					while (replace_ptr->right_child != nullptr) {
						replace_ptr = replace_ptr->right_child;
					}

					//����ptr->value��ֵΪ���������нڵ�����ֵ�������¸ýڵ����ӽڵ��parentָ��
					ptr->value = replace_ptr->value;
					replace_ptr->parent->right_child = replace_ptr->left_child;
					if (replace_ptr->left_child != nullptr) replace_ptr->left_child->parent = replace_ptr->parent;

					balance_ptr = get_balance_node(replace_ptr->parent);
					delete replace_ptr;
				}
			}
		}

		//ƽ��ڵ�
		if (balance_ptr != nullptr) balance(balance_ptr);
	}

	//print
	template<typename T>
	void avl_tree<T>::print()const {
		cout << "ǰ�����:" << endl;
		pre_print(root);		//ǰ��������
		cout << endl << "�������:" << endl;
		in_print(root);			//����������
		cout << endl;
	}
}