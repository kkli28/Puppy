#pragma once

#include "stdafx.h"
#include "iterator.h"

//================================================================================
// rb_tree_node<T> 类定义
//================================================================================

namespace kkli {


	template<typename T>
	class rb_tree_node {
	public:
		typedef bool rb_tree_color_type; //颜色类型
		constexpr static rb_tree_color_type RB_TREE_RED = false;
		constexpr static rb_tree_color_type RB_TREE_BLACK = true;

		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef rb_tree_node* link_type;
		typedef rb_tree_node self;

	private:
		void reset() {
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}

	public:
		T value;
		bool color;
		link_type* parent;
		link_type* left;
		link_type* right;

	public:
		static pointer* min(pointer* ptr) {
			while (ptr->left != nullptr) ptr = ptr->left;
			return ptr;
		}
		static pointer* max(pointer* ptr) {
			while (ptr->right != nullptr) ptr = ptr->right;
			return ptr;
		}

	public: //成员函数
		rb_tree_node():value(value_type()), color(RB_TREE_RED),		//self()
			parent(nullptr), left(nullptr), right(nullptr) {}
		explicit rb_tree_node(const value_type& val) :value(val), color(RB_TREE_RED),		//self(val)
			parent(nullptr), left(nullptr), right(nullptr) {}
		explicit rb_tree_node(value_type&& val):value(std::move(val)),color(RB_TREE_RED),	//self(&&val)
			parent(nullptr), left(nullptr), right(nullptr) {}
		rb_tree_node(const self& rhs) :value(rhs.value), color(rhs.color),		//self(rhs)
			parent(rhs.parent), left(rhs.left), right(rhs.right) {}
		rb_tree_node(self&& rhs):value(std::move(rhs.value)),color(rhs.color),	//self(&&rhs)
			parent(rhs.parent), left(rhs.left), right(rhs.right) {}

		self& operator=(const self& rhs) {
			value = rhs.value;
			color = rhs.color;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			return *this;
		}
		self& operator=(self&& rhs) {
			value = std::move(rhs.value);
			color = rhs.color;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			rhs.reset();
			return *this;
		}
	};
}

//================================================================================
// rb_tree_iterator<T> 类定义
//================================================================================

namespace kkli {

	template<typename T, typename Ref,typename Ptr>
	class rb_tree_iterator {
	public:
		typedef T value_type;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef kkli::bidirectional_iterator_tag iterator_category;

		typedef rb_tree_iterator<T, Ref, Ptr> self;
		typedef rb_tree_node<T>* link_type;
		typedef rb_tree_iterator<T, T&, T*>	iterator;
		typedef rb_tree_iterator<T, const T&, const T*>	const_iterator;

	private:
		void increment();
		void decrement();

	private:
		link_type node;

	public:
		rb_tree_iterator() {}
		rb_tree_iterator(link_type ptr) :node(ptr) {}
		rb_tree_iterator(const self& rhs) :node(rhs.node) {}

		self& operator=(const self& rhs) { node = rhs.node; return*this; }

		reference operator*()const { return node->value; }
		pointer operator->()const { return &(operator*()); }
		self& operator++() {
			increment();
			return *this;
		}
		self& operator--() {
			decrement();
			return *this;
		}
		self operator++(int) {
			auto temp = *this;
			increment();
			return temp;
		}
		self operator--(int) {
			auto temp = *this;
			decrement();
			return temp;
		}

		bool operator==(const self& rhs) {
			return node == rhs.node;
		}
		bool operator!=(const self& rhs) {
			return !(this->operator==(rhs));
		}
	};
}

//================================================================================
// rb_tree_iterator<T> 成员函数定义
//================================================================================

namespace kkli {

	//increment
	template<typename T,typename Ref,typename Ptr>
	void rb_tree_iterator<T, Ref, Ptr>::increment() {
		if (node->right != nullptr) {
			node = node->right;
			while (node->left != nullptr) node = node->left;
		}
		else {
			link_type lt = node->parent;
			while (lt!=nullptr && node == lt->right) {
				node = lt;
				lt = lt->parent;
			}
			node = lt;
		}
	}

	//decrement
	template<typename T,typename Ref,typename Ptr>
	void rb_tree_iterator<T, Ref, Ptr>::decrement() {
		if (node->left != nullptr) {
			node = node->left;
			while (node->right != nullptr) node = node->right;
		}
		else {
			link_type lt = node->parent;
			while (lt != nullptr && node == lt->left) {
				node = lt;
				lt = lt->parent;
			}
			node = lt;
		}
	}
}
