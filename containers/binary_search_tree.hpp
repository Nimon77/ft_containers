/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:37:26 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/18 22:11:14 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "iterator.hpp"
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

		BST_Node(): value(), parent(NULL), left(NULL), right(NULL) {}
		BST_Node(BST_Node *parent = NULL, BST_Node *left = NULL, BST_Node *right = NULL): value(), parent(parent), left(left), right(right) {}
		BST_Node(value_type const &value, BST_Node *parent = NULL, BST_Node *left = NULL, BST_Node *right = NULL): value(value), parent(parent), left(left), right(right) {}
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
			typedef T											value_type;
			typedef typename T::first_type						key_type;
			typedef typename T::second_type						mapped_type;
			typedef Node										node_type;
			typedef Node *										node_pointer;
			typedef Node const *								node_const_pointer;
			typedef Node &										node_reference;
			typedef Node const &								node_const_reference;
			typedef Type_Alloc									type_allocator;
			typedef Node_Alloc									node_allocator;
			typedef Compare										key_compare;
			typedef ft::BST_iterator<Node, key_compare>			iterator;
			typedef ft::BST_const_iterator<Node, key_compare>	const_iterator;

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
				this->_root = NULL;
				this->cmp = cmp;
				this->_end = _alloc.allocate(1);
			}

			BST(BST const &other)
			{
				this->_root = NULL;
				this->cmp = other.cmp;
				this->_end = _alloc.allocate(1);
				this->insert(other.begin(), other.end());
			}

			virtual ~BST()
			{
				clear();
				_alloc.deallocate(this->_end, 1);
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
				node_pointer ret = NULL;
				if (node)
				{
					if (node->value.first == to_find.first)
						return (node);
					if (node->left)
						ret = find(to_find, node->left);
					if (node->right && ret == NULL)
						ret = find(to_find, node->right);
				}
				return (ret);
			}

			node_pointer find(const key_type &to_find, node_pointer node) const
			{
				node_pointer ret = NULL;
				if (node)
				{
					if (node->value.first == to_find)
						return (node);
					if (node->left)
						ret = find(to_find, node->left);
					if (node->right && ret == NULL)
						ret = find(to_find, node->right);
				}
				return (ret);
			}

			node_pointer find(const key_type &to_find) const
			{
				return (find(to_find, _root));
			}

			pair<iterator,bool> insert(const value_type &value, node_pointer node)
			{
				node_pointer parent = NULL;
				while (node)
				{
					parent = node;
					if (cmp(value.first, node->value.first))
						node = node->left;
					else if (cmp(node->value.first, value.first))
						node = node->right;
					else
						return pair<iterator,bool>(iterator(node, NULL), false);
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
				return pair<iterator,bool>(iterator(node, NULL), true);
			}

			pair<iterator,bool> insert(const value_type &value)
			{
				return (insert(value, _root));
			}

			void insert(node_pointer toInsert)
			{
				insert(toInsert->value, _root);
				if (toInsert->left)
					insert(toInsert->left, _root);
				if (toInsert->right)
					insert(toInsert->right, _root);
			}

			iterator insert(iterator position, const value_type &value)
			{
				return (insert(value, position.getNode()).first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first, _root);
					++first;
				}
			}

			void erase(const value_type &to_find)
			{
				if ((_root = erase(to_find, _root)))
					_root->parent = NULL;
			}

			void erase(node_pointer node)
			{
				if ((_root = erase(node->value, _root)))
					_root->parent = NULL;
			}

			node_pointer erase(const value_type &to_find, node_pointer node)
			{
				if (node == NULL)
					return NULL;
				else if (cmp(to_find.first, node->value.first))
				{
					if ((node->left = erase(to_find, node->left)))
						node->left->parent = node;
				}
				else if (cmp(node->value.first, to_find.first))
				{
					if ((node->right = erase(to_find, node->right)))
						node->right->parent = node;
				}
				else
				{
					if (node->left == NULL)
					{
						node_pointer tmp = node->right;
						_alloc.destroy(node);
						_alloc.deallocate(node, 1);
						return tmp;
					}
					else if (node->right == NULL)
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
						if ((node->right = erase(tmp->value, node->right)))
							node->right->parent = node;
					}
				}
				return (node);
			}

			node_pointer minValue() const
			{
				return (minValue(_root));
			}
			node_pointer minValue(node_pointer node) const
			{
				if (node)
					while (node->left)
						node = node->left;
				return (node);
			}

			node_pointer maxValue() const
			{
				return (maxValue(_root));
			}
			node_pointer maxValue(node_pointer node) const
			{
				if (node)
					while (node->right)
						node = node->right;
				return (node);
			}

			iterator begin()
			{
				return (iterator(minValue(), NULL));
			}
			const_iterator begin() const
			{
				return (const_iterator(minValue(), NULL));
			}

			iterator end()
			{
				return (iterator(NULL, maxValue()));
			}
			const_iterator end() const
			{
				return (const_iterator(NULL, maxValue()));
			}

			iterator lower_bound(const key_type &value)
			{
				iterator it = begin();
				iterator ite = end();

				while (it != ite)
				{
					if (cmp(it->first, value))
						it++;
					else
						break;
				}
				if (it == ite)
					return (iterator(_end, maxValue()));
				return (it);
			}
			const_iterator lower_bound(const key_type &value) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				while (it != ite)
				{
					if (cmp(it->first, value))
						it++;
					else
						break;
				}
				if (it == ite)
					return (const_iterator(_end, maxValue()));
				return (it);
			}

			iterator upper_bound(const key_type &value)
			{
				iterator it = begin();
				iterator ite = end();

				while (it != ite)
				{
					if (cmp(value, it->first))
						it++;
					else
						break;
				}
				if (++it == ite)
					return (iterator(_end, maxValue()));
				return (it);
			}
			const_iterator upper_bound(const key_type &value) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				while (it != ite)
				{
					if (cmp(value, it->first))
						it++;
					else
						break;
				}
				if (++it == ite)
					return (const_iterator(_end, maxValue()));
				return (it);
			}

			node_pointer clear(node_pointer node)
			{
				if (node)
				{
					node->left = clear(node->left);
					node->right = clear(node->right);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}
				return (NULL);
			}

			void clear()
			{
				this->_root = clear(this->_root);
			}

			// void print() {
			// 	if (this->_root)
			// 		print(this->_root);
			// }
			// void print(const node_pointer node, const std::string& prefix = "", bool isLeft = false)
			// {
			// 	if (node != NULL)
			// 	{
			// 		std::cout << prefix;
			// 		std::cout << (isLeft ? "├──" : "└──");
			// 		std::cout << node->value.first << ":" << node->value.second;
			// 		//std::cout << (isLeft ? " left" : " right");
			// 		std::cout << std::endl;
			// 		print(node->left, prefix + (isLeft ? "│   " : "    "), true);
			// 		print(node->right, prefix + (isLeft ? "│   " : "    "), false);
			// 	}
			// }

			node_pointer	_root;
			node_pointer	_end;

		private:
			node_allocator	_alloc;
			key_compare	cmp;
	};
}

#endif
