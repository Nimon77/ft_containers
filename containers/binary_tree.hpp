/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:37:26 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/16 23:12:48 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include "utility.hpp"

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key> >
	class binaryTree
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef struct s_node {
				Key key;
				T value;
				s_node *left;
				s_node *right;
			} t_node;
			typedef ft::pair<const Key, T>						value_type;
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

			binaryTree(void)
			{
				this->_root = _alloc.allocate(sizeof(t_node));
				this->_root->key = 50;
				this->_root->value = 50;
				this->_root->left = NULL;
				this->_root->right = NULL;
				_size++;

				genRandom();
				print();
				int value;
				std::cin >> value;
				erase(value_type(value, value));
				print();
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
				if (cmp(value.first, parent->key))
					parent->left = node;
				else
					parent->right = node;
				_size++;
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

			void reinsert(t_node* to_insert)
			{
				key_compare cmp = key_compare();
				t_node *node = _root;
				t_node *parent = NULL;
				while (node)
				{
					parent = node;
					if (cmp(to_insert->key, node->key))
						node = node->left;
					else if (cmp(node->key, to_insert->key))
						node = node->right;
					else
						return ;
				}
				if (cmp(to_insert->key, parent->key))
					parent->left = to_insert;
				else
					parent->right = to_insert;
				_size++;
				return;
			}

			void erase(const value_type &to_find)
			{
				erase(to_find, _root, NULL);
			}

			int erase(const value_type &to_find, t_node* node, t_node* parent)
			{
				int ret = 0;
				if (node)
				{
					if (to_find.first == node->key)
					{
						if (parent)
						{
							if (parent->right->key == node->key)
								parent->right = NULL;
							else if (parent->left->key == node->key)
								parent->left = NULL;
							if (node->right)
								reinsert(node->right);
							if (node->left)
								reinsert(node->left);
						}
						_size--;
						return 1;
					}
					if (node->left)
						ret = erase(to_find, node->left, node);
					if (node->right && ret == 0)
						ret = erase(to_find, node->right, node);
				}
				return (ret);
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

			void print() { print(this->_root); }
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
			size_type _size;
			allocator_type _alloc;
	};
}

#endif
