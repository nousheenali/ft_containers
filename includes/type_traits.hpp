/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:28:42 by nali              #+#    #+#             */
/*   Updated: 2023/01/27 16:35:17 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
    
    // Primary template.
     /// Define a member typedef `type` only if a boolean constant is true.
    template<bool, typename _Tp = void>
    struct enable_if
    { };

     // Partial specialization for true.
    template<typename _Tp>
    struct enable_if<true, _Tp>
    { typedef _Tp type; };    

    template<typename>
    struct is_integral_helper {static const bool value = false;};

    template<>
    struct is_integral_helper<bool> {static const bool value = true;};

    template<>
    struct is_integral_helper<char> {static const bool value = true;};

    template<>
    struct is_integral_helper<signed char> {static const bool value = true;};

    template<>
    struct is_integral_helper<unsigned char> {static const bool value = true;};

    template<>
    struct is_integral_helper<wchar_t> {static const bool value = true;};

    template<>
    struct is_integral_helper<char16_t> {static const bool value = true;};

    template<>
    struct is_integral_helper<char32_t> {static const bool value = true;};

    template<>
    struct is_integral_helper<short> {static const bool value = true;};

    template<>
    struct is_integral_helper<unsigned short> {static const bool value = true;};

    template<>
    struct is_integral_helper<int> {static const bool value = true;};

    template<>
    struct is_integral_helper<unsigned int> {static const bool value = true;};

    template<>
    struct is_integral_helper<long> {static const bool value = true;};

    template<>
    struct is_integral_helper<unsigned long> {static const bool value = true;};

    template<>
    struct is_integral_helper<long long> {static const bool value = true;};

    template<>
    struct is_integral_helper<unsigned long long> {static const bool value = true;};
    
    
    template<typename T>
    struct is_integral: public is_integral_helper<T>{};
}

#endif