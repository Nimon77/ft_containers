/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:28:34 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/01 20:11:52 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP
namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;
			T1 first;
			T2 second;

			pair() : first(), second() {}
			template< class U, class V >
			pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
			pair(const first_type& a, const second_type& b) : first(a), second(b) {}

			pair& operator= (const pair& pr)
			{
				if (*this == pr)
					return (*this);
				first = pr.first;
				second = pr.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator< (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator> (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
