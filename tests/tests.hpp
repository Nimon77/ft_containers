/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:21:03 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/09 14:45:38 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>
#include <algorithm>
#include <list>

#define FT true
#include "color.hpp"

#if FT
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "iterator.hpp"
# include "vector.hpp"
# include "utility.hpp"
# include "binary_search_tree.hpp"
# include "map.hpp"
#else
# include <vector>
# include <type_traits>
# include <iterator>
# include <map>
	namespace ft = std;
#endif

void test_reverse_iterator();
void test_iterator();
void test_vector();
void test_utility();

#endif
