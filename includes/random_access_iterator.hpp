/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:53:39 by nali              #+#    #+#             */
/*   Updated: 2023/01/24 22:58:35 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterators.hpp"
#include <memory> //for ptrdiff_t - for pointer arithmetic

namespace ft{
    template<typename T>
    class random_access_iterator :public ft::iterator<ft::random_access_iterator_tag, T>
    {
        protected:
            T* current;
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>    traits_type;
            // To be a valid iterator you need to define these 5 types:
            // These two you can inherit from base_iterator
            typedef typename traits_type::iterator_category  iterator_category;
            typedef typename traits_type::difference_type    difference_type;
            // These three you have changed from the base_iterato so must provide your own definition.
            typedef T								value_type;
            typedef T&								reference;
            typedef T*								pointer;
            
        public:
            //constructors
            random_access_iterator():current(NULL){}
            random_access_iterator(T* current):current(current){}
            random_access_iterator (const random_access_iterator& x) //copy constrctor
            {
                current = x.current;
            }
            random_access_iterator &operator=(const random_access_iterator& x) //copy assignment
            {
				current = x.current;
			    return *this;
		    }
            ~random_access_iterator(){} //destructor
            
            /*properties*/
            pointer base() const
            { 
                return (current); 
            }
            reference operator*()
            {
                return *(current);
            }
            pointer operator->() const
            { 
                return (current);
            }
            random_access_iterator &operator++() // pre-increment, return *this by reference
            {
			    ++(current);
			    return *this;
		    }
		    random_access_iterator operator++(int) //post-increment, return unmodified copy by value
            {
                return random_access_iterator(current++);
		    }
             random_access_iterator &operator--() //pre decrement
            {
                --(current);
                return *this;
		    }
		    random_access_iterator operator--(int) //post decrement
            {
                return random_access_iterator(current--);
		    }
            reference operator[](difference_type n) const
            {   
                return current[n]; 
            }
            random_access_iterator &operator+=(difference_type n)
            {
                return (current + n);
            }
            random_access_iterator operator+(difference_type n) const 
            { 
                return random_access_iterator(current + n); 
            }
            random_access_iterator &operator-=(difference_type n)
            {
                current -= n; 
                return *this; 
            }
            random_access_iterator operator-(difference_type n) const 
            {
                return random_access_iterator(current - n); 
            }
    };
    
    template<typename IL, typename IR>
    bool operator==(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() == rhs.base(); }

    template<typename I>
    bool operator==(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() == rhs.base(); }

    template<typename IL, typename IR>
    bool operator!=(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() != rhs.base(); }

    template<typename I>
    bool operator!=(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() != rhs.base(); }

    template<typename IL, typename IR>
    bool operator<(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() < rhs.base(); }

    template<typename I>
    bool operator<(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() < rhs.base(); }

    template<typename IL, typename IR>
    bool operator>(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() > rhs.base(); }

    template<typename I>
    bool operator>(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() > rhs.base(); }

    template<typename IL, typename IR>
    bool operator<=(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() <= rhs.base(); }

    template<typename I>
    bool operator<=(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() <= rhs.base(); }

    template<typename IL, typename IR>
    bool operator>=(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() >= rhs.base(); }

    template<typename I>
    bool operator>=(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() >= rhs.base(); }

    template<typename IL, typename IR>
    typename random_access_iterator<IL>::difference_type
    operator-(const random_access_iterator<IL>& lhs, const random_access_iterator<IR>& rhs)
    { return lhs.base() - rhs.base(); }

    template<typename I>
    typename random_access_iterator<I>::difference_type
    operator-(const random_access_iterator<I>& lhs, const random_access_iterator<I>& rhs)
    { return lhs.base() - rhs.base(); }

    template<typename I>
    random_access_iterator<I>
    operator+(typename random_access_iterator<I>::difference_type n, const random_access_iterator<I>& i)
    { return random_access_iterator<I>(i.base() + n); }
}

#endif


/* REFERENCES
    concept of container/iterator/algorithm
    https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits

    Iterator base class
    // https://cplusplus.com/reference/iterator/iterator/
    
    implementing custom iterator
    https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators
    https://codereview.stackexchange.com/questions/198035/implementing-a-custom-iterator-by-inheriting-from-an-existing-iterator-class-and

    why use typename?
    https://stackoverflow.com/questions/1600936/officially-what-is-typename-for
    https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
*/ 