/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:16:41 by nali              #+#    #+#             */
/*   Updated: 2023/04/05 13:17:28 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterators.hpp"

/*  Reverse iterators are implemented using an underlying iterator
    Current refers to underlying iterator*/
namespace ft
{
    template<class _Iterator>
    class reverse_iterator
    {
        protected:
            _Iterator current;
            typedef iterator_traits<_Iterator>		    traits_type;
            
        public:
            typedef _Iterator					            iterator_type;
            typedef typename traits_type::iterator_category iterator_category;
            typedef typename traits_type::value_type        value_type;
            typedef typename traits_type::pointer		    pointer;
            typedef typename traits_type::difference_type	difference_type;
            typedef typename traits_type::reference		    reference;
        
        public:
            /*constructors*/
            reverse_iterator():current(NULL){}
            explicit reverse_iterator (iterator_type it):current(it){}
            reverse_iterator (const reverse_iterator<_Iterator>& rev_it):current(rev_it.current){}
            
            /*copy assignment*/
            reverse_iterator& operator=(const reverse_iterator& rev_it)
            {
                this->current = rev_it.current;
                return (*this);
            }

            template<typename It>
            reverse_iterator(const reverse_iterator<It> & x): current(x.base()) { }

            /*destructor*/
            ~reverse_iterator() {}
            
            /* returns the %iterator used for underlying work.*/
            iterator_type base() const
            { return current; }
            
            reference operator*() const
            {
                _Iterator tmp = current;
                return *--tmp;
            }
            
            pointer operator->() const
            {
                return &(operator*());
            }
            
            reverse_iterator& operator++()
            {
                --current;
                return *this;
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                --current;
                return tmp;
            }

            reverse_iterator& operator--()
            {
                ++current;
                return *this;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                ++current;
                return tmp;
            }

            reverse_iterator operator+(difference_type n) const
            { return reverse_iterator(current - n); }

            reverse_iterator& operator+=(difference_type n)
            {
                current -= n;
                return *this;
            }
            
            reverse_iterator operator-(difference_type n) const
            { return reverse_iterator(current + n); }
      
            reverse_iterator& operator-=(difference_type n)
            {
	            current += n;
	            return *this;
            }

            reference operator[](difference_type n) const
            { return *(*this + n); }
        
    };
    
    template<typename _It>
    bool operator==(const reverse_iterator<_It>& x, const reverse_iterator<_It>& y)
    { return x.base() == y.base(); }

    template<typename _It>
    bool operator<(const reverse_iterator<_It>& x, const reverse_iterator<_It>& y)
    { return y.base() < x.base(); }
    
    template<typename _It>
    bool operator!=(const reverse_iterator<_It>& x, const reverse_iterator<_It>& y)
    { return !(x == y); }

    template<typename _It>
    bool operator>(const reverse_iterator<_It>& x, const reverse_iterator<_It>& y)
    { return y < x; }

    template<typename _It>
    bool operator<=(const reverse_iterator<_It>& x, const reverse_iterator<_It>& y)
    { return !(y < x); }

    template<typename _It>
    bool operator>=(const reverse_iterator<_It>& x, const reverse_iterator<_It>& y)
    { return !(x < y); }

    template<typename _IL, typename _IR>
    bool operator==(const reverse_iterator<_IL>& x, const reverse_iterator<_IR>& y)
    { return x.base() == y.base(); }

    template<typename _IL, typename _IR>
    bool operator<(const reverse_iterator<_IL>& x, const reverse_iterator<_IR>& y)
    { return x.base() > y.base(); }

    template<typename _IL, typename _IR>
    bool operator!=(const reverse_iterator<_IL>& x,const reverse_iterator<_IR>& y)
    { return x.base() != y.base(); }

    template<typename _IL, typename _IR>
    bool operator>(const reverse_iterator<_IL>& x, const reverse_iterator<_IR>& y)
    { return x.base() < y.base(); }

    template<typename _IL, typename _IR>
    bool operator<=(const reverse_iterator<_IL>& x, const reverse_iterator<_IR>& y)
    { return x.base() >= y.base(); }

    template<typename _IL, typename _IR>
    bool operator>=(const reverse_iterator<_IL>& x, const reverse_iterator<_IR>& y)
    { return x.base() <= y.base(); }

    template<typename _IL, typename _IR>
    typename reverse_iterator<_IL>::difference_type 
    operator-(const reverse_iterator<_IL>& x, const reverse_iterator<_IR>& y)
    { return y.base() - x.base(); }

    template<typename _It>
    reverse_iterator<_It> operator+(typename reverse_iterator<_It>::difference_type n,const reverse_iterator<_It>& x)
    { return reverse_iterator<_It>(x.base() - n); }
}

#endif

/*
    DEREFERENCING in reverse iterator
    https://devblogs.microsoft.com/oldnewthing/20211112-00/?p=105908
*/