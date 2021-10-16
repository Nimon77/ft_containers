/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 00:05:16 by nsimon            #+#    #+#             */
/*   Updated: 2021/10/11 09:22:22 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_constructor()
{
	std::cout << C_RED << "test_consstructor" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;
	iter_type from (myvector.begin());
	iter_type until (myvector.end());
	ft::reverse_iterator<iter_type> rev_until (from);
	ft::reverse_iterator<iter_type> rev_from (until);

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';
	std::cout << std::endl;
}

void test_base()
{
	std::cout << C_RED << "test_base" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_end (myvector.begin());
	ft::reverse_iterator<iter_type> rev_begin (myvector.end());

	std::cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << std::endl;
}

void test_operator_mult()
{
	std::cout << C_RED << "test_operator_mult" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;
	iter_type from (myvector.begin());
	iter_type until (myvector.end());
	ft::reverse_iterator<iter_type> rev_until (from);
	ft::reverse_iterator<iter_type> rev_from (until);

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';
	std::cout << std::endl;
}

void test_operator_plus()
{
	std::cout << C_RED << "test_operator_plus" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_it;

	rev_it = myvector.rbegin() +3;

	std::cout << "The fourth element from the end is: " << *rev_it << '\n';
	std::cout << std::endl;
}

void test_operator_plusplus()
{
	std::cout << C_RED << "test_operator_plusplus" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;
	iter_type from (myvector.begin());
	iter_type until (myvector.end());
	ft::reverse_iterator<iter_type> rev_until (from);
	ft::reverse_iterator<iter_type> rev_from (until);

	std::cout << "myvector:";
	while (rev_from != rev_until) {
		std::cout << ' ' << *rev_from;
		++rev_from;
	}
	std::cout << '\n';
	std::cout << std::endl;
}

void test_operator_plusequal()
{
	std::cout << C_RED << "test_operator_plusequal" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	rev_iterator += 2;

	std::cout << "The third element from the end is: " << *rev_iterator << '\n';
	std::cout << std::endl;
}

void test_operator_minus()
{
	std::cout << C_RED << "test_operator_minus" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator;

	rev_iterator = myvector.rend() - 3;

	std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';
}

void test_operator_minusminus()
{
	std::cout << C_RED << "test_operator_minusminus" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_begin (myvector.end());
	ft::reverse_iterator<iter_type> rev_end (myvector.begin());

	ft::reverse_iterator<iter_type> rev_iterator = rev_begin;
	while ( rev_iterator != rev_end )
		std::cout << *rev_iterator++ << ' ';
	std::cout << '\n';

	while ( rev_iterator != rev_begin )
		std::cout << *(--rev_iterator) << ' ';
	std::cout << '\n';
	std::cout << std::endl;
}

void test_operator_minusequal()
{
	std::cout << C_RED << "test_operator_minusequal" << C_RESET << std::endl;
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rend();

	rev_iterator -= 4;

	std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';
	std::cout << std::endl;
}

/*
void test_operator_pointer()
{
	ft::map<int,std::string> numbers;
	numbers.insert (std::make_pair(1,"one"));
	numbers.insert (std::make_pair(2,"two"));
	numbers.insert (std::make_pair(3,"three"));

	typedef ft::map<int,std::string>::iterator map_iter;

	ft::reverse_iterator<map_iter> rev_end (numbers.begin());

	ft::reverse_iterator<map_iter> rev_iterator (numbers.end());

	for ( ; rev_iterator != rev_end ; ++rev_iterator )
		std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';

}
*/



void test_operator_chevron()
{
	std::cout << C_RED << "test_operator_chevron" << C_RESET << std::endl;
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
	std::cout << std::endl;
}

void test_reverse_iterator()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_reverse_iterator" << C_RESET << std::endl;
	test_constructor();
	test_base();
	test_operator_mult();
	test_operator_plus();
	test_operator_plusplus();
	test_operator_plusequal();
	test_operator_minus();
	test_operator_minusminus();
	test_operator_minusequal();
	//test_operator_pointer()
	test_operator_chevron();
	std::cout << std::endl;
}
