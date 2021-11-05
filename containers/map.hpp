/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 12:55:18 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/05 18:42:16 by nsimon           ###   ########.fr       */
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
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename ft::BST<value_type, key_compare>::node_type		node_type;
			typedef typename ft::BST<value_type, key_compare>::iterator			iterator;
			typedef typename ft::BST<value_type, key_compare>::const_iterator	const_iterator;
			//typedef ft::reverse_iterator<iterator>							reverse_iterator;
			//typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
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

			iterator begin()
			{
				return (iterator(_tree.minValue(), nullptr));
			}

			iterator end()
			{
				return (iterator(nullptr, _tree.maxValue()));
			}

			pair<iterator, bool> insert (const value_type& val)
			{
				_tree.insert(val);
				_size++;
				return pair<iterator, bool>();
			}

			size_type size() const
			{
				return _size;
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
