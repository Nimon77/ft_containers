/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:51:01 by nsimon            #+#    #+#             */
/*   Updated: 2021/11/05 17:59:01 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

void map_iterator()
{
	std::cout << C_B_RED << "map iterator" << C_RESET << std::endl;
	ft::map<char,int> first;

	first.insert(ft::pair<char, int>('A', 1));
	first.insert(ft::pair<char, int>('a', 10));
	first.insert(ft::pair<char, int>('b', 30));
	first.insert(ft::pair<char, int>('c', 50));
	first.insert(ft::pair<char, int>('e', 70));
	first.insert(ft::pair<char, int>('D', 60));
	first.insert(ft::pair<char, int>('B', 60));

	ft::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	for (ft::map<char,int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << it->first << " => " << it->second << std::endl;
}

void test_map()
{
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << C_WHITE_BACK << C_B_RED << "TEST MAP" << C_RESET << std::endl;
	map_iterator();
	std::cout << "-------------------------------------------------------" << std::endl;
}
