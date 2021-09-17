/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:21:03 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/17 10:10:32 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>
#include <algorithm>
#include <vector>

#define FT true
#include "color.hpp"

#if FT
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "iterator.hpp"
# include "vector.hpp"
#else
# include <type_traits>
# include <iterator>
	namespace ft = std;
#endif

void test_reverse_iterator();
void test_iterator();
void test_vector();

#endif
