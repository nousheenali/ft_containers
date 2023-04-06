/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:31:54 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 13:26:31 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
// #include <vector>
// #include <list>

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            /* -- Member Types -- */
            typedef Container                                container_type;
            typedef typename container_type::value_type      value_type;
            typedef typename container_type::reference       reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type       size_type;

        protected:
            container_type c; //member object

        public:
            /* -- member functions -- */
            //Default constructor - creates a container adaptor with underlying container obj.
            // This container object is a copy of the 'cntr' argument passed to the constructor
            explicit stack (const container_type& cntr = container_type()):c(cntr){}
            
            /*destructor*/
            ~stack(){}
            
            /*copy constructor*/
            stack(const stack& q) 
            {
                this->c = q.c;
            }
            
            /*copy assignment*/
            stack& operator=(const stack& q)
            {
                this->c = q.c;
                return(*this);
            }
            
            /* -- Element Access -- */
            T& top()
            {
                return (this->c.back());
            }
            
            /* -- Capacity --*/
            bool empty() const
            {
                return (this->c.empty());
            }
            size_type size() const
            {
                return(this->c.size());
            }
            /* -- Modifiers -- */
            void push(const T& x)
            {
                this->c.push_back(x);
            }
            void pop()
            {
                return (this->c.pop_back());
            }
            /*relational*/
            /*these have been made as friend functions so that they can access the protected memeber c*/
            friend  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return(lhs.c == rhs.c);
            }
            friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return(lhs.c < rhs.c);
            }
    }; 
    /*non member functions*/
    template <class T, class Container>  
    bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
    {
        return!(lhs == rhs);
    }
    template <class T, class Container>  
    bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
    {
        return!(rhs < lhs);
    }
    template <class T, class Container>  
    bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
    {
        return(rhs < lhs);
    }
    template <class T, class Container>  
    bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
    {
        return!(lhs < rhs);
    } 
}
#endif