/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_utils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:44:10 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 11:54:02 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_UTILS_HPP
#define COMPARE_UTILS_HPP


namespace ft
{
    template <class InputIterator1, class InputIterator2>  
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1!=last1) 
        {
            if (!(*first1 == *first2)) 
                return false;
            ++first1; ++first2;
        }
        return true;
    }
	
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>  
    bool equal (InputIterator1 first1, InputIterator1 last1, 
    InputIterator2 first2, BinaryPredicate pred)
    {
		while (first1 != last1) 
        {
			if (!pred(*first1, *first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}

    template <class InputIterator1, class InputIterator2>  
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, 
    InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) 
                return false;
            else if (*first1<*first2) 
                return true;
            ++first1; ++first2;
        }
        return (first2!=last2);//If both sequences compare equal until one of them ends, the shorter 
        // sequence is lexicographically less than the longer one.
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, 
    InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) 
                return false;
            else if (comp(*first1, *first2))
                return true;
            ++first1; ++first2;
        }
        return (first2!=last2); 
    }
    
    template<typename T>
    const T& max(const T& a, const T& b)
    {
        if (a < b)
            return b;
        return a;
    }

}

/*  A lexicographical comparison is the kind of comparison generally used
    to sort words alphabetically in dictionaries; It involves comparing 
    sequentially the elements that have the same position in both ranges 
    against each other until one element is not equivalent to the other. 
    The result of comparing these first non-matching elements is the result
    of the lexicographical comparison.

    If both sequences compare equal until one of them ends, the shorter 
    sequence is lexicographically less than the longer one.

*/

#endif