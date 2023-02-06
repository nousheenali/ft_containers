/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:21:29 by nali              #+#    #+#             */
/*   Updated: 2023/02/06 21:56:18 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../includes/pair.hpp"
#include <functional> //to access std::less

namespace ft
{
    template< class Key, class T, 
              class Compare = std::less<Key>,
              class Allocator = std::allocator<ft::pair<const Key, T>>> 
            class map
            {
                public:
                    typedef Key					        key_type;
                    typedef T					        mapped_type;
                    typedef ft::pair<const Key, T>		value_type;
                    typedef Compare					    key_compare;
                    typedef Alloc					    allocator_type;
            };   
}
#endif