/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:16:41 by nali              #+#    #+#             */
/*   Updated: 2023/01/24 23:06:03 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterators.hpp"

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
            reverse_iterator():current(NULL){}
            explicit reverse_iterator (iterator_type it):current(it){}
            reverse_iterator (const reverse_iterator<Iter>& rev_it):current(rev_it.current){}
        
        
    };
}

#endif