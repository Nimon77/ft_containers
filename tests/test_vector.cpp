/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 01:13:53 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/17 10:36:24 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void vector_create()
{
	std::cout << C_RED << "vector_create" << C_OFF << std::endl;
	// constructors used in the same order as described above:
	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int>::iterator begin(second.begin());
	for (; begin != second.end(); begin++) std::cout << *begin << std::endl;
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

void vector_size()
{
	std::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
}

void vector_resize()
{
	std::cout << C_RED << "vector_resize" << C_OFF << std::endl;
	ft::vector<int> myvector;

	// set some initial content:
	for (int i = 1; i < 10; i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (unsigned long i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void vector_reserve()
{
	std::cout << C_RED << "vector_reserve" << C_OFF << std::endl;
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);	 // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void vector_shrink_to_fit()
{
	std::cout << C_RED << "vector_shrink_to_fit" << C_OFF << std::endl;
	ft::vector<int> myvector (100);
	std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';

	myvector.resize(10);
	std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';

	myvector.shrink_to_fit();
	std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';
}

void vector_operator_access()
{
	std::cout << C_RED << "vector_operator_access" << C_OFF << std::endl;
	ft::vector<int> myvector (10); // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void vector_at()
{
	std::cout << C_RED << "vector_at" << C_OFF << std::endl;
	ft::vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}

void vector_front()
{
	std::cout << C_RED << "vector_front" << C_OFF << std::endl;
	ft::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

  // now front equals 78, and back 16

	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void vector_back()
{
	std::cout << C_RED << "vector_back" << C_OFF << std::endl;
	std::vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back ( myvector.back() -1 );
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size() ; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void vector_element_access()
{
	std::cout << C_B_RED << "vector_element_access" << C_OFF << std::endl;
	vector_operator_access();
	vector_at();
	vector_front();
	vector_back();
}

void test_vector()
{
	std::cout << C_WHITE_BACK << C_B_RED << "test_vector" << C_OFF << std::endl;
	vector_create();
	vector_copy();
	vector_size();
	vector_resize();
	vector_reserve();
	vector_shrink_to_fit();
	vector_element_access();
	std::cout << C_OFF << std::endl;
}
