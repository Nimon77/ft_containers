/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:42:01 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/24 11:40:10 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utility.hpp"
# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include <memory>
# include <stdexcept>

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
				: _alloc(alloc), _vector(NULL), _size(0), _capacity(0) {}

			explicit vector (size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _vector(NULL), _size(n), _capacity(n)
			{
				if (n)
					_vector = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++) _alloc.construct(&_vector[i], val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				: _alloc(alloc), _vector(NULL), _size(0), _capacity(ft::distance(first, last))
			{
				if (_capacity)
					_vector = _alloc.allocate(_capacity);
				for (; first != last; first++) _alloc.construct(&_vector[_size++], *first);
			}

			vector (const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				if (_capacity)
					_vector = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++) _alloc.construct(&_vector[i], x._vector[i]);
			}

			~vector ()
			{
				for (size_type i = 0; i < _size; i++) _alloc.destroy(&_vector[i]);
				if (_vector != NULL) _alloc.deallocate(_vector, _capacity);
			}

			vector& operator= (const vector& x)
			{
				if (x == *this) return *this;
				this->clear();
				this->insert(begin(), x.begin(), x.end());
				return (*this);
			}

			iterator begin() { return iterator(_vector); }
			const_iterator begin() const { return const_iterator(_vector); }
			iterator end() { return iterator(_vector + _size); }
			const_iterator end() const { return const_iterator(_vector + _size); }
			reverse_iterator rbegin() { return reverse_iterator(_vector + _size); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_vector + _size); }
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
						value_type* tmp = _alloc.allocate(_capacity);
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(&tmp[i], _vector[i]);
							_alloc.destroy(&_vector[i]);
						}
						_alloc.deallocate(_vector, _capacity);
						_vector = tmp;
					}
					for (size_type i = _size; i < n; i++) _alloc.construct(&_vector[i], val);
					_size = n;
				}
			}

			size_type capacity() const { return _capacity; }

			bool empty() const { return (_size == 0); }
			
			void reserve(size_type n)
			{
				if (n > this->max_size()) throw std::length_error("vector::reserve");
				else if (n > _capacity)
				{
					pointer tmp = _alloc.allocate(n);
					if (_capacity > 0)
					{
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(&tmp[i], _vector[i]);
							_alloc.destroy(&_vector[i]);
						}
						_alloc.deallocate(_vector, _capacity);
					}
					_capacity = n;
					_vector = tmp;
				}
			}

			reference operator[] (size_type n) { return _vector[n]; }
			const_reference operator[] (size_type n) const { return _vector[n]; }
			reference at (size_type n) { if (n > _size) throw std::out_of_range("vector::at"); return _vector[n]; }
			const_reference at (size_type n) const { if (n > _size) throw std::out_of_range("vector::at"); return _vector[n]; }
			reference front() { return _vector[0]; }
			const_reference front() const { return _vector[0]; }
			reference back() { return _vector[_size - 1]; }
			const_reference back() const { return _vector[_size - 1]; }

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				this->clear();
				this->reserve(ft::distance(first, last));
				this->insert(begin(), first, last);
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				this->insert(begin(), n, val);
			}

			void push_back (const value_type& val)
			{
				if (_capacity > 0 && _size == _capacity)
				{
					pointer new_vector = _alloc.allocate(_capacity * 2);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(&new_vector[i], _vector[i]);
						_alloc.destroy(&_vector[i]);
					}
					_alloc.deallocate(_vector, _capacity);
					_capacity *= 2;
					_vector = new_vector;
				}
				else if (_capacity == 0)
				{
					_capacity = 1;
					_vector = _alloc.allocate(_capacity);
				}
				_alloc.construct(&_vector[_size], val);
				_size++;
			}

			void pop_back()
			{
				if (_size > 0)
				{
					_alloc.destroy(&_vector[_size - 1]);
					_size--;
				}
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type pos = position - _vector;
				this->reserve(_size + 1);
				for (difference_type i = _size; i > pos; i--)
				{
					_alloc.construct(&_vector[i], _vector[i - 1]);
					_alloc.destroy(&_vector[i - 1]);
				}
				_alloc.construct(&_vector[pos], val);
				_size++;
				return (&_vector[pos]);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type pos = position - _vector;
				this->reserve(_size + n);
				for (difference_type i = _size; i > pos; i--)
				{
					_alloc.construct(&_vector[i + n - 1], _vector[i - 1]);
					_alloc.destroy(&_vector[i - 1]);
				}
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(&_vector[pos + i], val);
				}
				_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				size_type pos = position - _vector;
				size_type n = ft::distance(first, last);
				this->reserve(_size + n);
				for (size_type i = _size; i > pos; i--)
				{
					_alloc.construct(&_vector[i + n - 1], _vector[i - 1]);
					_alloc.destroy(&_vector[i - 1]);
				}
				for (size_type i = 0; first != last; first++, i++)
				{
					_alloc.construct(&_vector[pos + i], *first);
				}
				_size += n;
			}

			iterator erase (iterator position)
			{
				for (size_type i = position - _vector; i < _size - 1; i++)
				{
					_alloc.destroy(&_vector[i]);
					_alloc.construct(&_vector[i], _vector[i + 1]);
				}
				_alloc.destroy(&_vector[_size - 1]);
				_size--;
				return (iterator(position));
			}

			iterator erase (iterator first, iterator last)
			{
				size_type n = last - first;
				for (size_type i = first - _vector; i < _size - n; i++)
				{
					_alloc.destroy(&_vector[i]);
					_alloc.construct(&_vector[i], _vector[i + n]);
				}
				for (size_type i = _size - n; i < _size; i++) _alloc.destroy(&_vector[i]);
				_size -= n;
				return (iterator(first));
			}

			void swap (vector& x)
			{
				ft::swap(_vector, x._vector);
				ft::swap(_size, x._size);
				ft::swap(_capacity, x._capacity);
			}

			void clear()
			{
				if (_vector)
					for (size_type i = 0; i < _size; i++) _alloc.destroy(&_vector[i]);
				_size = 0;
			}

			allocator_type get_allocator () const { return _alloc; }

		private:
			allocator_type	_alloc;
			pointer			_vector;
			size_type		_size;
			size_type		_capacity;
	};

	template <class T, class Alloc>
	bool operator== (const vector<T, Alloc>& x, const vector<T, Alloc>& y)
	{
		if (x.size() != y.size()) return false;
		for (size_t i = 0; i < x.size(); i++) if (x[i] != y[i]) return false;
		return true;
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T, Alloc>& x, const vector<T, Alloc>& y)
	{
		return !(x == y);
	}
	
	template <class T, class Alloc>
	bool operator< (const vector<T, Alloc>& x, const vector<T, Alloc>& y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T, Alloc>& x, const vector<T, Alloc>& y)
	{
		return !(y < x);
	}
	
	template <class T, class Alloc>
	bool operator> (const vector<T, Alloc>& x, const vector<T, Alloc>& y)
	{
		return y < x;
	}
	
	template <class T, class Alloc>
	bool operator>= (const vector<T, Alloc>& x, const vector<T, Alloc>& y)
	{
		return !(x < y);
	}

	template <class T, class Alloc>
	void swap (vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}

}

#endif
