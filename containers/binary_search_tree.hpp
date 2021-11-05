/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:37:26 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/05 18:41:25 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "binary_search_tree_iterator.hpp"
# include "utility.hpp"

namespace ft {
	template <typename T>
	struct BST_Node
	{
		typedef T	value_type;

		value_type	value;
		BST_Node	*parent;
		BST_Node	*left;
		BST_Node	*right;

		BST_Node(): value(), parent(nullptr), left(nullptr), right(nullptr) {}
		BST_Node(value_type const &value): value(value), parent(nullptr), left(nullptr), right(nullptr) {}
		BST_Node(BST_Node *parent = nullptr, BST_Node *left = nullptr, BST_Node *right = nullptr): value(), parent(parent), left(left), right(right) {}
		BST_Node(value_type const &value, BST_Node *parent = nullptr, BST_Node *left = nullptr, BST_Node *right = nullptr): value(value), parent(parent), left(left), right(right) {}
		BST_Node(BST_Node const &other): value(other.value), parent(other.parent), left(other.left), right(other.right) {}

		virtual ~BST_Node() {}

		BST_Node	&operator=(BST_Node const &other)
		{
			if (this != &other)
			{
				this->value = other.value;
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
			}
			return (*this);
		}

		bool	operator==(BST_Node const &other) const
		{
			return (this->value == other.value);
		}
	};
	template < class T, class Compare = ft::less<typename T::first_type>, class Node = ft::BST_Node<T>,
				class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
	class BST
	{
		public:
			typedef T				value_type;
			typedef Node			node_type;
			typedef Node *			node_pointer;
			typedef Node const *	node_const_pointer;
			typedef Node &			node_reference;
			typedef Node const &	node_const_reference;
			typedef Type_Alloc		type_allocator;
			typedef Node_Alloc		node_allocator;
			typedef Compare			key_compare;
			typedef ft::BST_iterator<Node, key_compare> iterator;
			typedef ft::BST_iterator<const Node, key_compare> const_iterator;

/*			BST test		*/
/*
			BST(void)
			{
				this->_root = NULL;
				//genRandom();
				insert(value_type(30, 30));
				insert(value_type(18, 18));
				insert(value_type(45, 45));
				insert(value_type(10, 10));
				insert(value_type(42, 42));
				insert(value_type(67, 67));
				print();
				int value = 30;
				std::cout << "delete : 30" << std::endl;
				//std::cin >> value;
				//std::cout << std::endl;
				erase(value_type(value, value));
				print();
			}
*/

			BST(const key_compare &cmp = key_compare())
			{
				this->_root = nullptr;
				this->cmp = cmp;
			}

			BST(BST const &other)
			{
				this->_root = other._root;
			}

			virtual ~BST()
			{
				clear(this->_root);
			}

			BST &operator=(BST const &other)
			{
				if (this != &other)
					this->_root = other._root;
				return (*this);
			}

			node_reference operator*() const
			{
				return ((this->_root));
			}
			node_pointer operator->() const
			{
				return (&(this->_root));
			}

			node_pointer find(const node_pointer to_find) const
			{
				return (find(to_find->value, _root));
			}

			node_pointer find(const node_pointer to_find, node_pointer node) const
			{
				return (find(to_find->value, node));
			}

			node_pointer find(const value_type &to_find) const
			{
				return (find(to_find, _root));
			}

			node_pointer find(const value_type &to_find, node_pointer node) const
			{
				node_pointer ret = nullptr;
				if (node)
				{
					if (node->value.first == to_find.first)
						return (node);
					if (node->left)
						ret = find(to_find, node->left);
					if (node->right && ret == nullptr)
						ret = find(to_find, node->right);
				}
				return (ret);
			}

			void insert(const value_type &value)
			{
				node_pointer node = _root;
				node_pointer parent = nullptr;
				while (node)
				{
					parent = node;
					if (cmp(value.first, node->value.first))
						node = node->left;
					else if (cmp(node->value.first, value.first))
						node = node->right;
					else
						return ;
				}
				node = _alloc.allocate(1);
				_alloc.construct(node, node_type(value, parent));
				if (parent)
				{
					if (cmp(value.first, parent->value.first))
						parent->left = node;
					else
						parent->right = node;
				}
				else
					_root = node;
				return;
			}

			void insert(node_pointer toInsert)
			{
				insert(toInsert->value);
				if (toInsert->left)
					insert(toInsert->left);
				if (toInsert->right)
					insert(toInsert->right);
			}

			void erase(const value_type &to_find)
			{
				_root = erase(to_find, _root);
			}

			node_pointer erase(const value_type &to_find, node_pointer node)
			{
				if (node == nullptr)
					return node;
				else if (to_find.first < node->value.first)
					node->left = erase(to_find, node->left);
				else if (to_find.first > node->value.first)
					node->right = erase(to_find, node->right);
				else
				{
					if (node->left == nullptr)
					{
						node_pointer tmp = node->right;
						_alloc.destroy(node);
						_alloc.deallocate(node, 1);
						return tmp;
					}
					else if (node->right == nullptr)
					{
						node_pointer tmp = node->left;
						_alloc.destroy(node);
						_alloc.deallocate(node, 1);
						return tmp;
					}
					else
					{
						node_pointer tmp = minValue(node->right);
						node->value = tmp->value;
						node->right = erase(tmp->value, node->right);
					}
				}
				return (node);
			}

			node_pointer erase(node_pointer node)
			{
				return (erase(value_type(node->key, node->value), _root));
			}

			node_pointer minValue()
			{
				return (minValue(_root));
			}
			node_pointer minValue(node_pointer node)
			{
				while (node->left)
					node = node->left;
				return (node);
			}

			node_pointer maxValue()
			{
				return (maxValue(_root));
			}
			node_pointer maxValue(node_pointer node)
			{
				while (node->right)
					node = node->right;
				return (node);
			}

			void genRandom(int size = 10)
			{
				srand(time(NULL));
				for (int i = 0; i < size; i++)
				{
					int val = rand() % 1000;
					insert(value_type(val, val));
				}
			}

			void print() {
				if (this->_root)
					print(this->_root);
			}
			void print(const node_pointer node, const std::string& prefix = "", bool isLeft = false)
			{
				if (node != nullptr)
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──");
					std::cout << node->value.first << ":" << node->value.second;
					//std::cout << (isLeft ? " left" : " right");
					std::cout << std::endl;
					print(node->left, prefix + (isLeft ? "│   " : "    "), true);
					print(node->right, prefix + (isLeft ? "│   " : "    "), false);
				}
			}

			node_pointer	_root;

		private:
			node_allocator	_alloc;
			key_compare	cmp;

			void clear(node_pointer node)
			{
				if (node)
				{
					clear(node->left);
					clear(node->right);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}
			}
	};
}

#endif
