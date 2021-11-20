/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:14:14 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/20 14:34:33 by nsimon           ###   ########.fr       */
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

			explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}

			bool empty() const { return _container.empty(); }

			size_type size() const { return _container.size(); }

			value_type& top() { return _container.back(); }
			const value_type& top() const { return _container.back(); }

			void push(const value_type& val) { _container.push_back(val); }

			void pop() { _container.pop_back(); }

			bool operator==(const stack& other) const { return _container == other._container; }
			bool operator!=(const stack& other) const { return !(*this == other); }
			bool operator<(const stack& other) const { return _container < other._container; }
			bool operator>(const stack& other) const { return _container > other._container; }
			bool operator<=(const stack& other) const { return _container <= other._container; }
			bool operator>=(const stack& other) const { return _container >= other._container; }

		protected:
			container_type	_container;
	};
}

#endif
