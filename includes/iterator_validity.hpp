/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_validity.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:58:59 by nali              #+#    #+#             */
/*   Updated: 2023/03/30 23:35:05 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_VALIDITY_HPP
#define ITERATOR_VALIDITY_HPP

#include "iterators.hpp"

namespace ft
{

    template <class It>
    void iterator_validity(It first, It last, typename ft::input_iterator_tag) 
    {
        (void)first;
        (void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename ft::output_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename ft::forward_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename ft::bidirectional_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename ft::random_access_iterator_tag) {
    	if (first > last) {
    		throw std::length_error("Iterator exceeds the size");
    	}
    }

    //std iterator categories have been included to accomodate the tester
    //condition where it uses std iterators of list to fill in vector
    template <class It>
    void iterator_validity(It first, It last, typename std::input_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename std::output_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename std::forward_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename std::bidirectional_iterator_tag) {
    	(void)first;
    	(void)last;
    }

    template <class It>
    void iterator_validity(It first, It last, typename std::random_access_iterator_tag) 
    {
        if (first > last) 
            throw std::length_error("iterator exceeds size");
    }

    template <class It>
    void check_range(It first, It last) 
    {
        iterator_validity(first, last, typename ft::iterator_traits<It>::iterator_category());
    }

}

#endif  