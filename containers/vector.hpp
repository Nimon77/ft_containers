/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:42:01 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/02 02:28:28 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft {
	

	template < class T, class Alloc = allocator<T> >
	class Vector {
		public:
			typedef T								value_type;
			typedef Alloc							allocator_type;
			typedef allocator_type::reference		reference;
			typedef allocator_type::const_reference	const_reference;
			typedef allocator_type::pointer			pointer;
			typedef allocator_type::const_pointer	const_pointer;
	};
}

#endif
