/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:42:01 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/16 18:20:10 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef typename allocator_type::size_type						size_type;

			explicit vector (const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _vector(nullptr), _size(0), _capacity(0) {}

			explicit vector (size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _size(n), _capacity(n)
			{
				_vector = _alloc.allocate(sizeof(value_type) * n);
				for (size_type i = 0; i < n; i++) _vector[i] = val;
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				: _alloc(alloc), _size(0), _capacity(0)
			{
				_vector = _alloc.allocate(sizeof(value_type) * (last - first));
				for (; first != last; first++)
				{
					_vector[_size++] = *first;
				}
			}

			vector (const vector& x)
			{
				_alloc = x._alloc;
				_size = x._size;
				_capacity = x._capacity;
				_vector = _alloc.allocate(sizeof(value_type) * _capacity);
				for (size_type i = 0; i < _size; i++) _vector[i] = x._vector[i];
			}

			~vector ()
			{
				_alloc.deallocate(_vector, _capacity * sizeof(value_type));
			}

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					_alloc.deallocate(_vector, _capacity * sizeof(value_type));
					_vector = _alloc.allocate(sizeof(value_type) * x._size);
					_size = x._size;
					_capacity = x._size;
					for (size_type i = 0; i < _size; i++) _vector[i] = x._vector[i];
				}
				return *this;
			}

			iterator begin() { return iterator(_vector); }
			const_iterator begin() const { return const_iterator(_vector); }
			iterator end() { return iterator(_vector + _size); }
			const_iterator end() const { return const_iterator(_vector + _size); }
			reverse_iterator rbegin() { return reverse_iterator(_vector + _size - 1); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_vector + _size - 1); }
			reverse_iterator rend() { return reverse_iterator(_vector); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_vector); }

			size_type size() const { return _size; }
			size_type max_size() const { return _alloc.max_size(); }
			void resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++) _alloc.destroy(&_vector[i]);
					_size = n;
				}
				else if (n > _size)
				{
					if (n > _capacity)
					{
						_capacity = n;
						value_type* tmp = _alloc.allocate(sizeof(value_type) * _capacity);
						for (size_type i = 0; i < _size; i++) tmp[i] = _vector[i];
						_alloc.deallocate(_vector, _capacity * sizeof(value_type));
						_vector = tmp;
					}
					for (size_type i = _size; i < n; i++) _alloc.construct(&_vector[i], val);
					_size = n;
				}
			}
			difference_type capacity() const { return _capacity; }

			reference operator[] (size_type n) { return _vector[n]; }
			const_reference operator[] (size_type n) const { return _vector[n]; }

			void push_back (const value_type& val)
			{
				if (_size == _capacity && _capacity != 0)
				{
					_capacity *= 2;
					pointer new_vector = _alloc.allocate(_capacity * sizeof(value_type));
					for (size_type i = 0; i < _size; i++) new_vector[i] = _vector[i];
					_alloc.destroy(_vector);
					_vector = new_vector;
				}
				else if (_capacity == 0)
				{
					_capacity = 1;
					_vector = _alloc.allocate(_capacity * sizeof(value_type));
				}
				_vector[_size++] = val;
			}

			allocator_type get_allocator () const { return _alloc; }

		private:
			allocator_type	_alloc;
			pointer			_vector;
			size_type		_size;
			size_type		_capacity;
	};
}

#endif
