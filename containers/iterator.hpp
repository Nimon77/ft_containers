/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:58:44 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/16 18:54:50 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef ft::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef ft::random_access_iterator_tag			iterator_category;
	};

	template <class Iterator>
	class random_access_iterator : ft::iterator<random_access_iterator_tag, Iterator>
	{
		public:
			typedef Iterator																			iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::reference			reference;

			random_access_iterator() : _it(nullptr) {}
			random_access_iterator(pointer It) : _it(It) {}
			random_access_iterator(const random_access_iterator& op) : _it(op._it) {}

			random_access_iterator &operator=(const random_access_iterator& op)
			{
				if (*this == op)
					return (*this);
				this->_it = op._it;
				return (*this);
			}

			reference operator*() const { return *_it; };
			pointer operator->() const { return _it; };

			random_access_iterator& operator+=(const difference_type n)
			{
				if (n >= 0)
					while (n--) ++_it;
				else
					while (n++) --_it;
				return (_it);
			}
			random_access_iterator operator+(difference_type n) const { return (_it + n); }
			random_access_iterator& operator-=(const difference_type n) { return (_it -= -n); }
			random_access_iterator operator-(const difference_type n) const { return (_it - n); }
			random_access_iterator& operator++()
			{
				++_it;
				return (*this);
			}
			random_access_iterator operator++(int) {
				random_access_iterator tmp = *this;
				++_it;
				return (tmp);
			}
			random_access_iterator& operator--()
			{
				--_it;
				return (*this);
			}
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				--_it;
				return (tmp);
			}
			bool operator==(const random_access_iterator& op) const { return (_it == op._it); }
			bool operator!=(const random_access_iterator& op) const { return (_it != op._it); }
			bool operator<(const random_access_iterator& op) const { return (_it < op._it); }
			bool operator<=(const random_access_iterator& op) const { return (_it <= op._it); }
			bool operator>(const random_access_iterator& op) const { return (_it > op._it); }
			bool operator>=(const random_access_iterator& op) const { return (_it >= op._it); }
			difference_type operator-(const random_access_iterator& op) { return (_it - op._it); }
			reference operator[](const difference_type n) const { return (_it[n]); }
		private:
			pointer _it;
	};

	template <class Iterator>
	bool operator< (const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs < rhs);
	}
	template <class Iterator>
	bool operator> (const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs > rhs);
	}
	template <class Iterator>
	bool operator>= (const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs >= rhs);
	}
	template <class Iterator>
	bool operator<= (const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs <= rhs);
	}
	template <class Iterator>
	bool operator== (const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs == rhs);
	}
	template <class Iterator>
	bool operator!= (const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs)
	{
		return (lhs != rhs);
	}
	

	/*
	** reverse_iterator
	*/
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator() : _it() {}

			explicit reverse_iterator(iterator_type it) : _it(it) {}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

			iterator_type base() const { return _it; }

			reference operator*() const { return *_it; }

			reverse_iterator operator+ (difference_type n) const { return reverse_iterator(_it - n); }

			reverse_iterator& operator++()
			{
				--_it;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--_it;
				return (tmp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				_it -= n;
				return *this;
			}

			reverse_iterator operator- (difference_type n) const { return reverse_iterator(_it + n); }

			reverse_iterator& operator--()
			{
				++_it;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator temp = *this;
				++_it;
				return temp;
			}

			reverse_iterator& operator-= (difference_type n)
			{
				_it += n;
				return *this;
			}

			pointer operator->() const { return &(operator*()); }

			bool operator==(const reverse_iterator& op) const { return (_it == op._it); }
			bool operator!=(const reverse_iterator& op) const { return (_it != op._it); }
			bool operator<(const reverse_iterator& op) const { return (_it > op._it); }
			bool operator<=(const reverse_iterator& op) const { return (_it >= op._it); }
			bool operator>(const reverse_iterator& op) const { return (_it < op._it); }
			bool operator>=(const reverse_iterator& op) const { return (_it <= op._it); }

			reference operator[] (difference_type n) const { return *(_it - n); }

		private:
			iterator_type	_it;
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() < lhs.base());
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() <= lhs.base());
	}
	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() > lhs.base());
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() >= lhs.base());
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it - n);
	}
}

#endif
