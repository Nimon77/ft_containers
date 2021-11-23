/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:14:14 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/22 08:31:33 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <memory>

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack {
		public:
			typedef T									value_type;
			typedef Container							container_type;
			typedef typename container_type::size_type	size_type;

			explicit stack (const container_type& cTr = container_type()) : c(cTr) {}

			bool empty() const { return c.empty(); }

			size_type size() const { return c.size(); }

			value_type& top() { return c.back(); }
			const value_type& top() const { return c.back(); }

			void push(const value_type& val) { c.push_back(val); }

			void pop() { c.pop_back(); }

			template <class T2, class Container2>
			friend bool operator== (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator!= (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);
			
			template <class T2, class Container2>
			friend bool operator< (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator<= (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator> (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator>= (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);

		protected:
			container_type	c;
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c > rhs.c;
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c <= rhs.c;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c >= rhs.c;
	}

}

#endif
