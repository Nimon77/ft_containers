/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:24:49 by nsimon            #+#    #+#             */
/*   Updated: 2021/09/02 17:15:14 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {

	/*
	** enable_if
	*/
	template < bool Cond, class T = void > struct enable_if {};
	template < class T > struct enable_if<true, T> { typedef T type; };

	/*
	** integral_constant
	*/
	template < class T, T v >
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	/*
	** is_integral
	*/
	template <typename> struct is_integral_type :						false_type {};
	
	template <> struct is_integral_type<bool> :							true_type {};
	template <> struct is_integral_type<char> :							true_type {};
	template <> struct is_integral_type<char16_t> :						true_type {};
	template <> struct is_integral_type<char32_t> :						true_type {};
	template <> struct is_integral_type<wchar_t> :						true_type {};
	template <> struct is_integral_type<signed char> :					true_type {};
	template <> struct is_integral_type<short int> :					true_type {};
	template <> struct is_integral_type<int> :							true_type {};
	template <> struct is_integral_type<long long int> :				true_type {};
	template <> struct is_integral_type<unsigned char> :				true_type {};
	template <> struct is_integral_type<unsigned short int> :			true_type {};
	template <> struct is_integral_type<unsigned int> :					true_type {};
	template <> struct is_integral_type<unsigned long int> :			true_type {};
	template <> struct is_integral_type<unsigned long long int> :		true_type {};

	template <> struct is_integral_type<const bool> :					true_type {};
	template <> struct is_integral_type<const char> :					true_type {};
	template <> struct is_integral_type<const char16_t> :				true_type {};
	template <> struct is_integral_type<const char32_t> :				true_type {};
	template <> struct is_integral_type<const wchar_t> :				true_type {};
	template <> struct is_integral_type<const signed char> :			true_type {};
	template <> struct is_integral_type<const short int> :				true_type {};
	template <> struct is_integral_type<const int> :					true_type {};
	template <> struct is_integral_type<const long long int> :			true_type {};
	template <> struct is_integral_type<const unsigned char> :			true_type {};
	template <> struct is_integral_type<const unsigned short int> :		true_type {};
	template <> struct is_integral_type<const unsigned int> :			true_type {};
	template <> struct is_integral_type<const unsigned long int> :		true_type {};
	template <> struct is_integral_type<const unsigned long long int> :	true_type {};

	template < class T > struct is_integral : is_integral_type<T> {};


}

#endif
