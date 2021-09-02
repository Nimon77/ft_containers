/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 00:05:16 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/03 00:05:42 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_operator_chevron()
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9
	typedef std::vector<int>::iterator iter_type;
	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();
	std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';
}

void test_reverse_iterator()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_reverse_iterator" << C_OFF << std::endl;
	std::cout << C_RED << "test_operator_chevron" << C_OFF << std::endl;
	test_operator_chevron();
	std::cout << std::endl;
}
