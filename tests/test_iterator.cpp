/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:17:25 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/01 18:07:42 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

class MyIterator : public ft::iterator<std::input_iterator_tag, int>
{
	int* p;
	public:
		MyIterator(int* x) :p(x) {}
		MyIterator(const MyIterator& mit) : p(mit.p) {}
		MyIterator& operator++() {++p;return *this;}
		MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
		bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
		bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
		int& operator*() {return *p;}
};

void test_iterator()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_iterator" << C_OFF << std::endl;
	int numbers[]={10,20,30,40,50};
	MyIterator from(numbers);
	MyIterator until(numbers+5);
	for (MyIterator it=from; it!=until; it++)
		std::cout << *it << ' ';
	std::cout << '\n';
	std::cout << std::endl;
}
