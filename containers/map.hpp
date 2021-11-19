/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 12:55:18 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/19 11:19:19 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utility.hpp"
# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include <memory>
# include "binary_search_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					key_compare													_comp;
					value_compare(key_compare comp) : _comp(comp) {}
				public:
					bool operator()(const value_type &x, const value_type &y) const { return _comp(x.first, y.first); }
			};
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename ft::BST<value_type, key_compare>::node_type		node_type;
			typedef typename ft::BST<value_type, key_compare>::iterator			iterator;
			typedef typename ft::BST<value_type, key_compare>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::difference_type					difference_type;

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp), _alloc(alloc), _size(0) {}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_tree = ft::BST<value_type, key_compare>(comp);
				_alloc = alloc;
				_size = ft::distance(first, last);
				for (; first != last; ++first)
					_tree.insert(*first);
			}

			map (const map& x) : _tree(x._tree), _alloc(x._alloc), _size(x._size) {}

			virtual ~map ()
			{}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					_alloc = x._alloc;
					_size = x._size;
					_tree.clear();
					_tree.insert(x.begin(), x.end());
				}
				return (*this);
			}

			iterator begin()
			{
				return (iterator(_tree.minValue(), NULL));
			}
			const_iterator begin() const
			{
				return (const_iterator(_tree.minValue(), NULL));
			}


			iterator end()
			{
				return (iterator(NULL, _tree.maxValue()));
			}
			const_iterator end() const
			{
				return (const_iterator(NULL, _tree.maxValue()));
			}


			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}


			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			bool empty() const
			{
				return (_size == 0);
			}
			
			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			mapped_type& operator[] (const key_type& k)
			{
				iterator it = find(k);
				if (it == end())
					it = insert(ft::make_pair(k, mapped_type())).first;
				return (it->second);
			}

			pair<iterator, bool> insert (const value_type& val)
			{
				pair<iterator, bool> res = _tree.insert(val);
				if (res.second)
					++_size;
				return (res);
			}

			iterator insert (iterator position, const value_type& val)
			{
				iterator res = _tree.insert(position, val);
				if (res != end())
					++_size;
				return (res);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			void erase (iterator position)
			{
				_tree.erase(*position);
				--_size;
			}

			size_type erase (const key_type& k)
			{
				_tree.erase(value_type(k, mapped_type()));
				--_size;
				return (_size);
			}

			void erase (iterator first, iterator last)
			{
				for (; first != last; ++first)
				{
					_tree.erase(*first);
					--_size;
				}
			}

			void swap (map& x)
			{
				_tree.swap(x._tree);
				ft::swap(_comp, x._comp);
				ft::swap(_alloc, x._alloc);
				ft::swap(_size, x._size);
			}

			void clear()
			{
				_tree.clear();
				_size = 0;
			}

			key_compare key_comp() const
			{
				return (_comp);
			}

			value_compare value_comp() const
			{
				return (value_compare(_comp));
			}

			iterator find (const key_type& k)
			{
				return (iterator(_tree.find(k), NULL));
			}

			const_iterator find (const key_type& k) const
			{
				return (const_iterator(_tree.find(k), NULL));
			}

			size_type count (const key_type& k) const
			{
				return (_tree.find(k) != NULL);
			}

			iterator lower_bound (const key_type& k)
			{
				return (iterator(_tree.lower_bound(k)));
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(_tree.lower_bound(k)));
			}

			iterator upper_bound (const key_type& k)
			{
				return (iterator(_tree.upper_bound(k)));
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(_tree.upper_bound(k)));
			}

			pair<iterator, iterator> equal_range (const key_type& k)
			{
				if (!count(k))
					return (pair<iterator, iterator>(end(), end()));
				else
					return (pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{
				if (!count(k))
					return (pair<const_iterator, const_iterator>(end(), end()));
				else
					return (pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}
/*
			void print()
			{
				_tree.print();
			}
*/
		private:
			ft::BST<value_type, key_compare>	_tree;
			key_compare				_comp;
			allocator_type			_alloc;
			size_type							_size;
	};


	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		typename map<Key, T, Compare, Allocator>::const_iterator	it = lhs.begin();
		typename map<Key, T, Compare, Allocator>::const_iterator	ite = lhs.end();
		typename map<Key, T, Compare, Allocator>::const_iterator	it2 = rhs.begin();

		while (it != ite && it2 != rhs.end())
		{
			if (it->first != it2->first || it->second != it2->second)
				return (false);
			it++;
			it2++;
		}
		return (it == ite && it2 == rhs.end());
	}
	
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator<(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		typename map<Key, T, Compare, Allocator>::const_iterator	it = lhs.begin();
		typename map<Key, T, Compare, Allocator>::const_iterator	ite = lhs.end();
		typename map<Key, T, Compare, Allocator>::const_iterator	it2 = rhs.begin();

		while (it != ite && it2 != rhs.end())
		{
			if (it->first != it2->first)
				return (it->first < it2->first);
			else if (it->second != it2->second)
				return (it->second < it2->second);
			it++;
			it2++;
		}
		return (it == ite && it2 != rhs.end());
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(map<Key, T, Compare, Allocator> &lhs, map<Key, T, Compare, Allocator> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
