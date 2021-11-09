/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 12:55:18 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/09 12:08:22 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utility.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
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
//			template <class InputIterator>
//			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
//			{
//				
//			}
//			map (const map& x)
//			{
//				
//			}

			virtual ~map ()
			{}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					_tree = x._tree;
					_alloc = x._alloc;
					_size = x._size;
				}
				return (*this);
			}

			iterator begin()
			{
				return (iterator(_tree.minValue(), nullptr));
			}

			iterator end()
			{
				return (iterator(nullptr, _tree.maxValue()));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
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

			pair<iterator, bool> insert (const value_type& val)
			{
				_tree.insert(val);
				_size++;
				return pair<iterator, bool>();
			}

			void erase (iterator position)
			{
				_tree.erase(position.node);
				_size--;
			}

			size_type erase (const key_type& k)
			{
				_tree.erase(k);
				_size--;
				return (_size);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					erase(first++);
				}
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
				return (iterator(_tree.find(k), nullptr));
			}

			const_iterator find (const key_type& k) const
			{
				return (const_iterator(_tree.find(k), nullptr));
			}

			size_type count (const key_type& k) const
			{
				return (_tree.find(k) != nullptr);
			}

			iterator lower_bound (const key_type& k)
			{
				return (iterator())
			}

			void print()
			{
				_tree.print();
			}

		private:
			ft::BST<value_type, key_compare>	_tree;
			key_compare				_comp;
			allocator_type			_alloc;
			size_type							_size;
	};
}

#endif
