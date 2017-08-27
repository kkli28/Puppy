#pragma once

#include "stdafx.h"
#include "memory.h"
#include "iterator.h"
#include "functional.h"
#include "pair.h"
#include "rb_tree_iterator.h"

//================================================================================
// rb_tree<T> 类定义
//================================================================================

namespace kkli {

	template<
		typename K,
		typename T,
		typename KOV, //KOV()函数对象可计算给定value的key
		typename Compare = kkli::less<K>
	>
		class rb_tree {
		public:
			typedef K				key_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef std::size_t		size_type;
			typedef std::ptrdiff_t	difference;
			typedef rb_tree_iterator<value_type, reference, pointer>				iterator;
			typedef rb_tree_iterator<value_type, const_reference, const_pointer>	const_iterator;
			typedef kkli::reverse_iterator<iterator>		reverse_iterator;
			typedef kkli::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef rb_tree_node<T> rb_tree_node;
			typedef rb_tree_node*	link_type;
			typedef Compare			compare_type;
			typedef rb_tree_color_type color_type;
			typedef kkli::allocator<rb_tree_node> node_allocator;

		private:
			link_type head;
			size_type node_count;
			Compare comp;

		private:
			link_type& root()const { return head->parent; }
			link_type& left_most()const { return head->left; }
			link_type& right_most()const { return head->right; }

			static link_type& left(link_type ptr) { return ptr->left; }
			static link_type& right(link_type ptr) { return ptr->right; }
			static link_type& parent(link_type ptr) { return ptr->parent; }
			static reference value(link_type ptr) { return ptr->value; }
			static const key_type& key(link_type ptr) { return KOV(value(ptr)); }
			static color_type& color(link_type ptr) { return ptr->color; }

			static link_type min(link_type ptr) { return ptr->min(); }
			static link_type max(link_type ptr) { return ptr->max(); }

		private:
			link_type get_node() { return node_allocator.allocate(1); }
			void put_node(link_type ptr) { node_allocator.deallocate(ptr); }
			link_type create_node(const value_type& value);
			void destroy_node(link_type ptr) {
				node_allocator.destroy(&(ptr->value));
				put_node(ptr);
			}
			void init() {
				head = get_node();
				head->color = RB_TREE_RED;
				head->parent = nullptr;
			}
			void destroy_tree(link_type ptr);
			iterator __insert(link_type x, link_type y, const value_type& value); //弃坑，写不下去了！！！

		public:
			//constructor
			rb_tree() :node_count(0), comp() {

			}
			rb_tree(const compare_type& cmp) :root(nullptr), node_count(0), comp(cmp) {}
			rb_tree(const rb_tree& rhs) :root(rhs.root), node_count(rhs.node_count), comp(rhs.comp) {}
			rb_tree(rb_tree&& rhs) :root(rhs.root), node_count(rhs.node_count), comp(std::move(rhs.comp)) {
				rhs.root = nullptr;
			}

			//destructor
			~rb_tree() {
				clear();
				put_node(head);
			}

			//operator =
			rb_tree& operator=(const rb_tree& rhs);
			rb_tree& operator=(rb_tree&& rhs);

			compare_type key_compare()const { return comp; }
			iterator begin() { return left_most(); }
			iterator end() { return head; }
			const_iterator cbegin()const { return left_most(); }
			const_iterator cend()const { return head; }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator crbegin() { return const_reverse_iterator(end()); }
			const_reverse_iterator crend() { return const_reverse_iterator(begin()); }
			bool empty()const { return node_count == 0; }
			size_type size()const { return node_count; }
			constexpr size_type max_size()const { return std::numeric_limits<size_type>::max(); }
			void swap(rb_tree& rhs) {
				kkli::swap(head);
				kkli::swap(node_count);
				kkli::swap(comp);
			}

		public:
			//insert_unique
			kkli::pair<iterator, bool> insert_unique(const value_type& value);
			iterator insert_unique(iterator pos, const value_type& value);
			template<typename InputIt>
			iterator insert_unique(InputIt first, InputIt last);

			//insert_equal
			iterator insert_equal(const value_type& value);
			iterator insert_equal(iterator pos, const value_type& value);
			template<typename InputIt>
			iterator insert_equal(InputIt first, InputIt last);

			//erase
			void erase(iterator pos);
			size_type erase(const key_type& k);
			void erase(iterator first, iterator last);
			
			//clear
			void clear();

			//find
			iterator find(const key_type& k);
			const_iterator find(const key_type& k)const;
			
			size_type count(const key_type& k)const;
			iterator lower_bound(const key_type& k);
			iterator upper_bound(const key_type& k);
			const_iterator lower_bound(const key_type& k)const;
			const_iterator upper_bound(const key_type& k)const;
			pair<iterator, iterator> equal_range(const key_type& k);
			pair<const_iterator, const_iterator> equal_range(const key_type& k)const;
	};
}

//================================================================================
// rb_tree<T> 成员函数定义
//================================================================================

namespace kkli {

	template<typename K, typename T, typename KOV, typename Compare>
	typename rb_tree<K, T, KOV, Compare>::link_type rb_tree<K, T, KOV, Compare>::create_node(const value_type& value) {
		link_type iter = node_allocator.allocate(1);
		node_allocator.construct(&(iter->value), value);
		return iter;
	}

	template<typename K, typename T, typename KOV, typename Compare>
	void rb_tree<K, T, KOV, Compare>::destroy_tree(link_type ptr) {
		if (ptr != nullptr) {
			destroy_tree(ptr->left);
			destroy_tree(ptr->right);
			destroy_node(ptr);
		}
	}

	template<typename K, typename T, typename KOV, typename Compare>
	rb_tree<K, T, KOV, Compare>& rb_tree<K, T, KOV, Compare>::operator=(const rb_tree& rhs) {
		root = rhs.root;
		node_count = rhs.root;
		comp = rhs.comp;
		return *this;
	}

	template<typename K, typename T, typename KOV, typename Compare>
	rb_tree<K, T, KOV, Compare>& rb_tree<K, T, KOV, Compare>::operator=(rb_tree&& rhs) {
		root = rhs.root;
		node_count = rhs.root;
		comp = std::move(rhs.comp);
		return *this;
	}

	template<typename K, typename T, typename KOV, typename Compare>
	void rb_tree<K, T, KOV, Compare>::clear() {
		if (node_count != 0) destroy_tree(root());
		left_most() = head;
		right_most() = head;
		root() = nullptr;
		node_count = 0;
	}

	template<typename K, typename T, typename KOV, typename Compare>
	kkli::pair<typename rb_tree<K,T,KOV,Compare>::iterator, bool> 
		rb_tree<K, T, KOV, Compare>::insert_unique(const value_type& value) {
		link_type pre_ptr = head;
		link_type ptr = root();
		bool comp_res = true;
		while (ptr != nullptr) {
			ptr_ptr = ptr;
			comp_res = key_compare(KOV()(value), key(ptr));
			ptr = comp_res ? left(ptr) : right(ptr);
		}
		iterator iter = iterator(pre_ptr);
		if (comp) {
			//TODO: 已弃坑，写不下去了！！！怀疑人生
		}
	}
}

//================================================================================
// 非成员函数定义
//================================================================================

namespace kkli {
	//template<typename K,typename T,typename KOV,typename Compare>

}