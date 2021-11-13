/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree_iterator.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:20:27 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/13 15:30:49 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_ITERATOR_HPP
# define BINARY_SEARCH_TREE_ITERATOR_HPP

# include "iterator.hpp"
# include "binary_search_tree.hpp"

namespace ft {
	template <typename T, class Compare>
	class BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type																	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;

			BST_iterator() : _node(NULL), _parent(NULL) {}
			BST_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {}
			BST_iterator(const BST_iterator &it) : _node(it._node), _parent(it._parent) {}

			virtual ~BST_iterator() {}

			reference operator*() const { return (_node->value); }
			pointer operator->() const { return (&(_node->value)); }

			BST_iterator &operator=(const BST_iterator &it)
			{
				_node = it._node;
				return (*this);
			}

			BST_iterator &operator++()
			{
				if (_node->right)
				{
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else
				{
					while (_node->parent && _node->parent->right == _node)
						_node = _node->parent;
					_node = _node->parent;
				}
				return (*this);
			}

			BST_iterator operator++(int)
			{
				BST_iterator tmp = *this;
				operator++();
				return (tmp);
			}

			BST_iterator &operator--()
			{
				if (_node != NULL)
				{
					if (_node->left)
						_node = _node->left;
					else
					{
						while (_node->parent && _node->parent->left == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else
					_node = _parent;
				return (*this);
			}

			BST_iterator operator--(int)
			{
				BST_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			bool operator==(const BST_iterator &it) const { return (_node == it._node); }
			bool operator!=(const BST_iterator &it) const { return (_node != it._node); }
			
			node_ptr	_node;
			node_ptr	_parent;
	};
		template <typename T, class Compare>
	class BST_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type																	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;

			BST_const_iterator() : _node(NULL), _parent(NULL) {}
			BST_const_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {}
			BST_const_iterator(const BST_const_iterator &it) : _node(it._node), _parent(it._parent) {}
			BST_const_iterator(const BST_iterator<T, Compare> &it) : _node(it._node), _parent(it._parent) {}

			virtual ~BST_const_iterator() {}

			reference operator*() const { return (_node->value); }
			pointer operator->() const { return (&(_node->value)); }

			BST_const_iterator &operator=(const BST_const_iterator &it)
			{
				_node = it._node;
				return (*this);
			}

			BST_const_iterator &operator++()
			{
				if (_node)
				{
					if (_node->right)
					{
						_node = _node->right;
						while (_node->left)
							_node = _node->left;
					}
					else
					{
						while (_node->parent && _node->parent->right == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return (*this);
			}

			BST_const_iterator operator++(int)
			{
				BST_const_iterator tmp = *this;
				operator++();
				return (tmp);
			}

			BST_const_iterator &operator--()
			{
				if (_node != NULL)
				{
					if (_node->left)
						_node = _node->left;
					else
					{
						while (_node->parent && _node->parent->left == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else
					_node = _parent;
				return (*this);
			}

			BST_const_iterator operator--(int)
			{
				BST_const_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			bool operator==(const BST_const_iterator &it) const { return (_node == it._node); }
			bool operator!=(const BST_const_iterator &it) const { return (_node != it._node); }
			
		
			node_ptr	_node;
			node_ptr	_parent;
	};
}

#endif
