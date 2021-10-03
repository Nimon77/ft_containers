/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utility.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:14:24 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/03 16:28:37 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_make_pair()
{
	std::cout << C_B_RED << "test_make_pair" << C_RESET << std::endl;
	ft::pair <int,int> foo;
	ft::pair <int,int> bar;

	foo = ft::make_pair (10,20);
	bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
}

struct Compare : public ft::binary_function<int,int,bool> {
	bool operator() (int a, int b) {return (a==b);}
};

void test_binary_function(Compare::first_argument_type input1 = 12, Compare::second_argument_type input2 = 12)
{
	Compare Compare_object;
	Compare::result_type result;

	result = Compare_object (input1,input2);

	std::cout << "Numbers " << input1 << " and " << input2;
	if (result)
		std::cout << " are equal.\n";
	else
		std::cout << " are not equal.\n";
}

void test_less()
{
	std::cout << C_RED << "test_less" << C_RESET << std::endl;
	int foo[]={10,20,5,15,25};
	int bar[]={15,10,20};
	std::sort (foo, foo+5, std::less<int>());  // 5 10 15 20 25
	std::sort (bar, bar+3, std::less<int>());  //   10 15 20
	if (std::includes (foo, foo+5, bar, bar+3, ft::less<int>()))
		std::cout << "foo includes bar.\n";
}

void test_utility()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_utility" << C_RESET << std::endl;
	test_make_pair();
	std::cout << C_RED << "test_binary_function" << C_RESET << std::endl;
	test_binary_function();
	test_binary_function(1, 99);
	test_binary_function(800, 10000);
	test_less();
	std::cout << std::endl;
}
