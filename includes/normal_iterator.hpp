/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:53:39 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 12:47:48 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include "iterators.hpp"
#include <memory> //for ptrdiff_t - for pointer arithmetic

namespace ft{
    template<typename T>
    class normal_iterator 
    {
        protected:
            T* current;
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>    traits_type;
            // To be a valid iterator you need to define these 5 types:
            // These two you can inherit from base_iterator
            typedef typename traits_type::iterator_category     iterator_category;
            typedef typename traits_type::difference_type       difference_type;
            // These three you have changed from the base_iterator so must provide your own definition.
            typedef T								            value_type;
            typedef T&								            reference;
            typedef T*								            pointer;
            
        public:
            //constructors
            normal_iterator():current(NULL){}
            normal_iterator(T* current):current(current){}
            // Allow iterator to const_iterator conversion
            template <typename It>
		    normal_iterator(const normal_iterator<It> &value) : current(value.base()) {}

            normal_iterator (const normal_iterator& x) //copy constrctor
            {
                current = x.current;
            }
            
            normal_iterator &operator=(const normal_iterator& x) //copy assignment
            {
                if  (this != &x)
				    current = x.current;
			    return *this;
		    }
            
            ~normal_iterator(){} //destructor
            
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
            
            normal_iterator &operator++() // pre-increment, return *this by reference
            {
			    ++(current);
			    return *this;
		    }
            
		    normal_iterator operator++(int) //post-increment, return unmodified copy by value
            {
                return normal_iterator(current++);
		    }
            
            normal_iterator &operator--() //pre decrement
            {
                --(current);
                return *this;
		    }
            
		    normal_iterator operator--(int) //post decrement
            {
                return normal_iterator(current--);
		    }
            
            reference operator[](difference_type n) const
            {   
                return current[n]; 
            }
            
            normal_iterator &operator+=(difference_type n)
            {
                current += n;
                return *this;
            }
            
            normal_iterator operator+(difference_type n) const 
            { 
                return normal_iterator(current + n); 
            }
            
            normal_iterator &operator-=(difference_type n)
            {
                current -= n; 
                return *this; 
            }
            
            normal_iterator operator-(difference_type n) const 
            {
                return normal_iterator(current - n); 
            }
    };
    
    template<typename I>
    bool operator==(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() == rhs.base(); }

    template<typename I>
    bool operator!=(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() != rhs.base(); }

    template<typename I>
    bool operator<(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() < rhs.base(); }

    template<typename I>
    bool operator>(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() > rhs.base(); }

    template<typename I>
    bool operator<=(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() <= rhs.base(); }

    template<typename I>
    bool operator>=(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() >= rhs.base(); }

    template<typename I>
    typename normal_iterator<I>::difference_type
    operator-(const normal_iterator<I>& lhs, const normal_iterator<I>& rhs)
    { return lhs.base() - rhs.base(); }

    template<typename I>
    normal_iterator<I>
    operator+(typename normal_iterator<I>::difference_type n, const normal_iterator<I>& i)
    { return normal_iterator<I>(i.base() + n); }

    //to compare different types of iterators such as const_iterator and iterator
    
    template<typename IL, typename IR>
    bool operator==(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() == rhs.base(); }

    template<typename IL, typename IR>
    bool operator!=(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() != rhs.base(); }
    
    template<typename IL, typename IR>
    bool operator<(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() < rhs.base(); }
    
    template<typename IL, typename IR>
    bool operator>(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() > rhs.base(); }
    
    template<typename IL, typename IR>
    bool operator<=(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() <= rhs.base(); }
    
    template<typename IL, typename IR>
    bool operator>=(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() >= rhs.base(); }

    template<typename IL, typename IR>
    typename normal_iterator<IL>::difference_type
    operator-(const normal_iterator<IL>& lhs, const normal_iterator<IR>& rhs)
    { return lhs.base() - rhs.base(); }

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