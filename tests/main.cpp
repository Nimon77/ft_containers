/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:46:51 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/09 11:03:50 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void	test_is_integral()
{
	std::cout << std::boolalpha;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "const int: " << ft::is_integral<const int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
}

bool mypredicate (int i, int j)
{
	return (i == j);
}

void	test_equal()
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3] = 81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( ft::equal(myvector.begin(), myvector.end(), myints, mypredicate))
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";
}

bool mycomp (char c1, char c2)
{ return std::tolower(c1) < std::tolower(c2); }

void test_lexicographical_compare () {
	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';
}

void test_distance()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_distance" << C_RESET << std::endl;
	std::list<int> mylist;
	for (int i=0; i<10; i++) mylist.push_back (i*10);

	std::list<int>::iterator first = mylist.begin();
	std::list<int>::iterator last = mylist.end();

	std::cout << "The distance is: " << ft::distance(first,last) << '\n';
	std::cout << std::endl;
}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

int		main(void)
{
	//ft::BST<ft::pair<int, int> > tree;
//	ft::map<int, int, ft::less<ft::pair<int, int> > > map;
//	map.insert(ft::pair<int, int>(1, 1));
//	map.insert(ft::pair<int, int>(8, 8));
//	map.insert(ft::pair<int, int>(4, 4));
//	map.insert(ft::pair<int, int>(9, 9));

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	fifth.insert(ft::pair<char, int>('a', 10));
	fifth.insert(ft::pair<char, int>('b', 30));
	fifth.insert(ft::pair<char, int>('c', 50));
	fifth.insert(ft::pair<char, int>('e', 70));
	fifth.insert(ft::pair<char, int>('D', 60));
		for (ft::map<char,int,bool(*)(char,char)>::reverse_iterator it = fifth.rbegin(); it != fifth.rend(); it++)
		std::cout << it->first << " => " << it->second << std::endl;
	//first.print();
	//fourth.print();
	//fifth.print();
	//std::cout << C_WHITE_BACK << C_B_RED << "is_integral:" << C_RESET << std::endl;
	//test_is_integral();
	//std::cout << std::endl;
	//std::cout << C_WHITE_BACK << C_B_RED << "equal:" << C_RESET << std::endl;
	//test_equal();
	//std::cout << std::endl;
	//std::cout << C_WHITE_BACK << C_B_RED << "lexicographical_compare:" << C_RESET << std::endl;
	//test_lexicographical_compare();
	//std::cout << std::endl;
	//test_utility();
	//test_reverse_iterator();
	//test_iterator();
	//test_distance();
	//test_vector();

	return (0);
}
