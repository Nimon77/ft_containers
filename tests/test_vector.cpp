/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 01:13:53 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/15 02:08:11 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

/*
void vector_create()
{
	std::cout << C_B_RED << "vector_create" << C_OFF << std::endl;
	// constructors used in the same order as described above:
	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int> third (second.begin(),second.end());  // iterating through second
	ft::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}
*/
void vector_copy()
{
	std::cout << C_RED << "vector_copy" << C_OFF << std::endl;
	ft::vector<int> first;
	ft::vector<int> second;

	second.push_back(100);
	second.push_back(100);
	second.push_back(100);
	second.push_back(100);
	second.push_back(1);
	std::cout << "capacity first : " << first.capacity() << std::endl;
	std::cout << "capacity second : " << second.capacity() << std::endl;
	first = second;
	second.push_back(100);
	first.push_back(100);
	std::cout << "copy capacity first : " << first.capacity() << std::endl;
	std::cout << "copy capacity second : " << second.capacity() << std::endl;
}

void test_vector()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_vector" << C_OFF << std::endl;
//	vector_create();
	vector_copy();
	std::cout << C_OFF << std::endl;
}
