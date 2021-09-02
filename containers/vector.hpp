/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:42:01 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/03 01:33:54 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class Vector {
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef allocator_type::size_type						size_type;

			explicit vector (const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _vector(nullptr), _begin(nullptr), _end(nullptr), _cap(nullptr) {}
			explicit vector (size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _size(n), _capacity(n);
			{
				_vector = alloc.allocate(sizeof(value_type) * n);
				for (size_type i = 0; i < n; i++) _alloc[i] = val;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _size(last - first), _capacity(last - first)
			{
				_vector = _alloc.allocate(sizeof(value_type) * _size)
				for (size_type i = 0;first + i != last; i++) _vector[i] = (first + i);
			}
		private:
			allocator_type	_alloc;
			pointer			_vector;
			size_type		_size;
			size_type		_capacity;
	};
}

#endif
