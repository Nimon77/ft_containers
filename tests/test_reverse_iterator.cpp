/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 00:05:16 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/01 20:05:17 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_operator_chevron()
{
	ft::vector<int> myvector;
	ft::vector<int> stdmyvector;
	for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9
	for (int i=0; i<10; i++) stdmyvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9
	std::cout << "myvector:";
	for (int i=0; i<10; i++) std::cout << " " << myvector[i];
	std::cout << "\tsize : " << myvector.size() << std::endl;
	std::cout << "stdmyvector:";
	for (int i=0; i<10; i++) std::cout << " " << stdmyvector[i];
	std::cout << "\tsize : " << stdmyvector.size() << std::endl;
	typedef ft::vector<int>::iterator iter_type;
	typedef ft::vector<int>::iterator stditer_type;
	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();
	ft::reverse_iterator<stditer_type> stdrev_iterator = stdmyvector.rbegin();
	std::cout << "ft : The first element from the end is: " << rev_iterator[0] << '\n';
	std::cout << "std : The first element from the end is: " << stdrev_iterator[0] << '\n';
	std::cout << "ft : The fourth element from the end is: " << rev_iterator[3] << '\n';
	std::cout << "std : The fourth element from the end is: " << stdrev_iterator[3] << '\n';
}

void test_reverse_iterator()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_reverse_iterator" << C_OFF << std::endl;
	std::cout << C_RED << "test_operator_chevron" << C_OFF << std::endl;
	test_operator_chevron();
	std::cout << std::endl;
}
