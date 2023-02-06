/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:46:03 by nali              #+#    #+#             */
/*   Updated: 2023/02/05 15:36:20 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP


#include <memory> //for ptrdiff_t - for pointer arithmetic
namespace ft
{
    /* iterator_tags Iterator Tags
     *  These are empty types, used to distinguish different iterators.  The
     *  distinction is not made by what they contain, but simply by what they
     *  are.  Different underlying algorithms can then be used based on the
     *  different operations supported by different iterator types. */
       
    struct input_iterator_tag { }; //  Marking input iterators.
    struct output_iterator_tag { }; //  Marking output iterators.
    struct forward_iterator_tag : public input_iterator_tag { }; /// Forward iterators support a superset of input iterator operations.
    struct bidirectional_iterator_tag : public forward_iterator_tag { }; /// Bidirectional iterators support a superset of forward iterator operations.
    struct random_access_iterator_tag : public bidirectional_iterator_tag { }; /// Random-access iterators support a superset of bidirectional iterator operations.

    /** This class does nothing but define nested typedefs.  %Iterator classes
        can inherit from this class to save some work.  The typedefs are then
        used in specializations and overloading.*/
        
    template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t, 
              typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
        typedef _Category  iterator_category;
        typedef _Tp        value_type; // The type "pointed to" by the iterator.
        typedef _Distance  difference_type; //Distance between iterators is represented as this type.
        typedef _Pointer   pointer; // This type represents a pointer-to-value_type.
        typedef _Reference reference; // This type represents a reference-to-value_type. 
    }; 

     /** Traits class for iterators.
      * This class does nothing but define nested typedefs.  The general
      * version simply @a forwards the nested typedefs from the Iterator
      * argument.  Specialized versions for pointers and pointers-to-const
      *  provide tighter, more correct semantics. */
     
    template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type        value_type;
      typedef typename _Iterator::difference_type   difference_type;
      typedef typename _Iterator::pointer           pointer;
      typedef typename _Iterator::reference         reference;
    };

    /// Partial specialization for pointer types.
    
    template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef _Tp*                        pointer;
      typedef _Tp&                        reference;
    };

    /// Partial specialization for const pointer types.
    
    template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };
        
}

#endif


/* Good read on iterators
https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp

why we have 'iterator_traits' when we can directly use 'iterator' struct ?

To allow all iterators to have a uniform interface. More specifically, 
pointers are iterators too and as non-class types, pointers cannot have members.
So, when for example the user of an iterator wants the answer to 
the question "What is the type of the object pointed by an_iterator_type", 
they cannot use an_iterator_type::value_type because that cannot be defined 
for all iterators - specifically pointers. What they can use is 
std::iterator_traits<an_iterator_type>::value_type which can be defined for 
all iterators - including pointers. That is the purpose of std::iterator_traits.

https://stackoverflow.com/questions/71737631/what-is-the-design-purpose-of-iterator-traits
https://stackoverflow.com/questions/6742008/what-are-the-typical-use-cases-of-an-iterator-trait

*/