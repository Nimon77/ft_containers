/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:37:26 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/18 18:55:48 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "utility.hpp"

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key> >
	class BST
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef struct s_node {
				Key key;
				T value;
				s_node *left;
				s_node *right;
			} t_node;
			typedef Compare										key_compare;
			typedef std::allocator<t_node>						allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;

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

			~BST()
			{
				clear(this->_root);
			}

			t_node* find(const t_node* to_find) const
			{
				return (find(value_type(to_find->key, to_find->value), _root));
			}

			t_node* find(const t_node* to_find, t_node* node) const
			{
				return (find(value_type(to_find->key, to_find->value), node));
			}

			t_node* find(const value_type &to_find) const
			{
				return (find(to_find, _root));
			}
			t_node* find(const value_type &to_find, t_node* node) const
			{
				t_node *ret = NULL;
				if (node)
				{
					if (node->key == to_find.first)
						return (node);
					if (node->left)
						ret = find(to_find, node->left);
					if (node->right && ret == NULL)
						ret = find(to_find, node->right);
				}
				return (ret);
			}

			void insert(const value_type &value)
			{
				key_compare cmp = key_compare();
				t_node *node = _root;
				t_node *parent = NULL;
				while (node)
				{
					parent = node;
					if (cmp(value.first, node->key))
						node = node->left;
					else if (cmp(node->key, value.first))
						node = node->right;
					else
						return ;
				}
				node = _alloc.allocate(sizeof(t_node));
				node->key = value.first;
				node->value = value.second;
				node->left = NULL;
				node->right = NULL;
				if (parent)
				{
					if (cmp(value.first, parent->key))
						parent->left = node;
					else
						parent->right = node;
				}
				else
					_root = node;
				return;
			}

			void insert(t_node* toInsert)
			{
				insert(value_type(toInsert->key, toInsert->value));
				if (toInsert->left)
					insert(toInsert->left);
				if (toInsert->right)
					insert(toInsert->right);
			}

			void erase(const value_type &to_find)
			{
				_root = erase(to_find, _root);
			}

			t_node* erase(const value_type &to_find, t_node* node)
			{
				if (node == NULL)
					return node;
				else if (to_find.first < node->key)
					node->left = erase(to_find, node->left);
				else if (to_find.first > node->key)
					node->right = erase(to_find, node->right);
				else
				{
					if (node->left == NULL)
					{
						t_node* tmp = node->right;
						_alloc.deallocate(node, sizeof(t_node));
						return tmp;
					}
					else if (node->right == NULL)
					{
						t_node* tmp = node->left;
						_alloc.deallocate(node, sizeof(t_node));
						return tmp;
					}
					else
					{
						t_node* tmp = minValue(node->right);
						node->key = tmp->key;
						node->value = tmp->value;
						node->right = erase(value_type(tmp->key, tmp->value), node->right);
					}
				}
				return (node);
			}

			t_node* erase(t_node* node)
			{
				return (erase(value_type(node->key, node->value), _root));
			}

			t_node* minValue()
			{
				minValue(_root);
			}
			t_node* minValue(t_node* node)
			{
				while (node->left)
					node = node->left;
				return (node);
			}

			t_node* maxValue()
			{
				maxValue(_root);
			}
			t_node* maxValue(t_node* node)
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
			void print(const t_node* node, const std::string& prefix = "", bool isLeft = false)
			{
				if (node != NULL)
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──");
					std::cout << node->value;
					std::cout << (isLeft ? " left" : " right");
					std::cout << std::endl;
					print(node->left, prefix + (isLeft ? "│   " : "    "), true);
					print(node->right, prefix + (isLeft ? "│   " : "    "), false);
				}
			}
		private:
			t_node *_root;
			allocator_type _alloc;

			void clear(t_node* node)
			{
				if (node)
				{
					clear(node->left);
					clear(node->right);
					_alloc.deallocate(node, sizeof(t_node));
				}
			}
	};
}

#endif
